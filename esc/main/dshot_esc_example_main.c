/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt_tx.h"
#include "driver/gpio.h"
#include "dshot_esc_encoder.h"

#define DSHOT_ESC_RESOLUTION_HZ 40000000 // 40MHz resolution, DSHot protocol needs a relative high resolution

#define NUM_CHANNELS			4

#define BLINK_GPIO    40
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<GPIO_OUTPUT_IO_0)

static const char *TAG = "example";

void app_main(void)
{
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    rmt_channel_handle_t esc_channels[NUM_CHANNELS] = {NULL};
    int gpio_nums[NUM_CHANNELS] = {1, 2, 42, 41};
    rmt_tx_channel_config_t tx_chan_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // select a clock that can provide needed resolution
        .mem_block_symbols = 48,
        .resolution_hz = DSHOT_ESC_RESOLUTION_HZ,
        .trans_queue_depth = 5, // set the number of transactions that can be pending in the background
    };

    for (int i = 0 ; i < NUM_CHANNELS; ++i)
    {
    	tx_chan_config.gpio_num = gpio_nums[i];
    	ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &esc_channels[i]));
    }


    ESP_LOGI(TAG, "Install Dshot ESC encoder");
    rmt_encoder_handle_t dshot_encoders[NUM_CHANNELS] = {NULL};
    dshot_esc_encoder_config_t encoder_config = {
        .resolution = DSHOT_ESC_RESOLUTION_HZ,
        .baud_rate = 300000, // DSHOT300 protocol
        .post_delay_us = 50, // extra delay between each frame
    };

    for (int i = 0 ; i < NUM_CHANNELS; ++i) {
    	ESP_ERROR_CHECK(rmt_new_dshot_esc_encoder(&encoder_config, &dshot_encoders[i]));
    }

    ESP_LOGI(TAG, "Enable RMT TX channel");
    for (int i = 0 ; i < NUM_CHANNELS; ++i) {
    	ESP_ERROR_CHECK(rmt_enable(esc_channels[i]));
    }

//    // install sync manager
//    rmt_sync_manager_handle_t synchro = NULL;
//    rmt_sync_manager_config_t synchro_config = {
//        .tx_channel_array = esc_channels,
//        .array_size = sizeof(esc_channels) / sizeof(esc_channels[0]),
//    };
//    ESP_ERROR_CHECK(rmt_new_sync_manager(&synchro_config, &synchro));


    rmt_transmit_config_t tx_config = {
        .loop_count = -1, // infinite loop
    };
    dshot_esc_throttle_t throttle = {
        .throttle = 0,
        .telemetry_req = false, // telemetry is not supported in this example
    };

    ESP_LOGI(TAG, "Start ESC by sending zero throttle for a while...");
    for (int i = 0 ; i < NUM_CHANNELS; ++i) {
    	ESP_ERROR_CHECK(rmt_transmit(esc_channels[i], dshot_encoders[i], &throttle, sizeof(throttle), &tx_config));
    }
    vTaskDelay(pdMS_TO_TICKS(5000));

    ESP_LOGI(TAG, "Increase throttle, no telemetry");
    int throttles[NUM_CHANNELS] = {100, 150, 600, 0};
    for (;;) {
        gpio_set_level(BLINK_GPIO, 1);
        for (int i = 0 ; i < NUM_CHANNELS; ++i) {
        	throttles[i] += 10;
        	if (throttles[i] > 150)
        		throttles[i] = 48;

            throttle.throttle = throttles[i];
            ESP_ERROR_CHECK(rmt_transmit(esc_channels[i], dshot_encoders[i], &throttle, sizeof(throttle), &tx_config));
            // the previous loop transfer is till undergoing, we need to stop it and restart,
            // so that the new throttle can be updated on the output
            ESP_ERROR_CHECK(rmt_disable(esc_channels[i]));
            ESP_ERROR_CHECK(rmt_enable(esc_channels[i]));
        }
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}

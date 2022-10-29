#include "DShot600.h"
#include <driver/rmt.h>
#include "esp_log.h"


#ifndef constrain
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif

/*RMT definition*/
#define DIVIDER    2 /* Diviseur du timer*/
#define DURATION  12.5 /* flash 80MHz => minimum time unit */

#define PULSE_T0H (  625 / (DURATION * DIVIDER));
#define PULSE_T1H (  1250 / (DURATION * DIVIDER));
#define PULSE_T0L (  1045 / (DURATION * DIVIDER));
#define PULSE_T1L (  420 / (DURATION * DIVIDER));

#define PULSE_T0H_RAW 625;
#define PULSE_T1H_RAW 1250;
#define PULSE_T0L_RAW 1045;
#define PULSE_T1L_RAW 420;

#define NUM_DSHOT_CHANNELS  4
#define DATA_PER_CHANNEL  16

rmt_config_t config;

class DShotDriver
{
public:
    DShotDriver() {}
    ~DShotDriver() {
    }

    void deInit() {
        rmt_driver_uninstall(RMT_CHANNEL_0);
        rmt_driver_uninstall(RMT_CHANNEL_1);
        rmt_driver_uninstall(RMT_CHANNEL_2);
        rmt_driver_uninstall(RMT_CHANNEL_3);
    }
    void attach(gpio_num_t pin, uint8_t id) {
        // rmt_config_t config =_configs[id];
        config.rmt_mode = RMT_MODE_TX;
        config.channel = (rmt_channel_t)id;
        config.gpio_num = pin;
        config.mem_block_num = 1;
        config.tx_config.loop_en = 0;
        config.tx_config.carrier_en = 0;
        config.tx_config.idle_output_en = 1;
        config.tx_config.idle_level = (rmt_idle_level_t)0;
        config.tx_config.carrier_duty_percent = 50;
        config.tx_config.carrier_freq_hz = 10000;
        config.tx_config.carrier_level = (rmt_carrier_level_t)1;
        config.clk_div = 2;

        rmt_driver_uninstall(config.channel);
        rmt_config(&config);
        rmt_driver_install(config.channel, 0, 0);

        rmt_set_tx_loop_mode(config.channel, 1);
        updateThrottle(id, 0);
    }

    void updateThrottle(uint8_t id, uint16_t value) {
        rmt_item32_t* data = createDShotFrame(id, value);
        rmt_write_items((rmt_channel_t)id, data, DATA_PER_CHANNEL, true);
        rmt_wait_tx_done((rmt_channel_t)id, 1 / portTICK_PERIOD_MS);
    }
private:
    rmt_item32_t* createDShotFrame(uint8_t id, uint16_t value) {
        value = (value << 1);
        uint8_t checksum = (value ^ (value >> 4) ^ (value >> 8)) & 0x0F;
        value = (value << 4) + (checksum & 0b1111);
        rmt_item32_t* dataArray = _data + id*DATA_PER_CHANNEL;

        for (int i = 0; i < DATA_PER_CHANNEL ; i++) {

            if ( ((value >> i) & 0b1) == 1 ) {
                dataArray[(15 - i)].duration0 = PULSE_T1H;
                dataArray[(15 - i)].level0 = 1;
                dataArray[(15 - i)].duration1 = PULSE_T1L;
                dataArray[(15 - i) ].level1 = 0;
            }
            else {
                dataArray[(15 - i)].duration0 = PULSE_T0H;
                dataArray[(15 - i)].level0 = 1;
                dataArray[(15 - i)].duration1 = PULSE_T0L;
                dataArray[(15 - i) ].level1 = 0;
            }

        }
        // dataArray[15].duration1 = PULSE_T0H;
        // dataArray[15].level1 = 1;
        dataArray[15].duration1 = 30000;
        dataArray[15].level1 = 0;

  //         ESP_LOGI("DSHOT", "Checksum:%u\n", checksum);


  //   for (int i = 0; i < 16; ++i) {
  //   ESP_LOGI("DSHOT","Frame: %u %u %u\n", i, dataArray[i].duration0, dataArray[i].duration1);
  // }
        return dataArray;
    }

    rmt_item32_t _data[DATA_PER_CHANNEL*NUM_DSHOT_CHANNELS];
};

static DShotDriver driver;

#ifdef __cplusplus
extern "C"
{
#endif

void initDShot600(uint8_t id, gpio_num_t pin)
{
    driver.attach(pin, id);
}
void updateDShotThrottle(uint8_t id, uint16_t throttle_value)
{
    driver.updateThrottle(id, throttle_value);
}

#ifdef __cplusplus
}
#endif

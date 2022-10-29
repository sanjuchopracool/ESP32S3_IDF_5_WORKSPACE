/* RMT example -- Morse Code

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "DShot600.h"
static const char *TAG = "example";

#define RMT_TX_CHANNEL RMT_CHANNEL_0

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

typedef  unsigned char byte;
// rmt_config_t config;

uint16_t Throttle = 1983;
uint16_t Throttlecut = 1983;
uint8_t Decalcut = 0;
byte Telem = 0;
uint8_t Checksum = 0;
uint16_t ThrottleTelem = 0;
uint16_t DshotBinFrame = 0;


/*
 * Prepare a raw table with a message in the Morse code
 *
 * The message is "ESP" : . ... .--.
 *
 * The table structure represents the RMT item structure:
 * {duration, level, duration, level}
 *
 */
// static const rmt_item32_t morse_esp[] = {
//     // E : dot
//     {{{ 32767, 1, 32767, 0 }}}, // dot
//     {{{ 32767, 0, 32767, 0 }}}, // SPACE
//     // S : dot, dot, dot
//     {{{ 32767, 1, 32767, 0 }}}, // dot
//     {{{ 32767, 1, 32767, 0 }}}, // dot
//     {{{ 32767, 1, 32767, 0 }}}, // dot
//     {{{ 32767, 0, 32767, 0 }}}, // SPACE
//     // P : dot, dash, dash, dot
//     {{{ 32767, 1, 32767, 0 }}}, // dot
//     {{{ 32767, 1, 32767, 1 }}},
//     {{{ 32767, 1, 32767, 0 }}}, // dash
//     {{{ 32767, 1, 32767, 1 }}},
//     {{{ 32767, 1, 32767, 0 }}}, // dash
//     {{{ 32767, 1, 32767, 0 }}}, // dot
//     // RMT end marker
//     {{{ 0, 1, 0, 0 }}}
// };

/*
 * Initialize the RMT Tx channel
 */

/* Compute Dshot checksum */
uint8_t ComputeDshotChecksum(uint16_t ThrottleTelem) {      //Coupe la valeur de 12 bits en 3 parties de 4 bits et les "somme" avec XOR.

  uint8_t Checksum = 0;

  for (int i = 0; i < 3; i++) {

    Decalcut = 12 - (i + 1) * 4;                           // On commence par la partie de 4 bits coté bit dominant, donc on décale de 8, 4 et 0 bits
    Throttlecut =  (ThrottleTelem >> Decalcut) & 0b1111;   // Maintenant on ne garde que les 4 premiers chiffres de l'uint8
    Checksum ^= Throttlecut;                               // On somme avec XOR


  }

  return Checksum;
}




/* Compute Complete ThrottleTelem Value */

uint16_t ComputeThrottleTelem(uint16_t Throttle , byte Telem) {      //Rassemble le throttle et le bit de telem en une valeur de 12 bit

  uint16_t ThrottleTelem = 0;

  ThrottleTelem = (Throttle << 1) + Telem;

  return ThrottleTelem;

}






/* Compute Full Dshot frame */

uint16_t ComputeFullDshotFrame(uint16_t ThrottleTelem , uint8_t Checksum) {      //Concatene 11 bits throttle, 1 bit telem, et 4 bits de checksum

  uint16_t DshotBinFrame = 0;

  DshotBinFrame = (ThrottleTelem << 4) + (Checksum & 0b1111);

  return DshotBinFrame;

}






// Fonction utilisée générant le véritable standard pour esp32
rmt_item32_t *ComputeDshotBuffer_RMT_ESP32(uint16_t DshotBinFrame) {     // Put timings in a table to use for RMT (1 = High during 1250ns, 0 = High during 625ns). Fonction qui renvoit un pointeur qui pointe vers le tableau cf http://www.dinduks.com/cpp-retourner-un-tableau-dans-une-fonction-ou-methode/;

  static rmt_item32_t Times_Array[16];                    // Allocation dynamique c++ ~ malloc, calloc

  for (int i = 0; i < 16 ; i++) {

    if ( ((DshotBinFrame >> i) & 0b1) == 1 ) {        //Prend les bits du signal entier un par un par décalage. Si ce bit vaut un, on met les durées du timing haut, sinon timing bas en fonction du divider rmt

      Times_Array[(15 - i)].duration0 = PULSE_T1H;
      Times_Array[(15 - i)].level0 = 1;
      Times_Array[(15 - i)].duration1 = PULSE_T1L;
      Times_Array[(15 - i) ].level1 = 0;

    }
    else {

      Times_Array[(15 - i)].duration0 = PULSE_T0H;
      Times_Array[(15 - i)].level0 = 1;
      Times_Array[(15 - i)].duration1 = PULSE_T0L;
      Times_Array[(15 - i) ].level1 = 0;

    }

  }
      // Times_Array[15].duration1 = PULSE_T0H;
      // Times_Array[15].level1 = 1;
      Times_Array[15].duration1 = 30000;
      Times_Array[15].level1 = 0;

  return Times_Array;

}

void sendValue(uint16_t val, uint8_t channel ) {
    ThrottleTelem = ComputeThrottleTelem(val , Telem);
  Checksum = ComputeDshotChecksum(ThrottleTelem);
  ESP_LOGI(TAG, "Checksum:%u\n", Checksum);
  DshotBinFrame = ComputeFullDshotFrame(ThrottleTelem , Checksum);


  rmt_item32_t *Times_Array = ComputeDshotBuffer_RMT_ESP32(DshotBinFrame);
    for (int i = 0; i < 16; ++i) {
    ESP_LOGI(TAG,"Frame: %u %u %u\n", i, Times_Array[i].duration0, Times_Array[i].duration1);
  }


  rmt_write_items(channel, Times_Array,
                  16, /* Number of items */
                  1 /* wait till done */);
  rmt_wait_tx_done(channel, 2 / portTICK_PERIOD_MS);
}

//working
//rmt_set_tx_loop_mode((rmt_channel_t)0, 1);
//sendValue(0);
//for (uint16_t i = 48; i < 1024; ++i) {
//	  sendValue(i);
//	  vTaskDelay(50 / portTICK_PERIOD_MS);
//}
//for (uint16_t i = 1024; i >= 48; --i) {
//		  sendValue(i);
//		  vTaskDelay(50 / portTICK_PERIOD_MS);
//}
void app_main(void)
{

/////////////////////////////////////////////////////
  ESP_LOGI(TAG,"HELLO_WORLD\n");
  // config.rmt_mode = RMT_MODE_TX;
  // config.channel = RMT_CHANNEL_0;
  // config.gpio_num = (gpio_num_t)3;
  // config.mem_block_num = 1;
  // config.tx_config.loop_en = 0;
  // config.tx_config.carrier_en = 0;
  // config.tx_config.idle_output_en = 1;
  // config.tx_config.idle_level = (rmt_idle_level_t)0;
  // config.tx_config.carrier_duty_percent = 50;
  // config.tx_config.carrier_freq_hz = 10000;
  // config.tx_config.carrier_level = (rmt_carrier_level_t)1;
  // config.clk_div = 2;

  // rmt_config(&config);
  // rmt_driver_install(config.channel, 0, 0);


  // rmt_set_tx_loop_mode((rmt_channel_t)0, 1);
  // sendValue(0, RMT_CHANNEL_0);
  // vTaskDelay(1500 / portTICK_PERIOD_MS);

//-----------------------------------------------------  
  // ESP_LOGI(TAG,"RAISING_THROTTLE\n");
  // for (uint16_t i = 48; i < 100; ++i) {
	//   sendValue(i);
  //   ESP_LOGI(TAG, "THROTTLE %u\n", i);
	//   vTaskDelay(2 / portTICK_PERIOD_MS);
  // }

  // sendValue(0, 0);
  // vTaskDelay(100 / portTICK_PERIOD_MS);
  // sendValue(47);
  // vTaskDelay(10000 / portTICK_PERIOD_MS);


  // ESP_LOGI(TAG,"WAITING\n");
  // vTaskDelay(10000 / portTICK_PERIOD_MS);
  // ESP_LOGI(TAG,"WAITING_FINISHED\n");

//  for (uint16_t i = 100000; i < 300; ++i) {
//	  for (uint16_t j = 0; j < 50; ++j) {
//		  sendValue(48);
//		  vTaskDelay(1 / portTICK_PERIOD_MS);
//	  }
//  }

//  vTaskDelay(1000 / portTICK_PERIOD_MS);
//    rmt_set_tx_loop_mode((rmt_channel_t)0, 1);
//  sendValue(0);

//  sendValue(300);

 
initDShot600(0, (gpio_num_t)3);
initDShot600(1, (gpio_num_t)4);
initDShot600(2, (gpio_num_t)5);
initDShot600(3, (gpio_num_t)6);
vTaskDelay(1500 / portTICK_PERIOD_MS);
// sendValue(48, 0);
  for (uint16_t i = 48; i < 100; ++i) {
	  updateDShotThrottle(0, i);
    updateDShotThrottle(1, i);
    updateDShotThrottle(2, i);
    updateDShotThrottle(3, i);
    // ESP_LOGI(TAG, "THROTTLE %u\n", i);
	  // vTaskDelay(2 / portTICK_PERIOD_MS);
  }
updateDShotThrottle(0, 0);
updateDShotThrottle(1, 0);
updateDShotThrottle(2, 0);
updateDShotThrottle(3, 0);
vTaskDelay(1000 / portTICK_PERIOD_MS);
  uint16_t val1 = 48;
  uint16_t val2 = 48;
  uint16_t val3 = 48;
  uint16_t val4 = 48;
    while (1) {
      // ESP_LOGI(TAG,"S\n");
    	updateDShotThrottle(0, val1);
      updateDShotThrottle(1, val2);
      updateDShotThrottle(2, val3);
      updateDShotThrottle(3, val4);
    	vTaskDelay(10 / portTICK_PERIOD_MS);
    	val1 += 1;
    	if (val1 > 100)
    		val1 = 100;
      val2 += 1;
    	if (val2 > 200)
    		val2 = 200;
      val3 += 1;
    	if (val3 > 400)
    		val3 = 400;
      val4 += 1;
    	if (val4 > 800)
    		val4 = 800;
    }
}

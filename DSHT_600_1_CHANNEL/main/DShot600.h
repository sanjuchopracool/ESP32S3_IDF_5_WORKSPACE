#ifndef _DSHOT_600_H_
#define _DSHOT_600_H_

#include <driver/rmt.h>

#ifdef __cplusplus
extern "C"
{
#endif

void initDShot600(uint8_t id, gpio_num_t pin);
void updateDShotThrottle(uint8_t id, uint16_t throttle_value);

#ifdef __cplusplus
}
#endif

#endif //_DSHOT_600_H_

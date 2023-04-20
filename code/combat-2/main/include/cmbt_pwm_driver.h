#ifndef CMBT_PWM_DRIVER_H
#define CMBT_PWM_DRIVER_H

#include "driver/ledc.h"

#define PWM_FREQUENCY 20000
#define PWM_RESOLUTION LEDC_TIMER_8_BIT

typedef struct cmbt_pwm_driver {
    gpio_num_t pin;
    ledc_channel_t channel;
    ledc_channel_config_t channel_config;
} cmbt_pwm_driver;

void cmbt_pwm_driver_init(cmbt_pwm_driver* pwm, gpio_num_t pwm_pin, ledc_channel_t pwm_channel);
void cmbt_pwm_driver_set_pwm(cmbt_pwm_driver* pwm, int pwm_value);


#endif
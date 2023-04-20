#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <cmbt_pwm_driver.h>

typedef enum {
    MOTOR_STATE_DIABLED,
    MOTOR_STATE_FORWARD,
    MOTOR_STATE_BACKWARD,
    MOTOR_STATE_STOP
} MOTOR_STATE;

typedef struct cmbt_motor_driver {
    gpio_num_t dir_1_pin;
    gpio_num_t dir_2_pin;
    cmbt_pwm_driver pwm;
    MOTOR_STATE state;
} cmbt_motor_driver;

void cmbt_motor_driver_init(cmbt_motor_driver* motor, gpio_num_t pwm_pin, ledc_channel_t pwm_channel, gpio_num_t dir_1_pin, gpio_num_t dir_2_pin);
void cmbt_motor_driver_set_pwm(cmbt_motor_driver* motor, int pwm_value);
void cmbt_motor_driver_set_state(cmbt_motor_driver* motor, MOTOR_STATE state);


#endif
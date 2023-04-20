#include "include/cmbt_motor_driver.h"

void cmbt_motor_driver_init(cmbt_motor_driver* motor, gpio_num_t pwm_pin, ledc_channel_t pwm_channel, gpio_num_t dir_1_pin, gpio_num_t dir_2_pin) {
    motor->dir_1_pin = dir_1_pin;
    motor->dir_2_pin = dir_2_pin;
    gpio_reset_pin(motor->dir_1_pin);
    gpio_reset_pin(motor->dir_2_pin);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(motor->dir_1_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(motor->dir_2_pin, GPIO_MODE_OUTPUT);
    cmbt_pwm_driver_init(&motor->pwm, pwm_pin, pwm_channel);
}
void cmbt_motor_driver_set_state(cmbt_motor_driver* motor, MOTOR_STATE state) {
    motor->state = state;
    switch (state) {
    case MOTOR_STATE_FORWARD:
        gpio_set_level(motor->dir_1_pin, 1);
        gpio_set_level(motor->dir_2_pin, 0);
        break;
    case MOTOR_STATE_BACKWARD:
        gpio_set_level(motor->dir_1_pin, 0);
        gpio_set_level(motor->dir_2_pin, 1);
        break;
    case MOTOR_STATE_STOP:
        gpio_set_level(motor->dir_1_pin, 0);
        gpio_set_level(motor->dir_2_pin, 0);
        break;
    default:
        break;
    }
}
#include "include/cmbt_pwm_driver.h"

void cmbt_pwm_driver_init(cmbt_pwm_driver* pwm, gpio_num_t pwm_pin, ledc_channel_t pwm_channel) {
    pwm->pin = pwm_pin;
    pwm->channel = pwm_channel;

    ledc_timer_config_t ledc_timer = {
        .duty_resolution = PWM_RESOLUTION,
        .freq_hz = PWM_FREQUENCY,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ledc_timer_config(&ledc_timer);
    pwm->channel_config.channel = pwm->channel;
    pwm->channel_config.duty = 0;
    pwm->channel_config.gpio_num = pwm->pin;
    pwm->channel_config.speed_mode = LEDC_HIGH_SPEED_MODE;
    pwm->channel_config.hpoint = 0;
    pwm->channel_config.timer_sel = LEDC_TIMER_0;
    ledc_channel_config(&pwm->channel_config);
}

void cmbt_pwm_driver_set_pwm(cmbt_pwm_driver* pwm, int pwm_duty) {
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, pwm->channel, pwm_duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, pwm->channel);
}
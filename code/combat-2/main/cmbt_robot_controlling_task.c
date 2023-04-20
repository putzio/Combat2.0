#include "cmbt_robot_controlling_task.h"

void CMBT_TaskRobotController_1(void* pvParameters) {
    uint8_t pwm_value = 0;
    cmbt_pwm_driver led;

    cmbt_pwm_driver_init(&led, CMBT_MOTOR_RIGHT_PWM_PIN, LEDC_CHANNEL_0);
    while (1) {
        cmbt_pwm_driver_set_pwm(&led, pwm_value);
        printf("PWM value: %d\n", pwm_value);
        pwm_value++;
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void CMBT_TaskRobotController_2(void* pvParameters) {
    cmbt_motor_driver motor;
    cmbt_motor_driver_init(&motor, CMBT_MOTOR_LEFT_PWM_PIN, LEDC_CHANNEL_1, CMBT_MOTOR_LEFT_DIR_1_PIN, CMBT_MOTOR_LEFT_DIR_2_PIN);
    while (1) {
        switch (motor.state) {
        case MOTOR_STATE_FORWARD:
            cmbt_motor_driver_set_state(&motor, MOTOR_STATE_BACKWARD);
            break;
        case MOTOR_STATE_BACKWARD:
            cmbt_motor_driver_set_state(&motor, MOTOR_STATE_STOP);
            break;
        case MOTOR_STATE_STOP:
            cmbt_motor_driver_set_state(&motor, MOTOR_STATE_FORWARD);
            break;
        default:
            cmbt_motor_driver_set_state(&motor, MOTOR_STATE_FORWARD);
            break;
        }
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
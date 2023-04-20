#ifndef CMBT_ROBOT_CONTROLLING_TASK_H
#define CMBT_ROBOT_CONTROLLING_TASK_H

#include <stdio.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "cmbt_pwm_driver.h"
#include "cmbt_pinout.h"
#include "cmbt_motor_driver.h"

void CMBT_TaskRobotController_1(void* pvParameters);
void CMBT_TaskRobotController_2(void* pvParameters);

#endif
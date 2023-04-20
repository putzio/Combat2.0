#include <stdio.h>
#include <sys/param.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "include/cmbt_webserver.h"
#include "include/cmbt_robot_controlling_task.h"

void app_main(void) {
  static httpd_handle_t server = NULL;

  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  xTaskCreate(&CMBT_TaskRobotController_1, "CMBT_TaskRobotController_1", 4096, NULL, 5, NULL);
  xTaskCreate(&CMBT_TaskRobotController_2, "CMBT_TaskRobotController_2", 4096, NULL, 5, NULL);

  /* This helper function configures Wi-Fi or Ethernet, as selected in
   * menuconfig. Read "Establishing Wi-Fi or Ethernet Connection" section in
   * examples/protocols/README.md for more information about this function.
   */
  ESP_ERROR_CHECK(example_connect());

  /* Register event handlers to stop the server when Wi-Fi is
   * disconnected, and re-start it upon connection.
   */

  ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
    &cmbt_connect_handler, &server));
  ESP_ERROR_CHECK(
    esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED,
      &cmbt_disconnect_handler, &server));

  /* Start the server for the first time */
  server = cmbt_start_webserver();

}
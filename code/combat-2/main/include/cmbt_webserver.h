#ifndef CMBT_WEBSERVER_H
#define CMBT_WEBSERVER_H

#include "esp_eth.h"
#include "esp_netif.h"
#include "esp_tls_crypto.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include <ctype.h>
#include <esp_event.h>
#include <esp_http_server.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <nvs_flash.h>

extern const char* TAG;

esp_err_t cmbt_send_web_page(httpd_req_t* req);
esp_err_t cmbt_get_req_handler(httpd_req_t* req);
esp_err_t cmbt_updatedData_get_handler(httpd_req_t* req);

esp_err_t cmbt_http_404_error_handler(httpd_req_t* req, httpd_err_code_t err);
httpd_handle_t cmbt_start_webserver(void);
esp_err_t cmbt_stop_webserver(httpd_handle_t server);

void cmbt_disconnect_handler(void* arg, esp_event_base_t event_base,
    int32_t event_id, void* event_data);

void cmbt_connect_handler(void* arg, esp_event_base_t event_base,
    int32_t event_id, void* event_data);

#endif
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
#include <stdio.h>
#include <sys/param.h>

#include "include/web_server_page.h"

static const char *TAG = "example";

esp_err_t send_web_page(httpd_req_t *req) {
  int response;
  response = httpd_resp_send(req, index_html, HTTPD_RESP_USE_STRLEN);
  return response;
}

esp_err_t get_req_handler(httpd_req_t *req) { return send_web_page(req); }

httpd_uri_t uri_get = {.uri = "/",
                       .method = HTTP_GET,
                       .handler = get_req_handler,
                       .user_ctx = NULL};

static esp_err_t slider1_get_handler(httpd_req_t *req) {
  char *buf;
  size_t buf_len;
  
  buf_len = httpd_req_get_hdr_value_len(req, "Host");
  if (buf_len > 1) {
    buf = malloc(buf_len);
    char param[32];
    if (httpd_req_get_hdr_value_str(req, "Host", param, sizeof(param)) ==
        ESP_OK) {
      ESP_LOGI(TAG, "header=%s", param);
    }
    free(buf);
  }

  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1) {
    buf = malloc(buf_len);

    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {

      ESP_LOGI(TAG, "%s URL query => %s",req->uri, buf);
      char param[32];
      /* Get value of expected key from query string */
      if (httpd_query_key_value(buf, "value", param, sizeof(param)) == ESP_OK) {
        ESP_LOGI(TAG, "Found URL query parameter => value=%s", param);
      }

      free(buf);
    }
  }
  return ESP_OK;
}

httpd_uri_t uri_slider1 = {.uri = "/slider1",
                           .method = HTTP_GET,
                           .handler = slider1_get_handler,
                           .user_ctx = NULL};


/* This handler allows the custom error handling functionality to be
 * tested from client side. For that, when a PUT request 0 is sent to
 * URI /ctrl, the /hello and /echo URIs are unregistered and following
 * custom error handler http_404_error_handler() is registered.
 * Afterwards, when /hello or /echo is requested, this custom error
 * handler is invoked which, after sending an error message to client,
 * either closes the underlying socket (when requested URI is /echo)
 * or keeps it open (when requested URI is /hello). This allows the
 * client to infer if the custom error handler is functioning as expected
 * by observing the socket state.
 */
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err) {
  /* For any other URI send 404 and close socket */
  httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
  return ESP_FAIL;
}

static httpd_handle_t start_webserver(void) {
  httpd_handle_t server = NULL;
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.lru_purge_enable = true;

  // Start the httpd server
  ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
  if (httpd_start(&server, &config) == ESP_OK) {
    // Set URI handlers
    ESP_LOGI(TAG, "Registering URI handlers");
    httpd_register_uri_handler(server, &uri_get);
    httpd_register_uri_handler(server, &uri_slider1);

    return server;
  }

  ESP_LOGI(TAG, "Error starting server!");
  return NULL;
}

static esp_err_t stop_webserver(httpd_handle_t server) {
  // Stop the httpd server
  return httpd_stop(server);
}

static void disconnect_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  httpd_handle_t *server = (httpd_handle_t *)arg;
  if (*server) {
    ESP_LOGI(TAG, "Stopping webserver");
    if (stop_webserver(*server) == ESP_OK) {
      *server = NULL;
    } else {
      ESP_LOGE(TAG, "Failed to stop http server");
    }
  }
}

static void connect_handler(void *arg, esp_event_base_t event_base,
                            int32_t event_id, void *event_data) {
  httpd_handle_t *server = (httpd_handle_t *)arg;
  if (*server == NULL) {
    ESP_LOGI(TAG, "Starting webserver");
    *server = start_webserver();
  }
}

void app_main(void) {
  static httpd_handle_t server = NULL;

  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  /* This helper function configures Wi-Fi or Ethernet, as selected in
   * menuconfig. Read "Establishing Wi-Fi or Ethernet Connection" section in
   * examples/protocols/README.md for more information about this function.
   */
  ESP_ERROR_CHECK(example_connect());

  /* Register event handlers to stop the server when Wi-Fi is
   * disconnected, and re-start it upon connection.
   */

  ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                             &connect_handler, &server));
  ESP_ERROR_CHECK(esp_event_handler_register(
      WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));

  /* Start the server for the first time */
  server = start_webserver();
}
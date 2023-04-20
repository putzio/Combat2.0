#include "include/cmbt_webserver.h"
#include "include/cmbt_webserver_page.h"

const char* TAG = "server";

httpd_uri_t uri_get = { .uri = "/",
                       .method = HTTP_GET,
                       .handler = cmbt_get_req_handler,
                       .user_ctx = NULL };

httpd_uri_t uri_slider1 = { .uri = "/updatedData",
                           .method = HTTP_GET,
                           .handler = cmbt_updatedData_get_handler,
                           .user_ctx = NULL };

esp_err_t cmbt_updatedData_get_handler(httpd_req_t* req) {
  char* buf;
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

      ESP_LOGI(TAG, "%s URL query => %s", req->uri, buf);
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

httpd_handle_t cmbt_start_webserver(void) {
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

esp_err_t cmbt_stop_webserver(httpd_handle_t server) {
  // Stop the httpd server
  return httpd_stop(server);
}

void cmbt_disconnect_handler(void* arg, esp_event_base_t event_base,
  int32_t event_id, void* event_data) {
  httpd_handle_t* server = (httpd_handle_t*)arg;
  if (*server) {
    ESP_LOGI(TAG, "Stopping webserver");
    if (cmbt_stop_webserver(*server) == ESP_OK) {
      *server = NULL;
    }
    else {
      ESP_LOGE(TAG, "Failed to stop http server");
    }
  }
}

void cmbt_connect_handler(void* arg, esp_event_base_t event_base,
  int32_t event_id, void* event_data) {
  httpd_handle_t* server = (httpd_handle_t*)arg;
  if (*server == NULL) {
    ESP_LOGI(TAG, "Starting webserver");
    *server = cmbt_start_webserver();
  }
}

esp_err_t cmbt_send_web_page(httpd_req_t* req) {
  int response;
  response = httpd_resp_send(req, index_html, HTTPD_RESP_USE_STRLEN);
  return response;
}

esp_err_t cmbt_get_req_handler(httpd_req_t* req) {
  return cmbt_send_web_page(req);
}

/* This handler allows the custom error handling functionality to be
 * tested from client side. For that, when a PUT request 0 is sent to
 * URI /ctrl, the /hello and /echo URIs are unregistered and following
 * custom error handler cmbt_http_404_error_handler() is registered.
 * Afterwards, when /hello or /echo is requested, this custom error
 * handler is invoked which, after sending an error message to client,
 * either closes the underlying socket (when requested URI is /echo)
 * or keeps it open (when requested URI is /hello). This allows the
 * client to infer if the custom error handler is functioning as expected
 * by observing the socket state.
 */
esp_err_t cmbt_http_404_error_handler(httpd_req_t* req, httpd_err_code_t err) {
  /* For any other URI send 404 and close socket */
  httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
  return ESP_FAIL;
}

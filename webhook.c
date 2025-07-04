#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/header.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Webhook {
  char *url;
  char *name;
} Webhook;

int webhook_delete(Webhook webhook) {
  char *url = webhook.url;
  CURL *curl = curl_easy_init();

  if(!curl) { return 1; }

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

  CURLcode res = curl_easy_perform(curl);
  if(res != CURLE_OK) {
    return 1;
  }

  curl_easy_cleanup(curl);


  return 0;
}

int webhook_message_send(Webhook webhook, char *content) {
  char *url = webhook.url;
  char *name = webhook.name;

  CURL *curl = curl_easy_init();

  char *payload = NULL;
  asprintf(&payload, "{\"content\": \"%s\", \"username\": \"%s\"}", content, name);

  if(!curl) { return 1; }

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Content-Type: application/json");

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

  CURLcode res = curl_easy_perform(curl);

  if(res != CURLE_OK) { return 1; }

  free(payload);
  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);

  return 0;
}

int webhook_edit(Webhook *webhook, char *name) {
  char *url = webhook->url;
  webhook->name = name;

  CURL *curl = curl_easy_init();

  char *payload = NULL;
  asprintf(&payload, "{\"name\": \"%s\"}", name);

  if(!curl) { return 1; }

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Content-Type: application/json");

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

  CURLcode res = curl_easy_perform(curl);

  if(res != CURLE_OK) { return 1; }

  free(payload);
  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);


  return 0;
}

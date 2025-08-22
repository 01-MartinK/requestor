#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curlHandler.h"

struct Memory {
  char *response;
  size_t size;
};

static char *default_url = "https://jsonplaceholder.typicode.com/posts/1";

// Callback for writing received data
static size_t write_callback(void *data, size_t size, size_t nmemb,
                             void *userp) {
  size_t realsize = size * nmemb;
  struct Memory *mem = (struct Memory *)userp;

  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if (ptr == NULL) {
    // Ran out of memory
    return 0;
  }

  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = '\0'; // null terminate

  return realsize;
}

char *curl_request(char *url) {
  CURL *curl;
  CURLcode res;

  printf(url);

  struct Memory chunk;
  chunk.response = malloc(1); // allocate
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
      printf("Response body:\n%s\n", chunk.response);
      return chunk.response;
    } else {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl_request);
  }
  curl_global_cleanup();
  return "No data";
}

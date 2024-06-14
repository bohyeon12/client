#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl.h>
#include "callapi.h"


static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        // out of memory! 
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

cJSON* getexchangerate(void) {
    SetConsoleOutputCP(CP_UTF8);

    CURL* curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handle = curl_easy_init();

    // ����Ű
    char* authkey = "fTBWVRKLRGOkfqrvfYxTfymAF7ZLLtqo";

    // �˻� ��û ��¥ (��: "20240101 / 2024-01-01 / default(�� ���ڿ� ��)���� �����ϸ� ������")
    char* searchdate = "20240607"; // 

    // API Ÿ�� ȯ���̶� "AP01"
    char* data_type = "AP01";

    char url[256];
    snprintf(url, sizeof(url), "https://www.koreaexim.go.kr/site/program/financial/exchangeJSON?authkey=%s&searchdate=%s&data=%s", authkey, searchdate, data_type);


    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    // SSL ������ ���� ��Ȱ��ȭ(���ϸ� ������ �������� �׳� �̷��� �س����)
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0L);


    res = curl_easy_perform(curl_handle);


    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return NULL;
    }
    else {
        curl_easy_cleanup(curl_handle);
        
        cJSON* json = cJSON_Parse(chunk.memory);
        free(chunk.memory);
        return json;
    }
}
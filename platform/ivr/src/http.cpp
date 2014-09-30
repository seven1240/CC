/*
 * Copyright 2002-2014 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      CC/LICENSE
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>
#include <curl/curl.h>
#include "http.h"

size_t http_t::write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
    write_data_t* wr_data = (write_data_t*)userp;
    int32_t segsize = size * nmemb;

    // fix bug: wr_data->wr_index + segsize == wr_data->maxlen
    // may cause get/post function: out=out_buf core
    if (wr_data->wr_buf == 0 || wr_data->wr_index + segsize >= wr_data->maxlen) {
        wr_data->wr_err = 1;
        return 0;
    }

    memcpy(wr_data->wr_buf + wr_data->wr_index, buffer, (size_t)segsize);
    wr_data->wr_index += segsize;
    wr_data->wr_buf[wr_data->wr_index] = 0;
    return segsize;
}


bool http_t::post(
    const char* url,
    std::string& out, int32_t timeout) {

    char out_buf[MAX_BUF] = {0};
    const char* post = "";

    write_data_t data;
    memset(&data, 0, sizeof(data));
    data.wr_buf = out_buf;
    data.maxlen = MAX_BUF;
    long code = 0;
    out_buf[0] = 0;

    CURL* curl = curl_easy_init();

    if (NULL == curl) {
        return false;
    }

    int ret = curl_easy_setopt(curl, CURLOPT_URL, url);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_POST, 1);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&data);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_perform(curl);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &code);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = data.wr_err;

    if (ret != CURLE_OK) {
        goto clean_up;
    }

clean_up:
    curl_easy_cleanup(curl);
    out = out_buf;
    return (CURLE_OK == ret);
}

bool http_t::get(
    const char* url,
    std::string& out, int32_t timeout) {

    char out_buf[MAX_BUF] = {0};

    write_data_t data;
    memset(&data, 0, sizeof(data));
    data.wr_buf = out_buf;
    data.maxlen = MAX_BUF;
    long code = 0;
    out_buf[0] = 0;

    CURL* curl = curl_easy_init();

    if (NULL == curl) {
        return false;
    }

    int ret = curl_easy_setopt(curl, CURLOPT_URL, url);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&data);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_perform(curl);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &code);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = data.wr_err;

    if (ret != CURLE_OK) {
        goto clean_up;
    }

clean_up:
    curl_easy_cleanup(curl);
    out = out_buf;
    return (CURLE_OK == ret);
}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */

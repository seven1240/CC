<<<<<<< HEAD
#include "utl.h"

enum CC2_RET {
    E_SUCCESS = 0,
    E_GENERAL = 1,
    E_MEM = 2,
    E_SIZE = 3
};
struct write_data_t {
    char* wr_buf;
    uint32_t  wr_index;
    int32_t  wr_err;
    size_t maxlen;
};

size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
    write_data_t* wr_data = (write_data_t*)userp;
    int32_t segsize = size * nmemb;

    if (wr_data->wr_buf == 0 || wr_data->wr_index + segsize > wr_data->maxlen) {
        wr_data->wr_err = 1;
        return 0;
    }

    memcpy(wr_data->wr_buf + wr_data->wr_index, buffer, (size_t)segsize);
    wr_data->wr_index += segsize;
    wr_data->wr_buf[wr_data->wr_index] = 0;
    return segsize;
}

int32_t http_post(
    const char* url, const char* post,
    long* pcode, char* out_buf,
    size_t maxlen, int32_t timeout) {
    write_data_t data;
    memset(&data, 0, sizeof(data));
    data.wr_buf = out_buf;
    data.maxlen = maxlen;
    *pcode = 0;
    out_buf[0] = 0;

    CURL* curl = curl_easy_init();

    if (NULL == curl) {
        return E_GENERAL;
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

    ret = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, pcode);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = data.wr_err;

    if (ret != CURLE_OK) {
        goto clean_up;
    }

clean_up:
    curl_easy_cleanup(curl);
    return (ret == CURLE_OK ? E_SUCCESS : E_GENERAL);
}
/*
int main(){
    char url[]="http://10.26.78.49:8010/login";
    char reqs[]="{\"agentid\":1001,\"agenttype\":1,\"optype\":\"system\",\"op\":\"login\",\"tab\":49849,\"param\":{}}";
    char* request=curl_escape( reqs , 0);
    char post[256];
    snprintf(post,255,"reqs=%s",request);
    curl_free(request);

    char output[1024];
    long code;
    int ret=http_post(url,post,&code,output,1023,1);
    printf("ret=%d,code=%d,output=%s\n",ret,code,output);
    return 0;
}*/
=======
#include "utl.h"

enum CC2_RET {
    E_SUCCESS = 0,
    E_GENERAL = 1,
    E_MEM = 2,
    E_SIZE = 3
};
struct write_data_t {
    char* wr_buf;
    uint32_t  wr_index;
    int32_t  wr_err;
    size_t maxlen;
};

size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
    write_data_t* wr_data = (write_data_t*)userp;
    int32_t segsize = size * nmemb;

    if (wr_data->wr_buf == 0 || wr_data->wr_index + segsize > wr_data->maxlen) {
        wr_data->wr_err = 1;
        return 0;
    }

    memcpy(wr_data->wr_buf + wr_data->wr_index, buffer, (size_t)segsize);
    wr_data->wr_index += segsize;
    wr_data->wr_buf[wr_data->wr_index] = 0;
    return segsize;
}

int32_t http_post(
    const char* url, const char* post,
    long* pcode, char* out_buf,
    size_t maxlen, int32_t timeout) {
    write_data_t data;
    memset(&data, 0, sizeof(data));
    data.wr_buf = out_buf;
    data.maxlen = maxlen;
    *pcode = 0;
    out_buf[0] = 0;

    CURL* curl = curl_easy_init();

    if (NULL == curl) {
        return E_GENERAL;
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

    ret = curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, pcode);

    if (ret != CURLE_OK) {
        goto clean_up;
    }

    ret = data.wr_err;

    if (ret != CURLE_OK) {
        goto clean_up;
    }

clean_up:
    curl_easy_cleanup(curl);
    return (ret == CURLE_OK ? E_SUCCESS : E_GENERAL);
}
/*
int main(){
    char url[]="http://10.26.78.49:8010/login";
    char reqs[]="{\"agentid\":1001,\"agenttype\":1,\"optype\":\"system\",\"op\":\"login\",\"tab\":49849,\"param\":{}}";
    char* request=curl_escape( reqs , 0);
    char post[256];
    snprintf(post,255,"reqs=%s",request);
    curl_free(request);

    char output[1024];
    long code;
    int ret=http_post(url,post,&code,output,1023,1);
    printf("ret=%d,code=%d,output=%s\n",ret,code,output);
    return 0;
}*/
>>>>>>> 52366f05890caf1d08efb5cba831089bd4c4b06f

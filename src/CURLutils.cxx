#include "CURLutils.h"

#include <iostream>

//#include "TwitchEndpoints.h"

#define OUT cout

using std::OUT;
using std::endl;

CURL *curl;

size_t response_func(void *ptr, size_t size, size_t count, void *stream) {
    ((std::string *)stream)->append((char *)ptr, 0, size*count);
    return size*count;
}

void Init_CURL() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    //TwitchEndpoints::Initialize();
}

void Destroy_CURL() {
    if(curl)
        curl_easy_cleanup(curl);
    curl_global_cleanup();
}

void ApplyHeader(std::string header) {
    struct curl_slist *list = NULL;
    list = curl_slist_append(list, header.c_str());
    list = curl_slist_append(list, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
}

std::string FinishRequest(std::string url, std::string header) {
        // PUT = CURLOPT_UPLOAD
        // HEAD= CURLOPT_HTTPGET 1L
        //     = CURLOPT_NOBODY 1L
    std::string response;
    CURLcode res;

    if(!header.empty()) {
        ApplyHeader(header);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    res = curl_easy_perform(curl);

    //long http_code = 0;
    //curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    //OUT << "HHTP: " << http_code << endl;
    if(res != CURLE_OK) {
        OUT << "Couldn't perform curl action" << endl;
        OUT << "At: " << url << endl;
        exit(EXIT_FAILURE);
    }
    return response;
}

std::string GET(std::string url, std::string header) {
    curl_easy_reset(curl);

    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    return FinishRequest(url, header);
}
 
std::string POST(std::string url, std::string content, std::string header) {
    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str());

    return FinishRequest(url, header);
}

std::string CUSTOM(std::string url, std::string request, std::string header) {
    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.c_str());

    return FinishRequest(url, header);
    
}

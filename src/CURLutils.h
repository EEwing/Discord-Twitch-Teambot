#ifndef CURL_UTILS_H
#define CURL_UTILS_H

#include <curl/curl.h>
#include <string>

extern CURL *curl;

void Init_CURL();
void Destroy_CURL();

// first string is the URL, last string is authorization header

std::string GET(std::string, std::string = "");

std::string POST(std::string, std::string, std::string = "");

std::string CUSTOM(std::string, std::string, std::string = "");

#endif

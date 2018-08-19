//
// Created by void on 8/18/18.
//

#include "CurlWrapper.h"

size_t CurlWrapper::stringAppendWriteFunction(void *ptr, size_t size, size_t nmemb, void *stream) {
 size_t ssize = size * nmemb;
 ((std::string*)stream)->append((char*)ptr, ssize);
 return ssize;
}

// Create separate CURL handle (for threading) and save output to string pointer
CURLcode CurlWrapper::get(const char* url, std::string* target) {
 CURL* curl = curl_easy_init();
 curl_easy_setopt(curl, CURLOPT_URL, url);
 curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, stringAppendWriteFunction);
 curl_easy_setopt(curl, CURLOPT_WRITEDATA, target);
 CURLcode result = curl_easy_perform(curl);
 curl_easy_cleanup(curl);
 return result;
}

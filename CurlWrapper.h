//
// Created by void on 8/18/18.
//

#ifndef FILE_MAKER_CURLWRAPPER_H
#define FILE_MAKER_CURLWRAPPER_H

#include <curl/curl.h>
#include <string>

class CurlWrapper final {
private:
 CurlWrapper() = default;

 static size_t stringAppendWriteFunction(void* ptr, size_t size, size_t nmemb, void* stream);

public:
 static CURLcode get(const char* url, std::string* target);
};

#endif //FILE_MAKER_CURLWRAPPER_H

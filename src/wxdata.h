#pragma once

#include <curl/curl.h>
#include <string>

class wxdata
{
public:
    wxdata();
    ~wxdata();

    int Refresh();
    std::string& GetBuffer();
    std::string& GetTemp();
    std::string& GetRH();

private:
    CURL* m_curl;
    CURLcode m_res;

    //char errorBuffer[CURL_ERROR_SIZE];
    std::string m_buffer;

    std::string m_temp;
    std::string m_rh;

    static int CurlWrite(char* data, size_t size, size_t nmemb, std::string* writerData);
};
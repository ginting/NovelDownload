#include "UrlLib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

UrlLib::UrlLib(const std::string& url)
: m_url(url)
{
    //ctor
}

UrlLib::~UrlLib()
{
    //dtor
    curl_easy_cleanup(m_curl);
}

bool UrlLib::open()
{
    curl_global_init(CURL_GLOBAL_ALL);
    m_curl = curl_easy_init();
    if (m_curl) {
        curl_easy_setopt(m_curl, CURLOPT_URL, m_url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 1L);

        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &UrlLib::receiveData);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_data);

        curl_easy_perform(m_curl);

        return true;
    }

    return false;
}

std::string UrlLib::read()
{
    std::string data;
    if (NULL != m_data._buffer) {
        data.assign(m_data._buffer, m_data._size);
    }

    return data;
}

ssize_t UrlLib::receiveData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    if (0 == ptr) {
        printf("the input data ptr is null\n");
        return 0;
    }

    DataBuffer *data = static_cast<DataBuffer *>(stream);
    if (0 == data) {
        printf("the output stream ptr is null\n");
        return 0;
    }

    return data->writeToBuffer(ptr, size, nmemb);
}

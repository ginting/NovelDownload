#ifndef URLLIB_H
#define URLLIB_H

#include <string>
#include <curl/curl.h>

class DataBuffer
{
    public:
        DataBuffer()
        : buffer(0)
        , size(0)
        {

        }

        virtual ~DataBuffer()
        {

        }

    public:
        char    *buffer;
        size_t  size;


};


class UrlLib
{
    public:
        UrlLib(const std::string& url);
        virtual ~UrlLib();

        bool        open();
        std::string read();
    protected:
        static  ssize_t receiveData(void *ptr, size_t size, size_t nmemb, void *stream);
    private:
        std::string     m_url;
        CURL            *m_curl;
        DataBuffer      m_data;
};

#endif // URLLIB_H

#ifndef URLLIB_H
#define URLLIB_H

#include <NovelPre.h>

#include <DataBuffer.h>


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

#ifndef URLSPLIT_H_INCLUDED
#define URLSPLIT_H_INCLUDED

#include <NovelPre.h>


class UrlSplit
{
    public:
        UrlSplit(const std::string& url);
        virtual ~UrlSplit();

        std::string getRootPath();
        std::string getMidPath();
        std::string getName();
    protected:
    private:
        UrlSplit();
        UrlSplit(const UrlSplit&);
        void _split(const std::string&  url);


    private:
        std::string m_url_full;
        std::string m_url_root;
        std::string m_url_mid;
        std::string m_url_name;
};

#endif // URLSPLIT_H_INCLUDED

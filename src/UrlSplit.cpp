#include "UrlSplit.h"

UrlSplit::UrlSplit(const std::string& url)
: m_url_full(url)
{
    //ctor
    _split(m_url_full);
}

UrlSplit::~UrlSplit()
{
    //dtor
}

std::string UrlSplit::getRootPath()
{
    return m_url_root;
}

std::string UrlSplit::getMidPath()
{
    return m_url_mid;
}

std::string UrlSplit::getName()
{
    return m_url_name;
}

void UrlSplit::_split(const std::string& url)
{
    if (url.empty()) {

        printf("the url string is empty.\n");
        return;
    }

    std::string head = "http://";
    //get root path
    std::string::size_type pos = url.find("://");
    std::string tmp_url = url;
    if (pos != std::string::npos) {

        head = url.substr(0, pos+3);
        tmp_url = url.substr(pos+3, std::string::npos);
    }

    pos = tmp_url.find("/");
    if (pos != std::string::npos) {

        m_url_root = head + tmp_url.substr(0, pos);
        tmp_url = tmp_url.substr(pos, std::string::npos);
    }

    pos = tmp_url.rfind("/");
    if (pos != std::string::npos) {

        m_url_mid = tmp_url.substr(0, pos+1);
        m_url_name = tmp_url.substr(pos+1, std::string::npos);
    }
}

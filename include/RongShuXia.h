#ifndef RONGSHUXIA_H
#define RONGSHUXIA_H

#include <string>
#include <vector>

class RongShuXia
{
    public:
        typedef std::vector<std::string>    SubUrlList;
    public:
        explicit RongShuXia(const std::string& html_text);
        virtual ~RongShuXia();

        void        execute();
        SubUrlList  getSubUrlList() const;
    protected:
        std::string getChapterTitle(const std::string& text);
        std::string getChapterUrl(const std::string& text);
    private:
        std::string     m_html_text;
        SubUrlList      m_sub_urls;
};

#endif // RONGSHUXIA_H

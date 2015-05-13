#ifndef RONGSHUXIA_CHAPTER_H_INCLUDED
#define RONGSHUXIA_CHAPTER_H_INCLUDED

#include <NovelPre.h>

namespace RongShuXia {

class Chapter
{
    public:
        explicit Chapter(const std::string& html_text);
        virtual ~Chapter();

        void parse();
        std::string getTitle() const;
        std::string getContent() const;
    protected:
        std::string _getChapterTitle(const std::string& html_text);
        std::string _getChapterContent(const std::string& html_text);
    private:
        std::string     m_html_text;
        std::string     m_title;
        std::string     m_content;
};

}   //namespace RongShuXia

#endif // RONGSHUXIA_CHAPTER_H_INCLUDED

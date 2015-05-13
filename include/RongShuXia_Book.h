#ifndef RONGSHUXIA_H
#define RONGSHUXIA_H

#include <NovelPre.h>

namespace RongShuXia {

struct ChapterUrlData
{
    std::string chapter_title;
    std::string chapter_url;
};

typedef std::vector<ChapterUrlData>    ChapterUrlDataList;

class Book
{
    public:
        explicit Book(const std::string& html_text);
        virtual ~Book();

        void                parse();
        ChapterUrlDataList  getChapterUrlList() const;
        std::string         getName() const;
    protected:
        std::string _getChapterTitle(const std::string& text);
        std::string _getChapterUrl(const std::string& text);
        std::string _getBookName(const std::string& text);
    private:
        std::string         m_html_text;
        std::string         m_book_name;
        ChapterUrlDataList  m_url_data_list;
};

}   //namespace RongShuXia

#endif // RONGSHUXIA_BOOK_H

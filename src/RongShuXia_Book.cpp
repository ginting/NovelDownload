#include "RongShuXia_Book.h"
#include <htmlcxx/html/ParserDom.h>
#include <htmlcxx/html/tree.h>

namespace RongShuXia {

Book::Book(const std::string& html_text)
: m_html_text(html_text)
{
    //ctor
}

Book::~Book()
{
    //dtor
}

void Book::parse()
{
   htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(m_html_text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        std::string tag_name = p_beg->tagName();
        if (strcasecmp(tag_name.c_str(), "div") == 0) {

            p_beg->parseAttributes();
            if (strcasecmp(p_beg->attribute("class").second.c_str(), "title") == 0) { //book name

                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                m_book_name = _getBookName(m_html_text.substr(offset, length));
                //std::cout << "book name:" << m_book_name << std::endl;
            }
            else if (strcasecmp(p_beg->attribute("class").second.c_str(), "lists") == 0) {

                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                std::string msg = _getChapterTitle(m_html_text.substr(offset, length));
                //std::cout << "title: " << msg << std::endl;
                //msg = getChapterUrl(html_text.substr(offset, length));
                //std::cout << "title: " << msg << std::endl;
            }
        }
    }
}

ChapterUrlDataList Book::getChapterUrlList() const
{
    return m_url_data_list;
}

std::string Book::getName() const
{
    return m_book_name;
}

 std::string Book::_getBookName(const std::string& text)
 {
    std::string result;
    htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        if (strcasecmp(p_beg->tagName().c_str(), "a") == 0) {

            /*
            std::cout   << "text: " << text <<std::endl
                        << "offset: " << p_beg->offset() << std::endl
                        << "text.length: " << p_beg->text().length() << std::endl
                        << "length:" << p_beg->length() << std::endl
                        << "closingText length: " << p_beg->closingText().length() << std::endl;
            */
            size_t offset = p_beg->offset() + p_beg->text().length();
            size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
            result = text.substr(offset, length);
            std::cout << "book name: " << result << std::endl;
        }
    }

    return result;
 }

std::string Book::_getChapterTitle(const std::string& text)
{
    std::string result;
    m_url_data_list.reserve(128);
    htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        if (strcasecmp(p_beg->tagName().c_str(), "a") == 0) {
            p_beg->parseAttributes();
            std::string url = p_beg->attribute("href").second;
            std::string title = p_beg->attribute("title").second;
            std::cout << "title: " << title << " => " << url << std::endl;
            ChapterUrlData data = {title, url};
            m_url_data_list.push_back(data);
        }
    }

    return result;
}

std::string Book::_getChapterUrl(const std::string& text)
{
    std::string result;
    htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        if (strcasecmp(p_beg->tagName().c_str(), "a") == 0) {
                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                result = text.substr(offset, length);
                break;
        }
    }

    return result;
}

}   //namespace RongShuXia

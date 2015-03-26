#include "RongShuXia.h"
#include <htmlcxx/html/ParserDom.h>
#include <htmlcxx/html/tree.h>

#include <iostream>

RongShuXia::RongShuXia(const std::string& html_text)
: m_html_text(html_text)
{
    //ctor
}

RongShuXia::~RongShuXia()
{
    //dtor
}

void RongShuXia::execute()
{
   htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(m_html_text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        std::string tag_name = p_beg->tagName();
        if (strcasecmp(tag_name.c_str(), "div") == 0) {
            p_beg->parseAttributes();
            if (strcasecmp(p_beg->attribute("class").second.c_str(), "lists") == 0) {
                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                std::string msg = getChapterTitle(m_html_text.substr(offset, length));
                //std::cout << "title: " << msg << std::endl;
                //msg = getChapterUrl(html_text.substr(offset, length));
                //std::cout << "title: " << msg << std::endl;
            }
        }
    }
}

RongShuXia::SubUrlList RongShuXia::getSubUrlList() const
{
    return m_sub_urls;
}

std::string RongShuXia::getChapterTitle(const std::string& text)
{
    std::string result;
    htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        if (strcasecmp(p_beg->tagName().c_str(), "a") == 0) {
            p_beg->parseAttributes();
            std::string url = p_beg->attribute("href").second;
            std::string title = p_beg->attribute("title").second;
            std::cout << "title: " << title << " => " << url << std::endl;
        }
    }

    return result;
}

std::string RongShuXia::getChapterUrl(const std::string& text)
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

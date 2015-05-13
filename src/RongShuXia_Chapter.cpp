#include "RongShuXia_Chapter.h"
#include <htmlcxx/html/ParserDom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

namespace RongShuXia {

Chapter::Chapter(const std::string& html_text)
: m_html_text(html_text)
{
    //ctor
}

Chapter::~Chapter()
{
    //dtor
}

std::string Chapter::getTitle() const
{
    return m_title;
}

std::string Chapter::getContent() const
{
    return m_content;
}

void Chapter::parse()
{
    htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(m_html_text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        std::string tag_name = p_beg->tagName();
        if (strcasecmp(tag_name.c_str(), "div") == 0) {
            p_beg->parseAttributes();
            if (strcasecmp(p_beg->attribute("class").second.c_str(), "title") == 0) {
                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                std::string msg = _getChapterTitle(m_html_text.substr(offset, length));
                std::cout << "title: " << msg << std::endl;
                m_title = msg;
            }
            else if (strcasecmp(p_beg->attribute("id").second.c_str(), "new_cpt_content") == 0) {
                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                std::string msg = _getChapterContent(m_html_text.substr(offset, length));
                std::cout << "content: " << msg << std::endl;
                m_content = msg;
            }
        }
    }
}

std::string Chapter::_getChapterTitle(const std::string& html_text)
{
    std::string result;
    htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(html_text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        if (strcasecmp(p_beg->tagName().c_str(), "strong") == 0) {
                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                result = html_text.substr(offset, length);
                break;
        }
    }

    return result;
}

std::string Chapter::_getChapterContent(const std::string& html_text)
{
    std::string result;
    htmlcxx::HTML::ParserDom dom_parser;
    tree<htmlcxx::HTML::Node> dom = dom_parser.parseTree(html_text);
    tree<htmlcxx::HTML::Node>::iterator p_beg = dom.begin(), p_end = dom.end();
    for (; p_beg != p_end; ++p_beg) {
        if (strcasecmp(p_beg->tagName().c_str(), "p") == 0) {
                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                result += std::string("\n") + html_text.substr(offset, length);
        }
    }

    return result;
}

}   //namespace RongShuXia

#include "HtmlParser.h"
#include <htmlcxx/html/ParserDom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

HtmlParser::HtmlParser(const std::string& html_text)
: m_html_text(html_text)
{
    //ctor
}

HtmlParser::~HtmlParser()
{
    //dtor
}

std::string HtmlParser::getTitle() const
{
    return m_title;
}

std::string HtmlParser::getContent() const
{
    return m_content;
}

void HtmlParser::parse()
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
                std::string msg = getChapterTitle(m_html_text.substr(offset, length));
                std::cout << "title: " << msg << std::endl;
                m_title = msg;
            }
            else if (strcasecmp(p_beg->attribute("id").second.c_str(), "new_cpt_content") == 0) {
                size_t offset = p_beg->offset() + p_beg->text().length();
                size_t length = p_beg->length() - p_beg->text().length() - p_beg->closingText().length();
                std::string msg = getChapterContent(m_html_text.substr(offset, length));
                std::cout << "content: " << msg << std::endl;
                m_content = msg;
            }
        }
    }
}

std::string HtmlParser::getChapterTitle(const std::string& html_text)
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

std::string HtmlParser::getChapterContent(const std::string& html_text)
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

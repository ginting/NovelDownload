#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>

class HtmlParser
{
    public:
        explicit HtmlParser(const std::string& html_text);
        virtual ~HtmlParser();

        void parse();
        std::string getTitle() const;
        std::string getContent() const;
    protected:
        std::string getChapterTitle(const std::string& html_text);
        std::string getChapterContent(const std::string& html_text);
    private:
        std::string     m_html_text;
        std::string     m_title;
        std::string     m_content;
};

#endif // HTMLPARSER_H

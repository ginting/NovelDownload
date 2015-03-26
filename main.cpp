#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UrlLib.h"
#include "HtmlParser.h"
#include "RongShuXia.h"


int main()
{
    /*
    std::string url = "http://www.rongshuxia.com/chapter/bookid-5483151-chapterid-76156.html";
    UrlLib rsx(url);
    rsx.open();
    std::string html_text = rsx.read();
    //std::cout << html_text << std::endl;

    HtmlParser hp(html_text);
    hp.parse();
    std::string title = hp.getTitle();
    std::string content = hp.getContent();
    std::cout   << "titile: " << title << std::endl
                << "content: " << content << std::endl;
    */

    std::string url = "http://www.rongshuxia.com/book/volume/bookid-5483151.html";
    UrlLib rsx(url);
    rsx.open();
    std::string html_text = rsx.read();

    RongShuXia rsx_html(html_text);
    rsx_html.execute();

    return 0;
}

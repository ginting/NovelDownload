#include <NovelPre.h>
#include "UrlLib.h"
#include "UrlSplit.h"
#include "RongShuXia_Chapter.h"
#include "RongShuXia_Book.h"

void testGetChapterContents(const std::string& chapter_url)
{
    UrlLib rsx(chapter_url);
    rsx.open();
    std::string html_text = rsx.read();
    //std::cout << html_text << std::endl;

    RongShuXia::Chapter hp(html_text);
    hp.parse();
    std::string title = hp.getTitle();
    std::string content = hp.getContent();
    std::cout   << "titile: " << title << std::endl
                << "content: " << content << std::endl;
}

void testUrlSplit(const std::string& url)
{
    UrlSplit split(url);
    std::cout   << "root: " << split.getRootPath() << std::endl
                << "mid: " << split.getMidPath() << std::endl
                << "name: " << split.getName() << std::endl;
}


int main()
{
    //test chapter url and get contents
    /*
    testGetChapterContents("http://www.rongshuxia.com/chapter/bookid-5483151-chapterid-76156.html");
    */

    //test url split
    //testUrlSplit("http://www.rongshuxia.com/book/volume/bookid-5483151.html");

#if 1
    //std::string url = "http://www.rongshuxia.com/book/volume/bookid-5483151.html";
    //std::string url = "http://www.rongshuxia.com/book/volume/bookid-6280764.html";
    std::string url= "http://www.rongshuxia.com/book/volume/bookid-6270533.html";
    UrlSplit split(url);
    UrlLib rsx(url);
    rsx.open();
    std::string html_text = rsx.read();

    RongShuXia::Book rsx_html(html_text);
    rsx_html.parse();
    RongShuXia::ChapterUrlDataList url_data_list = rsx_html.getChapterUrlList();

    std::stringstream ss;
    ss  << rsx_html.getName() << std::endl
        << std::endl;

    RongShuXia::ChapterUrlDataList::const_iterator p_beg = url_data_list.begin(), p_end = url_data_list.end();
    for (; p_beg != p_end; ++p_beg) {

        std::string chapter_url = split.getRootPath() + p_beg->chapter_url;
        //std::cout << chapter_url << std::endl;
        UrlLib urlch(chapter_url);
        urlch.open();
        //std::cout << urlch.read() << std::endl;
        RongShuXia::Chapter chapter(urlch.read());
        chapter.parse();
        std::cout << chapter.getContent() << std::endl;

        ss  << chapter.getTitle() << std::endl
            << chapter.getContent() << std::endl
            << std::endl;
    }

    //out the content to disk file
    std::string file_name = rsx_html.getName() + ".txt";
    FILE *fp = fopen(file_name.c_str(), "wb");
    if (0 == fp) {

        printf("open file %s failed.\n", file_name.c_str());
        return -1;
    }

    fprintf(fp, "%s", ss.str().c_str());

    fclose(fp);
#endif

    return 0;
}

#ifndef RONGSHUXIA_ROOT_H_INCLUDED
#define RONGSHUXIA_ROOT_H_INCLUDED

#include <NovelPre.h>

class RongShuXia_Root
{
    public:
        RongShuXia_Root(const std::string& text);
        virtual ~RongShuXia_Root();

        void execute();

    protected:
    private:
        std::string m_text;
};

#endif // RONGSHUXIA_ROOT_H_INCLUDED

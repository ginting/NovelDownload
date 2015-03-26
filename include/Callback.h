#ifndef CALLBACK_H
#define CALLBACK_H

#include <stddef.h>

class Callback
{
    public:
        Callback();
        virtual ~Callback();

        virtual size_t operator()(void *ptr, size_t size, size_t nmemb) = 0;
    protected:
    private:
};

#endif // CALLBACK_H

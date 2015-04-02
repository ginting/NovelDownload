#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <stdio.h>

class DataBuffer
{
    public:
        DataBuffer();
        virtual ~DataBuffer();

        ssize_t writeToBuffer(void *ptr, size_t size, size_t nmemb);
    public:
        char    *_buffer;
        size_t  _size;
};

#endif // DATABUFFER_H

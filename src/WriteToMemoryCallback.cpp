#include "WriteToMemoryCallback.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

WriteToMemoryCallback::WriteToMemoryCallback()
: m_buffer(0)
, m_size(0)
{
    //ctor
}

WriteToMemoryCallback::~WriteToMemoryCallback()
{
    //dtor
}

size_t WriteToMemoryCallback::operator()(void *ptr, size_t size, size_t nmemb)
{
    if (0 == ptr) {

        printf("the ptr is null pointer.\n");
        return -1;
    }

    size_t block_size = size * nmemb;
    if (0 == m_size && 0 == m_buffer) {

        m_buffer = (char *)malloc(sizeof(char) * (m_size + block_size));
    }
    else {

        m_buffer = (char *)realloc(m_buffer, sizeof(char) * (m_size + block_size));
    }

    memcpy(m_buffer + m_size, ptr, block_size);
    m_size += block_size;

    return block_size;
}

void* WriteToMemoryCallback::getBuffer() const
{
    return m_buffer;
}
size_t WriteToMemoryCallback::getSize() const
{
    return m_size;
}

#include "WriteToMemoryCallback.h"

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
    return 0;
}

void* WriteToMemoryCallback::getBuffer() const
{
    return m_buffer;
}
size_t WriteToMemoryCallback::getSize() const
{
    return m_size;
}

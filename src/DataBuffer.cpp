#include "DataBuffer.h"

#include <stdlib.h>
#include <string.h>

DataBuffer::DataBuffer()
: _buffer(0)
, _size(0)
{
    //ctor
}

DataBuffer::~DataBuffer()
{
    //dtor
    if (0 != _buffer && 0 < _size) {

        free(_buffer);
    }
}

ssize_t DataBuffer::writeToBuffer(void *ptr, size_t size, size_t nmemb)
{
    size_t block_size = size * nmemb;
    if (0 == _size) {
        _buffer = (char *)malloc(sizeof(char) * (_size + block_size));
    }
    else {
        _buffer = (char *)realloc(_buffer, sizeof(char) * (_size + block_size));
    }

    memcpy(_buffer+_size, ptr, block_size);
    _size += block_size;

    return block_size;
}

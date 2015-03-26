#ifndef WRITETOMEMORYCALLBACK_H
#define WRITETOMEMORYCALLBACK_H

#include <Callback.h>


class WriteToMemoryCallback : public Callback
{
    public:
        WriteToMemoryCallback();
        virtual ~WriteToMemoryCallback();

        virtual size_t operator()(void *ptr, size_t size, size_t nmemb);

        void*   getBuffer() const;
        size_t  getSize() const;
    protected:
    private:
        void    *m_buffer;
        size_t  m_size;
};

#endif // WRITETOMEMORYCALLBACK_H

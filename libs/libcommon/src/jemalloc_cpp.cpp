#include <common/memory.h>

#if USE_JEMALLOC

namespace JeMalloc
{

NO_INLINE void * handleOOM(std::size_t size, bool nothrow)
{
    void * ptr = nullptr;

    while (ptr == nullptr)
    {
        std::new_handler handler = std::get_new_handler();
        if (handler == nullptr)
            break;

        try
        {
            handler();
        }
        catch (const std::bad_alloc &)
        {
            break;
        }

        ptr = je_malloc(size);
    }

    if (ptr == nullptr && !nothrow)
        throw std::bad_alloc{};
    return ptr;
}

}

#endif // USE_JEMALLOC

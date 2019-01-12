#ifndef VANIR_SINGLETON_H
#define VANIR_SINGLETON_H

#include <memory>

namespace Vanir
{
    template <typename T>
    class Singleton
    {
    public:
        static T& GetInstance()
        {
            static T instance();

            return instance;
        }
    };

} /* Namespace Vanir. */

#endif /* VANIR_SINGLETON_H. */
#ifndef VANIR_SINGLETON_H
#define VANIR_SINGLETON_H

#include <memory>

namespace Vanir
{
    template <typename T>
    class Singleton
    {
    public:
        static std::shared_ptr<T> GetInstance()
        {
            static std::shared_ptr<T> instance(new T);

            return instance;
        }
    };

} /* Namespace Vanir. */

#endif /* VANIR_SINGLETON_H. */

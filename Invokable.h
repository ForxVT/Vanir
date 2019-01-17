#ifndef VANIR_INVOKABLE_H
#define VANIR_INVOKABLE_H

#include <vector>
#include <Vanir/Callback.h>

namespace Vanir
{
    template<typename... T>
    class Invokable
    {
    public:
        void Hook(Callback<T...> cb)
        {
            if (std::find(m_callbacks.begin(), m_callbacks.end(), cb) == m_callbacks.end())
                m_callbacks.push_back(cb);
        }

        void Unhook(Callback<T...> cb)
        {
            typename std::vector<Callback<T...>>::iterator it = std::find(m_callbacks.begin(), m_callbacks.end(), cb);

            if (it != m_callbacks.end())
                m_callbacks.erase(it);
        }

        void UnhookAll()
        {
            m_callbacks.clear();
        }

        void Invoke(T... args)
        {
            for (size_t i = 0; i < m_callbacks.size(); i++)
                m_callbacks[i](args...);
        }

    private:
        std::vector<Callback<T...>> m_callbacks;
    };

} /* Namespace Vanir. */

#endif /* VANIR_INVOKABLE_H. */

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
            m_safetyLock.lock();

            if (std::find(m_callbacks.begin(), m_callbacks.end(), cb) == m_callbacks.end())
                m_callbacks.push_back(cb);

            m_safetyLock.unlock();
        }

        void Unhook(Callback<T...> cb)
        {
            m_safetyLock.lock();

            typename std::vector<Callback<T...>>::iterator it = std::find(m_callbacks.begin(), m_callbacks.end(), cb);

            if (it != m_callbacks.end())
                m_callbacks.erase(it);

            m_safetyLock.unlock();
        }

        void UnhookAll()
        {
            m_safetyLock.lock();

            m_callbacks.clear();

            m_safetyLock.unlock();
        }

        void Invoke(T... args)
        {
            m_safetyLock.lock();

            for (size_t i = 0; i < m_callbacks.size(); i++)
                m_callbacks[i](args...);

            m_safetyLock.unlock();
        }

    private:
        std::mutex m_safetyLock;
        std::vector<Callback<T...>> m_callbacks;
    };

} /* Namespace Vanir. */

#endif /* VANIR_INVOKABLE_H. */
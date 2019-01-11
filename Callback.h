#ifndef VANIR_CALLBACK_H
#define VANIR_CALLBACK_H

#include <functional>
#include <type_traits>
#include <mutex>

namespace Vanir
{
    template<typename... T>
    class Callback
    {
    public:
        template<typename _T, class _Fx>
        Callback(_T* theObj, _Fx&& theFunc)
        {
            m_hashCode = reinterpret_cast<size_t>(&this->m_function) ^ (&typeid(Callback<T...>))->hash_code();

            Create(theObj, theFunc, std::make_integer_sequence<std::size_t, sizeof...(T)> {});
        }

        bool operator==(const Callback& cb)
        {
            return (m_hashCode == cb.m_hashCode);
        }

        bool operator!=(const Callback& cb)
        {
            return (m_hashCode != cb.m_hashCode);
        }

        const Callback& operator()(T... args)
        {
            m_function(args...);

            return (*this);
        }

        void Invoke(T... args)
        {
            m_function(args...);
        }

        Callback<T...> Clone()
        {
            return Callback<T...>(m_function);
        }

        constexpr size_t hash_code() const noexcept
        {
            return m_hashCode;
        }

    private:
        template<int>
        struct PlaceholderTemplate
        {

        };

        template<typename _T, class _Fx, std::size_t... Is>
        void Create(_T* theObj, _Fx&& theFunc, std::integer_sequence<std::size_t, Is...>)
        {
            this->m_function = std::function<void(T...)>(std::bind(theFunc, theObj, PlaceholderTemplate<Is>()...));
        }

        size_t m_hashCode;
        std::function<void(T...)> m_function;
    };

} /* Namespace Vanir. */

#endif /* VANIR_CALLBACK_H. */
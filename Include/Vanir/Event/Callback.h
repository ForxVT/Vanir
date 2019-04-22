//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo@gmail.com>                           //
//                                                                                  //
//  This file is part of the Aesir project.                                         //
//  Licensed under MIT License:                                                     //
//                                                                                  //
//  Permission is hereby granted, free of charge, to any person obtaining           //
//  a copy of this software and associated documentation files (the "Software"),    //
//  to deal in the Software without restriction, including without limitation       //
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,        //
//  and/or sell copies of the Software, and to permit persons to whom the           //
//  Software is furnished to do so, subject to the following conditions:            //
//                                                                                  //
//  The above copyright notice and this permission notice shall be included in      //
//  all copies or substantial portions of the Software.                             //
//                                                                                  //
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      //
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        //
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     //
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          //
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   //
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   //
//  SOFTWARE.                                                                       //
//                                                                                  //
//==================================================================================//

#ifndef VANIR_EVENT_CALLBACK_H
#define VANIR_EVENT_CALLBACK_H

#include <Vanir/Common.h>
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

#endif /* VANIR_EVENT_CALLBACK_H. */

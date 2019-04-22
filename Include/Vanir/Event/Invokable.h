//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo@gmail.com>                           //
//                                                                                  //
//  This file is part of the Vanir project.                                         //
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

#ifndef VANIR_EVENT_INVOKABLE_H
#define VANIR_EVENT_INVOKABLE_H

#include <Vanir/Common.h>
#include <Vanir/Event/Callback.h>

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

#endif /* VANIR_EVENT_INVOKABLE_H. */

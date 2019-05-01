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

#ifndef VANIR_FACTORY_H
#define VANIR_FACTORY_H

#include <Vanir/Factory/GenericFactory.h>
#include <map>

namespace Vanir
{
    template <class BaseType>
    class Factory
    {
    public:
        static Factory* GetInstance();

        template<class SubType>
        bool Register(std::string type);
        BaseType* Create(std::string type);

    private:
        std::map<std::string, BaseType*(*)()> m_factorys;
    };

    template <class BaseType>
    Factory<BaseType>* Factory<BaseType>::GetInstance()
    {
        static Factory<BaseType> factory;
        return &factory;
    }

    template <class BaseType>
    template <class SubType>
    bool Factory<BaseType>::Register(std::string type)
    {
        if (!m_factorys[type])
            m_factorys[type] = &GenericFactory<BaseType, SubType>;

        return true;
    }

    template <class BaseType>
    BaseType* Factory<BaseType>::Create(std::string type)
    {
        auto creator = m_factorys.find(type);

        if (creator == m_factorys.end())
            return nullptr;

        auto func = creator->second;

        return (BaseType*)func();
    }

} /* Namespace Vanir. */

#endif /* VANIR_FACTORY_H.*/
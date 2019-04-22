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

#ifndef VANIR_FACTORY_FACTORYREGISTER_H
#define VANIR_FACTORY_FACTORYREGISTER_H

#include <Vanir/Common.h>
#include <Vanir/Factory/Factory.h>

namespace Vanir
{
    template<class BaseType, class SubType>
    class FactoryRegister 
    {
    public:
        FactoryRegister(std::string type);
    };

    template <class BaseType, class SubType>
    FactoryRegister<BaseType, SubType>::FactoryRegister(std::string type)
    {
        Factory<BaseType>::GetInstance()->template Register<SubType>(type);
    }

} /* Namespace Vanir. */

#define VANIR_FACTORY_REGISTER(BASETYPE, SUBTYPE, TYPENAME) \
    static ::Vanir::FactoryRegister<BASETYPE, SUBTYPE> factoryRegistration_##SUBTYPE(TYPENAME);

#endif /* VANIR_FACTORY_FACTORYREGISTER_H. */

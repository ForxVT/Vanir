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

#include <Vanir/Common.h>

namespace Vanir
{
    template <class BaseType, class SubType, typename ...Args>
    static std::unique_ptr<BaseType> GenericFactory(Args&&... args)
    {
        return std::make_unique<SubType>(args...);
    }
    
    template <class BaseType>
    class VANIR_EXPORT Factory
    {
    public:
        template<class SubType, typename ...Args>
        static void Register(const std::string &typeName)
        {
            auto instance = GetInstance();
            
            if (instance->m_registry.find(typeName) == instance->m_registry.end())
                instance->m_registry[typeName] = reinterpret_cast<void*>(GenericFactory<BaseType, SubType, Args...>);
        }
    
        template <typename ...Args>
        static std::unique_ptr<BaseType> Create(const std::string &type, Args&&... args)
        {
            auto instance = GetInstance();
            
            auto constructor = instance->m_registry.find(type);
        
            if (constructor == instance->m_registry.end())
                return nullptr;
        
            typedef std::unique_ptr<BaseType> (*create_type)(Args...);
        
            auto func = reinterpret_cast<create_type>(constructor->second);
        
            return func(args...);
        }
        
    private:
        static std::shared_ptr<Factory<BaseType>> GetInstance()
        {
            static std::shared_ptr<Factory<BaseType>> factory = std::make_shared<Factory<BaseType>>();
        
            return factory;
        }
        
        std::unordered_map<std::string, void*> m_registry;
    };
    
    template<class BaseType, class SubType, typename ...Args>
    class VANIR_EXPORT FactoryRegister
    {
    public:
        explicit FactoryRegister(const std::string &typeName)
        {
            Factory<BaseType>::template Register<SubType, Args...>(typeName);
        }
    };
    
#define FACTORY_REGISTER(BASETYPE, SUBTYPE, TYPENAME, ...) \
static ::Vanir::FactoryRegister<BASETYPE, SUBTYPE, ##__VA_ARGS__> factoryRegistration_##SUBTYPE(TYPENAME);
    
} /* Namespace Vanir. */

#endif /* VANIR_FACTORY_H.*/
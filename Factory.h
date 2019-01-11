#ifndef VANIR_FACTORY_H
#define VANIR_FACTORY_H

#include <Vanir/GenericFactory.h>
#include <map>
#include "Logger.h"

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
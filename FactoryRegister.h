#ifndef VANIR_FACTORYREGISTER_H
#define VANIR_FACTORYREGISTER_H

#include <Vanir/Factory.h>

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

#define FACTORY_REGISTER(BASETYPE, SUBTYPE, TYPENAME) \
    static ::Vanir::FactoryRegister<BASETYPE, SUBTYPE> factoryRegistration_##SUBTYPE(TYPENAME);

#endif /* VANIR_FACTORYREGISTER_H. */
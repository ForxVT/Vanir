#ifndef VANIR_GENERICFACTORY_H
#define VANIR_GENERICFACTORY_H

namespace Vanir
{
    template <class BaseType, class SubType>
    BaseType* GenericFactory()
    {
        return new SubType;
    }

} /* Namespace Vanir. */

#endif /* VANIR_GENERICFACTORY_H. */

#ifndef VANIR_FILE_H
#define VANIR_FILE_H

#include <string>

namespace Vanir
{
    struct File
    {
        char Type;
        std::string Path;
        std::string Name;
    };

} /* Namespace Vanir. */

#endif /* VANIR_FILE_H. */

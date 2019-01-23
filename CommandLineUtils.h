#ifndef VANIR_COMMANDLINEUTILS_H
#define VANIR_COMMANDLINEUTILS_H

#include <Vanir/CommandLineOption.h>

namespace Vanir
{
    class CommandLineUtils
    {
    public:
        static void DrawOptions(std::vector<Vanir::CommandLineOption> options);
    };

} /* Namespace Vanir. */

#endif /* VANIR_COMMANDLINEUTILS_H. */

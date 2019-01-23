#ifndef VANIR_COMMANDLINEOPTION_H
#define VANIR_COMMANDLINEOPTION_H

#include <Vanir/CommandLineOptionTypes.h>
#include <string>
#include <vector>
#include <map>

namespace Vanir
{
    struct CommandLineOption
    {
        explicit CommandLineOption(const std::string& name = std::string(),
                                   std::vector<std::string> description = std::vector<std::string>(),
                                   void (*functionToCall)() = nullptr,
                                   CommandLineOptionTypes type = CommandLineOptionTypes_Option,
                                   const std::string& supplement = std::string(),
                                   std::vector<CommandLineOption> subOptions = std::vector<CommandLineOption>());

        std::string Name;
        std::vector<std::string> Description;
        void (*FunctionToCall)();
        CommandLineOptionTypes Type;
        std::string Supplement;
        std::vector<CommandLineOption> SubOptions;
    };

} /* Namespace Vanir. */

#endif /* VANIR_COMMANDLINEOPTION_H. */

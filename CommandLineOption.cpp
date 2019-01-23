#include <Vanir/CommandLineOption.h>
#include <utility>

namespace Vanir
{
    CommandLineOption::CommandLineOption(const std::string &name, std::vector<std::string> description,
                                         void (*functionToCall)(),
                                         CommandLineOptionTypes type, const std::string &supplement,
                                         std::vector<CommandLineOption> subOptions) :
        Name(name), Description(std::move(description)), FunctionToCall(functionToCall), Type(type), Supplement(supplement), SubOptions(std::move(subOptions))
    {

    }
} /* Namespace Vanir. */
#include "CommandLineUtils.h"
#include <Vanir/Logger.h>

namespace Vanir
{
    void CommandLineUtils::DrawOptions(std::vector<Vanir::CommandLineOption> options)
    {
        VANIR_LOG("Options:")

        int longerLength = 0;

        for (const auto &i : options)
        {
            int longer = static_cast<int>(i.Name.length() + i.Supplement.length() +
                                          (i.Type == Vanir::CommandLineOptionTypes_Value && i.SubOptions.empty() ? 1 : 0));

            if (longer > longerLength)
                longerLength = longer + 2;
        }

        for (const auto &i : options)
        {
            int textLength = static_cast<int>(i.Name.length() + i.Supplement.length() +
                                              (i.Type == Vanir::CommandLineOptionTypes_Value && i.SubOptions.empty() ? 1 : 0));
            int difference = longerLength - textLength;
            std::string space = std::string();

            for (auto y = 0; y < difference; y++)
                space += " ";

            VANIR_ULOG("  ", i.Name, (i.Type == Vanir::CommandLineOptionTypes_Value && i.SubOptions.empty() ? "=" : ""), i.Supplement, space, i.Description[0])

            space = std::string();

            for (auto y = 0; y < difference + textLength; y++)
                space += " ";

            for (int y = 1; y < i.Description.size(); y++)
                VANIR_ULOG("  ", space, i.Description[y]);

            for (const auto &y : i.SubOptions)
            {
                textLength = static_cast<int>(y.Name.length());
                difference = longerLength - textLength - 3;

                space = std::string();

                for (auto z = 0; z < difference; z++)
                    space += " ";

                VANIR_ULOG("    =", y.Name, space, "  ", y.Description[0])

                space = std::string();

                for (auto z = 0; z < difference + textLength; z++)
                    space += " ";

                for (int z = 1; z < y.Description.size(); z++)
                    VANIR_ULOG("     ", space, "  ", y.Description[z]);
            }
        }
    }

} /* Namespace Vanir. */
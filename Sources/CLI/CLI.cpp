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

#include <Vanir/CLI/CLI.h>
#include <Vanir/String/String.h>
#include <Vanir/Logger/Logger.h>
#ifdef __unix
#include <cstring>
#endif

namespace Vanir
{
    void CLI::ParseArguments(const int argc, char **argv, std::vector<Vanir::Argument> arguments, bool log)
    {
        std::string tempArgv;

        for (int i = 1; i < argc; i++)
        {
            tempArgv = argv[i];
            bool found = false;

            for (auto y : arguments)
            {
                if (y.Type == Vanir::ArgumentType_Argument)
                {
                    if (!strcmp(tempArgv.c_str(), y.Name.c_str()))
                    {
                        y.FunctionToCall(GetValueFromPassedArgument(tempArgv));

                        found = true;

                        break;
                    }
                }
                else
                {
                    if (tempArgv.rfind(y.Name + "=", 0) == 0)
                    {
                        if (tempArgv.size() > y.Name.size() + 1)
                        {
                            y.FunctionToCall(GetValueFromPassedArgument(tempArgv));

                            found = true;

                            break;
                        }
                        else
                        {
                            if (log)
                            {
                                ULOG_WARNING("Empty value passed for argument '", y.Name, "'")
                            }
                        }
                    }
                }
            }

            if (!found && log)
            {
                if (std::string(argv[i]).rfind('-', 0) == 0)
                {
                    ULOG_WARNING("Cannot find argument '", tempArgv, "'")
                    ULOG_WARNING("Did you mean '", FindNearestArgument(tempArgv, arguments), "' ?")
                }
            }
        }
    }

    std::vector<std::string> CLI::DrawOptions(std::vector<Vanir::Argument> options)
    {
        std::vector<std::string> output;

        output.emplace_back("Options:");

        int longerLength = 0;

        for (const auto &i : options)
        {
            int longer = static_cast<int>(i.Name.length() + i.Supplement.length() +
                                          (i.Type == Vanir::ArgumentType_Value && i.SubOptions.empty() ? 1 : 0));

            if (longer > longerLength)
                longerLength = longer + 2;
        }

        for (const auto &i : options)
        {
            int textLength = static_cast<int>(i.Name.length() + i.Supplement.length() +
                                              (i.Type == Vanir::ArgumentType_Value && i.SubOptions.empty() ? 1 : 0));
            int difference = longerLength - textLength;
            std::string space = std::string();

            for (auto y = 0; y < difference; y++)
                space += " ";

            output.emplace_back("  " + i.Name + (i.Type == Vanir::ArgumentType_Value && i.SubOptions.empty() ? "=" : "") + i.Supplement + space + i.Description[0]);

            space = std::string();

            for (auto y = 0; y < difference + textLength; y++)
                space += " ";

            for (int y = 1; y < int(i.Description.size()); y++)
                output.emplace_back("  " + space + i.Description[y]);

            for (const auto &y : i.SubOptions)
            {
                textLength = static_cast<int>(y.Name.length());
                difference = longerLength - textLength - 3;

                space = std::string();

                for (auto z = 0; z < difference; z++)
                    space += " ";

                output.emplace_back("    =" + y.Name + space + "  " + y.Description[0]);

                space = std::string();

                for (auto z = 0; z < difference + textLength; z++)
                    space += " ";

                for (int z = 1; z < int(y.Description.size()); z++)
                    output.emplace_back("     " + space + "  " + y.Description[z]);
            }
        }

        return output;
    }

    std::string CLI::GetValueFromPassedArgument(const std::string &argument)
    {
        auto optionName = argument.substr(0, argument.find('=') + 1);
        auto result = argument.substr(argument.find('=') + 1);

        if (result.empty())
            return std::string();
        else
            return result;
    }

    std::string CLI::FindNearestArgument(const std::string &argument, std::vector<Vanir::Argument> arguments)
    {
        int distance = -1;
        std::string nearest = std::string();

        for (const auto& y : arguments)
        {
            auto optionDistance = String::CalculateLevensteinDistance(y.Name, argument);

            if (optionDistance < distance || distance == -1)
            {
                distance = optionDistance;
                nearest = y.Name;
            }
        }

        return nearest;
    }

} /* Namespace Vanir. */
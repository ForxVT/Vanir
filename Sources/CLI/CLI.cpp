//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo.pro@gmail.com>                       //
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

#ifdef __unix
#include <cstring>
#endif
#include <Vanir/CLI/CLI.h>
#include <Vanir/String/String.h>
#include <Vanir/Logger/Logger.h>

namespace Vanir {
    std::string CLI::ParseArguments(const int argc, char **argv, const std::vector<Vanir::Argument>& arguments, bool log) {
        std::string tempArgv;
        
        for (int i = 1; i < argc; i++) {
            tempArgv = argv[i];
            bool found = false;

            for (const auto& y : arguments) {
                if (y.Type == Vanir::ArgumentType_Argument) {
                    for (const auto& w : y.Names) {
                        if (!strcmp(tempArgv.c_str(), w.c_str())) {
                            y.FunctionToCall(GetValueFromPassedArgument(tempArgv));
        
                            found = true;
        
                            break;
                        }
                    }
                }
                else {
                    for (const auto& w : y.Names) {
                        if (tempArgv.rfind(w + "=", 0) == 0) {
                            if (tempArgv.size() > w.size() + 1) {
                                y.FunctionToCall(GetValueFromPassedArgument(tempArgv));
            
                                found = true;
            
                                break;
                            }
                            else {
                                if (log) {
                                    ULOG_WARNING("Empty value passed for argument '", w, "'")
                                }
                            }
                        }
                    }
                }
            }

            if (!found && log) {
                if (std::string(argv[i]).rfind('-', 0) == 0) {
                    ULOG_WARNING("Cannot find argument '", tempArgv, "'")
                    ULOG_WARNING("Did you mean '", FindNearestArgument(tempArgv, arguments), "' ?")
                }
            }
        }
        
        if (argc >= 2 && std::string(argv[argc - 1]).rfind('-', 0) != 0) {
            return argv[argc - 1];
        }
        
        return std::string();
    }

    std::vector<std::string> CLI::DrawOptions(const std::vector<Vanir::Argument>& options) {
        int longuestLength = 0;
        std::vector<int> lenghts = std::vector<int>();
        std::vector<std::string> output = std::vector<std::string>();
    
        output.emplace_back("Options:");
    
        for (int i = 0; i < options.size(); i++) {
            int nameLengths = 0;
        
            for (const auto&j : options[i].Names) {
                nameLengths += j.size();
            }
    
            lenghts.emplace_back(static_cast<int>(
                nameLengths +
                (!options[i].Supplement.empty() ? options[i].Names.size() +
                    options[i].Names.size() * options[i].Supplement.size() : 0) +
                (options[i].Names.size() > 1 ? (options[i].Names.size() - 1) * 2 : 0)));
        
            if (lenghts.at(i) > longuestLength) {
                longuestLength = lenghts.at(i);
            }
        }
        
        for (int i = 0; i < options.size(); i++) {
            int difference = longuestLength - lenghts.at(i);
            std::string space = std::string();
            std::string line = std::string();
            
            for (int j = 0; j < difference + 2; j++) {
                space += " ";
            }
            
            for (int j = 0; j < options[i].Names.size(); j++) {
                line += (j == 0 ? "  " : ", ") +
                    options[i].Names[j] + (!options[i].Supplement.empty() ? (options[i].Names[j].rfind("--", 0) == 0 ? "=" : " ") + options[i].Supplement : "");
    
                if (j == options[i].Names.size() - 1) {
                    line += space + options[i].Description[0];
                }
            }
            
            output.emplace_back(line);
            space = std::string();
            line = "  ";
    
            for (int j = 0; j < difference + lenghts.at(i) + 2; j++) {
                space += " ";
            }
            
            for (int j = 1; j < options[i].Description.size(); j++) {
                line += space + options[i].Description[j];
    
                output.emplace_back(line);
            }
    
            for (const auto& subOption : options[i].SubOptions) {
                difference = longuestLength - (int)(subOption.Names[0].size() + 1);
                space = std::string();
                line = "    =";
    
                for (int j = 0; j < difference + 2; j++) {
                    space += " ";
                }
                
                line += subOption.Names[0] + space + subOption.Description[0];
                
                output.emplace_back(line);
                space = std::string();
                line = "    ";
    
                for (int j = 0; j < difference + (int)(subOption.Names[0].size() + 1) + 2; j++) {
                    space += " ";
                }
    
                for (int j = 1; j < subOption.Description.size(); j++) {
                    line += space + subOption.Description[j];
    
                    output.emplace_back(line);
                }
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
        
        return result;
    }

    
    std::string CLI::FindNearestArgument(const std::string &argument, const std::vector<Vanir::Argument>& arguments)
    {
        int distance = -1;
        std::string nearest = std::string();

        for (const auto& y : arguments)
        {
            for (const auto& w : y.Names) {
                auto optionDistance = String::CalculateLevenshteinDistance(w, argument);
    
                if (optionDistance < distance || distance == -1)
                {
                    distance = optionDistance;
                    nearest = w;
                }
            }
        }

        return nearest;
    }

} /* Namespace Vanir. */
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
    std::string CLI::ParseArguments(const int argc, char **argv, const std::vector<Vanir::Argument>& options, bool log) {
        std::string currentArgument;
        std::string lastArgument;
        std::vector<std::string> optionNotFound = std::vector<std::string>();
        
        for (int i = 1; i < argc; i++) {
            currentArgument = argv[i];
            lastArgument = currentArgument;
            
            if (!Vanir::String::StartsWith(currentArgument, "--") && !Vanir::String::StartsWith(currentArgument, "-")) {
                if (log) {
                    PrintNotFound(optionNotFound, options);
                }
                
                return argv[i];
            }
            
            bool argumentFound = false;
            bool errorOccured = false;
    
            if (Vanir::String::StartsWith(currentArgument, "--")) {
                if (currentArgument.size() > 2) {
                    for (const auto& j : options) {
                        for (const auto& k : j.Names) {
                            if (j.Type == Vanir::ArgumentType_Argument &&
                                currentArgument == k) {
                                j.FunctionToCall("");
                    
                                argumentFound = true;
                    
                                break;
                            } else if (Vanir::String::StartsWith(currentArgument, k + "=")) {
                                if (currentArgument.size() > k.size() + 1) {
                                    j.FunctionToCall(currentArgument.substr(currentArgument.find('=') + 1));
                        
                                    argumentFound = true;
                        
                                    break;
                                } else {
                                    errorOccured = true;
                        
                                    if (log) {
                                        ULOG_WARNING("Empty value passed for argument '", k, "'.")
                                    }
                                }
                            }
                        }
                    }
    
                    if (!argumentFound && !errorOccured) {
                        optionNotFound.emplace_back(lastArgument);
                    }
                } else {
                    errorOccured = true;
    
                    if (log) {
                        ULOG_WARNING("Empty option double hyphen.");
                    }
                }
            } else {
                if (currentArgument.size() > 1) {
                    for (int l = 1; l < currentArgument.size(); l++) {
                        std::string argument = "-" + currentArgument.substr(l, 1);
                        lastArgument = argument;
    
                        for (const auto& j : options) {
                            for (const auto& k : j.Names) {
                                if (j.Type == Vanir::ArgumentType_Argument &&
                                    argument == k) {
                                    j.FunctionToCall("");
    
                                    argumentFound = true;
    
                                    break;
                                } else if (argument == k) {
                                    std::string nextArg = (i + 1 < argc ? argv[i + 1] : std::string());
                                    
                                    if (!nextArg.empty() &&
                                        nextArg.rfind("--", 0) != 0 &&
                                        nextArg.rfind('-', 0) != 0) {
                                        j.FunctionToCall(nextArg);
                                        ++i;
        
                                        argumentFound = true;
        
                                        break;
                                    } else {
                                        errorOccured = true;
        
                                        if (log) {
                                            ULOG_WARNING("Empty value passed for argument '", k, "'.")
                                        }
                                    }
                                }
                            }
                        }
    
                        if (!argumentFound && !errorOccured) {
                            optionNotFound.emplace_back(lastArgument);
                        }
                    }
                } else {
                    errorOccured = true;
    
                    if (log) {
                        ULOG_WARNING("Empty option hyphen.");
                    }
                }
            }
        }
    
        if (log) {
            PrintNotFound(optionNotFound, options);
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
    
        for (const auto & option : options) {
            for (int j = 0; j < option.SubOptions.size(); j++) {
                int length = (int)(option.SubOptions[j].Names[0].size() + option.Supplement.size() + 5);
                
                if (length > longuestLength) {
                    longuestLength = length;
                }
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
            
            std::string supplementSpaces = std::string();
    
            for (int j = 0; j < options[i].Supplement.size(); j++) {
                supplementSpaces += " ";
            }
    
            for (int j = 0; j < options[i].SubOptions.size(); j++) {
                difference = longuestLength - (int)(options[i].SubOptions[j].Names[0].size() + options[i].Supplement.size() + 3);
                space = std::string();
                line = "    ";
    
                for (int k = 0; k < difference + 2; k++) {
                    space += " ";
                }
                
                line += (j == 0 ? options[i].Supplement : supplementSpaces) + " = " + options[i].SubOptions[j].Names[0] + space + options[i].SubOptions[j].Description[0];
                
                output.emplace_back(line);
                space = std::string();
                line = "    ";
    
                for (int k = 0; k < difference + (int)(options[i].SubOptions[j].Names[0].size() + options[i].Supplement.size() + 3) + 2; k++) {
                    space += " ";
                }
    
                for (int k = 1; k < options[i].SubOptions[j].Description.size(); k++) {
                    line += space + options[i].SubOptions[j].Description[k];
    
                    output.emplace_back(line);
                }
            }
        }

        return output;
    }

    std::string CLI::GetValueFromPassedArgument(const std::string &argument)
    {
        std::string result = std::string();
    
        if (argument.rfind("--", 0) == 0) {
            if (argument.rfind('=') != std::string::npos) {
                result = argument.substr(argument.find('=') + 1);
            }
        } else {
            if (argument.rfind(' ') != std::string::npos) {
                result = argument.substr(argument.find(' ') + 1);
            }
        }
        
        if (result.empty()) {
            return std::string();
        }
        
        return result;
    }

    
    std::string CLI::FindNearestArgument(const std::string &argument, const std::vector<Vanir::Argument>& options)
    {
        int distance = -1;
        std::string nearest = std::string();

        for (const auto& y : options)
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
    
    void CLI::PrintNotFound(const std::vector<std::string>& notFounds, const std::vector<Vanir::Argument>& options) {
        for (const auto& argument : notFounds) {
            ULOG_WARNING("Cannot find argument '", argument, "'.");
            
            if (argument.size() > 2) {
                ULOG_WARNING("Did you mean '", FindNearestArgument(argument, options), "'?");
            }
        }
    }
    
} /* Namespace Vanir. */
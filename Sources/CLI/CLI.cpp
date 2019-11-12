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

#include <Vanir/CLI/CLI.h>
#include <Vanir/String/String.h>
#include <Vanir/Logger/Logger.h>

namespace Vanir {
    CLIParsingResult CLI::parse(const int argc, char **argv,
        const std::vector<Vanir::CLIOption>& optionsList, bool logErrors) {
        CLIParsingResult result;
        std::string currentArgument;
        std::string lastArgument;
        std::vector<std::string> optionNotFound = std::vector<std::string>();
        
        for (int i = 1; i < argc; i++) {
            currentArgument = argv[i];
            lastArgument = currentArgument;
            
            if (!Vanir::String::StartsWith(currentArgument, "--") && !Vanir::String::StartsWith(currentArgument, "-")) {
                if (logErrors) {
                    printUnknownOptions(optionNotFound, optionsList);
                }
    
                result.result = argv[i];
                
                return result;
            }
            
            bool argumentFound = false;
            bool errorOccured = false;
    
            if (Vanir::String::StartsWith(currentArgument, "--")) {
                if (currentArgument.size() > 2) {
                    for (const auto& j : optionsList) {
                        for (const auto& k : j.Names) {
                            if (j.Type == Vanir::CLIOptionType_Option &&
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
                                    result.errors.emplace_back(CLIParsingError_OptionEmptyArgument);
                        
                                    if (logErrors) {
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
                    result.errors.emplace_back(CLIParsingError_OptionEmptyDoubleHyphen);
    
                    if (logErrors) {
                        ULOG_WARNING("Empty option double hyphen.");
                    }
                }
            } else {
                if (currentArgument.size() > 1) {
                    for (int l = 1; l < currentArgument.size(); l++) {
                        std::string argument = "-" + currentArgument.substr(l, 1);
                        lastArgument = argument;
    
                        for (const auto& j : optionsList) {
                            for (const auto& k : j.Names) {
                                if (j.Type == Vanir::CLIOptionType_Option &&
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
                                        result.errors.emplace_back(CLIParsingError_OptionEmptyArgument);
        
                                        if (logErrors) {
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
                    result.errors.emplace_back(CLIParsingError_OptionEmptyHyphen);
    
                    if (logErrors) {
                        ULOG_WARNING("Empty option hyphen.");
                    }
                }
            }
        }
    
        if (logErrors) {
            printUnknownOptions(optionNotFound, optionsList);
        }
        
        return result;
    }

    std::vector<std::string> CLI::getOptionsDescriptionList(const std::vector<Vanir::CLIOption>& optionsList) {
        int longuestLength = 0;
        std::vector<int> lenghts = std::vector<int>();
        std::vector<std::string> output = std::vector<std::string>();
    
        output.emplace_back("Options:");
    
        for (int i = 0; i < optionsList.size(); i++) {
            int nameLengths = 0;
        
            for (const auto&j : optionsList[i].Names) {
                nameLengths += j.size();
            }
    
            lenghts.emplace_back(static_cast<int>(
                nameLengths +
                (!optionsList[i].Supplement.empty() ? optionsList[i].Names.size() +
                    optionsList[i].Names.size() * optionsList[i].Supplement.size() : 0) +
                (optionsList[i].Names.size() > 1 ? (optionsList[i].Names.size() - 1) * 2 : 0)));
        
            if (lenghts.at(i) > longuestLength) {
                longuestLength = lenghts.at(i);
            }
        }
    
        for (const auto & option : optionsList) {
            for (int j = 0; j < option.SubOptions.size(); j++) {
                int length = (int)(option.SubOptions[j].Names[0].size() + option.Supplement.size() + 5);
                
                if (length > longuestLength) {
                    longuestLength = length;
                }
            }
        }
        
        for (int i = 0; i < optionsList.size(); i++) {
            int difference = longuestLength - lenghts.at(i);
            std::string space = std::string();
            std::string line = std::string();
            
            for (int j = 0; j < difference + 2; j++) {
                space += " ";
            }
            
            for (int j = 0; j < optionsList[i].Names.size(); j++) {
                line += (j == 0 ? "  " : ", ") +
                    optionsList[i].Names[j] +
                    (!optionsList[i].Supplement.empty() ?
                        (optionsList[i].Names[j].rfind("--", 0) == 0 ? "=" : " ") +optionsList[i].Supplement : "");
    
                if (j == optionsList[i].Names.size() - 1) {
                    line += space + optionsList[i].Description[0];
                }
            }
            
            output.emplace_back(line);
            space = std::string();
            line = "  ";
    
            for (int j = 0; j < difference + lenghts.at(i) + 2; j++) {
                space += " ";
            }
            
            for (int j = 1; j < optionsList[i].Description.size(); j++) {
                line += space + optionsList[i].Description[j];
    
                output.emplace_back(line);
            }
            
            std::string supplementSpaces = std::string();
    
            for (int j = 0; j < optionsList[i].Supplement.size(); j++) {
                supplementSpaces += " ";
            }
    
            for (int j = 0; j < optionsList[i].SubOptions.size(); j++) {
                difference = longuestLength -
                    (int)(optionsList[i].SubOptions[j].Names[0].size() + optionsList[i].Supplement.size() + 3);
                space = std::string();
                line = "    ";
    
                for (int k = 0; k < difference + 2; k++) {
                    space += " ";
                }
                
                line += (j == 0 ?
                    optionsList[i].Supplement :
                    supplementSpaces) + " = " + optionsList[i].SubOptions[j].Names[0] +
                        space + optionsList[i].SubOptions[j].Description[0];
                
                output.emplace_back(line);
                space = std::string();
                line = "    ";
    
                for (int k = 0;k < difference + (int)(optionsList[i].SubOptions[j].Names[0].size() +
                    optionsList[i].Supplement.size() + 3) + 2; k++) {
                    space += " ";
                }
    
                for (int k = 1; k < optionsList[i].SubOptions[j].Description.size(); k++) {
                    line += space + optionsList[i].SubOptions[j].Description[k];
    
                    output.emplace_back(line);
                }
            }
        }

        return output;
    }
    
    std::string CLI::findClosestOption(const std::string &option, const std::vector<Vanir::CLIOption>& optionsList) {
        int distance = -1;
        std::string nearest = std::string();

        for (const auto& y : optionsList) {
            for (const auto& w : y.Names) {
                auto optionDistance = String::CalculateLevenshteinDistance(w, option);
    
                if (optionDistance < distance || distance == -1) {
                    distance = optionDistance;
                    nearest = w;
                }
            }
        }

        return nearest;
    }
    
    void CLI::printUnknownOptions(const std::vector<std::string>& unknownOptions, const std::vector<Vanir::CLIOption>& optionsList) {
        for (const auto& argument : unknownOptions) {
            ULOG_WARNING("Cannot find argument '", argument, "'.");
            
            if (argument.size() > 2) {
                ULOG_WARNING("Did you mean '", findClosestOption(argument, optionsList), "'?");
            }
        }
    }
    
} /* Namespace Vanir. */

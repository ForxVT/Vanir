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

#ifndef VANIR_CLI_CLI_H
#define VANIR_CLI_CLI_H

#include <Vanir/Common.h>
#include <Vanir/CLI/CLIOption.h>
#include <Vanir/CLI/CLIParsingResult.h>

namespace Vanir {
    class CLI {
    public:
        static CLIParsingResult parse(int argc, char *argv[],
        	const std::vector<Vanir::CLIOption>& optionsList, bool logErrors = true);
        static std::vector<std::string> getOptionsDescriptionList(const std::vector<Vanir::CLIOption>& optionsList);
        static std::string findClosestOption(const std::string &option,
        	const std::vector<Vanir::CLIOption>& optionsList);

    private:
        static void printUnknownOptions(const std::vector<std::string>& unknownOptions,
        	const std::vector<Vanir::CLIOption>& optionsList);
        static bool detectError(CLIParsingError error, CLIParsingResult* result, bool logErrors);
    };

} /* Namespace Vanir. */

#endif /* VANIR_CLI_CLI_H. */

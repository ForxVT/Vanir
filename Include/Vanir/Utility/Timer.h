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

#ifndef VANIR_UTILITY_TIMER_H
#define VANIR_UTILITY_TIMER_H

#include <chrono>
#include <Vanir/Common.h>

namespace Vanir {
    /// Create a timer for querying high precision timers.
    class Timer {
    public:
        /// Constructor.
        Timer();
        /// Destructor.
        ~Timer();

        /// Reset the time.
        void reset();
        /// Return the current time in seconds.
        uint64_t getTimeInS() const;
        /// Return the current time in milliseconds.
        uint64_t getTimeInMS() const;
        /// Return the current time in microseconds.
        uint64_t getTimeInUS() const;
        /// Return the start time in seconds.
        uint64_t getStartTimeInS() const;
        /// Return the start time in milliseconds.
        uint64_t getStartTimeInMS() const;
        /// Return the start time in microseconds.
        uint64_t getStartTimeInUS() const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    };

} /* Namespace Vanir. */

#endif /* VANIR_UTILITY_TIMER_H. */

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

#include <Vanir/Utility/Timer.h>

namespace Vanir {
    Timer::Timer() {
        reset();
    }

    Timer::~Timer() = default;

    void Timer::reset() {
        m_startTime = std::chrono::high_resolution_clock::now();
    }

    uint64_t Timer::getTimeInS() const {
        auto currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = currentTime - m_startTime;

        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }

    uint64_t Timer::getTimeInMS() const {
        auto currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = currentTime - m_startTime;

        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    uint64_t Timer::getTimeInUS() const {
        auto currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = currentTime - m_startTime;

        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    uint64_t Timer::getStartTimeInS() const {
        std::chrono::nanoseconds startTimeNS = m_startTime.time_since_epoch();

        return std::chrono::duration_cast<std::chrono::seconds>(startTimeNS).count();
    }

    uint64_t Timer::getStartTimeInMS() const {
        std::chrono::nanoseconds startTimeNS = m_startTime.time_since_epoch();

        return std::chrono::duration_cast<std::chrono::milliseconds>(startTimeNS).count();
    }

    uint64_t Timer::getStartTimeInUS() const {
        std::chrono::nanoseconds startTimeNS = m_startTime.time_since_epoch();

        return std::chrono::duration_cast<std::chrono::microseconds>(startTimeNS).count();
    }

} /* Namespace Vanir. */

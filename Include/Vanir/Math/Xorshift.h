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

#ifndef VANIR_MATH_XORSHIFT_H
#define VANIR_MATH_XORSHIFT_H

#include <random>
#include <Vanir/Common.h>

namespace Vanir {
    /// Class to use the pseudorandom number generators Xorshift.
    class Xorshift {
    public:
        using result_type = uint32_t;

        /// Constructor.
        Xorshift();
        /// Constructor using std::random_device.
        explicit Xorshift(std::random_device &seed);
        /// Constructor using uint3_t.
        explicit Xorshift(uint32_t seed);
        /// Define the seed to use for the distribution.
        void seed(std::random_device &seed);
        /// Define the seed to use for the distribution.
        void seed(uint32_t seed);
        /// Advance internal state.
        void discard(unsigned long long n);
        /// Generates the next random number in the distribution.
        result_type operator()();
        /// Compares two distribution objects equality.
        friend bool operator==(Xorshift const &lhs, Xorshift const &rhs);
        /// Compares two distribution objects inequality.
        friend bool operator!=(Xorshift const &lhs, Xorshift const &rhs);
        /// Returns the minimum potentially generated value
        static constexpr result_type (min)() {
            return 0;
        }
        /// Returns the maximum potentially generated value
        static constexpr result_type (max)() {
            return UINT32_MAX;
        }

    private:
        uint64_t m_seed;
    };

} /* Namespace Vanir. */

#endif /* VANIR_MATH_XORSHIFT_H. */

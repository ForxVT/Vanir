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

#include <iostream>
#include <Vanir/Math/Xorshift.h>

namespace Vanir {
    Xorshift::Xorshift() : m_seed(0xc1f651c67c62c6e0ull) {

    }

    Xorshift::Xorshift(std::random_device &_seed) {
        seed(_seed);
    }

    Xorshift::Xorshift(uint32_t _seed) {
        seed(_seed);
    }

    void Xorshift::seed(std::random_device &rd) {
        m_seed = uint64_t(rd()) << 31 | uint64_t(rd());
    }

    void Xorshift::seed(uint32_t seed) {
        m_seed = seed;
    }

    void Xorshift::discard(unsigned long long n) {
        for (unsigned long long i = 0; i < n; ++i)
            operator()();
    }

    uint32_t Xorshift::operator()() {
        uint64_t result = m_seed * 0xd989bcacc137dcd5ull;

        m_seed ^= m_seed >> 11;
        m_seed ^= m_seed << 31;
        m_seed ^= m_seed >> 18;

        return result_type(result >> 32ull);
    }

    bool operator==(Xorshift const &lhs, Xorshift const &rhs) {
        return lhs.m_seed == rhs.m_seed;
    }

    bool operator!=(Xorshift const &lhs, Xorshift const &rhs) {
        return lhs.m_seed != rhs.m_seed;
    }

} /* Namespace Vanir. */

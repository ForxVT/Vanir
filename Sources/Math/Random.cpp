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

#include <chrono>
#include <Vanir/Math/Random.h>

namespace Vanir {
    Random::Random() {
        setSeed(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    }

    Random::Random(uint64_t seed) {
        setSeed(seed);
    }

    Random::~Random() = default;

    void Random::setSeed(uint64_t seed) {
        m_seed = seed;
        m_generator = Xorshift(m_seed);
    }

    uint64_t Random::getSeed() {
        return m_seed;
    }

    uint32_t Random::generate() {
        return generate(0, UINT32_MAX);
    }

    uint32_t Random::generate(uint32_t max) {
        return generate(0, max);
    }

    uint32_t Random::generate(uint32_t min, uint32_t max) {
        std::uniform_int_distribution<> distributor(min, max);

        return distributor(m_generator);
    }

    void Random::reset() {
        setSeed(m_seed);
    }

} /* Namespace Vanir. */

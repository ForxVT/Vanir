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

#ifndef VANIR_MODULE_MODULE_H
#define VANIR_MODULE_MODULE_H

#include <Vanir/Error/Error.h>

namespace Vanir {
    template<class T>
    class Module {
    public:
        Module(Module &&) = delete;
        Module(const Module &) = delete;
        
        Module &operator=(Module &&) = delete;
        Module &operator=(const Module &) = delete;
        
        static T &getInstance();
        static T *getInstancePtr();
        template<class ...Args>
        static void start(Args &&...args);
        template<class SubType, class ...Args>
        static void start(Args &&...args);
        static void shutdown();
        static bool isStarted();
        static bool isDestroyed();
    
    protected:
        Module() = default;
        virtual ~Module() = default;
        
        virtual void onStart();
        virtual void onShutdown();
        static T *&getInternalInstance();
        static bool &internalIsDestroyed();
        static bool &internalIsStarted();
    };
    
    template<class T>
    T &Module<T>::getInstance() {
        if (!internalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to access a module but it hasn't been started up yet.")
        }
        
        if (internalIsDestroyed()) {
            THROW_FATALERROR("FatalInternalException", "Trying to access a destroyed module.")
        }
        
        return *getInternalInstance();
    }
    
    template<class T>
    T *Module<T>::getInstancePtr() {
        if (!internalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to access a module but it hasn't been started up yet.")
        }
        
        if (internalIsDestroyed()) {
            THROW_FATALERROR("FatalInternalException", "Trying to access a destroyed module.")
        }
        
        return getInternalInstance();
    }
    
    template<class T>
    template<class... Args>
    void Module<T>::start(Args &&... args) {
        if (internalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to start an already started module.")
        }
        
        getInternalInstance() = new T(std::forward<Args>(args)...);
        internalIsStarted() = true;
        
        ((Module*)getInternalInstance())->onStart();
    }
    
    template<class T>
    template<class SubType, class... Args>
    void Module<T>::start(Args &&... args) {
        static_assert(std::is_base_of<T, SubType>::value,
                      "Provided type is not derived from type the module is initialized with.");
        
        if (internalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to start an already started module.")
        }
        
        getInternalInstance() = new SubType(std::forward<Args>(args)...);
        internalIsStarted() = true;
        
        ((Module*)getInternalInstance())->onStart();
    }
    
    template<class T>
    void Module<T>::shutdown() {
        if (internalIsDestroyed()) {
            THROW_FATALERROR("FatalInternalException", "Trying to shutdown an already shutdown module.")
        }
        
        if (!internalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to shut down a module which was never started.")
        }
        
        ((Module*)getInternalInstance())->onShutdown();
        
        delete getInternalInstance();
        
        internalIsDestroyed() = true;
    }
    
    template<class T>
    bool Module<T>::isStarted() {
        return internalIsStarted() && !internalIsDestroyed();
    }
    
    template<class T>
    bool Module<T>::isDestroyed() {
        return internalIsStarted() && internalIsDestroyed();
    }
    
    template<class T>
    void Module<T>::onStart() {
    
    }
    
    template<class T>
    void Module<T>::onShutdown() {
    
    }
    
    template<class T>
    T *&Module<T>::getInternalInstance() {
        static T *inst = nullptr;
        
        return inst;
    }
    
    template<class T>
    bool &Module<T>::internalIsDestroyed() {
        static bool inst = false;
        
        return inst;
    }
    
    template<class T>
    bool &Module<T>::internalIsStarted() {
        static bool inst = false;
        
        return inst;
    }
    
} /* Namespace Vanir. */

#endif /* VANIR_MODULE_MODULE_H. */
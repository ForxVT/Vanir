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
        
        static T &GetInstance();
        static T *GetInstancePtr();
        template<class ...Args>
        static void Start(Args &&...args);
        template<class SubType, class ...Args>
        static void Start(Args &&...args);
        static void Shutdown();
        static bool IsStarted();
        static bool IsDestroyed();
    
    protected:
        Module() = default;
        virtual ~Module() = default;
        virtual void OnStart();
        virtual void OnShutdown();
        static T *&GetInternalInstance();
        static bool &InternalIsDestroyed();
        static bool &InternalIsStarted();
    };
    
    template<class T>
    T &Module<T>::GetInstance() {
        if (!InternalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to access a module but it hasn't been started up yet.")
        }
        
        if (InternalIsDestroyed()) {
            THROW_FATALERROR("FatalInternalException", "Trying to access a destroyed module.")
        }
        
        return *GetInternalInstance();
    }
    
    template<class T>
    T *Module<T>::GetInstancePtr() {
        if (!InternalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to access a module but it hasn't been started up yet.")
        }
        
        if (InternalIsDestroyed()) {
            THROW_FATALERROR("FatalInternalException", "Trying to access a destroyed module.")
        }
        
        return GetInternalInstance();
    }
    
    template<class T>
    template<class... Args>
    void Module<T>::Start(Args &&... args) {
        if (InternalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to start an already started module.")
        }
        
        GetInternalInstance() = new T(std::forward<Args>(args)...);
        InternalIsStarted() = true;
        
        ((Module *) GetInternalInstance())->OnStart();
    }
    
    template<class T>
    template<class SubType, class... Args>
    void Module<T>::Start(Args &&... args) {
        static_assert(std::is_base_of<T, SubType>::value,
                      "Provided type is not derived from type the module is initialized with.");
        
        if (InternalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to start an already started module.")
        }
        
        GetInternalInstance() = new SubType(std::forward<Args>(args)...);
        InternalIsStarted() = true;
        
        ((Module *) GetInternalInstance())->OnStart();
    }
    
    template<class T>
    void Module<T>::Shutdown() {
        if (InternalIsDestroyed()) {
            THROW_FATALERROR("FatalInternalException", "Trying to shutdown an already shutdown module.")
        }
        
        if (!InternalIsStarted()) {
            THROW_FATALERROR("FatalInternalException", "Trying to shut down a module which was never started.")
        }
        
        ((Module *) GetInternalInstance())->OnShutdown();
        
        delete GetInternalInstance();
        
        InternalIsDestroyed() = true;
    }
    
    template<class T>
    bool Module<T>::IsStarted() {
        return InternalIsStarted() && !InternalIsDestroyed();
    }
    
    template<class T>
    bool Module<T>::IsDestroyed() {
        return InternalIsStarted() && InternalIsDestroyed();
    }
    
    template<class T>
    void Module<T>::OnStart() {
    
    }
    
    template<class T>
    void Module<T>::OnShutdown() {
    
    }
    
    template<class T>
    T *&Module<T>::GetInternalInstance() {
        static T *inst = nullptr;
        return inst;
    }
    
    template<class T>
    bool &Module<T>::InternalIsDestroyed() {
        static bool inst = false;
        return inst;
    }
    
    template<class T>
    bool &Module<T>::InternalIsStarted() {
        static bool inst = false;
        return inst;
    }
    
} /* Namespace Vanir. */

#endif /* VANIR_MODULE_MODULE_H. */
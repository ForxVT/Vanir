//==================================================================================//
//                                                                                  //
//  Copyright (c) 2019 Hugo Kindel <kindelhugo@gmail.com>                           //
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

#ifndef VANIR_EVENT_H
#define VANIR_EVENT_H

#include <Vanir/Common.h>
#include <Vanir/Event/EventHandle.h>
#include <functional>

namespace Vanir
{
    template <class RetType, class... Args>
    class VANIR_EXPORT EventType
    {
        struct EventConnectionData : ConnectionData
        {
        public:
            void Deactivate() override
            {
                Function = nullptr;

                ConnectionData::Deactivate();
            }

            std::function<RetType(Args...)> Function;
        };

    public:
        EventType();
        ~EventType();

        EventHandle Connect(std::function<RetType(Args...)> func);
        void Clear();
        bool Empty() const;

        void operator() (Args... args);

    private:
        std::shared_ptr<EventInternalData> m_internalData;
    };

    template<class RetType, class... Args>
    EventType<RetType, Args...>::EventType() :
        m_internalData(std::make_shared<EventInternalData>())
    {

    }

    template<class RetType, class... Args>
    EventType<RetType, Args...>::~EventType()
    {
        Clear();
    }

    template<class RetType, class... Args>
    EventHandle EventType<RetType, Args...>::Connect(std::function<RetType(Args...)> func)
    {
        EventConnectionData* connData = nullptr;

        if (m_internalData->FreeConnections != nullptr)
        {
            connData = static_cast<EventConnectionData*>(m_internalData->FreeConnections);
            m_internalData->FreeConnections = connData->Next;

            new (connData)EventConnectionData();

            if (connData->Next != nullptr)
                connData->Next->Previous = nullptr;

            connData->IsActive = true;
        }

        if (connData == nullptr)
            connData = new EventConnectionData();

        if(m_internalData->IsCurrentlyTriggering)
        {
            connData->Previous = m_internalData->NewConnections;

            if (m_internalData->NewConnections != nullptr)
                m_internalData->NewConnections->Next = connData;

            m_internalData->NewConnections = connData;
        }
        else
        {
            m_internalData->Connect(connData);
        }

        connData->Function = func;

        return EventHandle(m_internalData, connData);
    }

    template<class RetType, class... Args>
    void EventType<RetType, Args...>::Clear()
    {
        m_internalData->Clear();
    }

    template<class RetType, class... Args>
    bool EventType<RetType, Args...>::Empty() const
    {
        return m_internalData->Connections == nullptr;
    }

    template<class RetType, class... Args>
    void EventType<RetType, Args...>::operator()(Args... args)
    {
        std::shared_ptr<EventInternalData> internalData = m_internalData;

        internalData->IsCurrentlyTriggering = true;

        auto* conn = static_cast<EventConnectionData*>(internalData->Connections);
        while (conn != nullptr)
        {
            auto* next = static_cast<EventConnectionData*>(conn->Next);

            if (conn->Function != nullptr)
                conn->Function(std::forward<Args>(args)...);

            conn = next;
        }

        internalData->IsCurrentlyTriggering = false;

        if(internalData->NewConnections != nullptr)
        {
            ConnectionData* lastNewConnection = internalData->NewConnections;
            while (lastNewConnection != nullptr)
                lastNewConnection = lastNewConnection->Next;

            internalData->NewConnections = nullptr;
        }
    }

    template <typename Signature>
    class Event;

    template <class RetType, class... Args>
    class Event<RetType(Args...) > : public EventType <RetType, Args...>
    {

    };

} /* Namespace Vanir. */

#endif /* VANIR_EVENT_H. */

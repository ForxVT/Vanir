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

#include <Vanir/Event/EventHandle.h>

namespace Vanir
{
    EventHandle::EventHandle(std::shared_ptr<EventInternalData> eventData, ConnectionData *connection)
            : m_eventData(std::move(eventData)), m_connection(connection)
    {
        m_connection->HandleLinks++;
    }

    EventHandle::~EventHandle()
    {
        if (m_connection != nullptr)
            m_eventData->FreeHandle(m_connection);
    }

    void EventHandle::Disconnect()
    {
        if (m_connection != nullptr)
        {
            m_eventData->Disconnect(m_connection);

            m_eventData = nullptr;
            m_connection = nullptr;
        }
    }

    EventHandle &EventHandle::operator=(const EventHandle &rhs)
    {
        m_connection = rhs.m_connection;
        m_eventData = rhs.m_eventData;

        if (m_connection != nullptr)
            m_connection->HandleLinks++;

        return *this;
    }

    EventHandle::operator int Boolean::*() const
    {
        return (m_connection != nullptr ? &Boolean::Member : nullptr);
    }
} /* Namespace Vanir. */

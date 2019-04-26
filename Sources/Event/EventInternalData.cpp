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

#include <Vanir/Event/EventInternalData.h>

namespace Vanir
{
    EventInternalData::~EventInternalData()
    {
        ConnectionData* conn = Connections;

        while (conn != nullptr)
        {
            ConnectionData* next = conn->Next;

            free(conn);

            conn = next;
        }

        conn = FreeConnections;

        while (conn != nullptr)
        {
            ConnectionData* next = conn->Next;

            free(conn);

            conn = next;
        }

        conn = NewConnections;

        while (conn != nullptr)
        {
            ConnectionData* next = conn->Next;

            free(conn);

            conn = next;
        }
    }

    void EventInternalData::Connect(ConnectionData *conn)
    {
        conn->Previous = LastConnection;

        if(LastConnection != nullptr)
            LastConnection->Next = conn;

        LastConnection = conn;

        if(Connections == nullptr)
            Connections = conn;
    }

    void EventInternalData::Disconnect(ConnectionData *conn)
    {
        conn->Deactivate();
        conn->HandleLinks--;

        if (conn->HandleLinks == 0)
            free(conn);
    }

    void EventInternalData::Clear()
    {
        ConnectionData* conn = Connections;
        while (conn != nullptr)
        {
            ConnectionData* next = conn->Next;
            conn->Deactivate();

            if (conn->HandleLinks == 0)
                free(conn);

            conn = next;
        }

        Connections = nullptr;
        LastConnection = nullptr;
    }

    void EventInternalData::FreeHandle(ConnectionData *conn)
    {
        conn->HandleLinks--;

        if (conn->HandleLinks == 0 && !conn->IsActive)
            free(conn);
    }

    void EventInternalData::Free(ConnectionData *conn)
    {
        if (conn->Previous != nullptr)
            conn->Previous->Next = conn->Next;
        else
            Connections = conn->Next;

        if (conn->Next != nullptr)
            conn->Next->Previous = conn->Previous;
        else
            LastConnection = conn->Previous;

        conn->Previous = nullptr;
        conn->Next = nullptr;

        if (FreeConnections != nullptr)
        {
            conn->Next = FreeConnections;
            FreeConnections->Previous = conn;
        }

        FreeConnections = conn;
        FreeConnections->~ConnectionData();

    }
} /* Namespace Vanir. */


#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

    URHO3D_EVENT(E_TCPDATA, TcpData)
    {
        URHO3D_PARAM(P_DATA, Data);      // VectorBuffer
    }

    URHO3D_EVENT(E_TCPERROR, TcpErr)
    {
        URHO3D_PARAM(P_ERROR, Error);      // String
    }

    URHO3D_EVENT(E_TCPCONNECTED, TcpConnected)
    {
    }

    URHO3D_EVENT(E_REQUESTOK, RequestOK)
    {
        URHO3D_PARAM(P_REQUEST, Request);      // HttpRequest
        URHO3D_PARAM(P_FILEPATH, Filepath);      // FilePath, for download
        URHO3D_PARAM(P_BUFFER, Buffer);      // VectorBuffer, for get
    }

    URHO3D_EVENT(E_REQUESTERR, RequestErr)
    {
        URHO3D_PARAM(P_MSG, Message);      // String
    }
}

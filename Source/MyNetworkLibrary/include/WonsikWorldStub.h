#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MakeUnique.h"
#include "MyStlContainer.h"
#include "WonsikWorldPKT_TYPE.h"
class WonsikWorldStub
{
public:
	bool PacketProcSendChatMessage( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcSendChatMessage( SessionInfo sessionInfo, String id, String chatMessage ){}

	bool PacketProcHeartBeat( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcHeartBeat( SessionInfo sessionInfo ){}

	bool PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf);
};

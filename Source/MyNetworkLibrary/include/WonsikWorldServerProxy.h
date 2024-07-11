#pragma once
#include "Session.h"
#include "IOCPServer.h"
#include "MyStlContainer.h"
class WonsikWorldServerProxy
{
private:
	IOCPServer* _pServer;
public:
	void SendChatMessage(SessionInfo sessionInfo, INT64 accountNo, String id, String chatMessage, bool bDisconnect = false );
	void SendChatMessage(List<SessionInfo>& sessionInfoList, INT64 accountNo, String id, String chatMessage, bool bDisconnect = false);

	void HeartBeat(SessionInfo sessionInfo, bool bDisconnect = false );
	void HeartBeat(List<SessionInfo>& sessionInfoList, bool bDisconnect = false);

	WonsikWorldServerProxy(IOCPServer* pServer)
	{
		_pServer=pServer;
	}
};

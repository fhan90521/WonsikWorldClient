#pragma once
#include "Session.h"
#include "IOCPClient.h"
#include "MyStlContainer.h"
class WonsikWorldClientProxy
{
private:
IOCPClient* _pClient;
public:
	void SendChatMessage(SessionInfo sessionInfo, String id, String chatMessage, bool bDisconnect = false );
	void SendChatMessage(List<SessionInfo>& sessionInfoList, String id, String chatMessage, bool bDisconnect = false);

	void HeartBeat(SessionInfo sessionInfo, bool bDisconnect = false );
	void HeartBeat(List<SessionInfo>& sessionInfoList, bool bDisconnect = false);

	WonsikWorldClientProxy(IOCPClient* pClient=nullptr)
	{
		_pClient=pClient;
	}
};

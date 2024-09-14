#pragma once
#include "Network/Session.h"
#include "Container/MyStlContainer.h"
class WWVector2D;
class WonsikWorldClientProxy
{
private:
	class IOCPClient* _pClient;
public:
	void EnterGame_CS(const WString& nickName, bool bDisconnect = false);
	void EnterGame_SC(short enterGameResult, LONG64 playerID, bool bDisconnect = false);
	void CreateMyCharacter_SC(short mapID, const WWVector2D& dirVec, const WWVector2D& location, bool bDisconnect = false);
	void CreateOtherCharacter_SC(short mapID, LONG64 playerID, const WString& nickName, const WWVector2D& dirVec, const WWVector2D& location, bool bDisconnect = false);
	void DeleteCharacter_SC(short mapID, LONG64 playerID, bool bDisconnect = false);
	void ChangeMap_CS(short beforeMapID, short afterMapID, bool bDisconnect = false);
	void ChangeMap_SC(short beforeMapID, short afterMapID, bool bDisconnect = false);
	void SendChatMessage_CS(short mapID, const WString& chatMessage, bool bDisconnect = false);
	void SendChatMessage_SC(short mapID, LONG64 playerID, const WString& chatMessage, bool bDisconnect = false);
	void MoveMyCharacter_CS(short mapID, const WWVector2D& destination, bool bDisconnect = false);
	void MoveMyCharacter_SC(short mapID, const Vector<WWVector2D>& destinations, bool bDisconnect = false);
	void MoveOtherCharacter_SC(short mapID, LONG64 playerID, const Vector<WWVector2D>& destinations, bool bDisconnect = false);
	void HeartBeat_CS(bool bDisconnect = false);
	WonsikWorldClientProxy(class IOCPClient* pClient=nullptr)
	{
		_pClient = pClient;
	}
};

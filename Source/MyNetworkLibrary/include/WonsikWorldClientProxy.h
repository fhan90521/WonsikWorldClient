#pragma once
#include "Session.h"
#include "IOCPClient.h"
#include "MyStlContainer.h"
class WonsikWorldClientProxy
{
private:
	IOCPClient* _pClient;
public:
	void EnterGame_CS(WString& nickName, bool bDisconnect = false);
	void EnterGame_SC(short enterGameResult, LONG64 playerID, bool bDisconnect = false);
	void CreateMyCharacter_SC(short mapID, float dirX, float dirY, float locationX, float locationY, bool bDisconnect = false);
	void CreateOtherCharacter_SC(short mapID, LONG64 playerID, WString& nickName, float dirX, float dirY, float locationX, float locationY, bool bDisconnect = false);
	void DeleteCharacter_SC(short mapID, LONG64 playerID, bool bDisconnect = false);
	void ChangeMap_CS(short beforeMapID, short afterMapID, bool bDisconnect = false);
	void ChangeMap_SC(short beforeMapID, short afterMapID, bool bDisconnect = false);
	void SendChatMessage_CS(short mapID, WString& chatMessage, bool bDisconnect = false);
	void SendChatMessage_SC(short mapID, LONG64 playerID, WString& chatMessage, bool bDisconnect = false);
	void MoveMyCharacter_CS(short mapID, float destinationX, float destinationY, bool bDisconnect = false);
	void MoveMyCharacter_SC(short mapID, Vector<float>& destinationsX, Vector<float>& destinationsY, bool bDisconnect = false);
	void MoveOtherCharacter_SC(short mapID, LONG64 playerID, Vector<float>& destinationsX, Vector<float>& destinationsY, bool bDisconnect = false);
	void HeartBeat_CS(bool bDisconnect = false);
	WonsikWorldClientProxy(IOCPClient* pClient = nullptr)
	{
		_pClient = pClient;
	}
};

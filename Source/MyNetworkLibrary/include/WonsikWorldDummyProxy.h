#pragma once
#include "Session.h"
#include "IOCPDummyClient.h"
#include "MyStlContainer.h"
class WonsikWorldDummyProxy
{
private:
	IOCPDummyClient* _pDummy;
public:
	void EnterGame_CS(SessionInfo sessionInfo, WString& nickName, bool bDisconnect = false );
	void EnterGame_CS(List<SessionInfo>& sessionInfoList, WString& nickName, bool bDisconnect = false);

	void EnterGame_SC(SessionInfo sessionInfo, short enterGameResult, LONG64 playerID, bool bDisconnect = false );
	void EnterGame_SC(List<SessionInfo>& sessionInfoList, short enterGameResult, LONG64 playerID, bool bDisconnect = false);

	void CreateMyCharacter_SC(SessionInfo sessionInfo, short mapID, float dirX, float dirY, float locationX, float locationY, bool bDisconnect = false );
	void CreateMyCharacter_SC(List<SessionInfo>& sessionInfoList, short mapID, float dirX, float dirY, float locationX, float locationY, bool bDisconnect = false);

	void CreateOtherCharacter_SC(SessionInfo sessionInfo, short mapID, LONG64 playerID, WString& nickName, float dirX, float dirY, float locationX, float locationY, bool bDisconnect = false );
	void CreateOtherCharacter_SC(List<SessionInfo>& sessionInfoList, short mapID, LONG64 playerID, WString& nickName, float dirX, float dirY, float locationX, float locationY, bool bDisconnect = false);

	void DeleteCharacter_SC(SessionInfo sessionInfo, short mapID, LONG64 playerID, bool bDisconnect = false );
	void DeleteCharacter_SC(List<SessionInfo>& sessionInfoList, short mapID, LONG64 playerID, bool bDisconnect = false);

	void ChangeMap_CS(SessionInfo sessionInfo, short beforeMapID, short afterMapID, bool bDisconnect = false );
	void ChangeMap_CS(List<SessionInfo>& sessionInfoList, short beforeMapID, short afterMapID, bool bDisconnect = false);

	void ChangeMap_SC(SessionInfo sessionInfo, short beforeMapID, short afterMapID, bool bDisconnect = false );
	void ChangeMap_SC(List<SessionInfo>& sessionInfoList, short beforeMapID, short afterMapID, bool bDisconnect = false);

	void SendChatMessage_CS(SessionInfo sessionInfo, short mapID, WString& chatMessage, bool bDisconnect = false );
	void SendChatMessage_CS(List<SessionInfo>& sessionInfoList, short mapID, WString& chatMessage, bool bDisconnect = false);

	void SendChatMessage_SC(SessionInfo sessionInfo, short mapID, LONG64 playerID, WString& chatMessage, bool bDisconnect = false );
	void SendChatMessage_SC(List<SessionInfo>& sessionInfoList, short mapID, LONG64 playerID, WString& chatMessage, bool bDisconnect = false);

	void MoveMyCharacter_CS(SessionInfo sessionInfo, short mapID, float destinationX, float destinationY, bool bDisconnect = false );
	void MoveMyCharacter_CS(List<SessionInfo>& sessionInfoList, short mapID, float destinationX, float destinationY, bool bDisconnect = false);

	void MoveMyCharacter_SC(SessionInfo sessionInfo, short mapID, Vector<float>& destinationsX, Vector<float>& destinationsY, bool bDisconnect = false );
	void MoveMyCharacter_SC(List<SessionInfo>& sessionInfoList, short mapID, Vector<float>& destinationsX, Vector<float>& destinationsY, bool bDisconnect = false);

	void MoveOtherCharacter_SC(SessionInfo sessionInfo, short mapID, LONG64 playerID, Vector<float>& destinationsX, Vector<float>& destinationsY, bool bDisconnect = false );
	void MoveOtherCharacter_SC(List<SessionInfo>& sessionInfoList, short mapID, LONG64 playerID, Vector<float>& destinationsX, Vector<float>& destinationsY, bool bDisconnect = false);

	void HeartBeat_CS(SessionInfo sessionInfo, bool bDisconnect = false );
	void HeartBeat_CS(List<SessionInfo>& sessionInfoList, bool bDisconnect = false);

	WonsikWorldDummyProxy(IOCPDummyClient* pDummy)
	{
		_pDummy=pDummy;
	}
};

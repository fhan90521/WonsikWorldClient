#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MyStlContainer.h"
#include "WonsikWorldPKT_TYPE.h"
class WWVector2D;
class WonsikWorldClientStub
{
public:
	bool PacketProcEnterGame_CS(CRecvBuffer& buf);
	virtual void ProcEnterGame_CS(WString& nickName) {}

	bool PacketProcEnterGame_SC(CRecvBuffer& buf);
	virtual void ProcEnterGame_SC(short enterGameResult, LONG64 playerID) {}

	bool PacketProcCreateMyCharacter_SC(CRecvBuffer& buf);
	virtual void ProcCreateMyCharacter_SC(short mapID, WWVector2D& dirVec, WWVector2D& location) {}

	bool PacketProcCreateOtherCharacter_SC(CRecvBuffer& buf);
	virtual void ProcCreateOtherCharacter_SC(short mapID, LONG64 playerID, WString& nickName, WWVector2D& dirVec, WWVector2D& location) {}

	bool PacketProcDeleteCharacter_SC(CRecvBuffer& buf);
	virtual void ProcDeleteCharacter_SC(short mapID, LONG64 playerID) {}

	bool PacketProcChangeMap_CS(CRecvBuffer& buf);
	virtual void ProcChangeMap_CS(short beforeMapID, short afterMapID) {}

	bool PacketProcChangeMap_SC(CRecvBuffer& buf);
	virtual void ProcChangeMap_SC(short beforeMapID, short afterMapID) {}

	bool PacketProcSendChatMessage_CS(CRecvBuffer& buf);
	virtual void ProcSendChatMessage_CS(short mapID, WString& chatMessage) {}

	bool PacketProcSendChatMessage_SC(CRecvBuffer& buf);
	virtual void ProcSendChatMessage_SC(short mapID, LONG64 playerID, WString& chatMessage) {}

	bool PacketProcMoveMyCharacter_CS(CRecvBuffer& buf);
	virtual void ProcMoveMyCharacter_CS(short mapID, WWVector2D& destination) {}

	bool PacketProcMoveMyCharacter_SC(CRecvBuffer& buf);
	virtual void ProcMoveMyCharacter_SC(short mapID, Vector<WWVector2D>& destinations) {}

	bool PacketProcMoveOtherCharacter_SC(CRecvBuffer& buf);
	virtual void ProcMoveOtherCharacter_SC(short mapID, LONG64 playerID, Vector<WWVector2D>& destinations) {}

	bool PacketProcHeartBeat_CS(CRecvBuffer& buf);
	virtual void ProcHeartBeat_CS() {}

	bool PacketProc(CRecvBuffer& buf);
};

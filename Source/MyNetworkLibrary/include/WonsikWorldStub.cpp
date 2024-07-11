#include  "WonsikWorldStub.h"
 #include "IOCPServer.h"
#include <iostream>
#include "Log.h"
using namespace std;
bool WonsikWorldStub::PacketProcSendChatMessage(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	String id;
	String chatMessage;
	try
	{
		buf >> id >> chatMessage;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcSendChatMessage error\n");
		 return false;
	}
	ProcSendChatMessage( sessionInfo , id, chatMessage);
	return true;
}
bool WonsikWorldStub::PacketProcHeartBeat(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	try
	{
		buf;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcHeartBeat error\n");
		 return false;
	}
	ProcHeartBeat( sessionInfo );
	return true;
}

bool WonsikWorldStub::PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	short packetType;
	try
	{
		buf>>packetType;
	}
	catch(int remainSize)
	{
		 return false;
	}
	switch(packetType)
	{
	case PKT_TYPE_SendChatMessage:
	{
		return PacketProcSendChatMessage(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_HeartBeat:
	{
		return PacketProcHeartBeat(sessionInfo,buf);
		break;
	}
	default:
	{
		Log::LogOnFile(Log::DEBUG_LEVEL,"Packet Type not exist error\n");
		return false;
		break;
	}
	}
}

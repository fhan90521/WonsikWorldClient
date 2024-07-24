// Fill out your copyright notice in the Description page of Project Settings.


#include "WWGameInstance.h"
#include "Log.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WWJobQueue.h"
void UWWGameInstance::Init()
{
	Super::Init();
	//GetClientSetValues(TCHAR_TO_ANSI(*(FPaths::GameSourceDir() + FString::Printf(TEXT("ClientSetting.json")))));
	IOCP_THREAD_NUM = 1 ;
	CONCURRENT_THREAD_NUM = 1;
	SERVER_PORT = 6000;
	PACKET_CODE = 119;
	PACKET_KEY = 50;
	LOG_LEVEL = 0;
	ClientSetting();
	Run();
	return;
}

UWWGameInstance::UWWGameInstance(): WonsikWorldClientProxy(this)
{
	GJobQueue = new WWJobQueue;
}

UWWGameInstance::~UWWGameInstance()
{
	IsGameDestroyed = true;
	CloseClient();
}

void UWWGameInstance::OnConnect()
{
	return ;
}

void UWWGameInstance::OnDisconnect()
{
	//이것도 잡으로
	_onConnecting = false;
	if (bQuitGame == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Disconnect Error"));
	}
	GJobQueue->PushJob(&WWJobQueue::QuitGame);
}

void UWWGameInstance::OnRecv(CRecvBuffer& buf)
{
	if (PacketProc(buf) == false)
	{
		UE_LOG(LogTemp, Log, TEXT("PacketProc return false error"));
		//Disconnect(sessionInfo);
	}
}

void UWWGameInstance::Run()
{
	IOCPRun();
}

WString UWWGameInstance::GetMyNickName()
{
	return _myNickName;
}
short UWWGameInstance::GetInstanceMapID()
{
	return _instanceMapID;
}
LONG64 UWWGameInstance::GetMyPlayerID()
{
	return _myPlayerID;
}
bool UWWGameInstance::ConncectToServer(const String& ip)
{
	SERVER_IP = ip;
	if (Connect() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Connect Fail"));
		bConnectFail = true;
		return false;
	}
	bConnectFail = false;
	return true;
}
void UWWGameInstance::SetMyNickName(const WString& NickName)
{
	_myNickName = NickName;
}


void UWWGameInstance::ProcEnterGame_SC(short enterGameResult, LONG64 playerID)
{
	if (enterGameResult == ENTER_GAME_SUCCESS)
	{
		_myPlayerID = playerID;
	}
	else if (enterGameResult == NAME_DUPLICATION)
	{

	}
	else
	{
		//Disconnect(sessionInfo);
		UE_LOG(LogTemp, Log, TEXT("ProcEnterGame_SC not match instance map id error"));
	}
}
void UWWGameInstance::ProcChangeMap_SC(short beforeMapID, short afterMapID)
{
	if (beforeMapID == _instanceMapID)
	{
		_instanceMapID = afterMapID;
		GJobQueue->PushJob(&WWJobQueue::ChangeMapSC,beforeMapID ,afterMapID);
	}
	else
	{
		//Disconnect(sessionInfo);
		UE_LOG(LogTemp, Log, TEXT("ProcChangeMap_SC not match instance map id error"));
	}
}
void UWWGameInstance::ProcCreateMyCharacter_SC(short mapID, float dirX, float dirY, float locationX, float locationY)
{
	if (mapID == _instanceMapID)
	{
		GJobQueue->PushJob(&WWJobQueue::CreateMyCharacterSC, mapID, dirX, dirY, locationX, locationY);
	}
	else
	{
		//Disconnect(sessionInfo);
		UE_LOG(LogTemp, Log, TEXT("ProcCreateMyCharacter_SC not match instance map id error"));
	}
}
void UWWGameInstance::ProcCreateOtherCharacter_SC(short mapID, LONG64 playerID, WString& nickName, float dirX, float dirY, float locationX, float locationY)
{
	if (mapID == _instanceMapID)
	{
		GJobQueue->PushJob(&WWJobQueue::CreateOtherCharacterSC, mapID,playerID,FString(nickName.c_str()), dirX, dirY, locationX, locationY);
	}
	else
	{
		//Disconnect(sessionInfo);
		UE_LOG(LogTemp, Log, TEXT("ProcCreateOtherCharacter_SC not match instance map id error"));
	}
}
void UWWGameInstance::ProcDeleteCharacter_SC(short mapID, LONG64 playerID)
{
	if (mapID == _instanceMapID)
	{
		GJobQueue->PushJob(&WWJobQueue::DeleteCharacterSC, mapID, playerID);
	}
	else
	{
		//Disconnect(sessionInfo);
		UE_LOG(LogTemp, Log, TEXT("ProcDeleteCharacter_SC not match instance map id error"));
	}
}
void UWWGameInstance::ProcMoveOtherCharacter_SC(short mapID, LONG64 playerID, Vector<float>& destinationsX, Vector<float>& destinationsY)
{
	if (mapID == _instanceMapID)
	{
		if (destinationsX.size() == destinationsY.size())
		{
			List<FVector> destinations;
			for (int i = 0; i < destinationsX.size(); i++)
			{
				destinations.push_back(FVector(destinationsX[i], destinationsY[i], 0));
			}
			GJobQueue->PushJob(&WWJobQueue::MoveOtherCharacterSC, mapID, playerID, destinations);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("ProcMoveOtherCharacter_SC not match destinations size error"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ProcMoveOtherCharacter_SC not match instance map id error"));
		//Disconnect(sessionInfo);
	}
}
void UWWGameInstance::ProcSendChatMessage_SC(short mapID, LONG64 playerID, WString& chatMessage)
{
	if (mapID == _instanceMapID)
	{
		GJobQueue->PushJob(&WWJobQueue::SendChatMessageSC, mapID, playerID,FString(chatMessage.c_str()));
	}
	else
	{
		//Disconnect(sessionInfo);
		UE_LOG(LogTemp, Log, TEXT("ProcSendChatMessage_SC not match instance map id error"));
	}
}
void UWWGameInstance::ProcMoveMyCharacter_SC(short mapID, Vector<float>& destinationsX, Vector<float>& destinationsY)
{
	if (mapID == _instanceMapID)
	{
		if (destinationsX.size() == destinationsY.size())
		{
			List<FVector> destinations;
			for (int i = 0; i < destinationsX.size(); i++)
			{
				destinations.push_back(FVector(destinationsX[i], destinationsY[i], 0));
			}
			GJobQueue->PushJob(&WWJobQueue::MoveMyCharacterSC, mapID, destinations);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("ProcMoveMyCharacter_SC not match destinations size error"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ProcMoveMyCharacter_SC not match instance map id error"));
		//Disconnect(sessionInfo);
	}
}

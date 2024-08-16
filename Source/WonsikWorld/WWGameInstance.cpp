// Fill out your copyright notice in the Description page of Project Settings.


#include "WWGameInstance.h"
#include "Log.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WWJobQueue.h"
#include "WWPlayerController.h"
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
		AWWPlayerController* wwPlayerController = Cast <AWWPlayerController>(GetFirstLocalPlayerController());
		if (wwPlayerController)
		{
			wwPlayerController->_bChangingRoom = false;
		}
		bNickNameDuplication = true;
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
void UWWGameInstance::ProcCreateMyCharacter_SC(short mapID, WWVector2D& dirVec, WWVector2D& location)
{
	if (mapID == _instanceMapID)
	{
		GJobQueue->PushJob(&WWJobQueue::CreateMyCharacterSC, mapID,FVector(dirVec._x, dirVec._y,0), FVector(location._x, location._y,0));
	}
	else
	{
		//Disconnect(sessionInfo);
		UE_LOG(LogTemp, Log, TEXT("ProcCreateMyCharacter_SC not match instance map id error"));
	}
}
void UWWGameInstance::ProcCreateOtherCharacter_SC(short mapID, LONG64 playerID, WString& nickName, WWVector2D& dirVec, WWVector2D& location)
{
	if (mapID == _instanceMapID)
	{
		GJobQueue->PushJob(&WWJobQueue::CreateOtherCharacterSC, mapID,playerID,FString(nickName.c_str()), FVector(dirVec._x,dirVec._y,0), FVector(location._x, location._y, 0));
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
void UWWGameInstance::ProcMoveOtherCharacter_SC(short mapID, LONG64 playerID, Vector<WWVector2D>& destinations)
{
	if (mapID == _instanceMapID)
	{
		
		List<FVector> destinationList;
		for (auto& vector2D : destinations)
		{
			destinationList.push_back(FVector(vector2D._x, vector2D._y, 0));
		}
		GJobQueue->PushJob(&WWJobQueue::MoveOtherCharacterSC, mapID, playerID, destinationList);
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
void UWWGameInstance::ProcMoveMyCharacter_SC(short mapID, Vector<WWVector2D>& destinations)
{
	if (mapID == _instanceMapID)
	{
		List<FVector> destinationList;
		for (auto& vector2D : destinations)
		{
			destinationList.push_back(FVector(vector2D._x, vector2D._y, 0));
			UE_LOG(LogTemp, Log, TEXT("x: %f y:%f"), vector2D._x, vector2D._y);
		}
		GJobQueue->PushJob(&WWJobQueue::MoveMyCharacterSC, mapID, destinationList);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ProcMoveMyCharacter_SC not match instance map id error"));
		//Disconnect(sessionInfo);
	}
}

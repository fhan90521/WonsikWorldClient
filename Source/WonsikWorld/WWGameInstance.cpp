// Fill out your copyright notice in the Description page of Project Settings.


#include "WWGameInstance.h"
#include "Log.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WWMainMenuBox.h"
void UWWGameInstance::Init()
{
	Super::Init();
	GetClientSetValues(TCHAR_TO_ANSI(*(FPaths::GameSourceDir() + FString::Printf(TEXT("ClientSetting.json")))));
	ClientSetting();
	Run();
	if (Connect(_sessionInfo) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Connect Fail"));
		ConnectSuccess = false;
		return;
	}
	WWJobManager = NewObject<AWWJobManager>();
	return;
}

UWWGameInstance::UWWGameInstance(): WonsikWorldClientProxy(this)
{
}

void UWWGameInstance::OnDisconnect(SessionInfo sessionInfo)
{
	//이것도 잡으로
	UE_LOG(LogTemp, Error, TEXT("Disconnect Error"));
}

void UWWGameInstance::OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	if (PacketProc(sessionInfo, buf) == false)
	{
		Disconnect(sessionInfo);
	}
}

void UWWGameInstance::Run()
{
	IOCPRun();
}



void UWWGameInstance::SendChatMessageOnServer(FString ChatMessage)
{
	SendChatMessage(_sessionInfo, "ab", TCHAR_TO_ANSI(*ChatMessage));
}

void UWWGameInstance::ProcSendChatMessage(SessionInfo sessionInfo, String id, String chatMessage)
{
	WWJobManager->PushJob(&AWWJobManager::RecvChatMessage,id.c_str(), chatMessage.c_str());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "WWPlayerController.h"
#include "WWCharacterBase.h"
#include "WWGameInstance.h"
#include "WWJobQueue.h"
#include "WWGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MapSource.h"

void AWWPlayerController::InitMap(const int mapResource[10][10])
{
	for (int iY = 0; iY < 10; iY++)
	{
		for (int iX = 0; iX < 10; iX++)
		{
			if (mapResource[iY][iX] > 0)
			{
				for (int YPlus = 0; YPlus <= 8000; YPlus += 2000)
				{
					for (int XPlus = 0; XPlus <= 8000; XPlus += 2000)
					{
						CreateObstacle_BP(iX * GRID_CELL_SIZE * 2 + GRID_CELL_SIZE + XPlus, iY * GRID_CELL_SIZE * 2 + GRID_CELL_SIZE + YPlus);
					}
				}
			}
		}
	}
}
void AWWPlayerController::ProcessJob()
{
	size_t queueLen = GJobQueue->GetJobQueueLen();
	for (size_t i = 0; i < queueLen; i++)
	{
		if (_bCanProcessJob == false)
		{
			break;
		}
		Job* pJob = nullptr;
		GJobQueue->PopJob(&pJob);
		pJob->Execute();
		Delete<Job>(pJob);	
	}
}
void AWWPlayerController::HeartBeatCS()
{
	if (LAST_RECV_TIME_OUT == 0)
	{
		return;
	}
	ULONG64 currentTime = GetTickCount();
	if (currentTime - _lastHeartBeatTime>SEND_HEARTBEAT_PERIOD)
	{
		_lastHeartBeatTime = currentTime;
		_wwGameInstance->HeartBeat_CS();
	}
}
void AWWPlayerController::BeginPlay()
{
	Super::BeginPlay();
	_wwGameInstance = Cast<UWWGameInstance>(GetWorld()->GetGameInstance());
	if (_wwGameInstance)
	{
		_pcMapID = _wwGameInstance->GetInstanceMapID();
		_myPlayerID = _wwGameInstance->GetMyPlayerID();
		_myNickName = _wwGameInstance->GetMyNickName();
		MyFNickName = FString(_myNickName.c_str());
		_bChangingRoom = false;
		_lastHeartBeatTime = 0;
		GJobQueue = _wwGameInstance->GJobQueue;
		GJobQueue->_wwPlayerController = this;
	
		if (_pcMapID == MAP_ID_FIELD1)
		{
			InitMap(map1);
		}
		else if (_pcMapID == MAP_ID_FIELD2)
		{

			InitMap(map2);
		}

		ShowCurMapID_BP(_pcMapID);
		_bCanProcessJob = true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("PC BeginPlay error"));
		//QuitGame();
	}
}
void AWWPlayerController::QuitGame_BP()
{
	_wwGameInstance->bQuitGame = true;
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void AWWPlayerController::ChangeMapSC(short beforeMapID, short afterMapID)
{
	if (beforeMapID == _pcMapID)
	{
		//오픈월드 호출하고 새로운 controller가 생기기전까지 jobqueue를 건들지 않게 한다.
		_bCanProcessJob = false;
		ChangeMapSC_BP(afterMapID);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ChangeMapSC not match map id error"));
		//QuitGame();
	}
}
void AWWPlayerController::CreateMyCharacterSC(short mapID, float dirX, float dirY, float locationX, float locationY)
{
	if (mapID == _pcMapID)
	{
		CreateMyCharacterSC_BP(FVector(dirX, dirY, 0), FVector(locationX, locationY, 0));
	}
}
void AWWPlayerController::CreateOtherCharacterSC(short mapID, LONG64 playerID, const FString& nickName, float dirX, float dirY, float locationX, float locationY)
{
	if (mapID == _pcMapID)
	{
		CreateOtherCharacterSC_BP(playerID,nickName, FVector(dirX, dirY, 0), FVector(locationX, locationY, 0));
	}
}
void AWWPlayerController::DeleteCharacterSC(short mapID, LONG64 playerID)
{
	if (mapID == _pcMapID)
	{
		//DeleteCharacterSC_BP(playerID);
		AWWCharacterBase** pCharacter = OtherCharacters.Find(playerID);
		if (pCharacter!=nullptr)
		{
			(*pCharacter)->Destroy(true);
			OtherCharacters.Remove(playerID);
		}
	}
}
void AWWPlayerController::SendChatMessageSC(short mapID, LONG64 playerID, const FString& chatMessage)
{
	if (mapID == _pcMapID)
	{
		SendChatMessageSC_BP(playerID, chatMessage);
	}
}
void AWWPlayerController::MoveMyCharacterSC(short mapID, List<FVector>& destinations)
{
	if (mapID == _pcMapID)
	{
		MyCharacter->SetDestinaions(destinations);
	}
}
void AWWPlayerController::MoveOtherCharacterSC(short mapID, LONG64 playerID, List<FVector>& destinations)
{
	if (mapID == _pcMapID)
	{
		AWWCharacterBase** pCharacter = OtherCharacters.Find(playerID);
		if (pCharacter != nullptr)
		{
			(*pCharacter)->SetDestinaions(destinations);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("not exist other charactor move"));
		}
	}
}


void AWWPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	ProcessJob();

	//함수 내부에서 30초 마다 실행
	HeartBeatCS();
}

void AWWPlayerController::EnterGameCS(const FString& ServerIp, const FString& NickName)
{
	if (_wwGameInstance->_onConnecting==false && _wwGameInstance->ConncectToServer(TCHAR_TO_ANSI(*ServerIp))==false)
	{
		return;
	}
	_wwGameInstance->_onConnecting = true;
	if (_bChangingRoom == true)
	{
		return;
	}
	_bChangingRoom = true;
	WString nickName = (wchar_t*)TCHAR_TO_UTF16(*NickName);
	_wwGameInstance->SetMyNickName(nickName);
	_wwGameInstance->EnterGame_CS(nickName);
}

void AWWPlayerController::MoveMyCharacterCS(const FVector& Destination)
{
	if (_bChangingRoom == true)
	{
		return;
	}
	//멈추는 프로토콜을 사용해서 서버도 길을 못찾았을때 멈추게되면 부자연스로운 상황이 더 발생함
	//MyCharacter->Stop();
	_wwGameInstance->MoveMyCharacter_CS(_pcMapID, Destination.X, Destination.Y);
}

void AWWPlayerController::SendChatMessageCS(const FString& ChatMessage)
{
	if (_bChangingRoom == true)
	{
		return;
	}
	WString chatMessage = (wchar_t*)TCHAR_TO_UTF16(*ChatMessage);
	_wwGameInstance->SendChatMessage_CS(_pcMapID, chatMessage);
}

void AWWPlayerController::ChangeMapCS()
{
	if (_bChangingRoom == true)
	{
		return;
	}
	_bChangingRoom = true;
	if (_pcMapID == MAP_ID_FIELD1)
	{
		_wwGameInstance->ChangeMap_CS(_pcMapID, MAP_ID_FIELD2);
	}
	else if (_pcMapID == MAP_ID_FIELD2)
	{
		_wwGameInstance->ChangeMap_CS(_pcMapID, MAP_ID_FIELD1);
	}
}




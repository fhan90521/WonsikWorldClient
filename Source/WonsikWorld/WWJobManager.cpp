// Fill out your copyright notice in the Description page of Project Settings.


#include "WWJobManager.h"
#include "WWPlayerController.h"
// Sets default values
AWWJobManager::AWWJobManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWWJobManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWWJobManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProcJobOnClient();
}

void AWWJobManager::RecvChatMessage(const char* id,const char* Message)
{
	
	AWWPlayerController* MyPC=CastChecked<AWWPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	if (MyPC)
	{
		MyPC->RecvChatMessage(FString(id),FString(Message));
	}
	
}


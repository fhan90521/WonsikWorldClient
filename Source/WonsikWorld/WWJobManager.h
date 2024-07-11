// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JobQueue.h"
#include "WWJobManager.generated.h"
UCLASS()
class WONSIKWORLD_API AWWJobManager : public AActor,public JobQueue
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWWJobManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Chat Job
	void RecvChatMessage(const char* id, const char* ChatMessage);

};

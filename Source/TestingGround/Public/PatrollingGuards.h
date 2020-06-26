// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "D:\Programs\Repos\TestingGround\Source\TestingGround\TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "CoreMinimal.h"
#include "PatrollingGuards.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUND_API APatrollingGuards : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere , Category = "Patrol Route")
    TArray<AActor*> PatrolPointsCPP;
};

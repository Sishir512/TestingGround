// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Grass.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTINGGROUND_API UGrass : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FBox SpawningLimit;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int SpawnCount;

	void SpawnGrass();

};

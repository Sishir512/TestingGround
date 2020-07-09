// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUND_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 2 , float Radius = 300 , float MinScale = 1 , float MaxScale = 1);

	UFUNCTION(BlueprintCallable)
	void SetPool(UActorPool* InPool);

protected:
	UPROPERTY(EditDefaultsOnly , Category = "Spawning Limit")
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning Limit")
	FVector MaxExtent;
	
private:
	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	void SpawnActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint , float Rotation , float Scale);
	bool CanSpawnAtLocation(FVector Location, float Radius);

	class UActorPool* Pool;
	AActor* NavMeshBoundsVolume;

	void PositionNavMeshBoundsVolume();
	
};

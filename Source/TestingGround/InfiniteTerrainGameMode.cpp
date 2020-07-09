// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "ActorPool.h"
#include "EngineUtils.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() {

	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("NavMesh Pool"));


}

void AInfiniteTerrainGameMode::PopulateBoundsVolume() {
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator) {          //This is the standard way of performing ActorIteration using TActorIterator
		AddToPool(*VolumeIterator);
		
		++VolumeIterator;
	}
}


void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd) {
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}
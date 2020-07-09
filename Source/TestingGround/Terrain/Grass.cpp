// Fill out your copyright notice in the Description page of Project Settings.


#include "Grass.h"

void UGrass::BeginPlay() {
	Super::BeginPlay();
	SpawnGrass();
}

void UGrass::SpawnGrass() {
	for (int i = 0; i < SpawnCount; i++) {
		FVector Location = FMath::RandPointInBox(SpawningLimit);
		AddInstance(FTransform(Location));
	}
}

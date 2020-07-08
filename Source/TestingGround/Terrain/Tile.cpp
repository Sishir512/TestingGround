// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SpawnActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn , float Radius , float MinScale , float MaxScale) {
	
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < NumberToSpawn; i++) {
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		bool found = FindEmptyLocation(SpawnPoint, Radius * RandomScale);
		if (found) {
			float RandomRotation = FMath::RandRange(-180.f , 180.f);
			SpawnActor(ToSpawn, SpawnPoint , RandomRotation , RandomScale);
		}
		
		
		
		
	}
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius) {
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	FVector CandidatePoint = FMath::RandPointInBox(Bounds);
	for (int i = 0; i < 100; i++) {
		if (CanSpawnAtLocation(CandidatePoint, Radius)) {
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}
void ATile::SpawnActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint , float Rotation , float Scale) {
	auto SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(SpawnPoint);
	SpawnedActor->SetActorRotation(FRotator(0, Rotation, 0));
	SpawnedActor->SetActorScale3D(FVector(Scale));
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	
}


bool ATile::CanSpawnAtLocation(FVector Location, float Radius) {
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius));
	/*FColor Color = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, Color, true, 100);*/
	return !HasHit;
}

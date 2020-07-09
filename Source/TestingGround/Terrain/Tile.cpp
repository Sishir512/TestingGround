// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "NavigationSystem.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
}

void ATile::SetPool(UActorPool* InPool) {

	Pool = InPool;
	PositionNavMeshBoundsVolume();

}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr) { 
		UE_LOG(LogTemp, Error, TEXT("No NavMesh Bounds Volume"));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("[%s] Checked Out {%s}") , *GetName() , *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation()-FVector(2500 , 0 , 0));
	FNavigationSystem::Build(*GetWorld());
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}
void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ATile::SpawnActors(TSubclassOf<AActor> ToSpawn, int MinSpawn , int MaxSpawn , float Radius, float MinScale, float MaxScale) {
	auto SpawnPositionArray = RandomSpawnPositions(MinSpawn, MaxSpawn,  Radius,  MinScale , MaxScale);
	for (FSpawnPosition SpawnPosition : SpawnPositionArray) {
		SpawnActor(ToSpawn, SpawnPosition);
	}
}



void ATile::SpawnAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius) {
	auto SpawnPositionArray = RandomSpawnPositions(MinSpawn, MaxSpawn, Radius, 1, 1);
	for (FSpawnPosition SpawnPosition : SpawnPositionArray) {
		SpawnAIPawn(ToSpawn, SpawnPosition);
	}
}

void ATile::SpawnAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	auto SpawnedPawn = GetWorld()->SpawnActor<APawn>(ToSpawn);
	SpawnedPawn->SetActorRelativeLocation(SpawnPosition.Location);
	SpawnedPawn->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	SpawnedPawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedPawn->SpawnDefaultController();   //Never Forget to spawn Default Controller while spawning AI

	SpawnedPawn->Tags.Add(FName("Enemy"));
}


TArray<FSpawnPosition> ATile::RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale) {
	TArray<FSpawnPosition> SpawnPositionArray;
	int NumberToSpawn = FMath::RandRange(MinSpawn,MaxSpawn);
	for (int i = 0; i < NumberToSpawn; i++) {

		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool found = FindEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);
		if (found) {
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnPositionArray.Add(SpawnPosition);
		}

	}
	return SpawnPositionArray;
}


bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius) {
	
	FBox Bounds(MinExtent, MaxExtent);
	FVector CandidatePoint = FMath::RandPointInBox(Bounds);
	for (int i = 0; i < 100; i++) {
		if (CanSpawnAtLocation(CandidatePoint, Radius)) {
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}
void ATile::SpawnActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition) {
	auto SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(SpawnPosition.Location);
	SpawnedActor->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	SpawnedActor->SetActorScale3D(FVector(SpawnPosition.Scale));
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


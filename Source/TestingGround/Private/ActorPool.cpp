// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	
}

AActor* UActorPool::Checkout() {
	if (PoolArray.Num() == 0) return nullptr;
	return PoolArray.Pop();
}

void UActorPool::Return(AActor* ActorToReturn) {
	Add(ActorToReturn);
}

void UActorPool::Add(AActor* ActorToAdd) {
	PoolArray.Push(ActorToAdd);
}


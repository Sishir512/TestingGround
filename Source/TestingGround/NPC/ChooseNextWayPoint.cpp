// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"
#include "AIController.h"
#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("No patrol points found"));
		return EBTNodeResult::Failed;
	}

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	//Set NextWayPoint
	BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName , PatrolPoints[Index]);
	
	//Cycle the index
	auto NextIndex = (Index + 1) % (PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName,NextIndex);
	
	//UE_LOG(LogTemp, Warning, TEXT("Index : %d") , Index);

	

	return EBTNodeResult::Succeeded;
}

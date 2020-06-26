// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrollingGuards.h"
#include "AIController.h"
#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuards>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;
	if (!ensure(PatrolPoints)) { return; }

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

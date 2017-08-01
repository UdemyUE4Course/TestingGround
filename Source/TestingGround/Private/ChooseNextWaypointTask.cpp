// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGround.h"
#include "ChooseNextWaypointTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypointTask::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) {
	UBlackboardComponent*	blackboardComponent = OwnerComp.GetBlackboardComponent();
	UPatrolRoute*			patrolRoute			= GetPatrolRoute( OwnerComp );

	if ( !ensure( patrolRoute ) ) { return EBTNodeResult::Failed; }

	if ( patrolRoute->GetPatrolPoints().Num() > 0 ) {
		SetNextWaypoint( blackboardComponent, patrolRoute->GetPatrolPoints() );
		CycleIndex( blackboardComponent, patrolRoute->GetPatrolPoints() );
	} else {
		UE_LOG( LogTemp, Warning, TEXT( "%s actor has a patrol route with no points in it" ), *patrolRoute->GetOwner()->GetName() );
	}

	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypointTask::SetNextWaypoint( UBlackboardComponent* blackboardComp, const TArray<AActor*>& patrolPoints ) {
	int32 nextIndex = blackboardComp->GetValueAsInt( Index.SelectedKeyName );
	blackboardComp->SetValueAsObject( Waypoint.SelectedKeyName, patrolPoints[ nextIndex ] );
}

void UChooseNextWaypointTask::CycleIndex( UBlackboardComponent* blackboardComp, const TArray<AActor*>& patrolPoints ) {
	int32 nextIndex = blackboardComp->GetValueAsInt( Index.SelectedKeyName ) + 1;
	if ( nextIndex >= patrolPoints.Num() ) {
		nextIndex = 0;
	}

	blackboardComp->SetValueAsInt( Index.SelectedKeyName, nextIndex );
}

UPatrolRoute* UChooseNextWaypointTask::GetPatrolRoute( UBehaviorTreeComponent& OwnerComp ) {
	return OwnerComp.
				GetAIOwner()->
				GetPawn()->
				FindComponentByClass<UPatrolRoute>();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypointTask.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUND_API UChooseNextWaypointTask : public UBTTaskNode {
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type		ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) override;
	
protected:
	UPROPERTY( EditAnywhere, Category = "Blackboard" )
	struct FBlackboardKeySelector	Index;

	UPROPERTY( EditAnywhere, Category = "Blackboard" )
	struct FBlackboardKeySelector	Waypoint;

private:
	class UPatrolRoute*				GetPatrolRoute( UBehaviorTreeComponent& OwnerComp );
	void							SetNextWaypoint( UBlackboardComponent* blackboardComp, const TArray<AActor*>& patrolPoints );
	void							CycleIndex( UBlackboardComponent* blackboardComp, const TArray<AActor*>& patrolPoints );
};

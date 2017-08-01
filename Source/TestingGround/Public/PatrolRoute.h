// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUND_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrolRoute();

	const TArray<AActor*>&	GetPatrolPoints() const;
private:
	UPROPERTY( EditInstanceOnly, Category = "Patrol" )
	TArray<AActor*>			PatrolPoints;
};

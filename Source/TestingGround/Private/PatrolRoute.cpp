// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGround.h"
#include "PatrolRoute.h"

UPatrolRoute::UPatrolRoute() {
	PrimaryComponentTick.bCanEverTick = false;
}

const TArray<AActor*>& UPatrolRoute::GetPatrolPoints() const {
	return PatrolPoints;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TESTINGGROUND_API AGun : public AActor {
	GENERATED_BODY()
	
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
	class USkeletalMeshComponent*		Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
	class USceneComponent*				MuzzleLocation;
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void						BeginPlay() override;

public:	
	/** Projectile class to spawn */
	UPROPERTY( EditDefaultsOnly, Category = Projectile )
	TSubclassOf<class ABallProjectile>	ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	class USoundBase*					FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	class UAnimMontage*					FireAnimation;
	
	/** The animation instance of the player shooting */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	class UAnimInstance*				PlayerAnimInstance;

	/** Fires a projectile. */
	void								OnFire();
};
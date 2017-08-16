#include "TestingGround.h"
#include "Gun.h"
#include "BallProjectile.h"
#include "Animation/AnimInstance.h"

// Sets default values
AGun::AGun() {
	// Create a gun mesh component
	Gun = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "FP_Gun" ) );
	Gun->bCastDynamicShadow = false;
	Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	RootComponent = Gun;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>( TEXT( "MuzzleLocation" ) );
	MuzzleLocation->SetupAttachment( Gun );
	MuzzleLocation->SetRelativeLocation( FVector( 0.2f, 48.4f, -10.6f ) );
}

// Called when the game starts or when spawned
void AGun::BeginPlay() {
	Super::BeginPlay();
}

void AGun::OnFire() {
	// try and fire a projectile
	if ( ProjectileClass != NULL ) {
		UWorld* const World = GetWorld();
		if ( World != NULL ) {
			const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ABallProjectile>( ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams );
		}
	}

	// try and play the sound if specified
	if ( FireSound != NULL ) {
		UGameplayStatics::PlaySoundAtLocation( this, FireSound, GetActorLocation() );
	}

	// try and play a firing animation if specified
	if ( FireAnimation != NULL && PlayerAnimInstance != NULL ) {
		PlayerAnimInstance->Montage_Play( FireAnimation, 1.f );
	}
}
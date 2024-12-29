// Copyright apokrif6. All Rights Reserved

#include "ArenaStrike/Public/Character/ASCharacter.h"


// Sets default values
AASCharacter::AASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


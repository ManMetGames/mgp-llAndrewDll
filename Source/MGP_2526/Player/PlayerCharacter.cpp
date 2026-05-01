


#include "MGP_2526/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
	
	
	PlayerInputComponent->BindAxis("MoveForward", this,  &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this,  &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCharacter::TurnCamera);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);

}

void APlayerCharacter::MoveForward(float InputValue)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
}

void APlayerCharacter::MoveRight(float InputValue)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue);
}

void APlayerCharacter::TurnCamera(float InputValue)
{
	AddControllerYawInput(InputValue);
}

void APlayerCharacter::LookUp(float InputValue)
{
	AddControllerPitchInput(InputValue);
}

void APlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::Attack()
{

	UE_LOG(LogTemp, Warning, TEXT("Attack Pressed"));
	FHitResult Hit;

	FVector Start = Camera->GetComponentLocation() + Camera->GetForwardVector() * 50.0f;
	FVector End = Start + Camera->GetForwardVector() * 3000.0f;

		FCollisionQueryParams Params;
	    Params.AddIgnoredActor(this);

		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 2.0f);

		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
		{
			AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Hit.GetActor());

			if (Enemy)
			{
				Enemy->TakeAttackDamage(25.0f, CurrentAttackType);
				UE_LOG(LogTemp, Warning, TEXT("Enemy Hit"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit actor, but it is not an enemy"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Nothing"));
		}

}





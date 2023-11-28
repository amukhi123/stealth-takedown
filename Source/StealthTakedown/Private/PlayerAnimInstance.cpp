#include "PlayerAnimInstance.h"

#include "CharacterController.h"

#include "GameFramework/PawnMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
}

double UPlayerAnimInstance::GroundSpeed() const
{
	if (const TObjectPtr<const APawn> character {TryGetPawnOwner()})
	{
		if (const TObjectPtr<const UPawnMovementComponent> characterMovementComponent {character->GetMovementComponent()})
		{
			return UKismetMathLibrary::VSizeXY(characterMovementComponent->Velocity);
		}
	}

	return 0.0;
}

bool UPlayerAnimInstance::IsAssassinating() const
{
	if (const TObjectPtr<const APawn> character {TryGetPawnOwner()})
	{
		if (const TObjectPtr<const ACharacterController> characterController {Cast<ACharacterController>(character)})
		{
			return characterController->State() == ECharacterState::Assassinating;
		}
	}

	return false;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
}

#include "PlayerAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"

UPlayerAnimInstance::UPlayerAnimInstance() : m_GroundSpeed {}, m_PlayerMovementComponent {}
{
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (TObjectPtr<APawn> player {TryGetPawnOwner()})
	{
		if (TObjectPtr<UPawnMovementComponent> playerMovementComponent {player->GetMovementComponent()})
		{
			m_GroundSpeed = UKismetMathLibrary::VSizeXY(playerMovementComponent->Velocity);
		}
	}
}

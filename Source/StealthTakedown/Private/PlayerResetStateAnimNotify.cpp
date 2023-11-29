#include "PlayerResetStateAnimNotify.h"

#include "CharacterController.h"

void UPlayerResetStateAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		if (const TObjectPtr<const AActor> character {MeshComp->GetOwner()})
		{
			if (const TObjectPtr<ACharacterController> characterController {Cast<ACharacterController>(character)})
			{
				characterController->State(ECharacterState::Default);
			}
		}
	}
}

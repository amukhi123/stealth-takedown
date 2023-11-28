#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayerResetStateAnimNotify.generated.h"

UCLASS()
class STEALTHTAKEDOWN_API UPlayerResetStateAnimNotify : public UAnimNotify
{
GENERATED_BODY()
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

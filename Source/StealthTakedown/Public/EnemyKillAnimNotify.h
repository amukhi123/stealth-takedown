#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EnemyKillAnimNotify.generated.h"

UCLASS()
class STEALTHTAKEDOWN_API UEnemyKillAnimNotify : public UAnimNotify
{
GENERATED_BODY()
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

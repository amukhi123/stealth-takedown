#include "EnemyKillAnimNotify.h"

void UEnemyKillAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		MeshComp->bPauseAnims = true;
	}
}

#include "Enemy.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"

#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

AEnemy::AEnemy() : m_SkeletalMeshComponent {CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletelMeshComponent"))}, m_CapsuleComponent {CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"))}, m_AssassniationPosition {CreateDefaultSubobject<USceneComponent>(TEXT("AssassinationPosition"))}, m_AssassinatedAnimMontage {}
{
	if (m_CapsuleComponent)
	{
		SetRootComponent(m_CapsuleComponent);
	}

	if (const TObjectPtr<USceneComponent> rootComponent {GetRootComponent()})
	{
		if (m_SkeletalMeshComponent)
		{
			m_SkeletalMeshComponent->SetupAttachment(rootComponent);
		}

		if (m_AssassniationPosition)
		{
			m_AssassniationPosition->SetupAttachment(rootComponent);
		}
	}

	PrimaryActorTick.bCanEverTick = false;
}

void AEnemy::Die() const
{
	PlayAnimMontage();
}

void AEnemy::PlayAnimMontage() const
{
	if (m_SkeletalMeshComponent)
	{
		if (const TObjectPtr<UAnimInstance> animInstance {m_SkeletalMeshComponent->GetAnimInstance()})
		{
			animInstance->Montage_Play(m_AssassinatedAnimMontage);
		}
	}
}

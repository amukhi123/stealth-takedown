#include "Enemy.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"

AEnemy::AEnemy() : m_SkeletalMeshComponent {CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletelMeshComponent"))}, m_CapsuleComponent {CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"))}, m_AssassniationPosition {CreateDefaultSubobject<USceneComponent>(TEXT("AssassinationPosition"))}
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
}

#include "CharacterController.h"
#include "Enemy.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Math/Vector.h"

ACharacterController::ACharacterController() : m_Camera {CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"))}, m_SpringArmComponent {CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"))}, m_MotionWarpingComponent {CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"))}, m_InputMappingContext {}, m_MoveInputAction {}, m_AssassinateInputAction {}, m_MaxAssassinateDistance {}, m_SphereCastSize {}, m_MinDotValue {}, m_State {ECharacterState::Default}
{
	if (const TObjectPtr<USceneComponent> rootComponent {GetRootComponent()})
	{
		if (m_SpringArmComponent)
		{
			m_SpringArmComponent->SetupAttachment(rootComponent);

			m_SpringArmComponent->bUsePawnControlRotation = true;

			if (m_Camera)
			{
				m_Camera->SetupAttachment(m_SpringArmComponent);	
			}
		}
	}

	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (const TObjectPtr<const AController> controller {GetController()})
	{
		if (const TObjectPtr<const APlayerController> playerController {Cast<APlayerController>(controller)})
		{
			if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> enhancedLocalPlayerSubsystem {ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer())})
			{
				enhancedLocalPlayerSubsystem->AddMappingContext(m_InputMappingContext, 0);
			}
		}
	}

	if (const TObjectPtr<UCharacterMovementComponent> characterMovementComponent {GetCharacterMovement()})
	{
		characterMovementComponent->bOrientRotationToMovement = true;
	}
}

void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const TObjectPtr<UEnhancedInputComponent> enhancedInputComponent {Cast<UEnhancedInputComponent>(PlayerInputComponent)})
	{
		if (m_MoveInputAction)
		{
			enhancedInputComponent->BindAction(m_MoveInputAction, ETriggerEvent::Triggered, this, &ACharacterController::Move);
		}

		if (m_LookInputAction)
		{
			enhancedInputComponent->BindAction(m_LookInputAction, ETriggerEvent::Triggered, this, &ACharacterController::Look);
		}

		if (m_AssassinateInputAction)
		{
			enhancedInputComponent->BindAction(m_AssassinateInputAction, ETriggerEvent::Triggered, this, &ACharacterController::Assassinate);
		}
	}
}

void ACharacterController::Move(const FInputActionValue& InputActionValue)
{
	if (State() == ECharacterState::Default)
	{
		const FVector2D movementInput {InputActionValue.Get<FVector2D>()};
		const FRotator yawRotation {0.0, GetControlRotation().Yaw, 0.0};
	
		if (movementInput.X != 0)
		{
			FVector movementDirection {FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y)};
	
			AddMovementInput(movementDirection, movementInput.X);
		}
	
		if (movementInput.Y != 0)
		{
			FVector movementDirection {FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X)};
	
			AddMovementInput(movementDirection, movementInput.Y);
		}
	}
}

void ACharacterController::Look(const FInputActionValue& InputActionValue)
{
	if (GetController())
	{
		const FVector2D lookRotation {InputActionValue.Get<FVector2D>()};

		const double xLookRotation {lookRotation.X};

		if (xLookRotation != 0)
		{
			AddControllerYawInput(lookRotation.X);
		}

		const double yLookRotation {lookRotation.Y};	

		if (yLookRotation != 0)
		{
			AddControllerPitchInput(-yLookRotation);
		}
	}
}

void ACharacterController::Assassinate(const FInputActionValue& InputActionValue)
{
	if (const TObjectPtr<const UWorld> world {GetWorld()})
	{
		FHitResult hit {};

		PerformSphereCast(world, hit);

		if (hit.bBlockingHit)
		{
			if (m_MotionWarpingComponent && m_AssassinationMontage)
			{
				if (const TObjectPtr<const AActor> enemy {hit.GetActor()})
				{
					const double enemyCharacterDot {GetActorForwardVector().Dot(enemy->GetActorForwardVector())};

					if (enemyCharacterDot >= m_MinDotValue && enemyCharacterDot <= 1.0)
					{
						m_State = ECharacterState::Assassinating;

						if (const TObjectPtr<const AEnemy> enemyScript {Cast<AEnemy>(enemy)})
						{
							if (const TObjectPtr<UCapsuleComponent> enemyCapsuleComponent {enemyScript->CapsuleComponent()})
							{
								enemyCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
							}
	
							const FVector assassinationPosition {enemyScript->AssassinationPosition()->GetComponentLocation()};
	
							const FTransform targetTransform {enemy->GetActorRotation(), assassinationPosition, GetActorScale()};
		
							m_MotionWarpingComponent->AddOrUpdateWarpTarget(FMotionWarpingTarget(FName("AssassinateTarget"), targetTransform));
							
							PlayAnimMontage(m_AssassinationMontage);

							enemyScript->Die();
						}
					}	
				}
			}
		}
	}
}

void ACharacterController::PerformSphereCast(const TObjectPtr<const UWorld>& World, FHitResult& OutHitResult) const
{
	const FVector rayStart {GetActorLocation()};
	const FVector rayEnd {rayStart + (GetActorForwardVector() * m_MaxAssassinateDistance)};

	TArray<TEnumAsByte<EObjectTypeQuery>> sphereTraceObjectTypes {};

	sphereTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

	TArray<TObjectPtr<AActor>> actorsToIgnore {};

	if (TObjectPtr<AActor> character {GetOwner()})
	{
		actorsToIgnore.Add(character);
	}

	UKismetSystemLibrary::SphereTraceSingleForObjects(World, rayStart, rayEnd, m_SphereCastSize, sphereTraceObjectTypes, false, actorsToIgnore, EDrawDebugTrace::None, OutHitResult, true);
}

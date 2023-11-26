#include "CharacterController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "Camera/CameraComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterController::ACharacterController() : m_Camera {CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"))}, m_SpringArmComponent {CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"))}, m_InputMappingContext {}, m_MoveInputAction {}
{
	if (TObjectPtr<USceneComponent> rootComponent {GetRootComponent()})
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

	PrimaryActorTick.bCanEverTick = true;

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

	if (TObjectPtr<UCharacterMovementComponent> characterMovementComponent {GetCharacterMovement()})
	{
		characterMovementComponent->bOrientRotationToMovement = true;
	}
}

void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	}
}

void ACharacterController::Move(const FInputActionValue& InputActionValue)
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

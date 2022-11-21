// Fill out your copyright notice in the Description page of Project Settings.


#include "PMainPlayer.h"

#include "AMainObject.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Member variables
float ElapsedTime;
float TimerEnd;
bool IsSetMouse;
float ZoomFactor = 20.f;
float MaxZoom = 1000.f;
float MinZoom = 10.f;

// Sets default values
APMainPlayer::APMainPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmInstance = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainSpringArm"));

	SpringArmInstance->bEnableCameraLag = true;
	SpringArmInstance->TargetArmLength = 400.f;
	SpringArmInstance->CameraLagSpeed = 6.0f;
	SpringArmInstance->bDoCollisionTest = false;

	CameraInstance = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraInstance->SetupAttachment(SpringArmInstance, USpringArmComponent::SocketName);

	ElapsedTime = 0.f;
	TimerEnd = 5.f;
	IsSetMouse = true;
	
	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();

	const FVector Location(0.0f, 0.0f, 0.0f);
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	const FActorSpawnParameters SpawnInfo;
	CubeActor = World->SpawnActor<AAMainObject>(Location, Rotation, SpawnInfo);
	SpringArmInstance->SetupAttachment(CubeActor->Cube);

	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, TEXT("Press Q to rotate Left"));
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, TEXT("Press E to rotate Right"));
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, TEXT("Press W to increase Size"));
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, TEXT("Press S to decrease Size"));
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, TEXT("Press R to reset Level"));
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, TEXT("Scroll Wheel Up to zoom In"));
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, TEXT("Scroll Wheel Down to zoom Out"));
}

// Called every frame
void APMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElapsedTime += DeltaTime;
	

	if (ElapsedTime <= TimerEnd)
	{
		const FRotator Rotate = FRotator(0.0f, 1.f, 0.0f);
		const FQuat DeltaRotation = FQuat(Rotate);
		SpringArmInstance->AddWorldRotation(DeltaRotation, true, nullptr, ETeleportType::None);
	}
	else
	{
		if (IsSetMouse)
		{
			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
			{
				PlayerController->bShowMouseCursor = true;
				PlayerController->bEnableClickEvents = true;
				PlayerController->bEnableMouseOverEvents = true;
				IsSetMouse = false;

				EnableInput(PlayerController);
				check(InputComponent);
				InputComponent->BindAction("PressQ", IE_Pressed, this, &APMainPlayer::QPressed);
				InputComponent->BindAction("PressE", IE_Pressed, this, &APMainPlayer::EPressed);
				InputComponent->BindAction("PressW", IE_Pressed, this, &APMainPlayer::WPressed);
				InputComponent->BindAction("PressS", IE_Pressed, this, &APMainPlayer::SPressed);
				InputComponent->BindAction("PressR", IE_Pressed, this, &APMainPlayer::RPressed);

				InputComponent->BindAction("WheelDown", IE_Released, this, &APMainPlayer::WheelDown);
				InputComponent->BindAction("WheelUp", IE_Released, this, &APMainPlayer::WheelUp);
			}
		}
	}
}

// Called to bind functionality to input
void APMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APMainPlayer::QPressed()
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Q Pressed"));
	const FRotator Rotate = FRotator(0.0f, 4.f, 0.0f);
	const FQuat FQuatValue = FQuat(Rotate);
	SpringArmInstance->AddWorldRotation(FQuatValue, true, nullptr, ETeleportType::None);
}

void APMainPlayer::EPressed()
{
	const FRotator Rotate = FRotator(0.0f, -4.f, 0.0f);
	const FQuat FQuatValue = FQuat(Rotate);
	SpringArmInstance->AddWorldRotation(FQuatValue, true, nullptr, ETeleportType::None);
}

void APMainPlayer::WPressed()
{
	auto const CurrentScale = CubeActor->Cube->GetRelativeScale3D() + FVector(1.f, 1.f, 1.f);
	CubeActor->Cube->SetRelativeScale3D(CurrentScale);
}

void APMainPlayer::SPressed()
{
	if (auto const CurrentScale = CubeActor->Cube->GetRelativeScale3D() - FVector(1.f, 1.f, 1.f); CurrentScale.X >= 1.f)
	{
		 CubeActor->Cube->SetRelativeScale3D(CurrentScale);
	}
}

void APMainPlayer::RPressed()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void APMainPlayer::WheelDown()
{
	const float CurrentArmLength = SpringArmInstance->TargetArmLength;
	if (const float NewArmLength = CurrentArmLength + ZoomFactor; NewArmLength <= MaxZoom)
	{
		SpringArmInstance->TargetArmLength = NewArmLength;
	}
}

void APMainPlayer::WheelUp()
{
	const float CurrentArmLength = SpringArmInstance->TargetArmLength;
	if (const float NewArmLength = CurrentArmLength - ZoomFactor; NewArmLength >= MinZoom)
	{
		SpringArmInstance->TargetArmLength = NewArmLength;
	}
}

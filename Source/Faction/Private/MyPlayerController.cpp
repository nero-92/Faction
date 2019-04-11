// Jack Finan 2019

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController() {
	bShowMouseCursor = true;
}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	HUDPtr = Cast<AMyHUD>(GetHUD());
	GetViewportSize(ScreenSizeX, ScreenSizeY);
}

void AMyPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(!bIsInGameMenu && GetPawn() != nullptr)
		GetPawn()->AddActorWorldOffset(GetCameraPanDirection() * CamSpeed);
}

void AMyPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	
	InputComponent->BindAction("InGameMenu", IE_Pressed, this, &AMyPlayerController::ToggleInGameMenu);

	InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AMyPlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseButton", IE_Released, this, &AMyPlayerController::SelectionReleased);

	InputComponent->BindAction("RightMouseButton", IE_Pressed, this, &AMyPlayerController::Move);
}

void AMyPlayerController::ClientPostLogin_Implementation() {
	SetupInGameUI();
}

void AMyPlayerController::SetupInGameUI() {
	if (this->IsLocalPlayerController()) {
		if (HUDWidgetTemplate) {
			if (!HUDWidgetInstance) {
				HUDWidgetInstance = CreateWidget(this, HUDWidgetTemplate);
			}
			if (!HUDWidgetInstance->GetIsVisible()) {
				HUDWidgetInstance->AddToViewport();
				FInputModeGameAndUI GameMode;
				GameMode.SetWidgetToFocus(HUDWidgetInstance->GetCachedWidget());
				SetInputMode(GameMode);
			}
		}

		if (InGameMenuWidgetTemplate) {
			if (!InGameMenuWidgetInstance) {
				InGameMenuWidgetInstance = CreateWidget(this, InGameMenuWidgetTemplate);
			}
		}
	}
}

void AMyPlayerController::ShowInGameMenu() {
	InGameMenuWidgetInstance->AddToViewport();
	FInputModeUIOnly MenuMode;
	MenuMode.SetWidgetToFocus(InGameMenuWidgetInstance->GetCachedWidget());
	SetInputMode(MenuMode);

	bIsInGameMenu = true;
}

void AMyPlayerController::HideInGameMenu() {
	InGameMenuWidgetInstance->RemoveFromParent();
	FInputModeGameOnly GameMode;
	SetInputMode(GameMode);

	bIsInGameMenu = false;
}

void AMyPlayerController::ToggleInGameMenu() {
	if (bIsInGameMenu)
		HideInGameMenu();
	else
		ShowInGameMenu();
}

FVector AMyPlayerController::GetCameraPanDirection() {
	float MousePosX;
	float MousePosY;
	float CamDirectionX = 0;
	float CamDirectionY = 0;

	GetMousePosition(MousePosX, MousePosY);

	if (MousePosX <= Margin) {
		CamDirectionX = -1;
	}
	if (MousePosX >= ScreenSizeX - Margin) {
		CamDirectionX = 1;
	}
	if (MousePosY <= Margin) {
		CamDirectionY = -1;
	}
	if (MousePosY >= ScreenSizeY - Margin) {
		CamDirectionY = 1;
	}

	return FVector(CamDirectionX, CamDirectionY, 0);
}

void AMyPlayerController::SelectionPressed() {
	HUDPtr->InitialPoint = HUDPtr->GetMousePosition2D();
	HUDPtr->bStartSelecting = true;
}

void AMyPlayerController::SelectionReleased() {
	HUDPtr->bStartSelecting = false;
	SelectedActors = HUDPtr->FoundActors;
	UE_LOG(LogTemp, Warning, TEXT("%i actors selected"), SelectedActors.Num())
}

void AMyPlayerController::Move() {
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	UE_LOG(LogTemp, Warning, TEXT("right click at %f, %f, %f"), Hit.Location.X, Hit.Location.Y, Hit.Location.Z)
	for (int32 i = 0; i < SelectedActors.Num(); i++) {
		FVector MoveLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);
	}
}
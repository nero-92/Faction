// Jack Finan 2019

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController() {
	bShowMouseCursor = true;
}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	GetViewportSize(ScreenSizeX, ScreenSizeY);
}

void AMyPlayerController::Tick(float DeltaTime) {
	if(GetPawn() != nullptr)
		GetPawn()->AddActorWorldOffset(GetCameraPanDirection() * CamSpeed);
}

void AMyPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	
	InputComponent->BindAction("InGameMenu", IE_Pressed, this, &AMyPlayerController::ToggleInGameMenu);
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

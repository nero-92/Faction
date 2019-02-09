// Jack Finan 2019

#include "MyPlayerController.h"
#include "TimerManager.h"

AMyPlayerController::AMyPlayerController() {
	bShowMouseCursor = true;
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
				UE_LOG(LogTemp, Warning, TEXT("Adding HUD to viewport"));
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
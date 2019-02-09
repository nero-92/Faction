// Jack Finan 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class FACTION_API AMyPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	AMyPlayerController();

	virtual void SetupInputComponent() override;

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ClientPostLogin();

	UFUNCTION(BlueprintCallable)
	void HideInGameMenu();

	void SetupInGameUI();
	void ShowInGameMenu();
	void ToggleInGameMenu();

protected:
	bool bIsInGameMenu = false;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetTemplate;

	UPROPERTY()
	UUserWidget* HUDWidgetInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InGameMenuWidgetTemplate;

	UPROPERTY()
	UUserWidget* InGameMenuWidgetInstance;
};

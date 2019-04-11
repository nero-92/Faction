// Jack Finan 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MyHUD.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class FACTION_API AMyPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	AMyPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ClientPostLogin();

	UFUNCTION(BlueprintCallable)
	void HideInGameMenu();

	void SetupInGameUI();
	void ShowInGameMenu();
	void ToggleInGameMenu();

	UPROPERTY(EditAnywhere)
	float CamSpeed = 5;

	UPROPERTY()
	float Margin = 2;

	UFUNCTION()
	FVector GetCameraPanDirection();

	AMyHUD* HUDPtr;

protected:
	bool bIsInGameMenu = false;

	void SelectionPressed();
	void SelectionReleased();
	void Move();

	TArray <AUnit*> SelectedActors;

private:
	int32 ScreenSizeX;
	int32 ScreenSizeY;

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

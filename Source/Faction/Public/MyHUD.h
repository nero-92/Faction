// Jack Finan 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Unit.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class FACTION_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	virtual void DrawHUD() override;

	FVector2D InitialPoint;

	FVector2D CurrentPoint;

	FVector2D GetMousePosition2D();

	bool bStartSelecting = false;

	TArray <AUnit*> FoundActors;
};

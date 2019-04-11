// Jack Finan 2019

#include "MyHUD.h"

void AMyHUD::DrawHUD() {
	if (bStartSelecting) {
		for (int32 i = 0; i < FoundActors.Num(); i++)
			FoundActors[i] -> SetDeselected();
		FoundActors.Empty();

		CurrentPoint = GetMousePosition2D();
		DrawRect(FLinearColor(0, 1, 0, .15f), InitialPoint.X, InitialPoint.Y,
			CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);

		GetActorsInSelectionRectangle<AUnit>(InitialPoint, CurrentPoint, FoundActors, false, false);

		for (int32 i = 0; i < FoundActors.Num(); i++)
			FoundActors[i]->SetSelected();
	}
}

FVector2D AMyHUD::GetMousePosition2D() {
	float PosX;
	float PosY;

	GetOwningPlayerController()->GetMousePosition(PosX, PosY);

	return FVector2D(PosX, PosY);
}

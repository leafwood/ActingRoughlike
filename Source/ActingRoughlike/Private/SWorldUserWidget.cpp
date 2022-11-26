// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"


void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(!IsValid(ActorToAttach))
	{
		RemoveFromParent();
		return;
	}

	FVector2D ScreenLoLocation;
	auto Location = ActorToAttach->GetActorLocation() + FVector(0.f,0.f,HeightOffSet);
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),Location,ScreenLoLocation))
	{
		auto Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenLoLocation /= Scale;

		if(ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenLoLocation);
		}
	}
		
}

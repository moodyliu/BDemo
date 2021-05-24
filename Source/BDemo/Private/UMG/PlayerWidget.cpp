// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/PlayerWidget.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"

UPlayerWidget::UPlayerWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	HPBar = nullptr;
}

void UPlayerWidget::SetHPBarPercent(float Percent)
{
	if (HPBar)
	{
		UMaterialInstanceDynamic* Material = HPBar->GetDynamicMaterial();
		if (Material)
		{
			Material->SetScalarParameterValue(FName(TEXT("Precent")), Percent);
		}
	}
}

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UImage* bar = Cast<UImage>(GetWidgetFromName(FName(TEXT("HPBar")))))
	{
		HPBar = bar;
	}
}

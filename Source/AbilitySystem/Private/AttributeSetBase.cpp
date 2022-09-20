// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"

UAttributeSetBase::UAttributeSetBase():Health(200.0f),MaxHealth(200.0f)
{

}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
		UE_LOG(LogTemp, Warning, TEXT("OUCH!, My health now is: %f"), Health.GetCurrentValue());
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}
}

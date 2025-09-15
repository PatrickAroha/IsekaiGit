#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtributosSystem.h"          // seu componente de máximos (int32) + EAtributeType
#include "StatusComponent.generated.h"

// ===== Delegates =====
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature,  float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangedSignature,    float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDiedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ISEKAI_API UStatusComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStatusComponent();

protected:
    
    virtual void BeginPlay() override;
    
    UFUNCTION()
    void HandleAttributesUpdated(UAtributosSystem* AtribComp);
    
    void ApplyDeath();


public:

    UPROPERTY()
    UAtributosSystem* AtributosSystem = nullptr;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    float Health = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    float Stamina = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    float Mana = 0.f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    bool bDied = false;


    UPROPERTY(BlueprintAssignable, Category="Status")
    FOnHealthChangedSignature OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category="Status")
    FOnStaminaChangedSignature OnStaminaChanged;

    UPROPERTY(BlueprintAssignable, Category="Status")
    FOnManaChangedSignature OnManaChanged;

    UPROPERTY(BlueprintAssignable, Category="Status")
    FOnDiedSignature OnDied;

    // ===== API =====
    UFUNCTION(BlueprintCallable, Category="Status")
    void SubtractHealth(float Value);

    UFUNCTION(BlueprintCallable, Category="Status")
    void AddHealth(float Value);

    UFUNCTION(BlueprintCallable, Category="Status")
    void SubtractStamina(float Value);
    
    UFUNCTION(BlueprintCallable, Category="Status")
    void AddStamina(float Value);

    UFUNCTION(BlueprintCallable, Category="Status")
    void SubtractMana(float Value);

    UFUNCTION(BlueprintCallable, Category="Status")
    void AddMana(float Value);

    UFUNCTION(BlueprintPure, Category="Status")
    float GetNormalizedHealth() const;

    UFUNCTION(BlueprintPure, Category="Status")
    bool IsDead() const { return bDied; }

    float GetMax(EAtributeType Type) const;
};
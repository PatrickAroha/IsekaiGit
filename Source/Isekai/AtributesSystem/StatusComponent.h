#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtributosSystem.h"
#include "StatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedSignature, EAtributeType, Atribute, float, NewValue);
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
    void HandleAttributesUpdated(UAtributosSystem* AtribComp, EAtributeType Atribute, float Amount);

    void ApplyDeath();

public:

    UPROPERTY()
    UAtributosSystem* AtributosSystem = nullptr;

    // ======== Valores atuais ========
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    float Health = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    float Stamina = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    float Mana = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    bool bDied = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status")
    TMap<EAtributeType, float> BaseAttributes;

    // ======== Delegates ========
    UPROPERTY(BlueprintAssignable, Category="Status")
    FOnAttributeChangedSignature OnAttributeChanged;

    UPROPERTY(BlueprintAssignable, Category="Status")
    FOnDiedSignature OnDied;

    // ======== API ========
    UFUNCTION(BlueprintCallable, Category="Status")
    void ModifyAttributeValue(float Value, EAtributeType Atribute);

    UFUNCTION(BlueprintPure, Category="Status")
    bool IsDead() const { return bDied; }

    UFUNCTION(BlueprintCallable, Category="Status")
    float GetMax(EAtributeType Type) const;
};

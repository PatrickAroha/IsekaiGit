  #pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesTypes.h"
#include "AtributosSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributesUpdated, UAtributosSystem*, AtribComp, EAtributeType, Atribute, float, Amount);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class ISEKAI_API UAtributosSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UAtributosSystem();
	
	void SetValue(EAtributeType Atribute, int32 NewValue);
	
	void AddBonusValue(EAtributeType Atribute, float Amount);
	
	void RemoveValue(EAtributeType Atribute, float Amount);
	
	int32 GetValue(EAtributeType Atribute) const;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleLevelUp(int32 NewLevel);

public:
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnAttributesUpdated OnAttributesUpdated;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtributesStatus")
	TMap<EAtributeType, int32> Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AtributesStatus")
	TMap<EAtributeType, int32> BaseAttributes;

	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};



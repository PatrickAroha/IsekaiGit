#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtributosSystem.generated.h"

UENUM(BlueprintType)
enum class EAtributeType : uint8
{
	Vida,
	Stamina,
	Mana,
	Attack,
	Power,
	Defense,
	Velocity,
	Jump,
	Dodge
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class ISEKAI_API UAtributosSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UAtributosSystem();
	
protected:
	
	void SetValue(EAtributeType Atribute, int32 NewValue);
	
	void AddValue(EAtributeType Atribute, int32 Amount);
	
	void RemoveValue(EAtributeType Atribute, int32 Amount);
	
	int32 GetValue(EAtributeType Atribute) const;
	
	virtual void BeginPlay() override;

public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtributesStatus")
	TMap<EAtributeType, int32> Attributes;

	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};



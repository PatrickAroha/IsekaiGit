#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PDA_MissionInfo.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Main,
	Side,
	Random
};

UENUM(BlueprintType)
enum class ERequiredRank : uint8
{
	None,
	F,
	E,
	D,
	C,
	B,
	A,
	S,
	SS
};

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	Kill,
	Collect,
	ReachLocation,
	Dialogue
};

UENUM(BlueprintType)
enum class EUnlockType : uint8
{
	None,
	Item,
	Area,
	NPC,
	Dialogue,
	Recipe,
	Quest
};

USTRUCT(BlueprintType)
struct FQuestObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObjectiveType Type = EObjectiveType::Kill;

	//Alvo Do Objetivo (NPC, Região, Inimigo, Colletável)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Quest.Target"))
	FGameplayTag TargetTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="Type == EObjectiveType::Kill || Type == EObjectiveType::Collect", EditConditionHides))
	int32 RequiredAmount = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};

USTRUCT(BlueprintType)
struct FQuestUnlock
{
	//Struct de Coisas que serão liberadas ao Completar Essa Quest
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUnlockType Type = EUnlockType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="Type == EUnlockType::Recipe", EditConditionHides))
	FName UnlockRecipe;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetID;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;
};

UCLASS(BlueprintType)
class ISEKAI_API UPDA_MissionInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestType QuestType = EQuestType::Side;

	//Posição no ordenamento Da MainQuest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="QuestType == EQuestType::Main", EditConditionHides))
	int32 MainQuestOrder = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	//Objetivos Da QuestAtual
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestObjective> Objectives;

	//Novas quests que serão Adicionadas
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flow")
	TArray<TSoftObjectPtr<UPDA_MissionInfo>> NextQuests;

	//Requisitos Para Completar a taks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flow")
	TArray<FName> RequiredQuestIDs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flow")
	ERequiredRank RequiredRank = ERequiredRank::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rewards")
	int32 RewardXP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rewards")
	TArray<FName> RewardItemIDs;

	//Coisas que a QuestCompletaDesbloqueia
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Unlocks")
	TArray<FQuestUnlock> UnlocksOnComplete;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRepeatable = false;

	/** (Opcional) Encadear automaticamente a próxima ao concluir */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flow")
	bool bAutoStartNext = true;
};

// QuestProgressComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "PDA_MissionInfo.h"
#include "MissionComponent.generated.h"

class UQuestTargetRegistrySubsystem;

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	InProgress,
	Completed,
	Failed
};

USTRUCT(BlueprintType)
struct FObjectiveProgress {
	GENERATED_BODY()

	UPROPERTY()
	EObjectiveType Type = EObjectiveType::Kill;
	
	UPROPERTY()
	int32 CurrentCount = 0;

	UPROPERTY()
	bool bCompleted = false;

	UPROPERTY()
	FGameplayTag TargetTag;

	UPROPERTY()
	int32 RequiredAmount = 1;
	
};

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPDA_MissionInfo* Data;
	
	UPROPERTY()
	TArray<FObjectiveProgress> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestStatus Status = EQuestStatus::InProgress;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMissionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UMissionComponent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentMainQuestIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuest> Quests;

	UFUNCTION(BlueprintCallable) void TryReciveQuest(const TArray<UPDA_MissionInfo*>& MyData);
	UFUNCTION() void ReciveQuest(const TArray<UPDA_MissionInfo*>& MyData);
	UFUNCTION(BlueprintCallable) void TryProgressQuest(FGameplayTag EnemyTargetTag, EObjectiveType Type);
	UFUNCTION() void TryCompleteQuest(FObjectiveProgress& Obj, FQuest& Quest);
	UFUNCTION() void CompleteQuest(FQuest& Quest);
	UFUNCTION() void ReciveBonus(FQuest& Quest);
	UFUNCTION() void RemoveQuest(const FQuest& Quest);
	UFUNCTION() void ReciveNewQuests(FQuest& Quest);
	
};

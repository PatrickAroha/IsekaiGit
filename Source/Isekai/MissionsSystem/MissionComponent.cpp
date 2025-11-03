#include "MissionComponent.h"

#include "Isekai/AtributesSystem/LevelComponent.h"
#include "Isekai/Character/IsekaiCharacter.h"

UMissionComponent::UMissionComponent()
{
	
}

void UMissionComponent::TryReciveQuest(const TArray<TSoftObjectPtr<UPDA_MissionInfo>>& MyData)
{
	AIsekaiCharacter* Player = Cast<AIsekaiCharacter>(GetOwner());
	if (!Player) return;

	TArray<TSoftObjectPtr<UPDA_MissionInfo>> Aprovadas;
	
	for (const TSoftObjectPtr<UPDA_MissionInfo>& Ref : MyData)
	{
		if (!Ref) continue;
		UPDA_MissionInfo* DA = Ref.IsValid() ? Ref.Get() : Ref.LoadSynchronous();
		if (!DA) continue;
		
		if (static_cast<uint8>(Player->Rank) >= static_cast<uint8>(DA->RequiredRank))
			Aprovadas.Add(Ref);
	}

	if (Aprovadas.Num() > 0) ReciveQuest(Aprovadas);
}

void UMissionComponent::ReciveQuest(const TArray<TSoftObjectPtr<UPDA_MissionInfo>>& MyData)
{
	for (const TSoftObjectPtr<UPDA_MissionInfo>& Ref : MyData)
	{
		if (!Ref) continue;
		UPDA_MissionInfo* DA = Ref.Get();
		if (!DA) DA = Ref.LoadSynchronous();
		if (!DA) continue;

		FQuest NewQuest;
		NewQuest.Data = Ref;
		NewQuest.Status = EQuestStatus::InProgress;
		for (const FQuestObjective& Obj : DA->Objectives)
		{
			FObjectiveProgress NewObj;
			NewObj.Type = Obj.Type;
			NewObj.TargetTag = Obj.TargetTag;
			NewObj.RequiredAmount = Obj.RequiredAmount;
			NewQuest.Objectives.Add(NewObj);
		}

		Quests.Add(MoveTemp(NewQuest));
	}
}

void UMissionComponent::TryProgressQuest(FGameplayTag tag, EObjectiveType Type)
{
	for (int32 qi = Quests.Num()-1; qi >= 0; --qi)
	{
		FQuest& Q = Quests[qi];
		if (Q.Status != EQuestStatus::InProgress) continue;

		for (int32 oi = 0; oi < Q.Objectives.Num(); ++oi)
		{
			FObjectiveProgress& Obj = Q.Objectives[oi];
			if (Obj.bCompleted || Obj.Type != Type || Obj.TargetTag != tag) continue;

			TryCompleteQuest(Obj, Q);
			if (Q.Status == EQuestStatus::Completed) { RemoveQuest(Q); break; }
		}
	}
}


void UMissionComponent::TryCompleteQuest(FObjectiveProgress& Obj, FQuest& Quest)
{
	if (Obj.bCompleted) return;
	Obj.CurrentCount++;
	if (Obj.CurrentCount >= Obj.RequiredAmount)
	{
		Obj.bCompleted = true;
		CompleteQuest(Quest);
	}
}

void UMissionComponent::CompleteQuest(FQuest& Quest)
{
	for (const FObjectiveProgress& Obj : Quest.Objectives)
		if (!Obj.bCompleted) return;
	
		Quest.Status = EQuestStatus::Completed;
		ReciveBonus(Quest);
}

void UMissionComponent::ReciveBonus(FQuest& Quest)
{
	UPDA_MissionInfo* DA = Quest.Data.Get();
	if (!DA) DA = Quest.Data.LoadSynchronous();
	if (!DA) return;

	AIsekaiCharacter* Player = Cast<AIsekaiCharacter>(GetOwner());
	if (!Player) return;
	
	if (DA->RewardXP > 0 && Player->LevelComponent)
		Player->LevelComponent->AddXP(DA->RewardXP);
	
	
	for (const FQuestUnlock& MyUnlocked : DA->UnlocksOnComplete)
	{
		if (MyUnlocked.Type == EUnlockType::Recipe)
		{
			Player->UnlockedCrafts.FindOrAdd(MyUnlocked.UnlockRecipe) = true;
		}
		
		if (MyUnlocked.Type == EUnlockType::Area)
		{
			
		}

		if (MyUnlocked.Type == EUnlockType::Quest)
		{
			
		}

		if (MyUnlocked.Type == EUnlockType::Dialogue)
		{
			
		}

		if (MyUnlocked.Type == EUnlockType::NPC)
		{
			
		}

		if (MyUnlocked.Type == EUnlockType::Item)
		{
			
		}
	}
}

void UMissionComponent::RemoveQuest(const FQuest& Quest)
{
	int32 i = Quests.IndexOfByPredicate([&](const FQuest& Q){ return Q.Data == Quest.Data; });
	if (i != INDEX_NONE) Quests.RemoveAtSwap(i);
}

void UMissionComponent::ReciveNewQuests(FQuest& Quest)
{
	
}

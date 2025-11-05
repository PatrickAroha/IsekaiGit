#include "MissionComponent.h"

#include "Isekai/AtributesSystem/LevelComponent.h"
#include "Isekai/Character/IsekaiCharacter.h"

UMissionComponent::UMissionComponent()
{
	
}

void UMissionComponent::TryReciveQuest(const TArray<UPDA_MissionInfo*>& MyData)
{
	AIsekaiCharacter* Player = Cast<AIsekaiCharacter>(GetOwner());
	if (!Player) return;

	TArray<UPDA_MissionInfo*> Aprovadas;
	
	for (UPDA_MissionInfo* Ref : MyData)
	{
		if (static_cast<uint8>(Player->Rank) >= static_cast<uint8>(Ref->RequiredRank))
			Aprovadas.Add(Ref);
	}

	if (Aprovadas.Num() > 0) ReciveQuest(Aprovadas);
}

void UMissionComponent::ReciveQuest(const TArray<UPDA_MissionInfo*>& MyData)
{
	for (UPDA_MissionInfo* Ref : MyData)
	{

		FQuest NewQuest;
		NewQuest.Data = Ref;
		NewQuest.Status = EQuestStatus::InProgress;
		for (const FQuestObjective& Obj : Ref->Objectives)
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
	UE_LOG(LogTemp, Warning, TEXT("TESTE"));

	for (int32 qi = Quests.Num()-1; qi >= 0; --qi)
	{
		FQuest& Q = Quests[qi];
		
		UE_LOG(LogTemp, Warning, TEXT("1"));
		if (Q.Status != EQuestStatus::InProgress) continue;
		UE_LOG(LogTemp, Warning, TEXT("1"));

		for (int32 oi = 0; oi < Q.Objectives.Num(); ++oi)
		{
			FObjectiveProgress& Obj = Q.Objectives[oi];
			UE_LOG(LogTemp, Warning, TEXT("1"));
			if (Obj.bCompleted || Obj.Type != Type || Obj.TargetTag != tag) continue;
			UE_LOG(LogTemp, Warning, TEXT("2"));
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
		UE_LOG(LogTemp, Warning, TEXT("TESTE"));
	}
}

void UMissionComponent::CompleteQuest(FQuest& Quest)
{
	for (const FObjectiveProgress& Obj : Quest.Objectives)
		if (!Obj.bCompleted) return;
	
		Quest.Status = EQuestStatus::Completed;
		ReciveBonus(Quest);
		if (!Quest.Data->NextQuests.IsEmpty()) ReciveNewQuests(Quest);
}

void UMissionComponent::ReciveBonus(FQuest& Quest)
{

	UE_LOG(LogTemp, Warning, TEXT("TESTE"));
	
	AIsekaiCharacter* Player = Cast<AIsekaiCharacter>(GetOwner());
	if (!Player) return;
	
	if (Quest.Data->RewardXP > 0 && Player->LevelComponent)
		Player->LevelComponent->AddXP(Quest.Data->RewardXP);
	
	
	for (const FQuestUnlock& MyUnlocked : Quest.Data->UnlocksOnComplete)
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
	ReciveQuest(Quest.Data->NextQuests);
}

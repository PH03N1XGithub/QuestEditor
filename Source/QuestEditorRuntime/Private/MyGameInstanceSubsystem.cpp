#include "MyGameInstanceSubsystem.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TriggerBase.h"
#include "AssetRegistry/AssetData.h"
#include "NodeInfos/TriggerNodeInfo.h"
#include "Nodes/QuestRuntimeTriggerNode.h"


//DEFINE_LOG_CATEGORY_STATIC(QuestAssetEditorAppLogSub, Log, All);

void UMyGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("UMyGameInstanceSubsystem::Initialize"));// Time Profile for Initialization
	UE_LOG(QuestAssetEditorAppLogSub, Display, TEXT("UMyGameInstanceSubsystem::Initialize"));
	M_QuestAsset = GetQuestAsset();
	if (!M_QuestAsset)
		return;
	InitializeDelegates();// Initialize Delegates in Quest asset
	ExecuteQuest(M_QuestAsset);// Start Quest Execution
}

void UMyGameInstanceSubsystem::Deinitialize()
{
	if (!M_QuestAsset)
		return;
	UE_LOG(QuestAssetEditorAppLogSub, Display, TEXT("UMyGameInstanceSubsystem::DeInitialize"));
	for (const TObjectPtr<UQuestRuntimeNodeBase> Node: M_QuestAsset->Graph->Nodes)
	{
		/*if (Node && Node->NodeType == EQuestNodeType::StopNode && Node->ParentNode)
		{
			/*Old code for Stop execution when this module was dependent on editor.Big mistake dont ever do that.#1#
			// WHY THE FUCK I CANT CAST THİS DYNAMICALLY !!!!!!
			// Dynamic_Cast is overriden by unreal
			//UStopExecutionNode* TempNode = Cast<UStopExecutionNode>(Node->ParentNode); //Fixed it, you cant Cast without including module API to class (in node class)  
			//TempNode->bCanExecute = false;
		}*/
		if (Node && Node->NodeType == EQuestNodeType::TriggerNode)
		{
			UQuestRuntimeTriggerNode* TempNode = Cast<UQuestRuntimeTriggerNode>(Node);
			TempNode->bCanExecute = false;
		}
	}
	M_QuestAsset->Graph->QuestRuntimeNode = nullptr;
	Super::Deinitialize();

}

void UMyGameInstanceSubsystem::ActivateDelegate(const FName Name)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Name]()
	{
		TArray<ATriggerBase*> OutTrigger;
		UGameplayStatics::GetAllActorsOfClassWithTag(
			GetWorld(),
			ATriggerBase::StaticClass(),
			Name,
			reinterpret_cast<TArray<AActor*>&>(OutTrigger)
			);
		for (AActor* Actor : OutTrigger)
		{
			UE_LOG(QuestAssetEditorAppLogSub, Log, TEXT("Found Trigger: %s whit %s Tag"), *Actor->GetName(),*Name.ToString());
			Actor->OnActorBeginOverlap.AddDynamic(this, &UMyGameInstanceSubsystem::OnTriggerBeginOverlap);
		}
	},0.5f, false);
}

void UMyGameInstanceSubsystem::InitializeDelegates()
{

	for (UQuestRuntimeNodeBase* Node: M_QuestAsset->Graph->Nodes)
	{
		if (Node && Node->NodeType == EQuestNodeType::TriggerNode)
		{
			UQuestRuntimeTriggerNode* TempNode = Cast<UQuestRuntimeTriggerNode>(Node);
			TempNode->InitDelegates.AddUniqueDynamic(this, &UMyGameInstanceSubsystem::ActivateDelegate);
			UE_LOG(QuestAssetEditorAppLogSub, Log, TEXT("%s Delegate Initialized"), *TempNode->GetName());
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UMyGameInstanceSubsystem::OnTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Actor Overlap"));
	// Remove Delegate
	TArray<ATriggerBase*> OutTrigger;
	const FName Name = Cast<UTriggerNodeInfo>(Cast<UQuestRuntimeTriggerNode>(M_QuestAsset->Graph->QuestRuntimeNode)->NodeInfo)->TriggerTag;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(),ATriggerBase::StaticClass(),Name,reinterpret_cast<TArray<AActor*>&>(OutTrigger));
	for (AActor* Actor : OutTrigger)
	{
		Actor->OnActorBeginOverlap.RemoveAll(this);
	}
	
	ExecuteQuest(M_QuestAsset);
}

UQuestAsset* UMyGameInstanceSubsystem::GetQuestAsset()
{

	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	
	FARFilter Filter;
	Filter.ClassPaths.Add(UQuestAsset::StaticClass()->GetClassPathName());
	Filter.bRecursiveClasses = true;

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssets(Filter, AssetDataList);
	
	for (const FAssetData& AssetData : AssetDataList)
	{
		UE_LOG(QuestAssetEditorAppLogSub, Log, TEXT("Found QuestAsset: %s"), *AssetData.AssetName.ToString());
		if (UQuestAsset* QuestAsset = Cast<UQuestAsset>(AssetData.GetAsset()))
		{
			return QuestAsset;
		}
	}
	return nullptr;

}

void UMyGameInstanceSubsystem::ExecuteQuest(const UQuestAsset* QuestAsset)
{
	if (!QuestAsset)
		return;
	if (QuestAsset->Graph->QuestRuntimeNode == nullptr)
	{
		QuestAsset->Graph->QuestRuntimeNode = QuestAsset->Graph->GetStartNode();
	}
	if (!QuestAsset->Graph->QuestRuntimeNode->OutputPins.IsEmpty() && QuestAsset->Graph->QuestRuntimeNode->OutputPins[0]->Connection)
	{
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("UMyGameInstanceSubsystem::ExecuteQuest"));
		QuestAsset->Graph->QuestRuntimeNode = QuestAsset->Graph->QuestRuntimeNode->ExecuteNode();
	}
}






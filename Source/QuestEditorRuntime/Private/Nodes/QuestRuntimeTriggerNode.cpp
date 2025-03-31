#include "Nodes/QuestRuntimeTriggerNode.h"
#include "NodeInfos/TriggerNodeInfo.h"


void UQuestRuntimeTriggerNode::InitializeDelegates() const
{
	InitDelegates.Broadcast(Cast<UTriggerNodeInfo>(NodeInfo)->TriggerTag);
}

UQuestRuntimeNodeBase* UQuestRuntimeTriggerNode::ExecuteNode()
{
	if (bCanExecute)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,"UQuestRuntimeTriggerNode Executed");
		UE_LOG(LogTemp, Warning, TEXT("UTriggerNode::Execute"));
		bCanExecute = false;
		return  ActivateOutputPin(OutputPins[0]);
	}
	UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("UQuestRuntimeTriggerNode Stoped"));
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,"UQuestRuntimeTriggerNode Stoped");
	InitializeDelegates();
	bCanExecute = true;
	return this;
}

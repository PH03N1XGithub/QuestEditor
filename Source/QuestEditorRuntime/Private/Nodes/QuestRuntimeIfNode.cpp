#include "Nodes/QuestRuntimeIfNode.h"

UQuestRuntimeIfNode::UQuestRuntimeIfNode()
{
	IfNodeInfo = Cast<UIfNodeInfo>(NodeInfo);
}

UQuestRuntimeNodeBase* UQuestRuntimeIfNode::ExecuteNode()
{
	UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("UQuestRuntimeIfNode Executed"));
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Purple,"UQuestRuntimeIfNode Executed");
	
	if (IfNodeInfo)
		return ActivateOutputPin(IfNodeInfo->bCondition ? OutputPins[0] : OutputPins[1]);

	return ActivateOutputPin(OutputPins[0]);
}

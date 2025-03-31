#include "Nodes/QuestRuntimeNode.h"

UQuestRuntimeNode::UQuestRuntimeNode()
{
	QuestNodeInfo = Cast<UQuestNodeInfo>(NodeInfo);
}

UQuestRuntimeNodeBase* UQuestRuntimeNode::ExecuteNode()
{
	UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("UQuestRuntimeNode Executed"));
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,"UQuestRuntimeNode Executed");
	

	if (QuestNodeInfo && QuestNodeInfo->UExactQ)
		QuestNodeInfo->UExactQ->ExecuteQuestNode(this);
	
	return ActivateOutputPin(OutputPins[0]);
}
  
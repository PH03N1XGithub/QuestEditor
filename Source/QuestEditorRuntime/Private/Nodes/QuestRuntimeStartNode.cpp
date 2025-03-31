#include "Nodes/QuestRuntimeStartNode.h"

UQuestRuntimeNodeBase* UQuestRuntimeStartNode::ExecuteNode()
{
	UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("UQuestRuntimeStartNode Executed"));
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"UQuestRuntimeStartNode Executed");
	return ActivateOutputPin(OutputPins[0]);
}

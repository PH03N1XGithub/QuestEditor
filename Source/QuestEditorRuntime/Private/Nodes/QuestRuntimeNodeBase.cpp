#include "Nodes/QuestRuntimeNodeBase.h"

UQuestRuntimeNodeBase* UQuestRuntimeNodeBase::ExecuteNode()
{
	UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("UQuestRuntimeNodeBase::ExecuteNode"));
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Black,"ExecuteNodeBase");
	return ActivateOutputPin(OutputPins[0]);
}

bool UQuestRuntimeNodeBase::HasConnection(const UQuestRuntimePin* Output)
{
	return Output && Output->Connection;
}

UQuestRuntimeNodeBase* UQuestRuntimeNodeBase::ActivateOutputPin(const UQuestRuntimePin* Output)
{
	if (!HasConnection(Output))
		return nullptr;
	return Output->Connection->Parent->ExecuteNode();
}

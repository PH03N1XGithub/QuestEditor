#include "Nodes/QuestStartGraphNode.h"

UEdGraphPin* UQuestStartGraphNode::CreateCustomPin(const EEdGraphPinDirection Direction, const FName Name) {

	const FName Category = TEXT("Outputs");
	const FName Subcategory = TEXT("StartPin");
	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name
	);
	Pin->PinType.PinSubCategory = Subcategory;
	return Pin;
}



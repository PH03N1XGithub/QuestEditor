#include "Nodes/TriggerNode.h"

#include "QuestRuntimeGraph.h"


void UTriggerNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Custom Node Actions")));
   
	UTriggerNode* Node = const_cast<UTriggerNode*>(this);
	Section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Pin")),
		FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"), TEXT("CustomAssetEditor.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node] () {
				Node->CreateCustomPin(EEdGraphPinDirection::EGPD_Output, TEXT("AnotherOutput"));
				Node->GetGraph()->NotifyGraphChanged();
				Node->GetGraph()->Modify();
			}
		))
	);

	Section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete Pin")),
		FText::FromString(TEXT("Deletes the last pin")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"), TEXT("CustomAssetEditor.NodeDeletePinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node] () {
				if (UEdGraphPin* Pin = Node->GetPinAt(Node->Pins.Num() - 1); Pin->Direction != EEdGraphPinDirection::EGPD_Input) {
					Node->RemovePin(Pin);

					Node->GetGraph()->NotifyGraphChanged();
					Node->GetGraph()->Modify();
				}
			}
		))
	);

	Section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"), TEXT("CustomAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node] () {
				Node->GetGraph()->RemoveNode(Node);
			}
		))
	);
}

UEdGraphPin* UTriggerNode::CreateCustomPin(const EEdGraphPinDirection Direction, const FName Name)
{
	const FName Category = (Direction == EEdGraphPinDirection::EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	const FName Subcategory = TEXT("CustomPin");

	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name
	);
	Pin->PinType.PinSubCategory = Subcategory;

	return Pin;
}



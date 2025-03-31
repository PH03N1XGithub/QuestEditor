#include "Nodes/QuestGraphNode.h"
#include "Framework/Commands/UIAction.h"

void UQuestGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const {
    FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Custom Node Actions")));
    UQuestGraphNode* node = (UQuestGraphNode*)this;
    section.AddMenuEntry(
        TEXT("AddPinEntry"),
        FText::FromString(TEXT("Add Pin")),
        FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"), TEXT("CustomAssetEditor.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
            [node] () {
                node->CreateCustomPin(EEdGraphPinDirection::EGPD_Output, TEXT("AnotherOutput"));
                node->GetGraph()->NotifyGraphChanged();
                node->GetGraph()->Modify();
		    }
        ))
    );

    section.AddMenuEntry(
        TEXT("DeletePinEntry"),
        FText::FromString(TEXT("Delete Pin")),
        FText::FromString(TEXT("Deletes the last pin")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"), TEXT("CustomAssetEditor.NodeDeletePinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
            [node] () {
                UEdGraphPin* pin = node->GetPinAt(node->Pins.Num() - 1);
                if (pin->Direction != EEdGraphPinDirection::EGPD_Input) {
                    node->RemovePin(pin);

                    node->GetGraph()->NotifyGraphChanged();
                    node->GetGraph()->Modify();
                }
		    }
        ))
    );

    section.AddMenuEntry(
        TEXT("DeleteEntry"),
        FText::FromString(TEXT("Delete Node")),
        FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"), TEXT("CustomAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateLambda(
            [node] () {
                node->GetGraph()->RemoveNode(node);
		    }
        ))
    );
}

UEdGraphPin* UQuestGraphNode::CreateCustomPin(EEdGraphPinDirection Direction, FName Name) {
    
    FName category = (Direction == EEdGraphPinDirection::EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
    FName subcategory = TEXT("CustomPin");

    UEdGraphPin* pin = CreatePin(
        Direction,
        category,
        Name
    );
    //UEdGraphPin* pin = FGraphPanelPinFactory::CreatePin(Direction,category,Name);
    pin->PinType.PinSubCategory = subcategory;
    return pin;
}


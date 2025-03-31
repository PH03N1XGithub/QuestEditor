// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorApp/QuestAssetAction.h"
#include "QuestAsset.h"
#include "EditorApp/QuestAssetEditorApp.h"


namespace QuestEditor::EditorApp
{
	QuestAssetAction::QuestAssetAction(EAssetTypeCategories::Type category)
	{
		_assetCategory = category;
	}

	FText QuestAssetAction::GetName() const
	{
		return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomAsset", "Quest Asset");
	}

	FColor QuestAssetAction::GetTypeColor() const
	{
		return FColor::Red;
	}

	UClass* QuestAssetAction::GetSupportedClass() const
	{
		return UQuestAsset::StaticClass();
	}

	void QuestAssetAction::OpenAssetEditor(const TArray<UObject*>& inObjects,
	                                       TSharedPtr<class IToolkitHost> editWithinLevelEditor)
	{
		//FAssetTypeActions_Base::OpenAssetEditor(inObjects, editWithinLevelEditor);

		EToolkitMode::Type mode = editWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
		for (UObject* object : inObjects) {
			UQuestAsset* customAsset = Cast<UQuestAsset>(object);
			if (customAsset != nullptr) {
				TSharedRef<QuestAssetEditorApp> editor(new QuestAssetEditorApp());
				editor->InitEditor(mode, editWithinLevelEditor, customAsset);
			}
		}
	}

	uint32 QuestAssetAction::GetCategories()
	{
		return _assetCategory;
	}
}



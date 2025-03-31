// Fill out your copyright notice in the Description page of Project Settings.


#include "Factoryes/QuestAssetFactory.h"

#include "QuestAsset.h"

QuestEditor::EditorApp::UQuestAssetFactory::UQuestAssetFactory(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	SupportedClass = UQuestAsset::StaticClass();
}

UObject* QuestEditor::EditorApp::UQuestAssetFactory::FactoryCreateNew(UClass* uclass, UObject* inParent, FName name, EObjectFlags flags,
	UObject* context, FFeedbackContext* warn)
{
	UQuestAsset* asset = NewObject<UQuestAsset>(inParent, name, flags);
	return asset;
	//return Super::FactoryCreateNew(uclass, inParent, name, flags, context, warn);
}

bool QuestEditor::EditorApp::UQuestAssetFactory::CanCreateNew() const
{
	return true;	
	//return Super::CanCreateNew();
}

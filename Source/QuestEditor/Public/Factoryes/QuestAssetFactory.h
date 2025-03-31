// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class UQuestAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	explicit UQuestAssetFactory(const FObjectInitializer& objectInitializer);

public: // UFactory interface
	virtual UObject* FactoryCreateNew(UClass* uclass, UObject* inParent, FName name, EObjectFlags flags, UObject* context, FFeedbackContext* warn) override;
	virtual bool CanCreateNew() const override;
};

namespace QuestEditor::EditorApp {
	using UQuestAssetFactory = UQuestAssetFactory;
}

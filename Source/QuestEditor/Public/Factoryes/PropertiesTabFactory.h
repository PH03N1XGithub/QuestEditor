// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorApp/QuestAssetEditorApp.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

/**
 * 
 */

namespace QuestEditor::Factories
{
	class FPropertiesTabFactory final : public FWorkflowTabFactory
	{
	public:
		explicit FPropertiesTabFactory(const TSharedPtr<class EditorApp::QuestAssetEditorApp>& App);

		virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
		virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

	protected:
		TWeakPtr<class EditorApp::QuestAssetEditorApp> _app;
	};
}

// Fill out your copyright notice in the Description page of Project Settings.
#include "Factoryes/PropertiesTabFactory.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "EditorApp/QuestAssetEditorApp.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"


namespace QuestEditor::Factories
{
	class FQuestNodeInfoBaseDetailCustomization final : public IDetailCustomization
	{
	public:
		static TSharedRef<IDetailCustomization> MakeInstance()
		{
			return MakeShareable(new FQuestNodeInfoBaseDetailCustomization);
		}

		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override
		{
			// Add properties from the base class
			DetailBuilder.EditCategory("BaseClassCategory")
			             .AddProperty(GET_MEMBER_NAME_CHECKED(UQuestNodeInfoBase, NodeName));  // Only base class properties
		}
	};

	//this and appMode should be same FName("QuestAssetPrimaryTab")
	FPropertiesTabFactory::FPropertiesTabFactory(const TSharedPtr<class EditorApp::QuestAssetEditorApp>& App) :  FWorkflowTabFactory(FName("QuestAssetPropertiesTab"), App)
	{
		_app = App;
		TabLabel = FText::FromString(TEXT("Properties"));
		ViewMenuDescription = FText::FromString(TEXT("Displays a Properties."));
		ViewMenuTooltip = FText::FromString(TEXT("Show the Properties."));
	}

	TSharedRef<SWidget> FPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const 
	{
		//return SNew(STextBlock).Text(FText::FromString(TEXT("primary quest tab Widget")));

		const TSharedPtr<EditorApp::QuestAssetEditorApp> App = _app.Pin();
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

		PropertyEditorModule.RegisterCustomClassLayout(
			UQuestNodeInfoBase::StaticClass()->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(&FQuestNodeInfoBaseDetailCustomization::MakeInstance));
	

		FDetailsViewArgs DetailsViewArgs;
		{
			DetailsViewArgs.bAllowSearch = false;
			DetailsViewArgs.bHideSelectionTip = true;
			DetailsViewArgs.bLockable = false;
			DetailsViewArgs.bSearchInitialKeyFocus = true;
			DetailsViewArgs.bUpdatesFromSelection = false;
			DetailsViewArgs.NotifyHook = nullptr;
			DetailsViewArgs.bShowOptions = false;
			DetailsViewArgs.bShowModifiedPropertiesOption = false;
			DetailsViewArgs.bShowScrollBar = false;
		}

		const TSharedPtr<IDetailsView> SelectedNodeDetailsViewPtr = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
		SelectedNodeDetailsViewPtr->SetObject(nullptr);
		App->SetSelectedNodeDetailView(SelectedNodeDetailsViewPtr);
	

		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.HAlign(HAlign_Fill)
			[
				SelectedNodeDetailsViewPtr.ToSharedRef()
			];
	}
	
	FText FPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
	{
		return FText::FromString(TEXT("primary widget"));
	}
}








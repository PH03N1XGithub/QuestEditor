#include "QuestEditor.h"
#include "EditorApp/QuestAssetAction.h"
#include "IAssetTools.h"
#include "EdGraphUtilities.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"


namespace QuestEditor{
#define LOCTEXT_NAMESPACE "FQuestEditorModule"

	class SQuestStartGraphPin final : public SGraphPin {
	public:
		SLATE_BEGIN_ARGS(SQuestStartGraphPin) {}
		SLATE_END_ARGS()

		void Construct(const FArguments& inArgs, UEdGraphPin* inGraphPinObj) {
			SGraphPin::Construct(SGraphPin::FArguments(), inGraphPinObj);
		}

	protected:
		virtual FSlateColor GetPinColor() const override {
			return FSlateColor(FLinearColor(1.0f, 0.2f, 0.2f));
		}
	};

	struct FQuestPinFactory final : public FGraphPanelPinFactory {
	public:
		virtual ~FQuestPinFactory() override {}
		virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* pin) const override {
			if (FName(TEXT("StartPin")) == pin->PinType.PinSubCategory) {
				return SNew(SQuestStartGraphPin, pin);
			}if (FName(TEXT("CustomPin")) == pin->PinType.PinSubCategory) {
				return SNew(SQuestStartGraphPin, pin);
			} 
			return nullptr;
		}
	};



	void FQuestEditorModule::StartupModule()
	{
		IAssetTools& assetToolsModule = IAssetTools::Get();
		EAssetTypeCategories::Type assetType = assetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("CustomAssets")),
			LOCTEXT("CustomAssets", "Quest Assets"));
		TSharedPtr<EditorApp::QuestAssetAction> customAssetAction = MakeShareable(new EditorApp::QuestAssetAction(assetType));
		assetToolsModule.RegisterAssetTypeActions(customAssetAction.ToSharedRef());


		PinFactory = MakeShareable(new FQuestPinFactory());
		FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);

		/*// Create the Slate Style Set
	_styleSet = MakeShareable(new FSlateStyleSet(TEXT("CustomAssetEditorStyle")));

	// Create color brushes for the asset thumbnail/icon
	// Use FSlateColorBrush to apply a color instead of an image
	FSlateColorBrush* thumbnailColorBrush = new FSlateColorBrush(FLinearColor::Green);  // Replace with any color you want
	FSlateColorBrush* iconColorBrush = new FSlateColorBrush(FLinearColor::Blue);  // Replace with any color you want

	// Register brushes for the color asset icon
	_styleSet->Set(TEXT("ClassThumbnail.CustomAsset"), thumbnailColorBrush);  // This applies the color to the thumbnail
	_styleSet->Set(TEXT("ClassIcon.CustomAsset"), iconColorBrush);  // This applies the color to the icon

	// Register the style set
	FSlateStyleRegistry::RegisterSlateStyle(*_styleSet);

	// Log the successful registration
	UE_LOG(LogTemp, Log, TEXT("Custom asset colors registered successfully."));*/
		
	}

	void FQuestEditorModule::ShutdownModule()
	{
	
	}

#undef LOCTEXT_NAMESPACE

}
IMPLEMENT_MODULE(QuestEditor::FQuestEditorModule, QuestEditor)
	

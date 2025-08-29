#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"

#include "CrazyOperator.generated.h"

UENUM(BlueprintType)
enum class ECrazyColorChannel : uint8
{
	Red = 0 UMETA(DisplayName = "Red"),
	Green = 1 UMETA(DisplayName = "Green"),
	Blue = 2 UMETA(DisplayName = "Blue"),
	Alpha = 3 UMETA(DisplayName = "Alpha")
};


class CRAZYUASSET_API FCrazyAssetOperator : public UAssetActionUtility
{
public:
	static int SaveAsset(const FString& AssetToSave, bool bOnlyIfIsDirty = true);

	static void OpenSizeMapUI(TSharedPtr<FAssetData> AssetIn);
	
	static void OpenSizeMapUI(TArray<TSharedPtr<FAssetData>> AssetsIn);

};

UCLASS()
class CRAZYUASSET_API UCrazyAssetOperator : public UAssetActionUtility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CrazyAsset|Operator", meta = (CallInEditor = "true"))
	static void OpenEditorUI(const FAssetData & Asset);
	
	UFUNCTION(BlueprintCallable, Category = "CrazyAsset|Operator", meta = (CallInEditor = "true"))
	static int SaveAsset(UObject* ObjectToSave);

	UFUNCTION(BlueprintCallable, Category = "CrazyAsset|Operator", meta = (CallInEditor = "true"))
	static void OpenSizeMapUI_SingleAsset(FAssetData & AssetIn);

	UFUNCTION(BlueprintCallable, Category = "CrazyAsset|Operator", meta = (CallInEditor = "true"))
	static void OpenSizeMapUI(TArray<FAssetData> AssetsIn);

	
};
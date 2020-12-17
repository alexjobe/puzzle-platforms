// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	void SetServerList(const TArray<FString> ServerNames);

	void SelectIndex(uint32 Index);

private:
	TSubclassOf<class UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenu_HostButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenu_JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenu_BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenu_JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenu_QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void QuitGame();

	TOptional<uint32> SelectedIndex;
};

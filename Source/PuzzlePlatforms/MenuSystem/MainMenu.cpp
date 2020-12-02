// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(MainMenu_HostButton != nullptr)) return false;
	MainMenu_HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(MainMenu_JoinButton != nullptr)) return false;
	MainMenu_JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(JoinMenu_BackButton != nullptr)) return false;
	JoinMenu_BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinMenu_JoinButton != nullptr)) return false;
	JoinMenu_JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(MainMenu_QuitButton != nullptr)) return false;
	MainMenu_QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	Teardown();
}

void UMainMenu::HostServer()
{
	if (_MenuInterface != nullptr)
	{
		_MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (_MenuInterface != nullptr)
	{
		if (!ensure(IPAddressField != nullptr)) return;
		const FString& Address = IPAddressField->GetText().ToString();

		_MenuInterface->Join(Address);
	}
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::QuitGame()
{
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ConsoleCommand("quit");
}

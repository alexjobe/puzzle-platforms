// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "UObject/ConstructorHelpers.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}

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

void UMainMenu::SetServerList(const TArray<FString> ServerNames)
{
	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;
	if (!ensure(ServerRowClass != nullptr)) return;

	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FString& ServerName : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(ServerName));
		Row->Setup(this, i);
		++i;

		ServerList->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
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
	if (SelectedIndex.IsSet() && _MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index: %d"), SelectedIndex.GetValue());
		_MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set!"));
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

	if (_MenuInterface != nullptr)
	{
		_MenuInterface->RefreshServerList();
	}

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::QuitGame()
{
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ConsoleCommand("quit");
}

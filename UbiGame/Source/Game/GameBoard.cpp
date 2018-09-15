#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/GameComponents/NoteRenderComponent.h"
#include "GameEngine\Util\CameraManager.h"
#include "Game/Util/Note.h"
#include <vector>

#include "GameEngine/Util/MusicManager.h"

#include "GameEntities/Controller.h"
#include "GameComponents/RhythmLogicComponent.h"
#include "GameComponents/DualLogicComponent.h"

#include "GameEntities/Ticker.h"

using namespace Game;

GameBoard::GameBoard()
	: m_backGround(nullptr)
{

	//std::vector<Note*> notes = GameEngine::MusicManager::parseMusic("_8 8 4 2");
	//std::vector<float> beats = GameEngine::MusicManager::convertNotesToBeatTimes(notes, 60);

	//GameEngine::Entity* e = new GameEngine::Entity();
	//GameEngine::NoteRenderComponent* renderComponent = static_cast<GameEngine::NoteRenderComponent*>(e->AddComponent<GameEngine::NoteRenderComponent>());
	//renderComponent->setNote(notes[0]);
	//e->SetPos(sf::Vector2f(100, 100));
	//e->SetSize(sf::Vector2f(30, 30));
	//GameEngine::GameEngineMain::GetInstance()->AddEntity(e);

	//GameEngine::Entity* e2 = new GameEngine::Entity();
	//GameEngine::NoteRenderComponent* renderComponent2 = static_cast<GameEngine::NoteRenderComponent*>(e2->AddComponent<GameEngine::NoteRenderComponent>());
	//renderComponent2->setNote(notes[1]);
	//e2->SetPos(sf::Vector2f(150, 100));
	//e2->SetSize(sf::Vector2f(30, 30));
	//GameEngine::GameEngineMain::GetInstance()->AddEntity(e2);

	// Controller Entity
	GameEngine::Entity * controller = new Controller();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(controller);

	// Ticker Entity
	GameEngine::Entity * ticker = new Ticker();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(ticker);

}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();

}
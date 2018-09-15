#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/GameComponents/NoteRenderComponent.h"
#include "GameEngine\Util\CameraManager.h"

#include "GameEntities/Controller.h"
#include "GameComponents/RhythmLogicComponent.h"
#include "GameComponents/DualLogicComponent.h"

#include "GameEntities/Ticker.h"

using namespace Game;

GameBoard::GameBoard()
	: m_backGround(nullptr)
{
	GameEngine::Entity* e = new GameEngine::Entity();
	GameEngine::NoteRenderComponent* renderComponent = static_cast<GameEngine::NoteRenderComponent*>(e->AddComponent<GameEngine::NoteRenderComponent>());
	renderComponent->setNoteProps(GameEngine::NoteRenderComponent::eStemType::start, 100, true, true, false);
	e->SetPos(sf::Vector2f(100, 100));
	e->SetSize(sf::Vector2f(30, 30));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(e);

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
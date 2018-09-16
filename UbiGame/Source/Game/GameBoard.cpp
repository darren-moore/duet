#include "GameBoard.h"

// Game engine includes
#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine\Util\CameraManager.h"
#include "GameEngine\Util\AnimationManager.h"

// Game includes
#include "GameComponents/RhythmLogicComponent.h"
#include "GameComponents/DualLogicComponent.h"
#include "GameComponents/NoteRenderComponent.h"
#include "GameComponents/StaffRenderComponent.h"
#include "GameComponents/VelocityComponent.h"
#include "GameComponents/AccelerationComponent.h"
#include "GameComponents/PhysicsIntegratorComponent.h"
#include "GameComponents/CircleMoveComponent.h"
#include "GameEntities/Ticker.h"
#include "GameEntities/Controller.h"
#include "Util/Note.h"
#include "Util/MusicNoteUtils.h"

#include <vector>

using namespace Game;

GameBoard::GameBoard() {

	std::vector<Note*> notes = Game::MusicNoteUtils::parseMusic("_2 3,1 4,1 5,1 4,1 6,2 _1 14,1 10,1 6,1 3,2 0,2");
	std::vector<float> beats = Game::MusicNoteUtils::convertNotesToBeatTimes(notes, 60);

	// Add the staff render entities to the game
	GameEngine::Entity* rend = new GameEngine::Entity();
	Game::StaffRenderComponent* renderComponent = static_cast<Game::StaffRenderComponent*>(rend->AddComponent<Game::StaffRenderComponent>());
	renderComponent->SetZLevel(2);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(rend);

	// Ticker Entity
	Ticker * ticker = new Ticker();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(ticker);

	// Controller Entity
	Controller * controller = new Controller(ticker);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(controller);

	// Background Entity
	CreateBackground(ticker);
}


GameBoard::~GameBoard() {
	
}


void GameBoard::Update()
{
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();

}

void GameBoard::CreateBackground(Ticker * ticker) {
	{
		// Set the background image
		GameEngine::Entity* bgEntity = new GameEngine::Entity();
		GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
		render->SetTexture(GameEngine::eTexture::BG);
		render->SetZLevel(0);
		bgEntity->SetPos(sf::Vector2f(640.f, 360.f));
		bgEntity->SetSize(sf::Vector2f(1280.f, 720.f));
		GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);
	}

	{
		// Add a cloud in front of the background
		GameEngine::Entity* cloud = new GameEngine::Entity();
		GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(cloud->AddComponent<GameEngine::SpriteRenderComponent>());
		render->SetTexture(GameEngine::eTexture::Cloud);
		render->SetZLevel(1);
		cloud->SetPos(sf::Vector2f(640.f, 400.f));
		cloud->SetSize(sf::Vector2f(1500.f, 720.f));
		// Add a circular move component to the cloud
		CircleMoveComponent * circle = static_cast<CircleMoveComponent*>(cloud->AddComponent<CircleMoveComponent>());
		circle->setTicker(ticker);
		circle->setRadius(20.f);
		circle->setOriginalPos(640.f, 400.f);
		GameEngine::GameEngineMain::GetInstance()->AddEntity(cloud);
	}

	{
		// Add a cloud in front of the background
		GameEngine::Entity* cloud = new GameEngine::Entity();
		GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(cloud->AddComponent<GameEngine::SpriteRenderComponent>());
		render->SetTexture(GameEngine::eTexture::Cloud);
		render->SetZLevel(2);
		cloud->SetPos(sf::Vector2f(640.f, 360.f));
		cloud->SetSize(sf::Vector2f(1500.f, 720.f));
		// Add a circular move component to the cloud
		CircleMoveComponent * circle = static_cast<CircleMoveComponent*>(cloud->AddComponent<CircleMoveComponent>());
		circle->setTicker(ticker);
		circle->setRadius(20.f);
		circle->setOriginalPos(640.f, 400.f);
		circle->setXOperation(CircleMoveOperation::negative_sin);
		circle->setYOperation(CircleMoveOperation::negative_cos);
		GameEngine::GameEngineMain::GetInstance()->AddEntity(cloud);
	}
}

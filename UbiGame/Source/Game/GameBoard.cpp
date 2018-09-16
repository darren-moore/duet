#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/GameComponents/NoteRenderComponent.h"
#include "Game/GameComponents/StaffRenderComponent.h"
#include "Game/GameComponents/VelocityComponent.h"
#include "Game/GameComponents/AccelerationComponent.h"
#include "Game/GameComponents/PhysicsIntegratorComponent.h"
#include "GameEngine\Util\CameraManager.h"
#include "Game/Util/Note.h"
#include <vector>

#include "Game/Util/MusicNoteUtils.h"

#include "GameEntities/Controller.h"
#include "GameComponents/RhythmLogicComponent.h"
#include "GameComponents/DualLogicComponent.h"

#include "GameEntities/Ticker.h"

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
	CreateBackground();
}


GameBoard::~GameBoard() {
	
}


void GameBoard::Update()
{
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();

}

void GameBoard::CreateBackground() {
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(0);
	bgEntity->SetPos(sf::Vector2f(640.f, 360.f));
	bgEntity->SetSize(sf::Vector2f(1280.f, 720.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);
}

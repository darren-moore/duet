#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/GameComponents/NoteRenderComponent.h"
#include "Game/GameComponents/StaffRenderComponent.h"
#include "GameEngine\Util\CameraManager.h"
#include "Game/Util/Note.h"
#include <vector>

#include "GameEngine/Util/MusicManager.h"

#include "GameEntities/Controller.h"
#include "GameComponents/RhythmLogicComponent.h"
#include "GameComponents/DualLogicComponent.h"

#include "GameEntities/Ticker.h"

using namespace Game;

GameBoard::GameBoard() {

	std::vector<Note*> notes = GameEngine::MusicManager::parseMusic("1 1 2 2 3 4 3");
	std::vector<float> beats = GameEngine::MusicManager::convertNotesToBeatTimes(notes, 60);

	GameEngine::Entity* rend = new GameEngine::Entity();
	Game::StaffRenderComponent* renderComponent = static_cast<Game::StaffRenderComponent*>(rend->AddComponent<Game::StaffRenderComponent>());
	renderComponent->SetZLevel(1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(rend);

	std::vector<GameEngine::Entity*> noteEntities = GameEngine::MusicManager::prepareNoteEntities(notes, sf::Vector2f(640, 200));
	for (auto ne : noteEntities) {
		GameEngine::GameEngineMain::GetInstance()->AddEntity(ne);
	}

	GameEngine::MusicManager::moveNoteEntities(noteEntities, sf::Vector2f(0, 200));

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

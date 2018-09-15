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

using namespace Game;

GameBoard::GameBoard()
	: m_backGround(nullptr)
{

	std::vector<Note*> notes = GameEngine::MusicManager::parseMusic("2 2 3 4 3");
	std::vector<float> beats = GameEngine::MusicManager::convertNotesToBeatTimes(notes, 60);

	int position = 0;
	for (auto n : notes) {
		GameEngine::Entity* e = new GameEngine::Entity();
		GameEngine::NoteRenderComponent* renderComponent = static_cast<GameEngine::NoteRenderComponent*>(e->AddComponent<GameEngine::NoteRenderComponent>());
		renderComponent->SetTexture(GameEngine::eTexture::Note);
		renderComponent->SetZLevel(2);

		renderComponent->setNote(n);
		position += n->noteLength * 16 / 2;
		e->SetPos(sf::Vector2f(position, 100));
		e->SetSize(sf::Vector2f(30, 30));
		GameEngine::GameEngineMain::GetInstance()->AddEntity(e);
		position += n->noteLength * 16 / 2;
	}

	GameEngine::Entity * ent = new Controller();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(ent);

}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();

}
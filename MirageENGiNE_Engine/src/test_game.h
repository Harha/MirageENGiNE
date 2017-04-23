#ifndef TEST_GAME_H
#define TEST_GAME_H

// mirage includes
#include "game/game.h"

namespace mirage
{

	class CoreEngine;
	class GraphicsEngine;
	class GameObject;
	class GameComponent;

	class TestGame : public Game
	{
	public:
		TestGame();
		~TestGame();

		virtual void initialize() override;
		virtual void update(float dt) override;
		virtual void render(GraphicsEngine * const gfxEngine) override;
		virtual void renderGUI() override;
	private:
	protected:
	};

}

#endif // TEST_GAME_H
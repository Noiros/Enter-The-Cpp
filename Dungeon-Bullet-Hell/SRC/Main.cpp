
#include "Engine/Engine.h"
#include "Game/Game.h"

int main(int argc, char* argv[])
{    
    Engine engine;
    Game game;

    // Create a singleton of the engine
    Engine::SetInstance(&engine);

    engine.Setup();
    game.Start(&engine);

    engine.Run();

    return 0;
}

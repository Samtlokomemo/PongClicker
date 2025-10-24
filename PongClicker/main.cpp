// "" -> Arquivos Locais <> -> Bibliotecas
#include <iostream>
#include "Game.h"

using namespace std;
using namespace sf;

int main() {

	// Init Game Engine
	Game game;

	// Game Loop
	while (game.running()) {
		// Update
		game.update();
		// Render
		game.render();
	}
	return 0;
}
#include "game.h"

int main(int argc, char** argv) {

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	Init(window, renderer);

	Menu menu; Game game; Skin skin; SideMenu sidemenu;	Time timee;
	LoadCoreTextures(renderer, menu, game, sidemenu, skin);
	LoadUsualTextures(renderer, skin);

	PlatGenerate(game);

	while (!game.quit) {

		game.frameStart = clock();

		SDL_PollEvent(&game.event);
		LoadMusic(game, game.musicGame);

		switch (menu.item) {
		case 0: Gameplay(renderer, menu, game, skin, sidemenu, timee); break;
		case 1: Appearance(renderer, game, menu, skin); break;
		case 2: Rules(renderer, game, menu, skin); break;
		case 3: Settings(game, menu); break;
		case 4: Exit(game); break;
		case 5: MainMenu(game, menu); break;
		default: break;
		}

		Rendering(renderer, menu, game, skin, sidemenu, timee);

		game.frameEnd = clock() - game.frameStart;
		while (game.frameEnd < FPS) game.frameEnd = clock() - game.frameStart;
	}

	DeInit(0, window, renderer);
	DestroyTextures(renderer, menu, game, sidemenu, skin);

	return 0;
}
#pragma once

#pragma comment(lib, "SDL2_mixer.lib")
#include "SDL.h"
#include "stdlib.h"
#include "SDL_image.h"
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <SDL_ttf.h>
#include "SDL_mixer.h"

#define WIDTH 1200
#define HEIGHT 900
#define FPS 1000/180

#define SPEED 4
#define JUMP -6
#define PLATS 14
#define BULLETS 20

struct Time {

	int holeStart, holeEnd;
	int holeStartSize, holeEndSize;

	int ufoStart, ufoEnd;
	int ufoStartSize, ufoEndSize;

	int propStart, propEnd;

	int jetpackStart, jetpackEnd;
	int jetpackStart2, jetpackEnd2;

	int shotStart, shotEnd;

	int standStart, standEnd;

	int deadStart, deadEnd; 
	int deadStart2, deadEnd2;

	int gameoverStart, gameoverEnd;
}; 
struct Menu { 

	int item = 5;

	// ‘ŒÕ Ã≈Õﬁ
	SDL_Rect pos_menu_background;
	SDL_Texture* menu_background;
	SDL_Texture* menu_background2;

	//  ÕŒœ » √À¿¬ÕŒ√Œ Ã≈Õﬁ
	SDL_Rect pos_buttons[5];
	SDL_Texture* buttons[5];
	SDL_Texture* buttons_active[5];

	//  ÕŒœ » Ã≈Õﬁ ¬Õ≈ÿÕŒ—“»
	SDL_Rect APPpos_buttons[3];
	SDL_Texture* APPbuttons[3];
	SDL_Texture* APPbuttons_active[3];

	// œ–¿¬»À¿
	SDL_Texture* RULback;

	// Õ¿—“–Œ… »
	SDL_Texture* SETback;
	SDL_Rect checkboxSound;
	SDL_Rect checkboxMusic;
	SDL_Texture* on;
	SDL_Texture* off;

	TTF_Font* comic = TTF_OpenFont("sources/comic.ttf", 100);
};
struct Game {

	Mix_Chunk* Sounds = NULL;
	Mix_Music* Musics = NULL;

	bool SoundOn = false;
	bool MusicOn = false, MusicLoaded = false;

	char musicGame[40] = "sources/sounds/music.mp3";

	char soundMenuSelect[40] = "sources/sounds/menu-select.mp3";
	char soundJump[40] = "sources/sounds/jump.wav";
	char soundBreakPlat[40] = "sources/sounds/break-plat.wav";
	char soundShot[40] = "sources/sounds/shot.wav";
	char soundStrike[40] = "sources/sounds/strike.wav";
	char soundSpring[40] = "sources/sounds/spring.wav";
	char soundProp[40] = "sources/sounds/propeller.mp3";
	char soundJetpack[40] = "sources/sounds/jetpack.mp3";
	char soundLossFall[40] = "sources/sounds/loss-fall.wav";
	char soundLossMonster[40] = "sources/sounds/loss-monster.wav";
	char soundLossHole[40] = "sources/sounds/loss-hole.wav";
	char soundLossUFO[40] = "sources/sounds/loss-ufo.mp3";

	SDL_Event event;
	bool quit = false;
	bool paused = false;

	int frameStart, frameEnd;
	int h = 200;

	float dy = 0;
	int stand = 1;
	int dead = 0;

	int plats = PLATS;

	int plat_direction = 0;

	int distance = 0;
	int range_next = 5000;
	int type_enemy;

	int enemy_direction = 0;

	int springNextRange = 1000;
	bool springUsed = false;

	int propNextRange = 4000;
	int propRange = 0;
	bool propPicked = false;
	bool propUsed = false;
	bool propNextSelected = true;

	int jetpackNextRange = 7000;
	int jetpackRange = 0;
	bool jetpackPicked = false;
	bool jetpackUsed = false;
	bool jetpackNextSelected = true;

	int l = 0;
	int standMemory = 1;

	const Uint8* move = SDL_GetKeyboardState(NULL);

	// ‘ŒÕ
	SDL_Rect pos_background;
	SDL_Texture* background;

	// Œ¡€◊Õ¿ﬂ œÀ¿“‘Œ–Ã¿
	SDL_Texture* plat_state;
	SDL_Rect pos_plats[PLATS];
	//
	// ƒ¬»√¿ﬁŸ¿ﬂ—ﬂ œÀ¿“‘Œ–Ã¿
	SDL_Texture* plat_move;
	SDL_Rect pos_plat_move;
	//
	// ÀŒÃ¿ﬁŸ¿ﬂ—ﬂ œÀ¿“‘Œ–Ã¿
	SDL_Texture* plat_break;
	SDL_Rect pos_plat_break;
	//
	// œ–»«–¿◊Õ¿ﬂ œÀ¿“‘Œ–Ã¿
	SDL_Texture* plat_ghost;
	SDL_Rect pos_plat_ghost;

	//
	// “¿¡À»◊ ¿ ¬¿–Õ»Õ√
	SDL_Rect pos_warning;
	SDL_Texture* warning;
	//
	// “≈ ”Ÿ»… ¬–¿√
	SDL_Rect pos_current;
	SDL_Texture* current;
	//
	// √”À‹
	SDL_Rect pos_ghoul;
	SDL_Texture* ghoul;
	//
	// ¿ÃŒ√”—
	SDL_Rect pos_amogus;
	SDL_Texture* amogus;
	SDL_Texture* amogus2;
	//
	// Ã€ÿ‹
	SDL_Rect pos_bat;
	SDL_Texture* bat;
	//
	// ÕÀŒ
	SDL_Rect pos_ufo;
	SDL_Texture* ufo;
	//
	// ◊≈–Õ¿ﬂ ƒ€–¿
	SDL_Rect pos_hole;
	SDL_Texture* hole;

	// œ–”∆»Õ¿
	SDL_Rect pos_spring;
	SDL_Texture* spring;
	//
	// —∆¿“¿ﬂ œ–”∆»Õ¿
	SDL_Rect pos_spring_compressed;
	SDL_Texture* spring_compressed;
};
struct Skin {

	int TexturesLoaded = 0;

	// ƒÀﬂ Ã≈Õﬁ
	int SelectedSkin = 0;
	SDL_Rect menupos = { 740,600,150,150 };
	SDL_Rect APPmenupos = { 450,100,300,300 };
	SDL_Texture* APPmenu;

	// —“¿Õƒ¿–“Õ€≈ “≈ —“”–€
	SDL_Rect pos;
	SDL_Texture* left;
	SDL_Texture* right;
	SDL_Texture* top;

	// œ–Œœ≈ÀÀ≈–
	SDL_Rect pos_prop;
	SDL_Texture* prop;

	// ƒ∆≈“œ¿ 
	SDL_Rect pos_jetpack;
	SDL_Texture* jetpack;

	// — ƒ∆≈“œ¿ ŒÃ
	SDL_Texture* left_jetpack[10];
	SDL_Texture* right_jetpack[10];

	// — œ–Œœ≈ÀÀ≈–ŒÃ
	SDL_Texture* left_prop[4];
	SDL_Texture* right_prop[4];

	// —Œ «¬≈«ƒ¿Ã»
	SDL_Texture* left_stars[3];
	SDL_Texture* right_stars[3];

	// œ”Àﬂ
	SDL_Rect pos_bullets[BULLETS];
	SDL_Texture* bullet;
};
struct SideMenu {

	SDL_Rect panel = { 0,0,112,HEIGHT };
	SDL_Texture* panelTexture;

	SDL_Rect pos_pause = { 18,240,80,80 };
	SDL_Rect pos_sound = { 18,378,80,80 };
	SDL_Rect pos_music = { 18,516,80,80 };
	SDL_Rect pos_home = { 18,652,80,80 };
	SDL_Texture* pause;
	SDL_Texture* play;
	SDL_Texture* sound;
	SDL_Texture* music;
	SDL_Texture* home;

	int score = 0;
	char scoreout[256];
	SDL_Texture* texture;
	SDL_Surface* surface;
	SDL_Rect rect;
	SDL_Color fore = { 0,0,0 };
	SDL_Color back = { 255,255,255,255 };

	bool gameEnd = false;

	SDL_Rect pos_endpanel = { 0,0,1200,900 };
	SDL_Texture* endpanel[9];

	SDL_Rect pos_statspanel = { 0,0,1200,900 };
	SDL_Texture* statspanel;

	SDL_Rect pos_endmenubutton = { 450,600,300,100 };
	SDL_Texture* endmenubutton;
	SDL_Texture* endmenubutton_active;
};

void DeInit(int error, SDL_Window*& window, SDL_Renderer*& renderer);
void Init(SDL_Window*& window, SDL_Renderer*& renderer);

void LoadCoreTextures(SDL_Renderer*& renderer, Menu& menu, Game& game, SideMenu& sidemenu, Skin& skin);
void LoadUsualTextures(SDL_Renderer*& renderer, Skin& skin);
void LoadBunnyTextures(SDL_Renderer*& renderer, Skin& skin);
void Reload(SDL_Renderer*& renderer, Menu& menu, Game& game, SideMenu& sidemenu, Time& timee, Skin& skin);
void DestroyTextures(SDL_Renderer*& renderer, Menu& menu, Game& game, SideMenu& sidemenu, Skin& skin);
void DestroySkinTextures(SDL_Renderer*& renderer, Skin& skin);

void LoadMusic(Game& game, char* name);
void LoadSound(Game& game, char* name);
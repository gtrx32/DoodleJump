#include "load.h"

void DeInit(int error, SDL_Window*& window, SDL_Renderer*& renderer) {

	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	Mix_CloseAudio(); Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	exit(error);
}
void Init(SDL_Window*& window, SDL_Renderer*& renderer) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

		printf("Couldn't init SDL! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, window, renderer);
	}	

	if (TTF_Init() != 0) {

		printf("Couldn't init SDL_TTF! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, window, renderer);
	}

	if (Mix_Init(0) != 0) {

		printf("Couldn't init SDL_Mix! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, window, renderer);
	}
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	window = SDL_CreateWindow("Doodle Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {

		printf("Couldn't create window! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, window, renderer);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {

		printf("Couldn't create renderer! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1, window, renderer);
	}

	srand(time(NULL));
}

void LoadCoreTextures(SDL_Renderer*& renderer, Menu& menu, Game& game, SideMenu& sidemenu, Skin& skin) {

	/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
	/* ||||||||||||||||||||||||||||||| “≈ —“”–€ Ã≈Õﬁ ||||||||||||||||||||||||||||||| */
	/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

	SDL_Surface* surface;

	// ‘ŒÕ Ã≈Õﬁ
	menu.pos_menu_background = { 0,0,WIDTH,HEIGHT };
	surface = IMG_Load("sources/menu/mainmenu/menu-background.png");
	menu.menu_background = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/menu/mainmenu/menu-background2.png");
	menu.menu_background2 = SDL_CreateTextureFromSurface(renderer, surface);

	//  ÕœŒ » √À¿¬ÕŒ√Œ Ã≈Õﬁ
	for (int i = 0; i < 5; i++) {

		menu.pos_buttons[i] = { 130,210 + 133 * i,400,100 };

		char leftname[100] = "sources/menu/mainmenu/button";
		char leftnum[3]; _itoa_s(i, leftnum, 10);
		strcat_s(leftname, leftnum);
		strcat_s(leftname, ".png");
		surface = IMG_Load(leftname);
		menu.buttons[i] = SDL_CreateTextureFromSurface(renderer, surface);

		char rightname[100] = "sources/menu/mainmenu/button";
		char rightnum[3]; _itoa_s(i + 5, rightnum, 10);
		strcat_s(rightname, rightnum);
		strcat_s(rightname, ".png");
		surface = IMG_Load(rightname);
		menu.buttons_active[i] = SDL_CreateTextureFromSurface(renderer, surface);
	}

	//  ÕœŒ » Ã≈Õﬁ ¬Õ≈ÿÕŒ—“»
	menu.APPpos_buttons[0] = { 200,450,300,100 };
	surface = IMG_Load("sources/menu/appearance/button0.png");
	menu.APPbuttons[0] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/menu/appearance/button3.png");
	menu.APPbuttons_active[0] = SDL_CreateTextureFromSurface(renderer, surface);

	menu.APPpos_buttons[1] = { 700,450,300,100 };
	surface = IMG_Load("sources/menu/appearance/button1.png");
	menu.APPbuttons[1] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/menu/appearance/button4.png");
	menu.APPbuttons_active[1] = SDL_CreateTextureFromSurface(renderer, surface);

	menu.APPpos_buttons[2] = { 450,770,300,100 };
	surface = IMG_Load("sources/menu/appearance/button2.png");
	menu.APPbuttons[2] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/menu/appearance/button5.png");
	menu.APPbuttons_active[2] = SDL_CreateTextureFromSurface(renderer, surface);

	// œ–¿¬»À¿
	surface = IMG_Load("sources/menu/rules/rules.png");
	menu.RULback = SDL_CreateTextureFromSurface(renderer, surface);

	// Õ¿—“–Œ… »
	surface = IMG_Load("sources/menu/settings/settings.png");
	menu.SETback = SDL_CreateTextureFromSurface(renderer, surface);
	menu.checkboxSound = { 665,230,150,150 };
	menu.checkboxMusic = { 665,480,150,150 };
	surface = IMG_Load("sources/menu/settings/on.png");
	menu.on = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/menu/settings/off.png");
	menu.off = SDL_CreateTextureFromSurface(renderer, surface);

	/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
	/* ||||||||||||||||||||||||||||||| »√–Œ¬€≈ “≈ —“”–€ ||||||||||||||||||||||||||||||| */
	/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

	// ‘ŒÕ
	game.pos_background = { 0,0,WIDTH,HEIGHT };
	surface = IMG_Load("sources/game/background.png");
	game.background = SDL_CreateTextureFromSurface(renderer, surface);

	// Œ¡€◊Õ¿ﬂ œÀ¿“‘Œ–Ã¿
	surface = IMG_Load("sources/game/plat-state.png");
	game.plat_state = SDL_CreateTextureFromSurface(renderer, surface);

	// ƒ¬»√¿ﬁŸ¿ﬂ—ﬂ œÀ¿“‘Œ–Ã¿
	game.pos_plat_move = { 0,0,0,0 };
	surface = IMG_Load("sources/game/plat-move.png");
	game.plat_move = SDL_CreateTextureFromSurface(renderer, surface);

	// ÀŒÃ¿ﬁŸ¿ﬂ—ﬂ œÀ¿“‘Œ–Ã¿
	game.pos_plat_break = { 0,0,0,0 };
	surface = IMG_Load("sources/game/plat-break.png");
	game.plat_break = SDL_CreateTextureFromSurface(renderer, surface);

	// œ–»«–¿◊Õ¿ﬂ œÀ¿“‘Œ–Ã¿
	game.pos_plat_ghost = { 0,0,0,0 };
	surface = IMG_Load("sources/game/plat-ghost.png");
	game.plat_ghost = SDL_CreateTextureFromSurface(renderer, surface);

	// “¿¡À»◊ ¿ ¬¿–Õ»Õ√
	game.pos_warning = { 0,0,0,0 };
	surface = IMG_Load("sources/game/warning.png");
	game.warning = SDL_CreateTextureFromSurface(renderer, surface);

	// √”À‹
	game.pos_ghoul = { 0,0,122,175 };
	surface = IMG_Load("sources/game/enemy-ghoul.png");
	game.ghoul = SDL_CreateTextureFromSurface(renderer, surface);

	// ¿ÃŒ√”—
	game.pos_amogus = { 0,0,75,99 };
	surface = IMG_Load("sources/game/enemy-amogus.png");
	game.amogus = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/game/enemy-amogus2.png");
	game.amogus2 = SDL_CreateTextureFromSurface(renderer, surface);

	// Ã€ÿ‹
	game.pos_bat = { 0,0,156,87 };
	surface = IMG_Load("sources/game/enemy-bat.png");
	game.bat = SDL_CreateTextureFromSurface(renderer, surface);

	// ÕÀŒ
	game.pos_ufo = { 0,0,130,190 };
	surface = IMG_Load("sources/game/enemy-ufo.png");
	game.ufo = SDL_CreateTextureFromSurface(renderer, surface);

	// ◊≈–Õ¿ﬂ ƒ€–¿
	game.pos_hole = { 0,0,148,144 };
	surface = IMG_Load("sources/game/enemy-hole.png");
	game.hole = SDL_CreateTextureFromSurface(renderer, surface);

	// œ–”∆»Õ¿
	game.pos_spring = { 0,0,0,0 };
	surface = IMG_Load("sources/game/spring.png");
	game.spring = SDL_CreateTextureFromSurface(renderer, surface);

	// —∆¿“¿ﬂ œ–”∆»Õ¿
	game.pos_spring_compressed = { 0,0,0,0 };
	surface = IMG_Load("sources/game/spring-compressed.png");
	game.spring_compressed = SDL_CreateTextureFromSurface(renderer, surface);

	/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
	/* ||||||||||||||||||||||||||| ¡Œ Œ¬Œ≈ Ã≈Õﬁ »  ŒÕ≈÷ »√–€||||||||||||||||||||||||||| */
	/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

	surface = IMG_Load("sources/game/panel.png");
	sidemenu.panelTexture = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load("sources/game/pause.png");
	sidemenu.pause = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/game/play.png");
	sidemenu.play = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/game/sound.png");
	sidemenu.sound = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/game/music.png");
	sidemenu.music = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/game/home.png");
	sidemenu.home = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load("sources/endgame/endpanel1.png");
	sidemenu.endpanel[0] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/endpanel2.png");
	sidemenu.endpanel[1] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/endpanel3.png");
	sidemenu.endpanel[2] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/endpanel4.png");
	sidemenu.endpanel[3] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/endpanel5.png");
	sidemenu.endpanel[4] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/endpanel6.png");
	sidemenu.endpanel[5] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/endpanel7.png");
	sidemenu.endpanel[6] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/endpanel8.png");
	sidemenu.endpanel[7] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/endpanel9.png");
	sidemenu.endpanel[8] = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load("sources/endgame/statspanel.png");
	sidemenu.statspanel = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load("sources/endgame/end-menu-button.png");
	sidemenu.endmenubutton = SDL_CreateTextureFromSurface(renderer, surface);
	surface = IMG_Load("sources/endgame/end-menu-button-active.png");
	sidemenu.endmenubutton_active = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}
void LoadUsualTextures(SDL_Renderer*& renderer, Skin& skin) {

	SDL_Surface* surface;

	// —“¿Õƒ¿–“Õ€… — »Õ
	skin.pos = { 500, 500, 150, 150 };

	// —ÃŒ“–»“ ¬À≈¬Œ
	surface = IMG_Load("sources/skin-usual/usual-left.png");
	skin.left = SDL_CreateTextureFromSurface(renderer, surface);

	// —ÃŒ“–»“ ¬œ–¿¬Œ
	surface = IMG_Load("sources/skin-usual/usual-right.png");
	skin.right = SDL_CreateTextureFromSurface(renderer, surface);

	// —ÃŒ“–»“ ¬¬≈–’
	surface = IMG_Load("sources/skin-usual/usual-top.png");
	skin.top = SDL_CreateTextureFromSurface(renderer, surface);

	// œ–Œœ≈ÀÀ≈–
	skin.pos_prop = { 0,0,0,0 };
	surface = IMG_Load("sources/skin-usual/usual-prop.png");
	skin.prop = SDL_CreateTextureFromSurface(renderer, surface);

	// ƒ∆≈“œ¿ 
	skin.pos_jetpack = { 0,0,0,0 };
	surface = IMG_Load("sources/skin-usual/usual-jetpack.png");
	skin.jetpack = SDL_CreateTextureFromSurface(renderer, surface);

	// œ”Àﬂ
	for (int i = 0; i < BULLETS; i++) { skin.pos_bullets[i] = { 0,0,0,0 }; }
	surface = IMG_Load("sources/skin-usual/usual-bullet.png");
	skin.bullet = SDL_CreateTextureFromSurface(renderer, surface);

	// — ƒ∆≈“œ¿ ŒÃ
	for (int i = 1; i < 11; i++) {

		char leftname[100] = "sources/skin-usual/usual-left-jetpack/usual-left-jetpack";
		char leftnum[3]; _itoa_s(i, leftnum, 10);
		strcat_s(leftname, leftnum);
		strcat_s(leftname, ".png");
		surface = IMG_Load(leftname);
		skin.left_jetpack[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);

		char rightname[100] = "sources/skin-usual/usual-right-jetpack/usual-right-jetpack";
		char rightnum[3]; _itoa_s(i, rightnum, 10);
		strcat_s(rightname, rightnum);
		strcat_s(rightname, ".png");
		surface = IMG_Load(rightname);
		skin.right_jetpack[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);
	}

	// — œ–Œœ≈ÀÀ≈–ŒÃ
	for (int i = 1; i < 5; i++) {

		char leftname[100] = "sources/skin-usual/usual-left-prop/usual-left-prop";
		char leftnum[3]; _itoa_s(i, leftnum, 10);
		strcat_s(leftname, leftnum);
		strcat_s(leftname, ".png");
		surface = IMG_Load(leftname);
		skin.left_prop[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);

		char rightname[100] = "sources/skin-usual/usual-right-prop/usual-right-prop";
		char rightnum[3]; _itoa_s(i, rightnum, 10);
		strcat_s(rightname, rightnum);
		strcat_s(rightname, ".png");
		surface = IMG_Load(rightname);
		skin.right_prop[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);
	}

	// —Œ «¬≈«ƒ¿Ã»
	for (int i = 1; i < 4; i++) {

		char leftname[100] = "sources/skin-usual/usual-left-stars/usual-left-stars";
		char leftnum[3]; _itoa_s(i, leftnum, 10);
		strcat_s(leftname, leftnum);
		strcat_s(leftname, ".png");
		surface = IMG_Load(leftname);
		skin.left_stars[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);

		char rightname[100] = "sources/skin-usual/usual-right-stars/usual-right-stars";
		char rightnum[3]; _itoa_s(i, rightnum, 10);
		strcat_s(rightname, rightnum);
		strcat_s(rightname, ".png");
		surface = IMG_Load(rightname);
		skin.right_stars[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);
	}

	SDL_FreeSurface(surface);
}
void LoadBunnyTextures(SDL_Renderer*& renderer, Skin& skin) {

	SDL_Surface* surface;

	// —“¿Õƒ¿–“Õ€… — »Õ
	skin.pos = { 500, 500, 150, 150 };

	// —ÃŒ“–»“ ¬À≈¬Œ
	surface = IMG_Load("sources/skin-bunny/bunny-left.png");
	skin.left = SDL_CreateTextureFromSurface(renderer, surface);

	// —ÃŒ“–»“ ¬œ–¿¬Œ
	surface = IMG_Load("sources/skin-bunny/bunny-right.png");
	skin.right = SDL_CreateTextureFromSurface(renderer, surface);

	// —ÃŒ“–»“ ¬¬≈–’
	surface = IMG_Load("sources/skin-bunny/bunny-top.png");
	skin.top = SDL_CreateTextureFromSurface(renderer, surface);

	// œ–Œœ≈ÀÀ≈–
	skin.pos_prop = { 0,0,0,0 };
	surface = IMG_Load("sources/skin-bunny/bunny-prop.png");
	skin.prop = SDL_CreateTextureFromSurface(renderer, surface);

	// ƒ∆≈“œ¿ 
	skin.pos_jetpack = { 0,0,0,0 };
	surface = IMG_Load("sources/skin-bunny/bunny-jetpack.png");
	skin.jetpack = SDL_CreateTextureFromSurface(renderer, surface);

	// œ”Àﬂ
	for (int i = 0; i < BULLETS; i++) { skin.pos_bullets[i] = { 0,0,0,0 }; }
	surface = IMG_Load("sources/skin-bunny/bunny-bullet.png");
	skin.bullet = SDL_CreateTextureFromSurface(renderer, surface);

	// — ƒ∆≈“œ¿ ŒÃ
	for (int i = 1; i < 11; i++) {

		char leftname[100] = "sources/skin-bunny/bunny-left-jetpack/bunny-left-jetpack";
		char leftnum[3]; _itoa_s(i, leftnum, 10);
		strcat_s(leftname, leftnum);
		strcat_s(leftname, ".png");
		surface = IMG_Load(leftname);
		skin.left_jetpack[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);

		char rightname[100] = "sources/skin-bunny/bunny-right-jetpack/bunny-right-jetpack";
		char rightnum[3]; _itoa_s(i, rightnum, 10);
		strcat_s(rightname, rightnum);
		strcat_s(rightname, ".png");
		surface = IMG_Load(rightname);
		skin.right_jetpack[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);
	}

	// — œ–Œœ≈ÀÀ≈–ŒÃ
	for (int i = 1; i < 5; i++) {

		char leftname[100] = "sources/skin-bunny/bunny-left-prop/bunny-left-prop";
		char leftnum[3]; _itoa_s(i, leftnum, 10);
		strcat_s(leftname, leftnum);
		strcat_s(leftname, ".png");
		surface = IMG_Load(leftname);
		skin.left_prop[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);

		char rightname[100] = "sources/skin-bunny/bunny-right-prop/bunny-right-prop";
		char rightnum[3]; _itoa_s(i, rightnum, 10);
		strcat_s(rightname, rightnum);
		strcat_s(rightname, ".png");
		surface = IMG_Load(rightname);
		skin.right_prop[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);
	}

	// —Œ «¬≈«ƒ¿Ã»
	for (int i = 1; i < 4; i++) {

		char leftname[100] = "sources/skin-bunny/bunny-left-stars/bunny-left-stars";
		char leftnum[3]; _itoa_s(i, leftnum, 10);
		strcat_s(leftname, leftnum);
		strcat_s(leftname, ".png");
		surface = IMG_Load(leftname);
		skin.left_stars[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);

		char rightname[100] = "sources/skin-bunny/bunny-right-stars/bunny-right-stars";
		char rightnum[3]; _itoa_s(i, rightnum, 10);
		strcat_s(rightname, rightnum);
		strcat_s(rightname, ".png");
		surface = IMG_Load(rightname);
		skin.right_stars[i - 1] = SDL_CreateTextureFromSurface(renderer, surface);
	}

	SDL_FreeSurface(surface);
}
void Reload(SDL_Renderer*& renderer, Menu& menu, Game& game, SideMenu& sidemenu, Time& timee, Skin& skin) {

	menu.item = 5;

	timee.holeStart = 0, timee.holeEnd = 0;
	timee.holeStartSize = 0, timee.holeEndSize = 0;
	timee.ufoStart = 0, timee.ufoEnd = 0;
	timee.ufoStartSize = 0, timee.ufoEndSize = 0;
	timee.propStart = 0, timee.propEnd = 0;
	timee.jetpackStart = 0, timee.jetpackEnd = 0;
	timee.jetpackStart2 = 0, timee.jetpackEnd2 = 0;
	timee.shotStart = 0, timee.shotEnd = 0;
	timee.standStart = 0, timee.standEnd = 0;
	timee.deadStart = 0, timee.deadEnd = 0;
	timee.deadStart2 = 0, timee.deadEnd2 = 0;
	timee.gameoverStart = 0, timee.gameoverEnd = 0;

	sidemenu.score = 0;
	sidemenu.gameEnd = false;

	game.paused = false;
	game.dead = 0;
	game.dy = 0;
	game.stand = 1;
	game.dead = 0;
	game.plats = PLATS;
	game.plat_direction = 0;
	game.distance = 0;
	game.range_next = 5000;
	game.type_enemy;
	game.enemy_direction = 0;
	game.springNextRange = 1000;
	game.springUsed = false;
	game.propNextRange = 4000;
	game.propRange = 0;
	game.propPicked = false;
	game.propUsed = false;
	game.propNextSelected = true;
	game.jetpackNextRange = 7000;
	game.jetpackRange = 0;
	game.jetpackPicked = false;
	game.jetpackUsed = false;
	game.jetpackNextSelected = true;
	game.l = 0;
	game.standMemory = 1;
	game.pos_spring = { 0,0,0,0 };
	game.pos_plat_move = { 0,0,0,0 };
	game.pos_plat_break = { 0,0,0,0 };
	game.pos_plat_ghost = { 0,0,0,0 };
	game.pos_warning = { 0,0,0,0 };
	game.pos_ghoul = { 0,0,0,0 };
	game.pos_amogus = { 0,0,0,0 };
	game.pos_bat = { 0,0,0,0 };
	game.pos_ufo = { 0,0,0,0 };
	game.pos_hole = { 0,0,0,0 };
	game.pos_spring = { 0,0,0,0 };
	game.pos_spring_compressed = { 0,0,0,0 };
	game.pos_current = { 0,0,0,0 };

	skin.pos_prop = { 0,0,0,0 };
	skin.pos_jetpack = { 0,0,0,0 };
	skin.pos = { 500, 500, 150, 150 };
	for (int i = 0; i < BULLETS; i++) { skin.pos_bullets[i] = { 0,0,0,0 }; }
}
void DestroyTextures(SDL_Renderer*& renderer, Menu& menu, Game& game, SideMenu& sidemenu, Skin& skin) {

	SDL_DestroyTexture(menu.menu_background);
	SDL_DestroyTexture(menu.menu_background2);
	for(int i = 0; i<5; i++) SDL_DestroyTexture(menu.buttons[i]);
	for (int i = 0; i < 5; i++) SDL_DestroyTexture(menu.buttons_active[i]);
	for (int i = 0; i < 3; i++) SDL_DestroyTexture(menu.APPbuttons[i]);
	for (int i = 0; i < 3; i++) SDL_DestroyTexture(menu.APPbuttons_active[i]);
	SDL_DestroyTexture(menu.RULback);
	SDL_DestroyTexture(menu.SETback);
	SDL_DestroyTexture(menu.on);
	SDL_DestroyTexture(menu.off);
	SDL_DestroyTexture(game.background);
	SDL_DestroyTexture(game.plat_state);
	SDL_DestroyTexture(game.plat_move);
	SDL_DestroyTexture(game.plat_break);
	SDL_DestroyTexture(game.plat_ghost);
	SDL_DestroyTexture(game.warning);
	SDL_DestroyTexture(game.current);
	SDL_DestroyTexture(game.ghoul);
	SDL_DestroyTexture(game.amogus);
	SDL_DestroyTexture(game.amogus2);
	SDL_DestroyTexture(game.bat);
	SDL_DestroyTexture(game.ufo);
	SDL_DestroyTexture(game.spring);
	SDL_DestroyTexture(game.spring_compressed);
	SDL_DestroyTexture(skin.APPmenu);
	SDL_DestroyTexture(skin.left);
	SDL_DestroyTexture(skin.right);
	SDL_DestroyTexture(skin.top);
	SDL_DestroyTexture(skin.prop);
	SDL_DestroyTexture(skin.jetpack);
	for (int i = 0; i < 10; i++) SDL_DestroyTexture(skin.left_jetpack[i]);
	for (int i = 0; i < 10; i++) SDL_DestroyTexture(skin.right_jetpack[i]);
	for (int i = 0; i < 4; i++) SDL_DestroyTexture(skin.left_prop[i]);
	for (int i = 0; i < 4; i++) SDL_DestroyTexture(skin.right_prop[i]);
	for (int i = 0; i < 3; i++) SDL_DestroyTexture(skin.left_stars[i]);
	for (int i = 0; i < 3; i++) SDL_DestroyTexture(skin.right_stars[i]);
	SDL_DestroyTexture(skin.bullet);
	SDL_DestroyTexture(sidemenu.panelTexture);
	SDL_DestroyTexture(sidemenu.pause);
	SDL_DestroyTexture(sidemenu.play);
	SDL_DestroyTexture(sidemenu.sound);
	SDL_DestroyTexture(sidemenu.music);
	SDL_DestroyTexture(sidemenu.home);
	SDL_DestroyTexture(sidemenu.texture);
	for (int i = 0; i < 9; i++) SDL_DestroyTexture(sidemenu.endpanel[i]);
	SDL_DestroyTexture(sidemenu.statspanel);
	SDL_DestroyTexture(sidemenu.endmenubutton);
	SDL_DestroyTexture(sidemenu.endmenubutton_active);


	SDL_Texture* sound;
	SDL_Texture* music;
	SDL_Texture* home;
	SDL_Texture* texture;
	SDL_Texture* endpanel[9];
	SDL_Texture* statspanel;
	SDL_Texture* endmenubutton;
	SDL_Texture* endmenubutton_active;
}
void DestroySkinTextures(SDL_Renderer*& renderer, Skin& skin) {

	SDL_DestroyTexture(skin.left);
	SDL_DestroyTexture(skin.right);
	SDL_DestroyTexture(skin.top);
	SDL_DestroyTexture(skin.prop);
	SDL_DestroyTexture(skin.jetpack);
	for (int i = 0; i < 10; i++) SDL_DestroyTexture(skin.left_jetpack[i]);
	for (int i = 0; i < 10; i++) SDL_DestroyTexture(skin.right_jetpack[i]);
	for (int i = 0; i < 4; i++) SDL_DestroyTexture(skin.left_prop[i]);
	for (int i = 0; i < 4; i++) SDL_DestroyTexture(skin.right_prop[i]);
	for (int i = 0; i < 3; i++) SDL_DestroyTexture(skin.left_stars[i]);
	for (int i = 0; i < 3; i++) SDL_DestroyTexture(skin.right_stars[i]);
	SDL_DestroyTexture(skin.bullet);
}

void LoadMusic(Game& game, char* name) {

	if (game.MusicOn and !game.MusicLoaded) {
		game.Musics = Mix_LoadMUS(name);
		Mix_PlayMusic(game.Musics, -1);
		game.MusicLoaded = true;
	}

}
void LoadSound(Game& game, char* name) {

	if (game.SoundOn) {
		game.Sounds = Mix_LoadWAV(name);
		Mix_PlayChannel(-1, game.Sounds, 0);
	}
}
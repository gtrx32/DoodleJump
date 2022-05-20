#include "game.h"

void PlatGenerate(Game& game) {

	for (int i = 0; i < game.plats; i++) {

		bool check;

		do {

			check = true;

			game.pos_plats[i] = { rand() % (WIDTH - 212) + 112, rand() % (HEIGHT - 100) + 100, 100, 30 };

			for (int j = 0; j < game.plats; j++) {

				if (abs(game.pos_plats[i].x - game.pos_plats[j].x) < 200 and abs(game.pos_plats[i].y - game.pos_plats[j].y) < 100 and i != j) check = false;

			}

		} while (check == false);
	}
}
void MovePlat(Game& game, int score) {

	if (score > 5000) {

		int scroll = 2000;

		switch (game.plats) {
		case 14: { scroll = 2000; break; }
		case 13: { scroll = 1800; break; }
		case 12: { scroll = 1600; break; }
		case 11: { scroll = 1000; break; }
		case 10: { scroll = 750; break; }
		case 9: { scroll = 500; break; }
		case 8: { scroll = 250; break; }
		case 7: { scroll = 0; break; }
		}

		if (game.pos_plat_move.w == 0) {

			bool freeplace = true;

			for (int i = 0; i < game.plats; i++) {

				if (game.pos_plats[i].y < 0) {

					freeplace = false;
					break;
				}
			}
			if (game.pos_plat_ghost.y < 50) freeplace = false;
			if (game.pos_plat_break.y < 50) freeplace = false;

			if (freeplace and game.pos_plat_move.w == 0) {

				game.pos_plat_move = { rand() % (WIDTH - 212) + 112, -100, 100, 30 };
			}
		}
		else {

			if (game.plat_direction == 0) {

				if (game.pos_plat_move.x < 112 + 10) game.plat_direction = 1;
				game.pos_plat_move.x -= 2;
			}
			else if (game.plat_direction == 1) {

				if (game.pos_plat_move.x > WIDTH - 100 - 10) game.plat_direction = 0;
				game.pos_plat_move.x += 2;
			}
		}

		if (game.pos_plat_move.y > HEIGHT + scroll) game.pos_plat_move = { 0,0,0,0 };
	}
}
void GhostPlat(Game& game, int score) {

	if (game.pos_plat_ghost.w == 0) {

		bool freeplace = true;

		for (int i = 0; i < game.plats; i++) {

			if (game.pos_plats[i].y < 50) {

				freeplace = false;
				break;
			}
		}
		if (game.pos_plat_move.y < 0) freeplace = false;
		if (game.pos_plat_break.y < 0) freeplace = false;

		if (freeplace and game.pos_plat_ghost.w == 0) {

			game.pos_plat_ghost = { rand() % (WIDTH - 212) + 112, -50, 100, 30 };
		}
	}

	if (game.pos_plat_ghost.y > HEIGHT + 150) game.pos_plat_ghost = { 0,0,0,0 };
}
void BreakPlat(Game& game, int score) {

	if (score > 10000) {

		if (game.pos_plat_break.w == 0) {

			bool freeplace = true;

			for (int i = 0; i < game.plats; i++) {

				if (game.pos_plats[i].y < 0) {

					freeplace = false;
					break;
				}
			}
			if (game.pos_plat_move.y < 0) freeplace = false;
			if (game.pos_plat_ghost.y < 0) freeplace = false;

			if (freeplace and game.pos_plat_break.w == 0) {

				game.pos_plat_break = { rand() % (WIDTH - 212) + 112, -150, 100, 30 };
			}
		}

		if (game.pos_plat_break.y > HEIGHT) game.pos_plat_break = { 0,0,0,0 };
	}
}
bool CheckPosPlats(Game& game, int score, int x, int y, int n, int k) {

	bool overlay = false;

	if (n == game.plats - 1) {

		for (int j = 0; j < game.plats; j++) {

			if (abs(y - game.pos_plats[j].y) < 300 and n != j) { overlay = true; break; }
		}

		if (overlay == true) {

			switch (game.plats) {
			case 14: if (score > 1000) { game.plats -= 1; break; }
			case 13: if (score > 3000) { game.plats -= 1; break; }
			case 12: if (score > 5000) { game.plats -= 1; break; }
			case 11: if (score > 7000) { game.plats -= 1; break; }
			case 10: if (score > 10000) { game.plats -= 1; break; }
			case 9: if (score > 30000) { game.plats -= 1; break; }
			case 8: if (score > 100000) { game.plats -= 1; break; }
			default: break;
			}

		}
	}

	if (k > 100) {

		return true;
	}

	if (game.plats > 10) {
		for (int i = 0; i < game.plats; i++) {

			if (abs(x - game.pos_plats[i].x) < 200 and abs(y - game.pos_plats[i].y) < 100 and i != n
				and abs(y - game.pos_plat_move.y < 100) and abs(y - game.pos_plat_ghost.y < 100) and abs(y - game.pos_plat_break.y < 100)) return false;

		}
	}
	else if (game.plats < 11) {
		for (int i = 0; i < game.plats; i++) {

			if (abs(x - game.pos_plats[i].x) < 300 and abs(y - game.pos_plats[i].y) < 200 and i != n
				and abs(y - game.pos_plat_move.y < 200) and abs(y - game.pos_plat_ghost.y < 100) and abs(y - game.pos_plat_break.y < 100)) return false;

		}
	}

	return true;
}

void Spring(Game& game, Skin& skin, Menu& menu, int score) {

	if (score > game.springNextRange and game.pos_spring.w == 0 and game.pos_spring_compressed.w == 0) {

		for (int i = 0; i < game.plats; i++) {

			if (game.pos_plats[i].y < 0) {
				game.pos_spring = { game.pos_plats[i].x + 32, game.pos_plats[i].y - 52, 35, 50 };
				game.springUsed = false;
				break;
			}
		}
	}

	if (game.springUsed and game.pos_spring.w != 0) {

		game.pos_spring_compressed = { game.pos_spring.x, game.pos_spring.y + 21, 35, 29 };
		game.pos_spring = { 0,0,0,0 };
	}

	if ((game.pos_spring.y > HEIGHT or game.pos_spring_compressed.y > HEIGHT) and (game.pos_spring.w != 0 or game.pos_spring_compressed.w != 0)) {

		game.pos_spring = { 0,0,0,0 };
		game.pos_spring_compressed = { 0,0,0,0 };
		game.springNextRange = score + rand() % (1000) + 2000;
	}
}
void Prop(Game& game, Skin& skin, Menu& menu, Time& timee, int score) {

	if (score > game.propNextRange and skin.pos_prop.w == 0) {

		for (int i = 0; i < game.plats; i++) {

			if (game.pos_plats[i].y < 0) {
				skin.pos_prop = { game.pos_plats[i].x + 20, game.pos_plats[i].y - 41, 59, 39 };
				game.propNextSelected = false;
				break;
			}
		}
	}

	if (game.propPicked) {

		if (game.propRange < 5000) {

			timee.propEnd = time(NULL) - timee.propStart;

			if (timee.propEnd > 50) {

				game.stand += 1;
				if (game.stand == 16) game.stand = 12;
				if (game.stand == 34) game.stand = 30;

				timee.propStart = time(NULL);
			}
		}
		else {

			if (game.stand < 19) game.stand = 1;
			if (game.stand > 18) game.stand = 19;
			game.propPicked = false;
			game.propRange = 0;
		}

		if (game.move[SDL_SCANCODE_A] or game.move[SDL_SCANCODE_LEFT]) {
			if (game.stand > 18) game.stand -= 18;
		}
		if (game.move[SDL_SCANCODE_D] or game.move[SDL_SCANCODE_RIGHT]) {
			if (game.stand < 19) game.stand += 18;
		}

		game.dy = -5;
		game.propRange -= game.dy;
	}

	if (game.propPicked and skin.pos_prop.w != 0) {

		skin.pos_prop = { 0,0,0,0 };
	}

	if (skin.pos_prop.y > HEIGHT and skin.pos_prop.w != 0) skin.pos_prop = { 0,0,0,0 };

	if (skin.pos_prop.w == 0 and !game.propNextSelected) {

		game.propNextRange = score + rand() % (3000) + 7000;
		game.propNextSelected = true;
	}
}
void Jetpack(Game& game, Skin& skin, Menu& menu, Time& timee, int score) {

	if (score > game.jetpackNextRange and skin.pos_jetpack.w == 0) {

		for (int i = 0; i < game.plats; i++) {

			if (game.pos_plats[i].y < 0) {
				skin.pos_jetpack = { game.pos_plats[i].x + 35, game.pos_plats[i].y - 73, 30, 70 };
				game.jetpackNextSelected = false;
				break;
			}
		}
	}

	if (game.jetpackPicked) {

		timee.jetpackEnd2 = clock() - timee.jetpackStart2;

		if (timee.jetpackEnd2 < 400) {

			timee.jetpackEnd = clock() - timee.jetpackStart;

			if (timee.jetpackEnd > 200) {

				game.stand += 1;
				if (game.stand == 5) game.stand = 2;
				if (game.stand == 23) game.stand = 20;

				timee.jetpackStart = clock();
			}
		}
		else if (timee.jetpackEnd2 >= 400 and timee.jetpackEnd2 < 3500) {

			timee.jetpackEnd = clock() - timee.jetpackStart;

			if (timee.jetpackEnd > 150) {

				game.stand += 1;
				if (game.stand == 8) game.stand = 5;
				if (game.stand == 26) game.stand = 23;

				timee.jetpackStart = clock();
			}
		}
		else if (timee.jetpackEnd2 >= 3500 and timee.jetpackEnd2 < 4500) {

			timee.jetpackEnd = clock() - timee.jetpackStart;

			if (timee.jetpackEnd > 150) {

				game.stand += 1;
				if (game.stand == 11) game.stand = 8;
				if (game.stand == 29) game.stand = 26;

				timee.jetpackStart = clock();
			}
		}
		else if (timee.jetpackEnd2 >= 4500 and timee.jetpackEnd2 < 5000) {

			if (game.stand < 19) game.stand = 11;
			if (game.stand > 18) game.stand = 29;
		}
		else if (timee.jetpackEnd2 >= 5000) {

			if (game.stand < 19) game.stand = 1;
			if (game.stand > 18) game.stand = 19;
			game.jetpackPicked = false;
			game.jetpackRange = 0;
		}

		if (game.move[SDL_SCANCODE_A] or game.move[SDL_SCANCODE_LEFT]) {
			if (game.stand > 18) game.stand -= 18;
		}
		if (game.move[SDL_SCANCODE_D] or game.move[SDL_SCANCODE_RIGHT]) {
			if (game.stand < 19) game.stand += 18;
		}

		game.dy = -9;
		game.jetpackRange -= game.dy;
	}

	if (game.jetpackPicked and skin.pos_jetpack.w != 0) {

		skin.pos_jetpack = { 0,0,0,0 };
	}

	if (skin.pos_jetpack.y > HEIGHT and skin.pos_jetpack.w != 0) skin.pos_jetpack = { 0,0,0,0 };

	if (skin.pos_jetpack.w == 0 and !game.jetpackNextSelected) {

		game.jetpackNextRange = score + rand() % (3000) + 15000;
		game.jetpackNextSelected = true;
	}
}

void Shot(Game& game, Skin& skin, Time& timee) {

	timee.shotEnd = clock() - timee.shotStart;

	if (game.stand == 0 and timee.shotEnd > 300) {

		game.stand = game.standMemory;
	}

	if (game.stand == 1 or game.stand == 19) {

		if (game.move[SDL_SCANCODE_SPACE] and timee.shotEnd > 150) {

			LoadSound(game, game.soundShot);

			if (game.stand == 1) game.standMemory = 1;
			if (game.stand == 19) game.standMemory = 19;

			game.stand = 0;

			skin.pos_bullets[game.l] = { skin.pos.x + 65, skin.pos.y, 14, 14 };

			game.l += 1;
			if (game.l == BULLETS) game.l = 0;

			timee.shotStart = clock();
		}
	}

	for (int i = 0; i < BULLETS; i++) {

		skin.pos_bullets[i].y -= 6;

		if (skin.pos_bullets[i].y < HEIGHT * (-1) or skin.pos_bullets[i].y > HEIGHT) skin.pos_bullets[i] = { 0,0,0,0 };
	}

}
void EnemyMove(Game& game, Skin& skin) {

	if (game.type_enemy == 0 or game.type_enemy == 1 or game.type_enemy == 2) {

		if (game.enemy_direction == 0) {

			if (game.pos_current.x < 112 + 10) game.enemy_direction = 1;
			game.pos_current.x -= 2;
		}
		else if (game.enemy_direction == 1) {

			if (game.pos_current.x > WIDTH - 100 - 10) game.enemy_direction = 0;
			game.pos_current.x += 2;
		}
	}

	if (game.pos_current.y > HEIGHT) {

		game.pos_current = { 0,0,0,0 };
	}
}
void EnemyAppear(Game& game) {

	switch (game.type_enemy) {
	case 0: // юлнцся
		game.pos_current = { game.pos_warning.x, -299, 75, 99 };
		break;
	case 1: // лшьэ
		game.pos_current = { game.pos_warning.x, -287, 156, 87 };
		break;
	case 2: // цскэ
		game.pos_current = { game.pos_warning.x, -375, 122, 175 };
		break;
	case 3: // вепмюъ дшпю
		game.pos_current = { game.pos_warning.x, -344, 148, 144 };
		break;
	case 4: // мкн
		game.pos_current = { game.pos_warning.x, -341, 130, 190 };
		break;
	}
}
void EnemyWarning(Game& game, int score) {

	if (game.pos_warning.w == 0 and score > game.range_next) {

		game.pos_warning = { rand() % (WIDTH - 212) + 112, 0, 100, 100 };
	}

	if (game.pos_warning.w != 0 and game.distance > 1000) {

		game.type_enemy = rand() % (5);
		EnemyAppear(game);

		game.distance = 0;
		game.pos_warning = { 0,0,0,0 };

		game.range_next = score + rand() % (5000) + 2000;
	}
}
bool CheckContact(Skin& skin, Game& game, Time& timee, int stand, int dy, int score) {

	// ярнкймнбемхъ я окюртнплюлх
	switch (stand) {
	case 1: case 0: // онбепмср бкебн

		// я окюртнплюлх
		// нашвмюъ
		for (int i = 0; i < game.plats; i++) {
			if ((dy > 0) && (skin.pos.x > game.pos_plats[i].x - skin.pos.w + 60) // якебю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
				&& (skin.pos.x + 50 < game.pos_plats[i].x + game.pos_plats[i].w) // яопюбю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
				&& (skin.pos.y + skin.pos.h > game.pos_plats[i].y + 30) // ябепус нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
				&& (skin.pos.y + 125 < game.pos_plats[i].y + game.pos_plats[i].h)) // ямхгс нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			{
				LoadSound(game, game.soundJump);
				return true;
			}
		}
		// дбхцючыюъяъ
		if ((dy > 0) && (skin.pos.x > game.pos_plat_move.x - skin.pos.w + 60) // якебю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.x + 50 < game.pos_plat_move.x + game.pos_plat_move.w) // яопюбю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.y + skin.pos.h > game.pos_plat_move.y + 30) // ябепус нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.y + 125 < game.pos_plat_move.y + game.pos_plat_move.h)) // ямхгс нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
		{
			LoadSound(game, game.soundJump);
			return true;
		}
		// кнлючыюъяъ
		if ((dy > 0) && (skin.pos.x > game.pos_plat_break.x - skin.pos.w + 60) // якебю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.x + 50 < game.pos_plat_break.x + game.pos_plat_break.w) // яопюбю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.y + skin.pos.h > game.pos_plat_break.y + 30) // ябепус нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.y + 125 < game.pos_plat_break.y + game.pos_plat_break.h)) // ямхгс нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
		{
			LoadSound(game, game.soundBreakPlat);
			game.pos_plat_break = { 0,0,0,0 };
			return true;
		}

		// опсфхмю
		if (((game.pos_spring.x > skin.pos.x + 40 and game.pos_spring.x < skin.pos.x + skin.pos.w - 40 and
			game.pos_spring.y > skin.pos.y + 100 and game.pos_spring.y < skin.pos.y + skin.pos.h - 25)

			or (game.pos_spring.x + 35 > skin.pos.x + 40 and game.pos_spring.x + 35 < skin.pos.x + skin.pos.w - 40 and
				game.pos_spring.y > skin.pos.y + 100 and game.pos_spring.y < skin.pos.y + skin.pos.h - 25))

			and game.dy > 0)
		{
			LoadSound(game, game.soundSpring);
			game.springUsed = true;
			game.dy = -9;
		}
		// опноеккеп
		if ((skin.pos_prop.x > skin.pos.x + 40 and skin.pos_prop.x < skin.pos.x + skin.pos.w - 40 and
			skin.pos_prop.y > skin.pos.y + 40 and skin.pos_prop.y < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_prop.x + 35 > skin.pos.x + 40 and skin.pos_prop.x + 35 < skin.pos.x + skin.pos.w - 40 and
				skin.pos_prop.y > skin.pos.y + 40 and skin.pos_prop.y < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_prop.x > skin.pos.x + 40 and skin.pos_prop.x < skin.pos.x + skin.pos.w - 40 and
				skin.pos_prop.y + skin.pos_prop.h > skin.pos.y + 40 and skin.pos_prop.y + skin.pos_prop.h < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_prop.x + 35 > skin.pos.x + 40 and skin.pos_prop.x + 35 < skin.pos.x + skin.pos.w - 40 and
				skin.pos_prop.y + skin.pos_prop.h > skin.pos.y + 40 and skin.pos_prop.y + skin.pos_prop.h < skin.pos.y + skin.pos.h - 25))
		{
			LoadSound(game, game.soundProp);
			game.propPicked = true;
			if (game.stand < 19) game.stand = 12;
			else game.stand = 30;
		}
		// дфероюй
		if ((skin.pos_jetpack.x > skin.pos.x + 40 and skin.pos_jetpack.x < skin.pos.x + skin.pos.w - 40 and
			skin.pos_jetpack.y > skin.pos.y + 40 and skin.pos_jetpack.y < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_jetpack.x + 35 > skin.pos.x + 40 and skin.pos_jetpack.x + 35 < skin.pos.x + skin.pos.w - 40 and
				skin.pos_jetpack.y > skin.pos.y + 40 and skin.pos_jetpack.y < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_jetpack.x > skin.pos.x + 40 and skin.pos_jetpack.x < skin.pos.x + skin.pos.w - 40 and
				skin.pos_jetpack.y + skin.pos_jetpack.h > skin.pos.y + 40 and skin.pos_jetpack.y + skin.pos_jetpack.h < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_jetpack.x + 35 > skin.pos.x + 40 and skin.pos_jetpack.x + 35 < skin.pos.x + skin.pos.w - 40 and
				skin.pos_jetpack.y + skin.pos_jetpack.h > skin.pos.y + 40 and skin.pos_jetpack.y + skin.pos_jetpack.h < skin.pos.y + skin.pos.h - 25))
		{
			LoadSound(game, game.soundJetpack);
			timee.jetpackStart2 = clock();
			game.jetpackPicked = true;
			if (game.stand < 19) game.stand = 2;
			else game.stand = 20;

		}

		// юлнцся
		if (game.type_enemy == 0) {

			if ((skin.pos.x + 15 > game.pos_current.x and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w and
				skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 15 > game.pos_current.x and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossMonster);
				game.dead = 2;
				game.dy = 0;
				if (game.stand < 19) game.stand = 16;
				else game.stand = 34;
			}
		}
		// лшьэ
		else if (game.type_enemy == 1) {

			if ((skin.pos.x + 15 > game.pos_current.x and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w and
				skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 15 > game.pos_current.x and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossMonster);
				game.dead = 2;
				game.dy = 0;
				if (game.stand < 19) game.stand = 16;
				else game.stand = 34;
			}
		}
		// цскэ
		else if (game.type_enemy == 2) {

			if ((skin.pos.x + 15 > game.pos_current.x and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w and
				skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 15 > game.pos_current.x and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossMonster);
				game.dead = 2;
				game.dy = 0;
				if (game.stand < 19) game.stand = 16;
				else game.stand = 34;
			}
		}
		// вепмюъ дшпю
		else if (game.type_enemy == 3) {

			if ((skin.pos.x + 15 > game.pos_current.x and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w and
				skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 15 > game.pos_current.x and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossHole);
				game.dead = 3;
				game.dy = 0;
			}
		}
		// мкн
		else if (game.type_enemy == 4) {

			if ((skin.pos.x + 15 > game.pos_current.x + 30 and skin.pos.x + 15 < game.pos_current.x + game.pos_current.w - 30 and
				skin.pos.y + 30 > game.pos_current.y + 60 and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 105 > game.pos_current.x + 30 and skin.pos.x + 105 < game.pos_current.x + game.pos_current.w - 30 and
					skin.pos.y + 30 > game.pos_current.y + 60 and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossUFO);
				game.dead = 4;
				game.dy = 0;
			}
		}

		break;

	case 19: // онбепмср бопюбн

		// я окюртнплюлх
		// нашвмюъ
		for (int i = 0; i < game.plats; i++) {
			if ((dy > 0) && (skin.pos.x > game.pos_plats[i].x - skin.pos.w + 60) // якебю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
				&& (skin.pos.x + 45 < game.pos_plats[i].x + game.pos_plats[i].w) // яопюбю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
				&& (skin.pos.y + skin.pos.h > game.pos_plats[i].y + 30) // ябепус нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
				&& (skin.pos.y + 125 < game.pos_plats[i].y + game.pos_plats[i].h)) // ямхгс нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			{
				LoadSound(game, game.soundJump);
				return true;
			}
		}
		// дбхцючыюъяъ
		if ((dy > 0) && (skin.pos.x > game.pos_plat_move.x - skin.pos.w + 60) // якебю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.x + 45 < game.pos_plat_move.x + game.pos_plat_move.w) // яопюбю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.y + skin.pos.h > game.pos_plat_move.y + 30) // ябепус нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.y + 125 < game.pos_plat_move.y + game.pos_plat_move.h)) // ямхгс нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
		{
			LoadSound(game, game.soundJump);
			return true;
		}
		// кнлючыюъяъ
		if ((dy > 0) && (skin.pos.x > game.pos_plat_break.x - skin.pos.w + 60) // якебю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.x + 45 < game.pos_plat_break.x + game.pos_plat_break.w) // яопюбю нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.y + skin.pos.h > game.pos_plat_break.y + 30) // ябепус нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
			&& (skin.pos.y + 125 < game.pos_plat_break.y + game.pos_plat_break.h)) // ямхгс нр окюртнплш (опх сбекхвемхх вхякю слемэьюеряъ ухранйя)
		{
			LoadSound(game, game.soundBreakPlat);
			game.pos_plat_break = { 0,0,0,0 };
			return true;
		}

		// опсфхмю
		if (((game.pos_spring.x > skin.pos.x + 40 and game.pos_spring.x < skin.pos.x + skin.pos.w - 60 and
			game.pos_spring.y > skin.pos.y + 100 and game.pos_spring.y < skin.pos.y + skin.pos.h - 25)

			or (game.pos_spring.x + 35 > skin.pos.x + 40 and game.pos_spring.x + 35 < skin.pos.x + skin.pos.w - 40 and
				game.pos_spring.y > skin.pos.y + 100 and game.pos_spring.y < skin.pos.y + skin.pos.h - 25))

			and game.dy > 0)
		{
			LoadSound(game, game.soundSpring);
			game.springUsed = true;
			game.dy = -9;
		}
		// опноеккеп
		if ((skin.pos_prop.x > skin.pos.x + 40 and skin.pos_prop.x < skin.pos.x + skin.pos.w - 60 and
			skin.pos_prop.y > skin.pos.y + 100 and skin.pos_prop.y < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_prop.x + 35 > skin.pos.x + 40 and skin.pos_prop.x + 35 < skin.pos.x + skin.pos.w - 40 and
				skin.pos_prop.y > skin.pos.y + 100 and skin.pos_prop.y < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_prop.x > skin.pos.x + 40 and skin.pos_prop.x < skin.pos.x + skin.pos.w - 60 and
				skin.pos_prop.y + skin.pos_prop.h > skin.pos.y + 40 and skin.pos_prop.y + skin.pos_prop.h < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_prop.x + 35 > skin.pos.x + 40 and skin.pos_prop.x + 35 < skin.pos.x + skin.pos.w - 40 and
				skin.pos_prop.y + skin.pos_prop.h > skin.pos.y + 40 and skin.pos_prop.y + skin.pos_prop.h < skin.pos.y + skin.pos.h - 25))
		{
			LoadSound(game, game.soundProp);
			game.propPicked = true;
			if (game.stand < 19) game.stand = 12;
			else game.stand = 30;
		}
		// дфероюй
		if ((skin.pos_jetpack.x > skin.pos.x + 40 and skin.pos_jetpack.x < skin.pos.x + skin.pos.w - 60 and
			skin.pos_jetpack.y > skin.pos.y + 100 and skin.pos_jetpack.y < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_jetpack.x + 35 > skin.pos.x + 40 and skin.pos_jetpack.x + 35 < skin.pos.x + skin.pos.w - 40 and
				skin.pos_jetpack.y > skin.pos.y + 100 and skin.pos_jetpack.y < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_jetpack.x > skin.pos.x + 40 and skin.pos_jetpack.x < skin.pos.x + skin.pos.w - 60 and
				skin.pos_jetpack.y + skin.pos_jetpack.h > skin.pos.y + 40 and skin.pos_jetpack.y + skin.pos_jetpack.h < skin.pos.y + skin.pos.h - 25)

			or (skin.pos_jetpack.x + 35 > skin.pos.x + 40 and skin.pos_jetpack.x + 35 < skin.pos.x + skin.pos.w - 40 and
				skin.pos_jetpack.y + skin.pos_jetpack.h > skin.pos.y + 40 and skin.pos_jetpack.y + skin.pos_jetpack.h < skin.pos.y + skin.pos.h - 25))
		{
			LoadSound(game, game.soundJetpack);
			timee.jetpackStart2 = clock();
			game.jetpackPicked = true;
			if (game.stand < 19) game.stand = 2;
			else game.stand = 20;
		}

		// юлнцся
		if (game.type_enemy == 0) {

			if ((skin.pos.x + 35 > game.pos_current.x and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w and
				skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 35 > game.pos_current.x and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossMonster);
				game.dead = 2;
				game.dy = 0;
				if (game.stand < 19) game.stand = 16;
				else game.stand = 34;
			}
		}
		// лшьэ
		else if (game.type_enemy == 1) {

			if ((skin.pos.x + 35 > game.pos_current.x and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w and
				skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 35 > game.pos_current.x and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossMonster);
				game.dead = 2;
				game.dy = 0;
				if (game.stand < 19) game.stand = 16;
				else game.stand = 34;
			}
		}
		// цскэ
		else if (game.type_enemy == 2) {

			if ((skin.pos.x + 35 > game.pos_current.x and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w and
				skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 35 > game.pos_current.x and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossMonster);
				game.dead = 2;
				game.dy = 0;
				if (game.stand < 19) game.stand = 16;
				else game.stand = 34;
			}
		}
		// вепмюъ дшпю
		else if (game.type_enemy == 3) {

			if ((skin.pos.x + 35 > game.pos_current.x and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w and
				skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 30 > game.pos_current.y and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 35 > game.pos_current.x and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w and
					skin.pos.y + 120 > game.pos_current.y and skin.pos.y + 120 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossHole);
				game.dead = 3;
				game.dy = 0;
			}
		}
		// мкн
		else if (game.type_enemy == 4) {

			if ((skin.pos.x + 35 > game.pos_current.x + 30 and skin.pos.x + 35 < game.pos_current.x + game.pos_current.w - 30 and
				skin.pos.y + 30 > game.pos_current.y + 60 and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h)

				or (skin.pos.x + 125 > game.pos_current.x + 30 and skin.pos.x + 125 < game.pos_current.x + game.pos_current.w - 30 and
					skin.pos.y + 30 > game.pos_current.y + 60 and skin.pos.y + 30 < game.pos_current.y + game.pos_current.h))
			{
				LoadSound(game, game.soundLossUFO);
				game.dead = 4;
				game.dy = 0;
			}
		}

		break;
	}

	// бшунд гю йпюъ хцпнбни накюярх
	if (skin.pos.x > WIDTH - 33 && stand == 19) skin.pos.x = -50 + 112;
	if (skin.pos.x < -100 + 112 && stand == 1) skin.pos.x = WIDTH - 80;

	// оюдемхе
	if (skin.pos.y > HEIGHT - 100) {

		if (score == 0) game.dy = -5;
		else {
			LoadSound(game, game.soundLossFall);
			game.dead = 1;
		}
	}

	// оскх
	for (int i = 0; i < BULLETS; i++) {

		if ((skin.pos_bullets[i].x + skin.pos_bullets[i].w > game.pos_current.x
			and skin.pos_bullets[i].x + skin.pos_bullets[i].w < game.pos_current.x + game.pos_current.w
			and skin.pos_bullets[i].y + skin.pos_bullets[i].h > game.pos_current.y
			and skin.pos_bullets[i].y + skin.pos_bullets[i].h < game.pos_current.y + game.pos_current.h)
			and game.type_enemy < 3)
		{
			LoadSound(game, game.soundStrike);
			game.pos_current = { 0,0,0,0 };
			skin.pos_bullets[i] = { 0,0,0,0 };
		}

		if ((skin.pos_bullets[i].x + skin.pos_bullets[i].w > game.pos_current.x
			and skin.pos_bullets[i].x + skin.pos_bullets[i].w < game.pos_current.x + game.pos_current.w
			and skin.pos_bullets[i].y + skin.pos_bullets[i].h > game.pos_current.y
			and skin.pos_bullets[i].y + skin.pos_bullets[i].h < game.pos_current.y + 70)
			and game.type_enemy == 4)
		{
			LoadSound(game, game.soundStrike);
			game.pos_current = { 0,0,0,0 };
			skin.pos_bullets[i] = { 0,0,0,0 };
		}
	}

	if (game.dead != 0) timee.deadStart2 = clock();

	return false;
}

void GameOver(SDL_Renderer* renderer, Game& game, SideMenu& sidemenu, Time& timee, Menu& menu, Skin& skin) {

	timee.gameoverEnd = clock() - timee.gameoverStart;

	if (timee.gameoverEnd < 25) SDL_RenderCopy(renderer, sidemenu.endpanel[0], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd < 50 and timee.gameoverEnd >= 25) SDL_RenderCopy(renderer, sidemenu.endpanel[1], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd < 75 and timee.gameoverEnd >= 50) SDL_RenderCopy(renderer, sidemenu.endpanel[2], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd < 100 and timee.gameoverEnd >= 75) SDL_RenderCopy(renderer, sidemenu.endpanel[3], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd < 125 and timee.gameoverEnd >= 100) SDL_RenderCopy(renderer, sidemenu.endpanel[4], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd < 150 and timee.gameoverEnd >= 125) SDL_RenderCopy(renderer, sidemenu.endpanel[5], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd < 175 and timee.gameoverEnd >= 150) SDL_RenderCopy(renderer, sidemenu.endpanel[6], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd < 200 and timee.gameoverEnd >= 175) SDL_RenderCopy(renderer, sidemenu.endpanel[7], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd < 225 and timee.gameoverEnd >= 200) SDL_RenderCopy(renderer, sidemenu.endpanel[8], NULL, &sidemenu.pos_endpanel);
	else if (timee.gameoverEnd >= 225) {

		SDL_RenderCopy(renderer, sidemenu.statspanel, NULL, &sidemenu.pos_statspanel);
		GetScoreText(renderer, sidemenu, menu, 1);
		SDL_RenderCopy(renderer, sidemenu.endmenubutton, NULL, &sidemenu.pos_endmenubutton);
		if (game.event.type == SDL_MOUSEBUTTONDOWN and CheckEntry(sidemenu.pos_endmenubutton)) {

			LoadSound(game, game.soundMenuSelect);
			Reload(renderer, menu, game, sidemenu, timee, skin);
			PlatGenerate(game);
		}
		if (CheckEntry(sidemenu.pos_endmenubutton)) SDL_RenderCopy(renderer, sidemenu.endmenubutton_active, NULL, &sidemenu.pos_endmenubutton);
	}
}
void Death(Game& game, Skin& skin, Time& timee, SideMenu& sidemenu) {

	switch (game.dead) {
	case 1: // оюдемхе

		game.dy += 0.04;

		if (skin.pos.y > 400) skin.pos.y -= game.dy / 4;

		// окюртнплш
		for (int i = 0; i < game.plats; i++) { game.pos_plats[i].y = game.pos_plats[i].y - game.dy; }
		if (game.pos_plat_move.w != 0) game.pos_plat_move.y = game.pos_plat_move.y - game.dy;
		if (game.pos_plat_ghost.w != 0) game.pos_plat_ghost.y = game.pos_plat_ghost.y - game.dy;
		if (game.pos_plat_break.w != 0) game.pos_plat_break.y = game.pos_plat_break.y - game.dy;

		if (game.pos_current.y != 0) game.pos_current.y = game.pos_current.y - game.dy;

		if (game.pos_spring.w != 0) game.pos_spring.y -= game.dy;
		if (game.pos_spring_compressed.w != 0) game.pos_spring_compressed.y -= game.dy;
		if (skin.pos_prop.w != 0) skin.pos_prop.y -= game.dy;
		if (skin.pos_jetpack.w != 0) skin.pos_jetpack.y -= game.dy;

		break;

	case 2: // лнмярпш

		timee.deadEnd = clock() - timee.deadStart;

		if (timee.deadEnd > 70) {

			game.stand += 1;
			if (game.stand == 19) game.stand = 16;
			if (game.stand == 37) game.stand = 34;

			timee.deadStart = clock();
		}

		if (skin.pos.y != HEIGHT) {

			game.dy += 0.02;

			// окюртнплш
			for (int i = 0; i < game.plats; i++) { game.pos_plats[i].y = game.pos_plats[i].y - game.dy; }
			if (game.pos_plat_move.w != 0) game.pos_plat_move.y = game.pos_plat_move.y - game.dy;
			if (game.pos_plat_ghost.w != 0) game.pos_plat_ghost.y = game.pos_plat_ghost.y - game.dy;
			if (game.pos_plat_break.w != 0) game.pos_plat_break.y = game.pos_plat_break.y - game.dy;

			game.pos_current.y = game.pos_current.y - game.dy;

			if (game.pos_spring.w != 0) game.pos_spring.y -= game.dy;
			if (game.pos_spring_compressed.w != 0) game.pos_spring_compressed.y -= game.dy;
			if (skin.pos_prop.w != 0) skin.pos_prop.y -= game.dy;
			if (skin.pos_jetpack.w != 0) skin.pos_jetpack.y -= game.dy;
		}

		break;

	case 3: // вепмюъ дшпю

		timee.holeEnd = clock() - timee.holeStart;

		if (timee.holeEnd > 5) {

			if ((skin.pos.x + skin.pos.w / 2) - (game.pos_current.x + game.pos_current.w / 2) < -3) {
				skin.pos.x += 1;
			}
			if ((skin.pos.x + skin.pos.w / 2) - (game.pos_current.x + game.pos_current.w / 2) > 3) {
				skin.pos.x -= 1;
			}

			if ((skin.pos.y + skin.pos.h / 2) - (game.pos_current.y + game.pos_current.h / 2) < -3) {
				skin.pos.y += 1;
			}
			if ((skin.pos.y + skin.pos.h / 2) - (game.pos_current.y + game.pos_current.h / 2) > 3) {
				skin.pos.y -= 1;
			}
			timee.holeStart = clock();
		}

		timee.holeEndSize = clock() - timee.holeStartSize;

		if (timee.holeEndSize > 10) {

			if (skin.pos.w > 0) skin.pos.w -= 1;
			if (skin.pos.h > 0) skin.pos.h -= 1;
			timee.holeStartSize = clock();
		}

		break;

	case 4: // мкн

		timee.ufoEnd = clock() - timee.ufoStart;

		if (timee.ufoEnd > 5) {

			if (abs((skin.pos.x + skin.pos.w / 2) - (game.pos_current.x + game.pos_current.w / 2)) > 3) {

				if ((skin.pos.x + skin.pos.w / 2) - (game.pos_current.x + game.pos_current.w / 2) < -3) skin.pos.x += 1;
				if ((skin.pos.x + skin.pos.w / 2) - (game.pos_current.x + game.pos_current.w / 2) > 3) skin.pos.x -= 1;
			}
			else {
				if ((skin.pos.y + skin.pos.h / 2) - (game.pos_current.y + game.pos_current.h / 4) < -3) skin.pos.y += 1;
				if ((skin.pos.y + skin.pos.h / 2) - (game.pos_current.y + game.pos_current.h / 4) > 3) skin.pos.y -= 1;
			}

			timee.ufoStart = clock();
		}

		timee.ufoEndSize = clock() - timee.ufoStartSize;

		if (timee.ufoEndSize > 10) {

			if (skin.pos.w > 0) skin.pos.w -= 1;
			if (skin.pos.h > 0) skin.pos.h -= 1;
			timee.ufoStartSize = clock();
		}

		break;

	default:

		break;
	}

	timee.deadEnd2 = clock() - timee.deadStart2;
}

void GetScoreText(SDL_Renderer*& renderer, SideMenu& sidemenu, Menu& menu, int type) {

	if (type == 0) SDL_RenderCopy(renderer, sidemenu.panelTexture, NULL, &sidemenu.panel);

	_itoa_s(sidemenu.score, sidemenu.scoreout, 10);

	sidemenu.surface = TTF_RenderText_Shaded(menu.comic, sidemenu.scoreout, sidemenu.fore, sidemenu.back);
	SDL_SetColorKey(sidemenu.surface, SDL_TRUE, SDL_MapRGB(sidemenu.surface->format, 255, 255, 255));
	sidemenu.texture = SDL_CreateTextureFromSurface(renderer, sidemenu.surface);

	if (sidemenu.score >= 0 and sidemenu.score <= 9) {
		if (type == 0) sidemenu.rect = { 30,0,50,70 };
		else sidemenu.rect = { 550,350,100,140 };
		SDL_RenderCopy(renderer, sidemenu.texture, NULL, &sidemenu.rect);
	}
	else if (sidemenu.score >= 10 and sidemenu.score <= 99) {
		if (type == 0) sidemenu.rect = { 17,0,75,70 };
		else sidemenu.rect = { 525,350,150,140 };
		SDL_RenderCopy(renderer, sidemenu.texture, NULL, &sidemenu.rect);
	}
	else if (sidemenu.score >= 100 and sidemenu.score <= 999) {
		if (type == 0) sidemenu.rect = { 5,0,100,70 };
		else sidemenu.rect = { 500,350,200,140 };
		SDL_RenderCopy(renderer, sidemenu.texture, NULL, &sidemenu.rect);
	}
	else {
		if (type == 0) sidemenu.rect = { 0,0,110,70 };
		else sidemenu.rect = { 490,350,220,140 };
		SDL_RenderCopy(renderer, sidemenu.texture, NULL, &sidemenu.rect);
	}

	SDL_FreeSurface(sidemenu.surface);
	SDL_DestroyTexture(sidemenu.texture);
}
bool CheckEntry(SDL_Rect rect) {

	int x, y;

	SDL_GetMouseState(&x, &y);

	if (x > rect.x and x < rect.x + rect.w and y > rect.y and y < rect.y + rect.h) return true;

	return false;
}

void MainMenu(Game& game, Menu& menu) {

	if (game.event.type == SDL_QUIT) game.quit = true;

	for (int i = 0; i < 5; i++) {

		if (game.event.type == SDL_MOUSEBUTTONDOWN and CheckEntry(menu.pos_buttons[i])) {

			menu.item = i;
			LoadSound(game, game.soundMenuSelect);
		}
	}
}
void Gameplay(SDL_Renderer* renderer, Menu& menu, Game& game, Skin& skin, SideMenu& sidemenu, Time& timee) {

	if (game.event.type == SDL_QUIT) game.quit = true;

	if (game.event.type == SDL_MOUSEBUTTONDOWN) {

		if (CheckEntry(sidemenu.pos_pause)) {

			if (game.paused) { game.paused = false;	LoadSound(game, game.soundMenuSelect); }
			else { game.paused = true; LoadSound(game, game.soundMenuSelect); }
		}
		if (CheckEntry(sidemenu.pos_sound)) {

			if (game.SoundOn) { game.SoundOn = false; LoadSound(game, game.soundMenuSelect); }
			else { game.SoundOn = true; LoadSound(game, game.soundMenuSelect); }
		}
		if (CheckEntry(sidemenu.pos_music)) {
			if (game.MusicOn) { game.MusicOn = false; LoadSound(game, game.soundMenuSelect); Mix_PauseMusic(); }
			else { game.MusicOn = true; LoadSound(game, game.soundMenuSelect); Mix_ResumeMusic(); }
		}
		if (CheckEntry(sidemenu.pos_home)) {
			LoadSound(game, game.soundMenuSelect);
			menu.item = 5;
			Reload(renderer, menu, game, sidemenu, timee, skin);
			PlatGenerate(game);
		}
	}

	if (!game.paused) {
		if (game.dead == 0) {

			// дбхфемхе он цнпхгнмрюкх
			if (game.move[SDL_SCANCODE_A] or game.move[SDL_SCANCODE_LEFT]) {
				skin.pos.x -= SPEED;
				if (!game.propPicked and !game.jetpackPicked) game.stand = 1;
			}
			if (game.move[SDL_SCANCODE_D] or game.move[SDL_SCANCODE_RIGHT]) {
				skin.pos.x += SPEED;
				if (!game.propPicked and !game.jetpackPicked) game.stand = 19;
			}

			// дбхфемхе он бепрхйюкх
			game.dy += 0.04;
			skin.pos.y += game.dy;

			// опнйпсрйю йюпрш
			if (skin.pos.y < game.h) {

				skin.pos.y = game.h;

				// ондяв╗р нвйнб
				sidemenu.score -= game.dy;

				//  ярнъвхе окюртнплш
				for (int i = 0; i < game.plats; i++) {

					game.pos_plats[i].y = game.pos_plats[i].y - game.dy;

					if (game.pos_plats[i].y > HEIGHT) {

						int k = 0;

						do {
							k++;
							game.pos_plats[i].x = rand() % (WIDTH - 212) + 112;
							game.pos_plats[i].y = rand() % ((200) + 100) * -1;
						} while (!CheckPosPlats(game, sidemenu.score, game.pos_plats[i].x, game.pos_plats[i].y, i, k));

					}
				}

				// дпсцхе окюртнплш
				if (game.pos_plat_move.w != 0) game.pos_plat_move.y = game.pos_plat_move.y - game.dy;
				if (game.pos_plat_ghost.w != 0) game.pos_plat_ghost.y = game.pos_plat_ghost.y - game.dy;
				if (game.pos_plat_break.w != 0) game.pos_plat_break.y = game.pos_plat_break.y - game.dy;

				// бпюцх
				if (game.pos_warning.w != 0) game.distance = game.distance - game.dy;
				if (game.pos_current.w != 0) game.pos_current.y = game.pos_current.y - game.dy;

				// асярепш
				if (game.pos_spring.w != 0) game.pos_spring.y -= game.dy;
				if (game.pos_spring_compressed.w != 0) game.pos_spring_compressed.y -= game.dy;
				if (skin.pos_prop.w != 0) skin.pos_prop.y -= game.dy;
				if (skin.pos_jetpack.w != 0) skin.pos_jetpack.y -= game.dy;
			}

			// ярнкймнбемхъ
			if (CheckContact(skin, game, timee, game.stand, game.dy, sidemenu.score)) game.dy = JUMP;

			Shot(game, skin, timee);

			MovePlat(game, sidemenu.score);
			GhostPlat(game, sidemenu.score);
			BreakPlat(game, sidemenu.score);

			EnemyWarning(game, sidemenu.score);
			EnemyMove(game, skin);

			Spring(game, skin, menu, sidemenu.score);
			Prop(game, skin, menu, timee, sidemenu.score);
			Jetpack(game, skin, menu, timee, sidemenu.score);
		}
		else if (timee.deadEnd2 < 2000) {
			Death(game, skin, timee, sidemenu);
			timee.gameoverStart = clock();
		}
		else {
			sidemenu.gameEnd = true;
		}
	}
}
void Appearance(SDL_Renderer* renderer, Game& game, Menu& menu, Skin& skin) {

	if (game.event.type == SDL_QUIT) game.quit = true;

	for (int i = 0; i < 3; i++) {

		if (game.event.type == SDL_MOUSEBUTTONDOWN and CheckEntry(menu.APPpos_buttons[i])) {

			if (i == 0) {
				LoadSound(game, game.soundMenuSelect);
				if (skin.SelectedSkin != 0) {
					DestroySkinTextures(renderer, skin);
					LoadUsualTextures(renderer, skin);
					skin.SelectedSkin = 0;
				}
			}
			if (i == 1) {
				LoadSound(game, game.soundMenuSelect);
				if (skin.SelectedSkin != 1) {
					DestroySkinTextures(renderer, skin);
					LoadBunnyTextures(renderer, skin);
					skin.SelectedSkin = 1;
				}
			}
			if (i == 2) {
				LoadSound(game, game.soundMenuSelect);
				menu.item = 5;
			}
		}
	}
}
void Rules(SDL_Renderer* renderer, Game& game, Menu& menu, Skin& skin) {

	if (game.event.type == SDL_QUIT) game.quit = true;

	if (game.event.type == SDL_MOUSEBUTTONDOWN and CheckEntry(menu.APPpos_buttons[2])) {

		LoadSound(game, game.soundMenuSelect);
		menu.item = 5;
	}
}
void Settings(Game& game, Menu& menu) {

	if (game.event.type == SDL_QUIT) game.quit = true;

	if (game.event.type == SDL_MOUSEBUTTONDOWN) {

		if (CheckEntry(menu.APPpos_buttons[2])) {

			LoadSound(game, game.soundMenuSelect);
			menu.item = 5;
		}

		if (CheckEntry(menu.checkboxSound)) {

			if (game.SoundOn) { game.SoundOn = false; LoadSound(game, game.soundMenuSelect); }
			else { game.SoundOn = true; LoadSound(game, game.soundMenuSelect); }

		}
		if (CheckEntry(menu.checkboxMusic)) {

			if (game.MusicOn) { game.MusicOn = false; LoadSound(game, game.soundMenuSelect); Mix_PauseMusic(); }
			else { game.MusicOn = true; LoadSound(game, game.soundMenuSelect); Mix_ResumeMusic(); }
		}
	}


}
void Exit(Game& game) {

	LoadSound(game, game.soundMenuSelect);
	game.quit = true;
}

void RenderSkin(SDL_Renderer* renderer, Game& game, Skin& skin) {

	switch (game.stand) {
	case 0:
		SDL_RenderCopy(renderer, skin.top, NULL, &skin.pos);
		break;
	case 1:
		SDL_RenderCopy(renderer, skin.left, NULL, &skin.pos);
		break;
	case 2:
		SDL_RenderCopy(renderer, skin.left_jetpack[0], NULL, &skin.pos);
		break;
	case 3:
		SDL_RenderCopy(renderer, skin.left_jetpack[1], NULL, &skin.pos);
		break;
	case 4:
		SDL_RenderCopy(renderer, skin.left_jetpack[2], NULL, &skin.pos);
		break;
	case 5:
		SDL_RenderCopy(renderer, skin.left_jetpack[3], NULL, &skin.pos);
		break;
	case 6:
		SDL_RenderCopy(renderer, skin.left_jetpack[4], NULL, &skin.pos);
		break;
	case 7:
		SDL_RenderCopy(renderer, skin.left_jetpack[5], NULL, &skin.pos);
		break;
	case 8:
		SDL_RenderCopy(renderer, skin.left_jetpack[6], NULL, &skin.pos);
		break;
	case 9:
		SDL_RenderCopy(renderer, skin.left_jetpack[7], NULL, &skin.pos);
		break;
	case 10:
		SDL_RenderCopy(renderer, skin.left_jetpack[8], NULL, &skin.pos);
		break;
	case 11:
		SDL_RenderCopy(renderer, skin.left_jetpack[9], NULL, &skin.pos);
		break;
	case 12:
		SDL_RenderCopy(renderer, skin.left_prop[0], NULL, &skin.pos);
		break;
	case 13:
		SDL_RenderCopy(renderer, skin.left_prop[1], NULL, &skin.pos);
		break;
	case 14:
		SDL_RenderCopy(renderer, skin.left_prop[2], NULL, &skin.pos);
		break;
	case 15:
		SDL_RenderCopy(renderer, skin.left_prop[3], NULL, &skin.pos);
		break;
	case 16:
		SDL_RenderCopy(renderer, skin.left_stars[0], NULL, &skin.pos);
		break;
	case 17:
		SDL_RenderCopy(renderer, skin.left_stars[1], NULL, &skin.pos);
		break;
	case 18:
		SDL_RenderCopy(renderer, skin.left_stars[2], NULL, &skin.pos);
		break;
	case 19:
		SDL_RenderCopy(renderer, skin.right, NULL, &skin.pos);
		break;
	case 20:
		SDL_RenderCopy(renderer, skin.right_jetpack[0], NULL, &skin.pos);
		break;
	case 21:
		SDL_RenderCopy(renderer, skin.right_jetpack[1], NULL, &skin.pos);
		break;
	case 22:
		SDL_RenderCopy(renderer, skin.right_jetpack[2], NULL, &skin.pos);
		break;
	case 23:
		SDL_RenderCopy(renderer, skin.right_jetpack[3], NULL, &skin.pos);
		break;
	case 24:
		SDL_RenderCopy(renderer, skin.right_jetpack[4], NULL, &skin.pos);
		break;
	case 25:
		SDL_RenderCopy(renderer, skin.right_jetpack[5], NULL, &skin.pos);
		break;
	case 26:
		SDL_RenderCopy(renderer, skin.right_jetpack[6], NULL, &skin.pos);
		break;
	case 27:
		SDL_RenderCopy(renderer, skin.right_jetpack[7], NULL, &skin.pos);
		break;
	case 28:
		SDL_RenderCopy(renderer, skin.right_jetpack[8], NULL, &skin.pos);
		break;
	case 29:
		SDL_RenderCopy(renderer, skin.right_jetpack[9], NULL, &skin.pos);
		break;
	case 30:
		SDL_RenderCopy(renderer, skin.right_prop[0], NULL, &skin.pos);
		break;
	case 31:
		SDL_RenderCopy(renderer, skin.right_prop[1], NULL, &skin.pos);
		break;
	case 32:
		SDL_RenderCopy(renderer, skin.right_prop[2], NULL, &skin.pos);
		break;
	case 33:
		SDL_RenderCopy(renderer, skin.right_prop[3], NULL, &skin.pos);
		break;
	case 34:
		SDL_RenderCopy(renderer, skin.right_stars[0], NULL, &skin.pos);
		break;
	case 35:
		SDL_RenderCopy(renderer, skin.right_stars[1], NULL, &skin.pos);
		break;
	case 36:
		SDL_RenderCopy(renderer, skin.right_stars[2], NULL, &skin.pos);
		break;
	default: break;
	}
}
void RenderEnemy(SDL_Renderer* renderer, Game& game) {

	switch (game.type_enemy) {
	case 0: // юлнцся
		if (game.enemy_direction == 0)SDL_RenderCopy(renderer, game.amogus2, NULL, &game.pos_current);
		else if (game.enemy_direction == 1)SDL_RenderCopy(renderer, game.amogus, NULL, &game.pos_current);
		break;
	case 1: // лшьэ
		SDL_RenderCopy(renderer, game.bat, NULL, &game.pos_current);
		break;
	case 2: // цскэ
		SDL_RenderCopy(renderer, game.ghoul, NULL, &game.pos_current);
		break;
	case 3: // вепмюъ дшпю
		SDL_RenderCopy(renderer, game.hole, NULL, &game.pos_current);
		break;
	case 4: // мкн
		break;
	}
}
void Rendering(SDL_Renderer*& renderer, Menu& menu, Game& game, Skin& skin, SideMenu& sidemenu, Time& timee) {

	switch (menu.item) {
	case 0:

		SDL_RenderCopy(renderer, game.background, NULL, &game.pos_background);

		if (!game.springUsed)SDL_RenderCopy(renderer, game.spring, NULL, &game.pos_spring);
		else SDL_RenderCopy(renderer, game.spring_compressed, NULL, &game.pos_spring_compressed);

		SDL_RenderCopy(renderer, skin.prop, NULL, &skin.pos_prop);
		SDL_RenderCopy(renderer, skin.jetpack, NULL, &skin.pos_jetpack);

		for (int i = 0; i < game.plats; i++) {
			SDL_RenderCopy(renderer, game.plat_state, NULL, &game.pos_plats[i]);
		}
		SDL_RenderCopy(renderer, game.plat_move, NULL, &game.pos_plat_move);
		SDL_RenderCopy(renderer, game.plat_break, NULL, &game.pos_plat_break);

		RenderEnemy(renderer, game);
		RenderSkin(renderer, game, skin);
		if (game.type_enemy == 4) {
			SDL_RenderCopy(renderer, game.ufo, NULL, &game.pos_current);
		}

		SDL_RenderCopy(renderer, game.plat_ghost, NULL, &game.pos_plat_ghost);
		SDL_RenderCopy(renderer, game.warning, NULL, &game.pos_warning);

		GetScoreText(renderer, sidemenu, menu, 0);
		if (!game.paused) SDL_RenderCopy(renderer, sidemenu.pause, NULL, &sidemenu.pos_pause);
		else SDL_RenderCopy(renderer, sidemenu.play, NULL, &sidemenu.pos_pause);

		SDL_RenderCopy(renderer, sidemenu.sound, NULL, &sidemenu.pos_sound);
		if (!game.SoundOn) SDL_RenderCopy(renderer, menu.off, NULL, &sidemenu.pos_sound);

		SDL_RenderCopy(renderer, sidemenu.music, NULL, &sidemenu.pos_music);
		if (!game.MusicOn) SDL_RenderCopy(renderer, menu.off, NULL, &sidemenu.pos_music);

		SDL_RenderCopy(renderer, sidemenu.home, NULL, &sidemenu.pos_home);

		for (int i = 0; i < 20; i++) {
			SDL_RenderCopy(renderer, skin.bullet, NULL, &skin.pos_bullets[i]);
		}

		if (sidemenu.gameEnd) GameOver(renderer, game, sidemenu, timee, menu, skin);

		break;

	case 1:  // "бмеьмнярэ"

		SDL_RenderCopy(renderer, menu.menu_background2, NULL, &menu.pos_menu_background);

		for (int i = 0; i < 3; i++) {

			SDL_RenderCopy(renderer, menu.APPbuttons[i], NULL, &menu.APPpos_buttons[i]);
		}

		for (int i = 0; i < 3; i++) {

			if (CheckEntry(menu.APPpos_buttons[i]) or skin.SelectedSkin == i) SDL_RenderCopy(renderer, menu.APPbuttons_active[i], NULL, &menu.APPpos_buttons[i]);
		}

		SDL_RenderCopy(renderer, skin.right, NULL, &skin.APPmenupos);

		break;

	case 2:  // "опюбхкю"

		SDL_RenderCopy(renderer, menu.RULback, NULL, &menu.pos_menu_background);

		SDL_RenderCopy(renderer, menu.APPbuttons[2], NULL, &menu.APPpos_buttons[2]);

		if (CheckEntry(menu.APPpos_buttons[2])) SDL_RenderCopy(renderer, menu.APPbuttons_active[2], NULL, &menu.APPpos_buttons[2]);

		break;

	case 3:  // "мюярпнийх"

		SDL_RenderCopy(renderer, menu.SETback, NULL, &menu.pos_menu_background);

		SDL_RenderCopy(renderer, menu.APPbuttons[2], NULL, &menu.APPpos_buttons[2]);

		if (CheckEntry(menu.APPpos_buttons[2])) SDL_RenderCopy(renderer, menu.APPbuttons_active[2], NULL, &menu.APPpos_buttons[2]);

		if (game.SoundOn) SDL_RenderCopy(renderer, menu.on, NULL, &menu.checkboxSound);
		else SDL_RenderCopy(renderer, menu.off, NULL, &menu.checkboxSound);
		if (game.MusicOn) SDL_RenderCopy(renderer, menu.on, NULL, &menu.checkboxMusic);
		else SDL_RenderCopy(renderer, menu.off, NULL, &menu.checkboxMusic);

		break;

	case 4:  // "бшунд"

		SDL_RenderCopy(renderer, menu.menu_background2, NULL, &menu.pos_menu_background);

		break;

	case 5:  // "лемч"

		SDL_RenderCopy(renderer, menu.menu_background, NULL, &menu.pos_menu_background);

		for (int i = 0; i < 5; i++) {

			SDL_RenderCopy(renderer, menu.buttons[i], NULL, &menu.pos_buttons[i]);
		}

		for (int i = 0; i < 5; i++) {

			if (CheckEntry(menu.pos_buttons[i])) SDL_RenderCopy(renderer, menu.buttons_active[i], NULL, &menu.pos_buttons[i]);
		}

		SDL_RenderCopy(renderer, skin.right, NULL, &skin.menupos);

		break;
	}

	SDL_RenderPresent(renderer);
}
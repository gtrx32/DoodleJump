#pragma once
#include "load.h"

void PlatGenerate(Game& game);
void MovePlat(Game& game, int score);
void GhostPlat(Game& game, int score);
void BreakPlat(Game& game, int score);
bool CheckPosPlats(Game& game, int score, int x, int y, int n, int k);

void Spring(Game& game, Skin& skin, Menu& menu, int score);
void Prop(Game& game, Skin& skin, Menu& menu, Time& timee, int score);
void Jetpack(Game& game, Skin& skin, Menu& menu, Time& timee, int score);

void Shot(Game& game, Skin& skin, Time& timee);
void EnemyMove(Game& game, Skin& skin);
void EnemyAppear(Game& game);
void EnemyWarning(Game& game, int score);
bool CheckContact(Skin& skin, Game& game, Time& timee, int stand, int dy, int score);

void GameOver(SDL_Renderer* renderer, Game& game, SideMenu& sidemenu, Time& timee, Menu& menu, Skin& skin);
void Death(Game& game, Skin& skin, Time& timee, SideMenu& sidemenu);

void GetScoreText(SDL_Renderer*& renderer, SideMenu& sidemenu, Menu& menu, int type);
bool CheckEntry(SDL_Rect rect);

void MainMenu(Game& game, Menu& menu);
void Gameplay(SDL_Renderer* renderer, Menu& menu, Game& game, Skin& skin, SideMenu& sidemenu, Time& timee);
void Appearance(SDL_Renderer* renderer, Game& game, Menu& menu, Skin& skin);
void Rules(SDL_Renderer* renderer, Game& game, Menu& menu, Skin& skin);
void Settings(Game& game, Menu& menu);
void Exit(Game& game);

void RenderSkin(SDL_Renderer* renderer, Game& game, Skin& skin);
void RenderEnemy(SDL_Renderer* renderer, Game& game);
void Rendering(SDL_Renderer*& renderer, Menu& menu, Game& game, Skin& skin, SideMenu& sidemenu, Time& timee);
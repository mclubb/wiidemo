#ifndef __GAME1_H__
#define __GAME1_H__

#include "Game.h"
#include "Camera.h"

#include "textures_tpl.h"
#include "textures.h"

#include "Platforms.h"
#include "Player.h"
#include "Enemy.h"


enum TEXTURES { BACKGROUND, BEAVER, PLATFORM, MENU, TITLE, VULTURE};
enum GAMESTATE { GS_TITLE, GS_MENU, GS_PLAYING, GS_PAUSE };
enum INGAMESTATE { START, RUNNING, STATUS }; 

class Game1 : public Game {
	public:
		Game1();
		void Initialize();
		void LoadContent();
		void Run();
		void Update();
		void Draw();
		Camera* GetCamera();

		void DrawTitleScene();
		void UpdateTitleScene();
		void DrawMenuScene();
		void UpdateMenuScene();
		void DrawLevelOneScene();
		void UpdateLevelOneScene();
		void DrawStatusFlag();

		void GenerateRandomPlatforms();
		
	private:
		Camera * camera;
		std::vector<GXTexObj> textures;
		std::vector<Platform*> platforms;
		Player* player;
		Enemy* enemy;


GAMESTATE gameState;
INGAMESTATE ingameState;
int chooseLevel;
guVector levelCoords[6];
float zoom;
float x;
int flagHeight;
int flagStatus;
vec3w_t accel;
guVector fontCoord[10];
int score;
float playerHeight;


	protected:
};

#endif
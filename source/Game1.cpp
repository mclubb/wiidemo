#include "Game1.h"

Game1::Game1() {
	
}

void Game1::Initialize() {
	GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	
	GX_SetNumChans(1);
	GX_SetNumTexGens(1);
	GX_SetTevOrder (GX_TEVSTAGE0, GX_TEXCOORD0,GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTevOp (GX_TEVSTAGE0, GX_MODULATE);	
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

	camera = new Camera( Game::gxrmode, (guVector){0,0,-25}, (guVector){0,1,0}, (guVector){0,0,0});
}

void Game1::LoadContent() {

	// Load the textures
	TPLFile texturesTPL;

	GXTexObj _background;
	GXTexObj _beaver;
	GXTexObj _platform;
	GXTexObj _menu;
	GXTexObj _title;
	GXTexObj _vulture;



	TPL_OpenTPLFromMemory(&texturesTPL, (void *)textures_tpl, textures_tpl_size);
	TPL_GetTexture(&texturesTPL, background, &_background);
	TPL_GetTexture(&texturesTPL, beaver, &_beaver);
	TPL_GetTexture(&texturesTPL, platformTexture, &_platform);
	TPL_GetTexture(&texturesTPL, menuTexture, &_menu);
	TPL_GetTexture(&texturesTPL, titleTexture, &_title);
	TPL_GetTexture(&texturesTPL, vultureTexture, &_vulture);

	
	

	textures.push_back(_background);
	textures.push_back(_beaver);
	textures.push_back(_platform);
	textures.push_back(_menu);
	textures.push_back(_title);
	textures.push_back(_vulture);

	levelCoords[0] = {30, 210, 0};
	levelCoords[1] = {200, 260, 0};
	levelCoords[2] = {390, 195, 0};
	levelCoords[3] = {495, 360, 0};
	levelCoords[4] = {310, 410, 0};
	levelCoords[5] = {60, 405, 0};

	chooseLevel = 1;

	gameState = GS_TITLE;

	player = new Player(0, 5, 0, 2.75f, 2.25f);
	playerHeight = 21;
	player->SetTexture(textures[BEAVER]);
	
	
	enemy = new Enemy(3, 5, 0, 2.75f, 2.25f);
	enemy->SetTexture(&textures[VULTURE]);
	
	GenerateRandomPlatforms();
}

void Game1::Update() {
	Game::Update();

	// Update goes here
	camera->Update();

	if( gameState == GS_TITLE) {
		UpdateTitleScene();
	}

	if( gameState == GS_MENU ) {
		UpdateMenuScene();
	}

	if( gameState == GS_PLAYING) {
		switch(chooseLevel) {
			case 1: 

			default:
				UpdateLevelOneScene();
		}
	}
}

void Game1::UpdateMenuScene() {
	if(WPAD_ButtonsUp(0) & WPAD_BUTTON_B) {
			gameState = GS_PLAYING;
			ingameState = START;
		}
		
		if( WPAD_ButtonsUp(0) & WPAD_BUTTON_LEFT ) { 
			chooseLevel--;
			if( chooseLevel <= 1 ) {
				chooseLevel = 1;
			}
		}
		
		if( WPAD_ButtonsUp(0) & WPAD_BUTTON_RIGHT) {
			chooseLevel++;
			if( chooseLevel >= 6 ) {
				chooseLevel = 6;
			}
		}
}

void Game1::UpdateTitleScene() {
	// Listen for the A button
		if( WPAD_ButtonsUp(0) & WPAD_BUTTON_A) {
			gameState = GS_MENU;
		}
}

void Game1::UpdateLevelOneScene() {
	player->Update();
	enemy->Update();
	//player->MovePlayer(accel.y * 0.0001f);
	// Check for collisions
	int i = 0;
	for(i = 0; i < (int)platforms.size(); i++) {
		if( player->GetMaxX() > platforms[i]->GetMinX() &&
			player->GetMinX() < platforms[i]->GetMaxX() &&
			player->GetMaxY() > platforms[i]->GetMinY() &&
			player->GetMinY() < platforms[i]->GetMaxY() ) {

			if( platforms[i]->GetBouncy())
				player->ReverseGravity();
			else 
				player->OnFloor();
		}
	}
	
	f32 p = playerHeight / flagHeight;
	p *= 480.0f;

	flagStatus = 480 - (int)p;

	if( player->GetPosition().y >= playerHeight) {
		playerHeight = player->GetPosition().y;
	}

	camera->UpdateView((guVector){0, playerHeight - 10, -25}, (guVector){0, 1, 0}, (guVector){0, playerHeight - 10, 0});
}

void Game1::DrawLevelOneScene() {
		camera->Setup3D();
		
		Mtx44 model;
		Mtx44 modelview;
		guMtxIdentity(model);
		guMtxIdentity(modelview);
		guMtxTransApply(model, model, 0,  playerHeight, 0);
		guMtxConcat(model, *camera->GetView(), modelview);
		GX_LoadPosMtxImm(modelview, GX_PNMTX0);
		GX_LoadTexObj(&textures[BACKGROUND], GX_TEXMAP0);
		
		float size = 75.0f;
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		  GX_Position3f32(-size, -size, -size);
		  GX_Color4u8(255, 255, 255, 255);
		  GX_TexCoord2f32(0,0);  
		  GX_Position3f32(size, -size, -size);
		  GX_Color4u8(255, 255, 255, 255);
		  GX_TexCoord2f32(1,0);
		  GX_Position3f32(size, size, -size);
		  GX_Color4u8(255, 255, 255, 255);
		  GX_TexCoord2f32(1,1);
		  GX_Position3f32(-size, size, -size);
		  GX_Color4u8(255, 255, 255, 255);
		  GX_TexCoord2f32(0,1);
		GX_End();

		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		  GX_Position3f32(-size, size, -size);
		  GX_Color4u8(255, 255, 255, 255);
		  GX_TexCoord2f32(0,0);  
		  GX_Position3f32(size, size, -size);
		  GX_Color4u8(255, 255, 255, 255);
		  GX_TexCoord2f32(1,0);
		  GX_Position3f32(size, size, size);
		  GX_Color4u8(255, 255, 255, 255);
		  GX_TexCoord2f32(1,1);
		  GX_Position3f32(-size, size, size);
		  GX_Color4u8(255, 255, 255, 255);
		  GX_TexCoord2f32(0,1);
		GX_End();		
		
		
		
		int i = 0;
		for(i = 0; i < (int)platforms.size(); i++) {
			platforms[i]->Draw(*camera->GetView());
		}
		
		enemy->Draw(*camera->GetView());
		
		player->Draw(*camera->GetView());
		
		
		// Draw 2d stuff
		//guOrtho(ortho, 0, gxrmode->viHeight, 0, gxrmode->viWidth, 0.1F, 300.0F);
		//GX_LoadProjectionMtx(ortho, GX_ORTHOGRAPHIC);
		camera->Setup2D();
		Mtx44 v;
		guMtxIdentity(v);
  		guMtxTransApply(v, v, 0, 0, -100.0f);
  		GX_LoadPosMtxImm(v, GX_PNMTX0);
		
		//if( ingameState == STATUS ) {
			
			//DrawStatus();
		//}
		//else {
			DrawStatusFlag();
		//}
}

void Game1::DrawStatusFlag() {
	GX_LoadTexObj(&textures[BEAVER], GX_TEXMAP0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(620, flagStatus, 0);
		GX_Color4u8(255,0,0,255);
		GX_TexCoord2f32(96/128.0f, 40/128.0f);
		
		GX_Position3f32(635, flagStatus, 0);
		GX_Color4u8(0,255,0,255);
		GX_TexCoord2f32(97.0f/128.0f, 40/128.0f);
		
		GX_Position3f32(635, flagStatus + 15, 0);
		GX_Color4u8(0,0,255,230);
		GX_TexCoord2f32(97.0f/128.0f, 41.0f/128.0f);
		
		GX_Position3f32(620, flagStatus + 15, 0);
		GX_Color4u8(255,0,255,255);
		GX_TexCoord2f32(96.0/128.0f, 41.0f/128.0f);
	GX_End();
	
	GX_LoadTexObj(&textures[MENU], GX_TEXMAP0);
	int fontNumber = 1;//log10(score);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(25, 25, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(fontCoord[fontNumber].x / 1024.0f, 472.0f / 512.0f);
		
		GX_Position3f32(75, 25, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32((fontCoord[fontNumber].x + 30.0f) / 1024.0f, 472.0f / 512.0f);
		
		GX_Position3f32(75, 75, 0);
		GX_Color4u8(255,255,255,230);
		GX_TexCoord2f32((fontCoord[fontNumber].x + 30.0f) / 1024.0f, (472.0f + 34.0f) / 512.0f);
		
		GX_Position3f32(25, 75, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(fontCoord[fontNumber].x / 1024.0f, (472.0f + 34.0f) / 512.0f);
	GX_End();
}

void Game1::DrawMenuScene() {
		camera->Setup2D();
		// Draw Map
		GX_LoadTexObj(&textures[MENU], GX_TEXMAP0);
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0, 0, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(0, 0);
		
		GX_Position3f32(640, 0, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(764.0f/1024.0f, 0);
		
		GX_Position3f32(640, 480, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(764/1024.0f, 458/512.0f);
		
		GX_Position3f32(0, 480, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(0, 458/512.0f);
		
		GX_End();
		
		// Draw Beaver next to level number
		GX_LoadTexObj(&textures[BEAVER], GX_TEXMAP0);
		//128x65
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		float x, y;
		x = levelCoords[chooseLevel - 1].x;
		y = levelCoords[chooseLevel - 1].y;

		if( chooseLevel > 3) {
		GX_Position3f32(x, y, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(1, 0);
		
		GX_Position3f32(x + 128.0f, y, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(0, 0);
		
		GX_Position3f32(x + 128, y + 65, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(0, 65.0f/128.0f);
		
		GX_Position3f32(x, y + 65, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(1, 65.0f/128.0f);
		
		GX_End();
		}
		else {
		GX_Position3f32(x, y, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(0, 0);
		
		GX_Position3f32(x + 128.0f, y, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(1, 0);
		
		GX_Position3f32(x + 128, y + 65, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(1, 65.0f/128.0f);
		
		GX_Position3f32(x, y + 65, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(0, 65.0f/128.0f);
		
		GX_End();	
		}
}

void Game1::DrawTitleScene() {
		camera->Setup2D();

		// Draw Map
		GX_LoadTexObj(&textures[TITLE], GX_TEXMAP0);
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0, 0, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(0, 0);
		
		GX_Position3f32(640, 0, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(640.0f/1024.0f, 0);
		
		GX_Position3f32(640, 480, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(640/1024.0f, 480/512.0f);
		
		GX_Position3f32(0, 480, 0);
		GX_Color4u8(255,255,255,255);
		GX_TexCoord2f32(0, 480/512.0f);
		
		GX_End();		
}

void Game1::GenerateRandomPlatforms() {
	platforms.push_back(new Platform(0, 0, 0, 30, 1.5, 3, textures[PLATFORM]));

	f32 height = 300.0f;
	int numPlatforms = 1000;
	f32 nextHeight = 8.0f;
	f32 currentHeight = 8.0f;
	int i = 0;
	for( i = 0; i < (int)height; i++ ) {
		f32 wide, pos;
		
		wide = rand() % 8;
		if( wide < 1.0f ) {  wide = 1.0f; }
		pos = rand() % 15;
		
		if( (int)pos % 2) { pos *= -1; }
		
		
		platforms.push_back(new Platform(pos, currentHeight, 0, wide, 1.5, 3, textures[PLATFORM]));
		currentHeight += nextHeight;
	}

	platforms[0]->SetBouncy(false);
	platforms[(int)platforms.size() - 1]->SetBouncy(false);
	
	flagHeight = 2400;
}

void Game1::Draw() {
	// Draw goes here
	
	if( gameState == GS_TITLE) {
		DrawTitleScene();
	}

	if( gameState == GS_MENU) {
		DrawMenuScene();
	}

	if( gameState == GS_PLAYING) {
		switch(chooseLevel) {
			case 1:

			default: 
				DrawLevelOneScene();
		}
	}

	Game::Draw();
}

Camera* Game1::GetCamera() {
	return this->camera;
}

void Game1::Run() {

	while(Game::IsRunning()) {
		Update();
		Draw();
	}
}
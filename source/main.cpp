#include "Game1.h"




int main() {
/*	
	
	
	
	gameState = PLAYING;
	ingameState = RUNNING;
	
	
	//27x34 from menu texture
	fontCoord[0] = {1,472,0};
	fontCoord[1] = {30,472,0};
	fontCoord[2] = {60,472,0};
	fontCoord[3] = {92,472,0};
	fontCoord[4] = {122,472,0};
	fontCoord[5] = {155,472,0};
	fontCoord[6] = {188,472,0};
	fontCoord[7] = {218,472,0};
	fontCoord[8] = {249,472,0};
	fontCoord[9] = {279,472,0};
	
	//player = new Player(0, 3, 0, 1.75f, 1.25f);
	player = new Player(0, 5, 0, 2.75f, 2.25f);
	playerHeight = 21;
	player->SetTexture(_beaver);
	
	
	enemy = new Enemy(3, 5, 0, 2.75f, 2.25f);
	enemy->SetTexture(&_vulture);
	
	while(1) {
		Update();
		Draw(view);
	}
	*/


	Game1 game;
	game.Initialize();
	game.LoadContent();
	game.Run();
return 0;
}

/*
void Update() {
	
	
	

	
	
	
	if( gameState == PLAYING) {
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
		
		guMtxIdentity(view);
		guVector eye = {0, playerHeight-11, zoom}, up = {0, 1, 0}, at = {0, playerHeight-11, 0};
		guLookAt(view, &eye, &up, &at);
	}
	
	if( gameState == MENU ) {
		
	}
	
	lastCurrentTime = CurrentTime;
	
}

void Draw(Mtx44 view) {
	
	if( gameState == PLAYING ) {
		guMtxIdentity(perspective);
		guMtxIdentity(ortho);
		
		guPerspective(perspective, 45, (f32)gxrmode->viWidth/gxrmode->viHeight, 0.1F, 300.0F);
		GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);
		
		Mtx44 model;
		Mtx44 modelview;
		guMtxIdentity(model);
		guMtxIdentity(modelview);
		guMtxTransApply(model, model, 0,  playerHeight, 0);
		guMtxConcat(model, view, modelview);
		GX_LoadPosMtxImm(modelview, GX_PNMTX0);
		GX_LoadTexObj(&_background, GX_TEXMAP0);
		
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
			platforms[i]->Draw(view);
		}
		
		enemy->Draw(view);
		
		player->Draw(view);
		
		
		// Draw 2d stuff
		guOrtho(ortho, 0, gxrmode->viHeight, 0, gxrmode->viWidth, 0.1F, 300.0F);
		GX_LoadProjectionMtx(ortho, GX_ORTHOGRAPHIC);
		Mtx44 v;
		guMtxIdentity(v);
  		guMtxTransApply(v, v, 0, 0, -100.0f);
  		GX_LoadPosMtxImm(v, GX_PNMTX0);
		
		if( ingameState == STATUS ) {
			
			DrawStatus();
		}
		else {
			DrawHUD();
		}
	
	}
	 




	//Nothing
	Mtx44 model, modelview;
	guMtxIdentity(model);
	guMtxIdentity(modelview);
	guMtxTransApply(model, model, 0, 0, 0);

	guMtxConcat(*camera->GetView(), model, modelview);
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);

	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-1, 1, 0);
		GX_Color4u8(255, 255, 255, 255);
		GX_Position3f32(1, 1, 0);
		GX_Color4u8(255, 255, 255, 255);
		GX_Position3f32(1, -1, 0);
		GX_Color4u8(255, 255, 255, 255);
		GX_Position3f32(-1, -1, 0);
		GX_Color4u8(255, 255, 255, 255);
	GX_End();



	
}

void DrawHUD()
{
	
	GX_LoadTexObj(&_beaver, GX_TEXMAP0);
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
			
			GX_LoadTexObj(&_menu, GX_TEXMAP0);
			int fontNumber = score;//log10(score);
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

void DrawStatus()
{
	
	// Just draws a grey screen to cover game scene
			GX_LoadTexObj(&_beaver, GX_TEXMAP0);
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				GX_Position3f32(0, 0, 0);
				GX_Color4u8(238,238,238,230);
				GX_TexCoord2f32(96/128.0f, 40/128.0f);
				
				GX_Position3f32(640, 0, 0);
				GX_Color4u8(238,238,238,230);
				GX_TexCoord2f32(97.0f/128.0f, 40/128.0f);
				
				GX_Position3f32(640, 490, 0);
				GX_Color4u8(238,238,238,230);
				GX_TexCoord2f32(97.0f/128.0f, 41.0f/128.0f);
				
				GX_Position3f32(0, 490, 0);
				GX_Color4u8(238,238,238,230);
				GX_TexCoord2f32(96.0/128.0f, 41.0f/128.0f);
			GX_End();
			
			// Lets Draw the three stars
			GX_LoadTexObj(&_menu, GX_TEXMAP0);
			
			int i, startx, gap, w;
			startx = 180;
			gap = 100;
			w = 80;
			for( i = 0; i < 3; i++ ) {
				GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
					GX_Position3f32(startx + (i * gap), 100, 0);
					GX_Color4u8(255, 255, 255, 255);
					GX_TexCoord2f32(941/1028.0f, 9/512.0f);
					
					GX_Position3f32(startx + (i * gap) + w, 100, 0);
					GX_Color4u8(255, 255, 255, 255);
					GX_TexCoord2f32(1023/1024.0f, 9/512.0f);
					
					GX_Position3f32(startx + (i * gap) + w, 100 + w, 0);
					GX_Color4u8(255, 255, 255, 255);
					GX_TexCoord2f32(1023/1024.0f, 90/512.0f);
					
					GX_Position3f32(startx + (i * gap), 100 + w, 0);
					GX_Color4u8(255, 255, 255, 255);
					GX_TexCoord2f32(941/1024.0f, 90/512.0f);
				GX_End();
			}

			// Lets Draw the Menu Button
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				GX_Position3f32(60, 240, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(770/1028.0f, 0/512.0f);
				
				GX_Position3f32(220, 240, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(930/1024.0f, 0/512.0f);
				
				GX_Position3f32(220, 400, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(930/1024.0f, 159/512.0f);
				
				GX_Position3f32(60, 400, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(770/1024.0f, 159/512.0f);
				GX_End();
			
			// Lets Draw the Retry Button
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				GX_Position3f32(260, 240, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(770/1028.0f, 320/512.0f);
				
				GX_Position3f32(400, 240, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(930/1024.0f, 320/512.0f);
				
				GX_Position3f32(400, 400, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(930/1024.0f, 479/512.0f);
				
				GX_Position3f32(260, 400, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(770/1024.0f, 479/512.0f);
				GX_End();

			// Lets Draw the Next Button
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				GX_Position3f32(420, 240, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(770/1028.0f, 160/512.0f);
				
				GX_Position3f32(580, 240, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(930/1024.0f, 160/512.0f);
				
				GX_Position3f32(580, 400, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(930/1024.0f, 319/512.0f);
				
				GX_Position3f32(420, 400, 0);
				GX_Color4u8(255, 255, 255, 255);
				GX_TexCoord2f32(770/1024.0f, 319/512.0f);
				GX_End();
				
}

void Init() {

}
*/
#include "Player.h"
#include <wiiuse/wpad.h>

Player::Player() {

}

Player::Player(f32 x, f32 y, f32 z, f32 w, f32 h) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->velx = 0.00f;
	this->vely = 0.0f;
	this->gravity = 0.23f; //0.75f;
}

void Player::SetTexture(GXTexObj tex) {
	this->texture = tex;
}

void Player::Update() {
		
	if( WPAD_ButtonsDown(0) & WPAD_BUTTON_A ) {
		this->vely = 2.5f;
	}
	
	if( WPAD_ButtonsHeld(0) & WPAD_BUTTON_UP ) { 
		this->velx = -0.15f;
	}
	
	if( WPAD_ButtonsHeld(0) & WPAD_BUTTON_DOWN ) { 
		this->velx = 0.15f;
	}
	
	this->x += this->velx;
	
	if( this->x < -12.5f) { 
		this->x = -12.5f;
	}
	if( this->x > 12.5f ) {
		this->x = 12.5f;
	}
	
	this->vely -= this->gravity;
	this->y += this->vely;
	
	if( this->vely <= -this->gravity ) { 
		this->vely = 0;
	}

	this->velx = 0;
}

void Player::ReverseGravity() {
	this->vely = 2.5f;
}

void Player::OnFloor() {
	this->y += this->gravity;
}

guVector Player::GetPosition() {
	return guVector{this->x, this->y, this->z};
}

void Player::Draw(Mtx44 view) {
	Mtx44 model, modelview;
	guMtxIdentity(model);
	guMtxTransApply(model, model, this->x, this->y, this->z);
	guMtxConcat(model, view, modelview);
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	GX_LoadTexObj(&this->texture, GX_TEXMAP0);
	
	f32 width, height;
	width = this->w / 2.0f;
	height = this->h / 2.0f;
	
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-width, height, 0);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0, 0);
		
		GX_Position3f32(width, height, 0);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(1, 0);
		
		GX_Position3f32(width, -height, 0);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(1, 65.0f/128.0f);
		
		GX_Position3f32(-width, -height, 0);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0, 65.0f/128.0f);
		
	GX_End();
}

void Player::MovePlayer(f32 mov) {
	this->x += mov;
}

f32 Player::GetMaxX() { return this->x + (this->w / 2.0f); }
f32 Player::GetMaxY() { return this->y + (this->h / 2.0f); }
f32 Player::GetMinX() { return this->x - (this->w / 2.0f); }
f32 Player::GetMinY() { return this->y - (this->h / 2.0f); }
#include "Enemy.h"

Enemy::Enemy() {

}

Enemy::Enemy(f32 x, f32 y, f32 z, f32 w, f32 h) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->velx = 0.025f;
}

void Enemy::SetTexture(GXTexObj * texture) {
	this->tex = texture;
}

void Enemy::Update() {
	this->x += this->velx;
	
	if( this->x < -13.0f || this->x > 13.0f ) { this->velx *= -1; }
}

void Enemy::Draw(Mtx44 view) {
	Mtx44 model, modelview;
	guMtxIdentity(model);
	guMtxIdentity(modelview);
	guMtxTransApply(model, model, this->x, this->y, this->z);
	guMtxConcat(view, model, modelview);
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	GX_LoadTexObj(this->tex, GX_TEXMAP0);
	
	f32 width, height;
	width = this->w / 2.0f;
	height = this->h / 2.0f;
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-width, height, 0);
		GX_Color4u8(255, 255, 255, 255);
		if( this->velx > 0 )
			GX_TexCoord2f32(1, 0);
		else
			GX_TexCoord2f32(0, 0);
		GX_Position3f32(width, height, 0);
		GX_Color4u8(255, 255, 255, 255);
		if( this->velx > 0 ) 
			GX_TexCoord2f32(0, 0);
		else
			GX_TexCoord2f32(1, 0);
		GX_Position3f32(width, -height, 0);
		GX_Color4u8(255, 255, 255, 255);
		if( this->velx > 0 )
			GX_TexCoord2f32(0, 1);
		else 
			GX_TexCoord2f32(1, 1);
		GX_Position3f32(-width, -height, 0);
		GX_Color4u8(255, 255, 255, 255);
		if( this->velx > 0 )
			GX_TexCoord2f32(1, 1);
		else 
			GX_TexCoord2f32(0, 1);
	GX_End();
}

bool Enemy::isAlive() {
	return this->alive;
}

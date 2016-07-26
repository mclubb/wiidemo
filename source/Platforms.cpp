#include "Platforms.h"

Platform::Platform() {

}

Platform::Platform(f32 x, f32 y, f32 z, f32 w, f32 h, f32 d, GXTexObj tex) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->d = d;
	this->tex = tex;
	this->bouncy = true;
}

void Platform::Update() {

}

void Platform::SetBouncy(bool b) {
	this->bouncy = b;
}

bool Platform::GetBouncy() {
	return this->bouncy;
}

void Platform::Draw(Mtx44 view) {
	Mtx44 model, modelview;
	guMtxIdentity(model);
	guMtxTransApply(model, model, this->x, this->y, this->z);
	guMtxConcat(model, view, modelview);
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	GX_InitTexObjWrapMode(&this->tex, GX_REPEAT, GX_REPEAT);
	
	GX_LoadTexObj(&this->tex, GX_TEXMAP0);

GX_InvalidateTexAll();
	
	f32 width, height, depth;
	width = this->w / 2.0f;
	height = this->h / 2.0f;
	depth = this->d / 2.0f;
	
	GX_Begin(GX_QUADS, GX_VTXFMT0, 20);
		// Top
		GX_Position3f32(-width, height, -depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(128.0f/512.0f,0);
		GX_Position3f32(width, height, -depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(255.0f/512.0f, 0.0f);
		GX_Position3f32(width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(255.0f/512.0f, 127.0f/512.0f);
		GX_Position3f32(-width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(128.0f/512.0f, 127.0f/512.0f);
		
		// Front
		GX_Position3f32(-width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(128.0f/512.0f,128.0f/512.0f);
		GX_Position3f32(width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(255.0f/512.0f, 128.0f/512.0f);
		GX_Position3f32(width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(255.0f/512.0f, 255.0f/512.0f);
		GX_Position3f32(-width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(128.0f/512.0f, 255.0f/512.0f);
		
		// Left Side
		GX_Position3f32(-width, height, -depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0,128/512.0f);
		GX_Position3f32(-width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(127/512.0f, 128/512.0f);
		GX_Position3f32(-width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(127/512.0f, 255/512.0f);
		GX_Position3f32(-width, -height, -depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0, 255/512.0f);
		
		// Right Side
		GX_Position3f32(width, height, -depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0,128/512.0f);
		GX_Position3f32(width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(127/512.0f, 128/512.0f);
		GX_Position3f32(width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(127/512.0f, 255/512.0f);
		GX_Position3f32(width, -height, -depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0, 255/512.0f);
		
		// botTom
		GX_Position3f32(-width, -height, -depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(128.0f/512.0f,256.0f/512.0f);
		GX_Position3f32(width, -height, -depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(255.0f/512.0f, 256.0f/512.0f);
		GX_Position3f32(width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(255.0f/512.0f, 383.0f/512.0f);
		GX_Position3f32(-width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(128.0f/512.0f, 383.0f/512.0f);
	GX_End();
}

f32 Platform::GetMaxX() { return this->x + (this->w / 2.0f); }
f32 Platform::GetMaxY() { return this->y + (this->h / 2.0f); }
f32 Platform::GetMinX() { return this->x - (this->w / 2.0f); }
f32 Platform::GetMinY() { return this->y - (this->h / 2.0f); }
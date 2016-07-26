#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <gccore.h>

class Enemy {
	public:
		Enemy();
		Enemy(f32, f32, f32, f32, f32);
		void SetTexture(GXTexObj *);
		void Update();
		void Draw(Mtx44);
		bool isAlive();
	private:
		f32 x, y, z, w, h;
		f32 velx, vely;
		bool alive;
		GXTexObj * tex;
};

#endif

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <gccore.h>

class Player {
	public:
		Player();
		Player(f32, f32, f32, f32, f32);
		void SetTexture(GXTexObj);
		void Update();
		void Draw(Mtx44);
		guVector GetPosition();
		f32 GetMaxX();
		f32 GetMaxY();
		f32 GetMinX();
		f32 GetMinY();
		void ReverseGravity();
		void MovePlayer(f32);
		void OnFloor();

	private:
		f32 x, y, z, w, h;
		f32 velx, vely, gravity;
		GXTexObj texture;
	protected:
};
#endif
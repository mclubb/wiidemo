#ifndef __GAME_H__
#define __GAME_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <malloc.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#define DEFAULT_FIFO_SIZE (256 * 1024)

class Game {
	private:
		void Init();
		
		Mtx44 perspective, view, ortho, blank;
		int fb;
		void * framebuffer[2];
		bool running;

	public:
		Game();
		bool IsRunning();
		void Run();
		void Update();
		void Draw();
		GXRModeObj * gxrmode;

	protected:	
};

#endif
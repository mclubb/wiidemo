#include "Game.h"

Game::Game() {
	Init();
	this->running = TRUE;
}

void Game::Run() {
	while(this->running) {
		Update();
		Draw();
	}
}

bool Game::IsRunning() {
	return this->running;
}

void Game::Draw() {
	GX_DrawDone();
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp(framebuffer[fb], GX_TRUE);
	  
	VIDEO_SetNextFramebuffer(framebuffer[fb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();

	fb ^= 1;
}

void Game::Update() {
	WPAD_ScanPads();
	
	if(WPAD_ButtonsUp(0) & WPAD_BUTTON_HOME) {
		exit(0);
	}
}



void Game::Init() {
	  VIDEO_Init();
  gxrmode = VIDEO_GetPreferredMode(NULL);
  
  framebuffer[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(gxrmode));
  framebuffer[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(gxrmode));
  
  fb = 0;
  
  VIDEO_Configure(gxrmode);
  VIDEO_SetNextFramebuffer(framebuffer[fb]);
  VIDEO_SetBlack(FALSE);
  VIDEO_Flush();
  VIDEO_WaitVSync();

  if( gxrmode->viTVMode&VI_NON_INTERLACE ) {
    VIDEO_WaitVSync();
  }
  
  // Setup the fifo memory
  void * gpfifo = memalign(32, DEFAULT_FIFO_SIZE);
  memset(gpfifo, 0, DEFAULT_FIFO_SIZE);
  
  // Init our GX
  GX_Init(gpfifo, DEFAULT_FIFO_SIZE);
  
  GXColor backgroundColor = {100,149,237,255};
  //GXColor backgroundColor = {0,0,0,255};
  GX_SetCopyClear(backgroundColor, 0x00ffffff);
  
  f32 yscale = GX_GetYScaleFactor(gxrmode->efbHeight, gxrmode->xfbHeight);
  u32 xfbheight = GX_SetDispCopyYScale(yscale);
  GX_SetScissor(0, 0, gxrmode->fbWidth, gxrmode->efbHeight);
  GX_SetDispCopySrc(0, 0, gxrmode->fbWidth, gxrmode->efbHeight);
  GX_SetDispCopyDst(gxrmode->fbWidth, xfbheight);
  GX_SetCopyFilter(gxrmode->aa, gxrmode->sample_pattern, GX_TRUE, gxrmode->vfilter);
  GX_SetFieldMode(gxrmode->field_rendering, ((gxrmode->viHeight==2*gxrmode->xfbHeight)?GX_ENABLE:GX_DISABLE));
  
     if( gxrmode->aa ) {
        GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    }
    else {
        GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    }

    GX_SetCullMode(GX_CULL_NONE);
	fb ^= 1;
    GX_CopyDisp(framebuffer[fb], GX_TRUE);
    GX_SetDispCopyGamma(GX_GM_1_0);
	
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
	
	GX_InvalidateTexAll();
	
	// Camera Stuff Goes here
	GX_SetViewport(0, 0, gxrmode->fbWidth, gxrmode->efbHeight, 0, 1);
	
	guMtxIdentity(perspective);
	guPerspective(perspective, 45, (f32)gxrmode->viWidth/gxrmode->viHeight, 0.1F, 300.0F);
    GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);
	
	
	guMtxIdentity(view);
	
	guVector eye = {0, 1, 20}, up = {0, 1, 0}, at = {0, 1, 0};

	guLookAt(view, &eye, &up, &at);
	GX_LoadPosMtxImm(view, GX_PNMTX0);
	
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(WPAD_CHAN_ALL,640, 480);
}
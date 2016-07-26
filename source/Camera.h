#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <gccore.h>

class Camera {
public:
	Camera(GXRModeObj *);
	Camera(GXRModeObj *, guVector, guVector, guVector);
	Mtx44* GetView();
	void UpdateView(guVector, guVector, guVector);
	void Update();
	void Setup2D();
	void Setup3D();
private:
	GXRModeObj * gxrmode;
	Mtx44 view, orthographic, perspective;

	guVector eye;
	guVector up;
	guVector at;

protected:
	
};

#endif
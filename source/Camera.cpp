#include "Camera.h"

Camera::Camera(GXRModeObj * gxrmode) {
	this->gxrmode = gxrmode;
}



Camera::Camera(GXRModeObj * gxrmode, guVector eye, guVector up, guVector at) {
	this->gxrmode = gxrmode;
	this->eye = eye;
	this->up = up;
	this->at = at;
}

void Camera::UpdateView(guVector eye, guVector up, guVector at) {
	this->eye = eye;
	this->up = up;
	this->at = at;
}

void Camera::Setup2D() {
	guMtxIdentity(orthographic);
	guOrtho(orthographic, 0, gxrmode->viHeight, 0, gxrmode->viWidth, 0.1F, 300.0F);
	GX_LoadProjectionMtx(orthographic, GX_ORTHOGRAPHIC);
}

void Camera::Setup3D() {
	guMtxIdentity(perspective);
	guPerspective(perspective, 45, (f32)gxrmode->viWidth/gxrmode->viHeight, 0.1F, 300.0F);
	GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);
}

Mtx44* Camera::GetView() {
	return &this->view;
}

void Camera::Update() {
	guLookAt(view, &this->eye, &this->up, &this->at);
}
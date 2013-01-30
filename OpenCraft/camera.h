#ifndef __CAMERA_H
#define __CAMERA_H
#include "stdsct.h"

void Cam_SetPos(struct vec3 *pos);
void Cam_SetPos3f(float x, float y, float z);
void Cam_SetRot(struct vec3 *rot);
void Cam_SetRot3f(float x, float y, float z);
struct vec3 *Cam_GetPos(void);
struct vec3 *Cam_GetRot(void);
void Cam_Translate(struct vec3 *vel);
void Cam_Translate3f(float xvel, float yvel, float zvel);
void Cam_Move(float vel, float dir);
void Cam_Rotate(struct vec3 *vel);
void Cam_Rotate3f(float xvel, float yvel, float zvel);
void Cam_Draw(void);

void Cam_Bind(struct vec3 *pos, struct vec3 *rot);
void Cam_Unbind(void);
bool_t Cam_GetBound(void);


#endif//__CAMERA_H
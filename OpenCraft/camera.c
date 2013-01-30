#include "camera.h"
#include <math.h>
#include <SDL/SDL_opengl.h>
#define DEG_TO_RAD(x) ((x) * 0.0174532925)

static struct vec3 local_pos = {0.0f, 0.0f, 0.0f}, local_rot = {0.0f, 0.0f, 0.0f};
static struct vec3 *cam_pos = &local_pos, *cam_rot = &local_rot;
static bool_t cam_bound = FALSE;

void Cam_SetPos(struct vec3 *pos)
{
	cam_pos = pos;
}

void Cam_SetPos3f(float x, float y, float z)
{
	cam_pos->x = x;
	cam_pos->y = y;
	cam_pos->z = z;
}

void Cam_SetRot(struct vec3 *rot)
{
	cam_rot = rot;
}

void Cam_SetRot3f(float x, float y, float z)
{
	cam_rot->x = x;
	cam_rot->y = y;
	cam_rot->z = z;
}

struct vec3 *Cam_GetPos(void)
{
	return cam_pos;
}

struct vec3 *Cam_GetRot(void)
{
	return cam_rot;
}

void Cam_Translate(struct vec3 *vel)
{
	cam_pos->x += vel->x;
	cam_pos->y += vel->y;
	cam_pos->z += vel->z;
}

void Cam_Translate3f(float xvel, float yvel, float zvel)
{
	cam_pos->x += xvel;
	cam_pos->y += yvel;
	cam_pos->z += zvel;
}

void Cam_Move(float vel, float dir)
{
	cam_pos->x -= sin(DEG_TO_RAD(cam_rot->y + dir)) * vel;
	cam_pos->z -= cos(DEG_TO_RAD(cam_rot->y + dir)) * vel;
}

void Cam_Rotate(struct vec3 *vel)
{
	cam_rot->x += vel->x;
	cam_rot->y += vel->y;
	cam_rot->z += vel->z;

	if(cam_rot->x > 90.0f) cam_rot->x = 90.0f;
	if(cam_rot->x < -90.0f) cam_rot->x = -90.0f;
	if(cam_rot->y > 360.0f) cam_rot->y -= 360.0f;
	if(cam_rot->y < 360.0f) cam_rot->y += 360.0f;
}

void Cam_Rotate3f(float xvel, float yvel, float zvel)
{
	cam_rot->x += xvel;
	cam_rot->y += yvel;
	cam_rot->z += zvel;

	if(cam_rot->x > 90.0f) cam_rot->x = 90.0f;
	if(cam_rot->x < -90.0f) cam_rot->x = -90.0f;
	if(cam_rot->y > 360.0f) cam_rot->y -= 360.0f;
	if(cam_rot->y < 360.0f) cam_rot->y += 360.0f;
}

void Cam_Draw(void)
{
	glRotatef(cam_rot->x, -1.0f, 0.0f, 0.0f);
	glRotatef(cam_rot->y, 0.0f, -1.0f, 0.0f);
	glRotatef(cam_rot->z, 0.0f, 0.0f, -1.0f);
	glTranslatef(-cam_pos->x, -cam_pos->y, -cam_pos->z);
}

void Cam_Bind(struct vec3 *pos, struct vec3 *rot)
{
	cam_pos = pos;
	cam_rot = rot;
	cam_bound = TRUE;
}

void Cam_Unbind(void)
{
	cam_pos = &local_pos;
	cam_rot = &local_rot;
	cam_bound = FALSE;
}

bool_t Cam_GetBound(void)
{
	return cam_bound;
}
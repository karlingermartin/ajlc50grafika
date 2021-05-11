#include "draw.h"
#include "model.h"
#include "callbacks.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

double mapWidth = 200;
double mapLength = 4000;
double mapHeight = 200;

GLfloat material_ambient_default[] = {0.9, 0.9, 0.9, 0.5};

void draw_content(World* world)
{
	Map roomToDraw = world -> map;
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		draw_walls(roomToDraw);
		draw_ground(roomToDraw);
		draw_finish(roomToDraw);
	glPopMatrix();

	draw_boxes(500, 0, 0);
	draw_boxes(1000, -80, 0);
	draw_boxes(1500, -120, 0);
	draw_boxes(2000, -60, 0);
	draw_boxes(2500, -100, 0);
	draw_boxes(3000, -70, 0);
	draw_boxes(3500, 0, 0);
	
	draw_boxes(250, -340, 0);
	draw_boxes(750, -290, 0);
	draw_boxes(1250, -280, 0);
	draw_boxes(1750, -260, 0);
	draw_boxes(2250, -280, 0);
	draw_boxes(2750, -270, 0);
	draw_boxes(3250, -310, 0);
	draw_boxes(3750, -330, 0);

	glPushMatrix();
		glTranslatef(world->cars[0].position.x, world->cars[0].position.y, world->cars[0].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->cars[0].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->cars[0].texture);
		glScalef(25.0f, 25.0f, 25.0f);
		glRotatef(world->cars[0].rotation, 0, 1, 0);

		draw_model(&world->cars[0].model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->cars[1].position.x, world->cars[1].position.y, world->cars[1].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->cars[1].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->cars[1].texture);
		glScalef(25.0f, 25.0f, 25.0f);
		glRotatef(world->cars[1].rotation, 0, 1, 0);

		draw_model(&world->cars[1].model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->cars[2].position.x, world->cars[2].position.y, world->cars[2].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->cars[2].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->cars[2].texture);
		glScalef(25.0f, 25.0f, 25.0f);
		glRotatef(world->cars[2].rotation, 0, 1, 0);

		draw_model(&world->cars[2].model);
    glPopMatrix();

	if (move_car_id != -1)
	{
		world->cars[move_car_id].position.x = camera.position.x;
		world->cars[move_car_id].position.z = camera.position.z;
	}
}

void draw_boxes(int moveX, int moveZ,int degree) {
	glPushMatrix();
		glTranslatef(world.boxes.position.x+moveX, world.boxes.position.y, world.boxes.position.z+moveZ);
		glRotatef(degree, 0, 1, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world.boxes.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world.boxes.texture);
		glScalef(15.0f, 15.0f, 15.0f);

		draw_model(&world.boxes.model);
    glPopMatrix();
}

void draw_ground(Map map) {
	glBindTexture(GL_TEXTURE_2D, map.ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	for (x = -200; x < mapLength; x += 50) {
		for (z = -200; z < mapWidth; z += 50) {
			glTexCoord2f(0.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}

void draw_finish(Map map) {
	glBindTexture(GL_TEXTURE_2D, map.finish);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(mapLength, -mapWidth, mapHeight);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(mapLength, mapWidth, mapHeight);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(mapLength, mapWidth, -mapHeight);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(mapLength, -mapWidth, -mapHeight);
	glEnd();
}

void draw_walls(Map map) {
	glBindTexture(GL_TEXTURE_2D, map.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-mapWidth, 0, -mapWidth);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-mapWidth, mapWidth, -mapWidth);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-mapWidth, mapWidth, mapWidth);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-mapWidth, 0, mapWidth);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, map.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-mapWidth, 0, -mapWidth);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(mapLength, 0, -mapWidth);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(mapLength, mapWidth, -mapWidth);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-mapWidth, mapWidth, -mapWidth);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, map.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(mapLength, 0, mapWidth);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(mapLength, mapWidth, mapWidth);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-mapWidth, mapWidth, mapWidth);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-mapWidth, 0, mapWidth);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, map.top);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(mapLength, mapWidth, mapWidth);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(mapLength, mapWidth, mapWidth);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-mapWidth, mapWidth, mapWidth);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-mapWidth, mapWidth, mapWidth);
	glEnd();
}

void draw_help(int texture) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
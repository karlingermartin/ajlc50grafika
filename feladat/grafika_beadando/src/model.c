#include "model.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include <obj/load.h>
#include <obj/draw.h>

void init_object(Object* object, int x, int z, int y)
{
	object->position.x = x;
	object->position.y = y;
	object->position.z = z;

	object->material_ambient[0] = 0.75;
	object->material_ambient[1] = 0.75;
	object->material_ambient[2] = 0.75;
	object->material_ambient[3] = 0.5;
}

// Loads the texture file with SOIL
GLuint load_texture(const char* filename) {
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	GLuint texture_name;
	Pixel* image;
	glGenTextures(1, &texture_name);

	int width;
	int height;

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

	glBindTexture(GL_TEXTURE_2D, texture_name);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGBA,GL_UNSIGNED_BYTE,(Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return texture_name;
}

void init_entities(World* world) {
	move_car_id = -1;

	//Cars:
	load_model(&world->cars[0].model, "data/models/car.obj");
	world->cars[0].texture = load_texture("data/textures//car.png");
	init_object(&world->cars[0], -120, -50, 0);
	world->cars[0].rotation = 90.0f;

	world->cars[1].model = world->cars[0].model;
	world->cars[1].texture = world->cars[0].texture;
	init_object(&world->cars[1], -120, 130, 0);
	world->cars[1].rotation = 90.0f;

	world->cars[2].model = world->cars[0].model;
	world->cars[2].texture = world->cars[0].texture;
	init_object(&world->cars[2], -120, 40, 0);
	world->cars[2].rotation = 90.0f;


	// Boxes:
	load_model(&world->boxes.model, "data/models/box.obj");
	world->boxes.texture = load_texture("data/textures//boxes_texture.png");
	init_object(&world->boxes, -120, 170, 2);

	// Map:
	world->map.finish = load_texture("data/textures//finish.png");
	world->map.ground = load_texture("data/textures//floor.jpg");
	world->map.back = load_texture("data/textures//brick.jpg");
	world->map.front = world->map.back;
	world->map.left = world->map.back;
	world->map.right = world->map.back;
	//world->map.top = load_texture("data/textures//top.jpg");

	// Help:
	world->helpTexture = load_texture("data/textures//help.png");
}

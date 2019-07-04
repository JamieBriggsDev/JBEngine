#pragma once
 
#include "ItemManager.h"

class Object;
class Camera;
class Window;

class DrawEngine
{
public:
	void Update(Camera* _camera, Window* _window, ItemManager<Object>* _objects);

	DrawEngine();
	~DrawEngine();
};


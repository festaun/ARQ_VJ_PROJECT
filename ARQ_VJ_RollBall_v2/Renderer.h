#pragma once
#include "core.h"
#include "Entity.h"
class Renderer {
	public:
		void draw();
		void setRenderField();
		void renderEntity(Entity* entity);
		void renderWorld();
};

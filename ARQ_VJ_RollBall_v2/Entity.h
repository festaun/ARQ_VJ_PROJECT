#pragma once
#include "core.h"
class Visual {
	vec2 pos;
	Visual();
};
class Entity {
	private:
		vec2 pos;
		Visual visual;

	public:
		Entity();
		void updateVisual();
};
class E_Player : public Entity {

};

class E_Item : public Entity {

};

class E_Obstacle : public Entity {

};
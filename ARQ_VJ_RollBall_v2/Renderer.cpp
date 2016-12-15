#include "stdafx.h"
#include "Renderer.h"

void Renderer::draw(){

}

void Renderer::setRenderField() {

}

void Renderer::renderEntity(Entity *entity) {

}


/*
		// Render
		glClear(GL_COLOR_BUFFER_BIT);

		// Render background
		for (int i = 0; i <= SCR_WIDTH / 128; i++)
			for (int j = 0; j <= SCR_HEIGHT / 128; j++)
				CORE_RenderCenteredSprite(vmake(i * 128.f + 64.f, j * 128.f + 64.f), vmake(128.f, 128.f), texbkg);
		//Render Player
		CORE_RenderCenteredSprite(player.pos, vmake(player.radius * 2.f, player.radius * 2.f),player.gfx);
		//Render Collectible items
		
		for (int i = 0; i < gameItems; i++)
			CORE_RenderCenteredSprite(items[i].pos, vmake(items[i].radius * 2.f, items[i].radius * 2.f), items[i].gfx);
		SYS_Show();

*/

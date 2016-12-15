#include "stdafx.h"
#include "sys.h"
#include "core.h"

//----------------------------------
#define PLAYER_SPEED 4
struct Player {
	vec2 pos;
	GLuint gfx;
	float  radius;
};

Player player;

struct Item {
	vec2 pos;
	GLuint gfx;
	float  radius;
};

#define NUM_ITEMS 5
std::vector<Item> items(NUM_ITEMS);
//----------------------------------



//----------------------------------
int Main(void)
{
	int gameItems = NUM_ITEMS;

	// Load textures
	GLuint texbkg = CORE_LoadPNG("data/game-bkg-128.png", true);
	GLuint texItem = CORE_LoadPNG("data/tyrian_ball.png", false);
	GLuint texPlayer = CORE_LoadPNG("data/player-icon.png", false);

	// Init game state
	player.pos = vmake(SCR_WIDTH / 2, SCR_HEIGHT / 2);
	player.gfx = texPlayer;
	player.radius = 16.f;

	for (int i = 0; i < gameItems; i++)
	{
		items[i].pos = vmake(rand() % SCR_WIDTH, rand() % SCR_HEIGHT);
		items[i].gfx = texItem;
		items[i].radius = 16.f;
	}
	
	// Set up rendering
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
	glClearColor(0.0f, 0.1f, 0.3f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!SYS_GottaQuit())
	{
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

		//Player Movement Logic
		
		if (SYS_KeyPressed(SYS_KEY_LEFT)) {
			player.pos = vsub(player.pos, { PLAYER_SPEED,0 });
		}
		if (SYS_KeyPressed(SYS_KEY_RIGHT)) {
			player.pos = vadd(player.pos, { PLAYER_SPEED,0 });
		}
		if (SYS_KeyPressed(SYS_KEY_DOWN)) {
			player.pos = vsub(player.pos, { 0,PLAYER_SPEED });
		}
		if (SYS_KeyPressed(SYS_KEY_UP)) {
			player.pos = vadd(player.pos, { 0,PLAYER_SPEED });
		}

		//Item collision Logic
		bool collision = false;
		int colliding_ball = -1;

		for (int j = 0; j < gameItems; j++)
		{
			float limit2 = (player.radius + items[j].radius)* (player.radius + items[j].radius);
			if (vlen2(vsub(player.pos, items[j].pos)) <= limit2)
			{
				collision = true;
				colliding_ball = j;
				break;
			}
		}
		
		if (collision ) {
			items.erase(items.begin() + colliding_ball);
			gameItems--;
			colliding_ball = -1;
			collision = false;
		}

		SYS_Pump();
		SYS_Sleep(16);

	}

	CORE_UnloadPNG(texbkg);
	CORE_UnloadPNG(texItem);
	CORE_UnloadPNG(texPlayer);

	return 0;
}

/*#include "stdafx.h"
#include "sys.h"
#include "core.h"

//-----------------------------------------------------------------------------
struct Ball
{
  vec2   pos;
  vec2   vel;
  GLuint gfx;
  float  radius;
};
#define NUM_BALLS 20
Ball balls[NUM_BALLS];

#define MAX_BALL_SPEED 8.f

//-----------------------------------------------------------------------------
int Main(void)
{
  // Load textures
  GLuint texbkg        = CORE_LoadPNG("data/circle-bkg-128.png"   , true);
  GLuint texlargeball  = CORE_LoadPNG("data/ball128.png"          , false);
  GLuint texsmallball  = CORE_LoadPNG("data/tyrian_ball.png"      , false);

  // Init game state
  for (int i = 0; i < NUM_BALLS; i++)
  {
    balls[i].pos = vmake(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
    balls[i].vel = vmake(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
    if (CORE_FRand(0.f, 1.f) < 0.10f)
    {
      balls[i].radius = 64.f;
      balls[i].gfx = texlargeball;
    }
    else
    {
      balls[i].radius = 16.f;
      balls[i].gfx = texsmallball;
    }
  }

  // Set up rendering
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
  glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!SYS_GottaQuit())
  {
    // Render
    glClear( GL_COLOR_BUFFER_BIT );

    // Render backgground
    for (int i = 0; i <= SCR_WIDTH/128; i++)
      for (int j = 0; j <= SCR_HEIGHT/128; j++)
        CORE_RenderCenteredSprite(vmake(i * 128.f + 64.f, j * 128.f + 64.f), vmake(128.f, 128.f), texbkg);

    // Render balls
    for (int i = 0; i < NUM_BALLS; i++)
      CORE_RenderCenteredSprite(balls[i].pos, vmake(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);
   
    SYS_Show();

    // Run balls
    for (int i = 0; i < NUM_BALLS; i++)
    {
      vec2 oldpos = balls[i].pos;
      vec2 newpos = vadd(oldpos, balls[i].vel);

      bool collision = false;
      int colliding_ball = -1;
      for (int j = 0; j < NUM_BALLS; j++)
      {
        if (i != j)
        {
          float limit2 = (balls[i].radius + balls[j].radius) * (balls[i].radius + balls[j].radius);
          if (vlen2(vsub(oldpos, balls[j].pos)) > limit2 && vlen2(vsub(newpos, balls[j].pos)) <= limit2)
          {
            collision = true;
            colliding_ball = j;
            break;
          }
        }
      }

      if (!collision)
        balls[i].pos = newpos;
      else
      {
        // Rebound!
        balls[i].vel = vscale(balls[i].vel, -1.f);
        balls[colliding_ball].vel = vscale(balls[colliding_ball].vel, -1.f);
      }

      // Rebound on margins
      if (balls[i].vel.x > 0.0)
      {
        if (balls[i].pos.x > SCR_WIDTH)
          balls[i].vel.x *= -1.0;
      } else {
        if (balls[i].pos.x < 0)
          balls[i].vel.x *= -1.0;
      }
      if (balls[i].vel.y > 0.0)
      {
        if (balls[i].pos.y > SCR_HEIGHT)
          balls[i].vel.y *= -1.0;
      } else {
        if (balls[i].pos.y < 0)
          balls[i].vel.y *= -1.0;
      }
    }
   
    // Keep system running
    SYS_Pump();
    SYS_Sleep(17);
  }

  CORE_UnloadPNG(texbkg);
  CORE_UnloadPNG(texlargeball);
  CORE_UnloadPNG(texsmallball);

  return 0;
}
*/
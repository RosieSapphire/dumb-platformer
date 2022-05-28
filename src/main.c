#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <stdio.h>

#include "vec2.h"

#define WINDOW_WIDTH        1280.0f
#define WINDOW_HEIGHT       720.0f
#define WINDOW_TITLE        "Platformer - SDL2"

#define ACCEL_RATE			0.6f * 5200.0f
#define DECCEL_RATE			18.0f
#define PLAYER_SIZE			32.0f

#define GRAVITY				ACCEL_RATE
#define FLOOR_HEIGHT		(player_size.y * 16)

#define VEL_LIMIT			1024.0f
#define BASE_JUMP_VEL		1024.0f

#define MAP_WIDTH			((uint32)WINDOW_WIDTH / (uint32)PLAYER_SIZE)
#define MAP_HEIGHT			((uint32)WINDOW_HEIGHT / (uint32)PLAYER_SIZE)
#define MAP_SIZE			MAP_WIDTH * MAP_HEIGHT

int main() {
	uint32 i;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;

	Vec2 player_pos;
	Vec2 player_vel;
	Vec2 player_accel;
	Vec2 player_size;
	float32 max_vel = VEL_LIMIT;
	float32 jump_vel = BASE_JUMP_VEL;
	SDL_FRect player_rect;

	float64 time_delta;
    float64 time_now;
    float64 time_last;
    boolean window_should_close = 0;

	const uint8 *keyboard_state;
	boolean move_left;
	boolean move_right;
	boolean is_grounded = 0;
	boolean is_running = 0;
	boolean should_jump = 0;

	uint8 map[MAP_SIZE] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	};

	window = SDL_CreateWindow(WINDOW_TITLE,
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						   	  WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	player_pos = vec2_new(64.0f, 64.0f);
	player_vel = vec2_zero();
	player_accel = vec2_zero();
	player_size = vec2_new(PLAYER_SIZE, PLAYER_SIZE);

	player_rect.x = player_pos.x;
	player_rect.y = player_pos.y;
	player_rect.w = player_size.x;
	player_rect.h = player_size.y;

	printf("%d\n", MAP_SIZE);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	time_last = (float64)SDL_GetPerformanceCounter() / (float64)SDL_GetPerformanceFrequency();
    while(!window_should_close) {
		uint16 x, y;

        time_now = (float64)SDL_GetPerformanceCounter() / (float64)SDL_GetPerformanceFrequency();
        time_delta = time_now - time_last;
        time_last = time_now;

		is_grounded = (player_pos.y >= FLOOR_HEIGHT);

        /* polling */
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_WINDOWEVENT_CLOSE:
					window_should_close = 1;
                break;

                case SDL_KEYDOWN:
					switch(e.key.keysym.sym) {
						case SDLK_ESCAPE:
							window_should_close = 1;
						break;

							/* TODO: Fix jumping button from looping */
						case SDLK_SPACE:
							if(is_grounded && !should_jump)
								should_jump = 1;
						break;

						default: break;
					}
                break;

                case SDL_QUIT:
					window_should_close = 1;
                break;
            }
        }

		keyboard_state = SDL_GetKeyboardState(NULL);
		move_left = keyboard_state[SDL_SCANCODE_D];
		move_right = keyboard_state[SDL_SCANCODE_A];

		is_running = keyboard_state[SDL_SCANCODE_LSHIFT];
		max_vel = VEL_LIMIT * (1 + (is_running * 0.5f));
		jump_vel = BASE_JUMP_VEL * (1 + (is_running * 0.5f));

		/* updating */
		player_accel = vec2_zero();
		player_accel.x += (float32)move_left * ACCEL_RATE * (float32)time_delta;
		player_accel.x -= (float32)move_right * ACCEL_RATE * (float32)time_delta;
		player_accel.y = GRAVITY * (float32)time_delta;

		player_vel = vec2_add(player_vel, player_accel);

		if(player_vel.x > max_vel)
			player_vel.x = max_vel;

		if(player_vel.x < -max_vel)
			player_vel.x = -max_vel;

		if(!move_left && !move_right) {
			player_vel.x = player_vel.x - ((player_vel.x) * DECCEL_RATE * (float32)time_delta);
		}

		if(is_grounded) {
			player_pos.y = FLOOR_HEIGHT;
			player_vel.y = 0.0f;
			if(should_jump)
				player_vel.y = -jump_vel;
		}

		if(!is_grounded)
			should_jump = 0;

		player_pos = vec2_add(player_pos, vec2_scale(player_vel, (float32)time_delta));

		if(player_pos.x < 0.0f) {
			player_pos.x = 0.0f;
			player_vel.x = 0.0f;
		}

		if(player_pos.x + player_size.x >= WINDOW_WIDTH) {
			player_pos.x = WINDOW_WIDTH - player_size.x;
			player_vel.x = 0.0f;
		}

		if(player_pos.y < 0.0f) {
			player_pos.y = 0.0f;
			player_vel.y = (-player_vel.y * 0.5f);
		}

		player_rect.x = player_pos.x;
		player_rect.y = player_pos.y;

        /* drawing */
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 0xFF);
		for(y = 0; y < MAP_HEIGHT; y++) {
			for(x = 0; x < MAP_WIDTH; x++) {
				SDL_Rect tile;
				SDL_Rect tile_b;
				tile.x = x * player_size.x;
				tile.y = y * player_size.y;
				tile.w = player_size.x;
				tile.h = player_size.y;
				tile_b.x = x * player_size.x;
				tile_b.y = y * player_size.y;
				tile_b.w = player_size.x;
				tile_b.h = player_size.y;
				if(map[y * MAP_WIDTH + x])
					SDL_RenderFillRect(renderer, &tile);

			}
		}

		/* TODO: Add collision with the tiles */
		map[((uint32)player_pos.y / MAP_HEIGHT) * MAP_WIDTH + ((uint32)player_pos.x / MAP_WIDTH)] = 1;

        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRectF(renderer, &player_rect);


        SDL_RenderPresent(renderer);

		/* printf("%f\n", 1.0 / time_delta); */
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

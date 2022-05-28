#include <stdio.h>
#include <math.h>
#include <SFML/Graphics.h>

#include "vec2.h"

#define WINDOW_WIDTH        1280.0f
#define WINDOW_HEIGHT       720.0f
#define WINDOW_TITLE        "Platformer - SFML"

#define ACCEL_RATE			0.6f * 5200.0f
#define DECCEL_RATE			18.0f
#define PLAYER_SIZE			32.0f

#define GRAVITY				ACCEL_RATE
#define FLOOR_HEIGHT		(player_size.y * 16)

#define VEL_LIMIT			1024.0f
#define BASE_JUMP_VEL		1024.0f
#define JUMP_VEL_INFLUENCE	0.0004f

#define MAP_WIDTH			((uint32)WINDOW_WIDTH / (uint32)PLAYER_SIZE)
#define MAP_HEIGHT			((uint32)WINDOW_HEIGHT / (uint32)PLAYER_SIZE)
#define MAP_SIZE			MAP_WIDTH * MAP_HEIGHT

int main() {
	sfVideoMode video_mode;
	sfRenderWindow *render_window;
	sfEvent e;

	sfVector2f player_pos;
	sfVector2f player_vel;
	sfVector2f player_accel;
	sfVector2f player_size;
	float32 max_vel = VEL_LIMIT;
	float32 jump_vel = BASE_JUMP_VEL;
	sfRectangleShape *player_rect;

	sfRectangleShape *tile_rect;

	sfClock *clock;
	float32 time_delta;

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

	video_mode.width = WINDOW_WIDTH;
	video_mode.height = WINDOW_HEIGHT;
	video_mode.bitsPerPixel = 24;
	render_window = sfRenderWindow_create(video_mode, WINDOW_TITLE, sfClose, NULL);

	player_pos = sfVector2f_new(64.0f, 64.0f);
	player_vel = sfVector2f_zero();
	player_accel = sfVector2f_zero();
	player_size = sfVector2f_new(PLAYER_SIZE, PLAYER_SIZE);

	player_rect = sfRectangleShape_create();
	sfRectangleShape_setPosition(player_rect, player_pos);
	sfRectangleShape_setSize(player_rect, player_size);
	sfRectangleShape_setFillColor(player_rect, sfGreen);

	tile_rect = sfRectangleShape_create();
	sfRectangleShape_setSize(tile_rect, player_size);
	sfRectangleShape_setFillColor(tile_rect, sfBlue);

	clock = sfClock_create();
    while(sfRenderWindow_isOpen(render_window)) {
		uint16 x, y;

        time_delta = sfTime_asSeconds(sfClock_restart(clock));

        /* polling */
        while(sfRenderWindow_pollEvent(render_window, &e)) {
            switch(e.type) {
                case sfEvtClosed:
					sfRenderWindow_close(render_window);
                break;

                case sfEvtKeyPressed:
					switch(e.key.code) {
						case sfKeyQ:
						case sfKeyEscape:
							sfRenderWindow_close(render_window);
						break;

							/* TODO: Fix jumping button from looping */
						case sfKeySpace:
							if(is_grounded && !should_jump)
								should_jump = 1;
						break;

						default: break;
					}
                break;

				default: break;
            }
        }

		move_left = sfKeyboard_isKeyPressed(sfKeyD);
		move_right = sfKeyboard_isKeyPressed(sfKeyA);
		is_running = sfKeyboard_isKeyPressed(sfKeyLShift);

		max_vel = VEL_LIMIT * (1 + (is_running * 0.5f));
		jump_vel = BASE_JUMP_VEL * (1 + (fabs(player_vel.x) * JUMP_VEL_INFLUENCE));

		/* updating */
		player_accel = sfVector2f_zero();
		player_accel.x += (float32)move_left * ACCEL_RATE * (float32)time_delta;
		player_accel.x -= (float32)move_right * ACCEL_RATE * (float32)time_delta;
		player_accel.y = GRAVITY * (float32)time_delta;

		player_vel = sfVector2f_add(player_vel, player_accel);

		if(player_vel.x > max_vel)
			player_vel.x = max_vel;

		if(player_vel.x < -max_vel)
			player_vel.x = -max_vel;

		if(!move_left && !move_right) {
			player_vel.x = player_vel.x - ((player_vel.x) * DECCEL_RATE * (float32)time_delta);
		}

		player_pos = sfVector2f_add(player_pos, sfVector2f_scale(player_vel, (float32)time_delta));

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

		is_grounded = player_pos.y >= FLOOR_HEIGHT;
		if(is_grounded) {
			player_vel.y = 0.0f;
			if(should_jump)
				player_vel.y = -jump_vel;
			else
				player_pos.y = FLOOR_HEIGHT;
		} else {
			should_jump = 0;
		}

		sfRectangleShape_setPosition(player_rect, player_pos);

        /* drawing */
		sfRenderWindow_clear(render_window, sfBlack);

		for(y = 0; y < MAP_HEIGHT; y++) {
			for(x = 0; x < MAP_WIDTH; x++) {
				sfVector2f tile_pos;
				tile_pos = sfVector2f_new(x * player_size.x, y * player_size.y);
				sfRectangleShape_setPosition(tile_rect, tile_pos);
				if(map[y * MAP_WIDTH + x])
					sfRenderWindow_drawRectangleShape(render_window, tile_rect, NULL);
			}
		}

		/* TODO: Add collision with the tiles */
		sfRenderWindow_drawRectangleShape(render_window, player_rect, NULL);
		sfRenderWindow_display(render_window);

		printf("%f\n", 1.0 / time_delta);
    }

	sfRenderWindow_destroy(render_window);
	sfRectangleShape_destroy(player_rect);
	sfRectangleShape_destroy(tile_rect);
	sfClock_destroy(clock);

    return 0;
}

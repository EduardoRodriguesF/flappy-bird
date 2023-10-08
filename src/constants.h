#pragma once

#define WINDOW_WIDTH 288
#define WINDOW_HEIGHT 512

#define LOGICAL_SCREEN_WIDTH (WINDOW_WIDTH / 1)
#define LOGICAL_SCREEN_HEIGHT (WINDOW_HEIGHT / 1)

#define FPS 60
#define TARGET_FRAME_TIME (1000 / FPS)

#define GRAVITY_FORCE 1.9f
#define JUMP_FORCE 0.8f
#define MAX_VERTICAL_SPEED 2.3f
#define FLOOR_HEIGHT (LOGICAL_SCREEN_HEIGHT - 24)

#define SCENE_SPEED 35.0f
#define BG_SPEED (SCENE_SPEED / 4.0f)

#define GAP_RADIUS 25
#define PIPE_WIDTH 52

#define PIPE_TIMEOUT_MS (3 * 1000)

#define S_BIRD_UPFLAP "yellowbird-upflap.png"
#define S_BIRD_MIDFLAP "yellowbird-midflap.png"
#define S_BIRD_DOWNFLAP "yellowbird-downflap.png"

#define S_PIPE "pipe-green.png"

#define S_BG_DAY "background-day.png"
#define S_BG_NIGHT "background-day.png"

#define S_BASE "base.png"

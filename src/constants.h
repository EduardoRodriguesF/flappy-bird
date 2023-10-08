#pragma once

#define WINDOW_WIDTH 288
#define WINDOW_HEIGHT 512

#define LOGICAL_SCREEN_WIDTH (WINDOW_WIDTH / 1)
#define LOGICAL_SCREEN_HEIGHT (WINDOW_HEIGHT / 1)

#define FPS 60

constexpr int TARGET_FRAME_TIME = 1000 / FPS;
constexpr int FLOOR_HEIGHT = (LOGICAL_SCREEN_HEIGHT - 24);

constexpr float UNIT = 100.0f;

constexpr float GRAVITY_FORCE = (6.0f * UNIT);
constexpr float JUMP_FORCE = (2.6f * UNIT);
constexpr float MAX_VERTICAL_SPEED = (4.8f * UNIT);

constexpr float SCENE_SPEED = (0.9f * UNIT);
constexpr float BG_SPEED = (SCENE_SPEED / 4.0f);

constexpr int PIPE_TIMEOUT_MS = (2.0f * 1000);

#define GAP_RADIUS 35
#define PIPE_WIDTH 52

#define S_BIRD_UPFLAP "yellowbird-upflap.png"
#define S_BIRD_MIDFLAP "yellowbird-midflap.png"
#define S_BIRD_DOWNFLAP "yellowbird-downflap.png"

#define S_PIPE "pipe-green.png"

#define S_BG_DAY "background-day.png"
#define S_BG_NIGHT "background-day.png"

#define S_BASE "base.png"

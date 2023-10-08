#pragma once

#include <string>
#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 420

#define LOGICAL_SCREEN_WIDTH (WINDOW_WIDTH / 1)
#define LOGICAL_SCREEN_HEIGHT (WINDOW_HEIGHT / 1)

#define FPS 60

constexpr int TARGET_FRAME_TIME = 1000 / FPS;
constexpr int FLOOR_HEIGHT = (LOGICAL_SCREEN_HEIGHT - 24);

constexpr float UNIT = 100.0f;

constexpr float GRAVITY_FORCE = (8.5f * UNIT);
constexpr float JUMP_FORCE = (2.6f * UNIT);
constexpr float MAX_VERTICAL_SPEED = (4.8f * UNIT);

constexpr float SCENE_SPEED = (0.9f * UNIT);
constexpr float BG_SPEED = (SCENE_SPEED / 4.0f);

constexpr int PIPE_TIMEOUT_MS = (2.0f * 1000);

#define GAP_RADIUS 40
#define PIPE_WIDTH 52

#define A_POINT "point.wav"
#define A_DIE "die.wav"

#define S_BIRD_UPFLAP "yellowbird-upflap.png"
#define S_BIRD_MIDFLAP "yellowbird-midflap.png"
#define S_BIRD_DOWNFLAP "yellowbird-downflap.png"

#define S_PIPE "pipe-green.png"

#define S_BG_DAY "background-day.png"
#define S_BG_NIGHT "background-day.png"

#define S_0 "0.png"
#define S_1 "1.png"
#define S_2 "2.png"
#define S_3 "3.png"
#define S_4 "4.png"
#define S_5 "5.png"
#define S_6 "6.png"
#define S_7 "7.png"
#define S_8 "8.png"
#define S_9 "9.png"

#define S_BASE "base.png"

const std::string_view DIGITS[10] { S_0, S_1, S_2, S_3, S_4, S_5, S_6, S_7, S_8, S_9 };

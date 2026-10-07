#pragma once

#include <Arduino.h>

// ======================================================================
// --- FACE BITMAPS ---
// Bitmaps for the faces are stored here, can be generated with image2cpp
// Optional animated frames can be added by defining bitmaps with suffixes
// _1, _2, _3, ... (example: epd_bitmap_walk_1).
// ======================================================================

// Add or remove faces here (single source of truth)
#define FACE_LIST     \
	X(walk)           \
	X(rest)           \
	X(swim)           \
	X(dance)          \
	X(wave)           \
	X(point)          \
	X(stand)          \
	X(cute)           \
	X(pushup)         \
	X(freaky)         \
	X(bow)            \
	X(worm)           \
	X(shake)          \
	X(shrug)          \
	X(dead)           \
	X(crab)           \
	X(defualt)        \
	X(idle)           \
	X(idle_blink)     \
	X(happy)          \
	X(talk_happy)     \
	X(sad)            \
	X(talk_sad)       \
	X(angry)          \
	X(talk_angry)     \
	X(surprised)      \
	X(talk_surprised) \
	X(sleepy)         \
	X(talk_sleepy)    \
	X(love)           \
	X(talk_love)      \
	X(excited)        \
	X(talk_excited)   \
	X(confused)       \
	X(talk_confused)  \
	X(thinking)       \
	X(talk_thinking)

#define X(name) extern const unsigned char epd_bitmap_##name[] PROGMEM __attribute__((weak));
FACE_LIST
#undef X

// Paste raw image2cpp output below. This remaps `const` so the symbols
// have external linkage and can be weak-referenced safely.
#define const extern const

// 'sleepy-1', 128x64px
const unsigned char epd_bitmap_talk_sleepy[] PROGMEM = {
    // Enter custom bitmap
};

// 'sleepy', 128x64px
const unsigned char epd_bitmap_sleepy[] PROGMEM = {
    // Enter custom bitmap
};

// 'sad-1', 128x64px
const unsigned char epd_bitmap_talk_sad[] PROGMEM = {
    // Enter custom bitmap
};

// 'sad', 128x64px
const unsigned char epd_bitmap_sad[] PROGMEM = {
    // Enter custom bitmap
};

// 'excited-1', 128x64px
const unsigned char epd_bitmap_talk_excited[] PROGMEM = {
    // Enter custom bitmap
};

// 'love-1', 128x64px
const unsigned char epd_bitmap_talk_love[] PROGMEM = {
    // Enter custom bitmap
};

// 'love', 128x64px
const unsigned char epd_bitmap_love[] PROGMEM = {
    // Enter custom bitmap
};

// 'excited', 128x64px
const unsigned char epd_bitmap_excited[] PROGMEM = {
    // Enter custom bitmap
};

// 'thinking', 128x64px
const unsigned char epd_bitmap_thinking[] PROGMEM = {
    // Enter custom bitmap
};

// 'thinking-1', 128x64px
const unsigned char epd_bitmap_talk_thinking[] PROGMEM = {
    // Enter custom bitmap
};

// 'thinking-2', 128x64px
const unsigned char epd_bitmap_thinking_2[] PROGMEM = {
    // Enter custom bitmap
};

// 'confused-1', 128x64px
const unsigned char epd_bitmap_talk_confused[] PROGMEM = {
    // Enter custom bitmap
};

// 'confused', 128x64px
const unsigned char epd_bitmap_confused[] PROGMEM = {
    // Enter custom bitmap
};

// 'surprised', 128x64px
const unsigned char epd_bitmap_surprised[] PROGMEM = {
    // Enter custom bitmap
};

// 'surprised-1', 128x64px
const unsigned char epd_bitmap_talk_surprised[] PROGMEM = {
    // Enter custom bitmap
};

// 'angry-1', 128x64px
const unsigned char epd_bitmap_talk_angry[] PROGMEM = {
    // Enter custom bitmap
};

// 'angry', 128x64px
const unsigned char epd_bitmap_angry[] PROGMEM = {
    // Enter custom bitmap
};

// 'happy', 128x64px
const unsigned char epd_bitmap_happy[] PROGMEM = {
    // Enter custom bitmap
};

// 'happy-1', 128x64px
const unsigned char epd_bitmap_talk_happy[] PROGMEM = {
    // Enter custom bitmap
};

// 'swim', 128x64px
const unsigned char epd_bitmap_swim[] PROGMEM = {
    // Enter custom bitmap
};

// 'rest', 128x64px
const unsigned char epd_bitmap_rest[] PROGMEM = {
    // Enter custom bitmap
};

// 'point-1', 128x64px
const unsigned char epd_bitmap_point_1[] PROGMEM = {
    // Enter custom bitmap
};

// 'dance-1', 128x64px
const unsigned char epd_bitmap_dance_1[] PROGMEM = {
    // Enter custom bitmap
};

// 'point-2', 128x64px
const unsigned char epd_bitmap_point_2[] PROGMEM = {
    // Enter custom bitmap
};

// 'point', 128x64px
const unsigned char epd_bitmap_point[] PROGMEM = {
    // Enter custom bitmap
};

// 'dead-1', 128x64px
const unsigned char epd_bitmap_dead_1[] PROGMEM = {
    // Enter custom bitmap
};

// 'rest-1', 128x64px
const unsigned char epd_bitmap_rest_1[] PROGMEM = {
    // Enter custom bitmap
};

// 'idle-blink-2', 128x64px
const unsigned char epd_bitmap_idle_blink_2[] PROGMEM = {
    // Enter custom bitmap
};

// 'shrug', 128x64px
const unsigned char epd_bitmap_shrug[] PROGMEM = {
    // Enter custom bitmap
};

// 'crab', 128x64px
const unsigned char epd_bitmap_crab[] PROGMEM = {
    // Enter custom bitmap
};

// 'dead', 128x64px
const unsigned char epd_bitmap_dead[] PROGMEM = {
    // Enter custom bitmap
};

// 'dead-2', 128x64px
const unsigned char epd_bitmap_dead_2[] PROGMEM = {
    // Enter custom bitmap
};

// 'walk', 128x64px
const unsigned char epd_bitmap_walk[] PROGMEM = {
    // Enter custom bitmap
};

// 'idle-blink', 128x64px
const unsigned char epd_bitmap_idle_blink[] PROGMEM = {
    // Enter custom bitmap
};

// 'idle-blink-1', 128x64px
const unsigned char epd_bitmap_idle_blink_1[] PROGMEM = {
    // Enter custom bitmap
};

// 'cute', 128x64px
const unsigned char epd_bitmap_cute[] PROGMEM = {
    // Enter custom bitmap
};

// 'rest-2', 128x64px
const unsigned char epd_bitmap_rest_2[] PROGMEM = {
    // Enter custom bitmap
};

// 'wave', 128x64px
const unsigned char epd_bitmap_wave[] PROGMEM = {
    // Enter custom bitmap
};

// 'freaky', 128x64px
const unsigned char epd_bitmap_freaky[] PROGMEM = {
    // Enter custom bitmap
};

// 'bow', 128x64px
const unsigned char epd_bitmap_bow[] PROGMEM = {
    // Enter custom bitmap
};

// 'pushup', 128x64px
const unsigned char epd_bitmap_pushup[] PROGMEM = {
    // Enter custom bitmap
};

// 'shake', 128x64px
const unsigned char epd_bitmap_shake[] PROGMEM = {
    // Enter custom bitmap
};

// 'worm', 128x64px
const unsigned char epd_bitmap_worm[] PROGMEM = {
    // Enter custom bitmap
};

// 'dance', 128x64px
const unsigned char epd_bitmap_dance[] PROGMEM = {
    // Enter custom bitmap
};

// 'idle', 128x64px
const unsigned char epd_bitmap_idle[] PROGMEM = {
    // Enter custom bitmap
};

// 'idle-blink-3', 128x64px
const unsigned char epd_bitmap_idle_blink_3[] PROGMEM = {
    // Enter custom bitmap
};

// Optional animated frames (weak symbols). If a frame is not defined,
// its pointer will be null and the animation will stop at the base frame.
#undef const

#define DECLARE_FACE_FRAMES(name)                                                     \
	extern const unsigned char epd_bitmap_##name##_1[] PROGMEM __attribute__((weak)); \
	extern const unsigned char epd_bitmap_##name##_2[] PROGMEM __attribute__((weak)); \
	extern const unsigned char epd_bitmap_##name##_3[] PROGMEM __attribute__((weak)); \
	extern const unsigned char epd_bitmap_##name##_4[] PROGMEM __attribute__((weak)); \
	extern const unsigned char epd_bitmap_##name##_5[] PROGMEM __attribute__((weak));

#define X(name) DECLARE_FACE_FRAMES(name)
FACE_LIST
#undef X
#undef DECLARE_FACE_FRAMES

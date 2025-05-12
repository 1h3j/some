#ifndef CALLBACK_H
#define CALLBACK_H

#include <SDL3/SDL.h>

#ifndef GL_MAJOR
#define GL_MAJOR 3
#endif // !GL_MAJ

#ifndef GL_MINOR
#define GL_MINOR 3
#endif // !GL_MIN

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 512
#endif // !WINDOW_WIDTH

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 512
#endif // !WINDOW_HEIGHT

#include "events.h"

define_event_listener(EVENT_TYPE_RENDER_EVENT);

define_event_listener(EVENT_TYPE_SDL_EVENT);

define_event_listener(EVENT_TYPE_INIT_EVENT);
define_event_listener(EVENT_TYPE_QUIT_EVENT);

#ifdef USE_EVENT_CALLBACKS
int main(int argc, char** argv);
#endif // USE_EVENT_CALLBACKS

#endif // CALLBACK_H

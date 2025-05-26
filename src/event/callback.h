#ifndef CALLBACK_H
#define CALLBACK_H

#include <SDL3/SDL.h>

#if !defined (GL_MAJOR)
#define GL_MAJOR 3
#endif // !GL_MAJOR

#if !defined (GL_MINOR)
#define GL_MINOR 3
#endif // !GL_MINOR

#if !defined (WINDOW_WIDTH)
#define WINDOW_WIDTH 512
#endif // !WINDOW_WIDTH

#if !defined (WINDOW_HEIGHT)
#define WINDOW_HEIGHT 512
#endif // !WINDOW_HEIGHT

#include "events.h"

define_event_listener(EVENT_TYPE_RENDER_EVENT);

define_event_listener(EVENT_TYPE_SDL_EVENT);

define_event_listener(EVENT_TYPE_INIT_EVENT);
define_event_listener(EVENT_TYPE_QUIT_EVENT);

#endif // CALLBACK_H

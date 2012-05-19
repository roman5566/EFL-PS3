#include <assert.h>
#include "main.h"

#include <Evas_Engine_GL_SDL.h>

Eina_Bool
engine_gl_sdl_args(const char *engine, int width, int height)
{
   Evas_Engine_Info_GL_SDL *einfo;
   int                  i;

   evas_output_method_set(evas, evas_render_method_lookup("gl_sdl"));

   einfo = (Evas_Engine_Info_GL_SDL *) evas_engine_info_get(evas);
   if (!einfo)
     {
        printf("Evas wasn't build with GL SDL backend.\n");
        return EINA_FALSE;
     }

   /* the following is specific to the engine */
   einfo->flags.fullscreen = fullscreen;
   einfo->flags.noframe = 0;

   if (!evas_engine_info_set(evas, (Evas_Engine_Info *) einfo))
     {
	printf("Evas could not initialize the GL SDL Engine\n");
        return EINA_FALSE;
     }

   return EINA_TRUE;
}

void
engine_gl_sdl_loop(void)
{
   SDL_Event event;

   while(SDL_PollEvent(&event))
     {
        switch(event.type)
          {
          case SDL_MOUSEMOTION:
             evas_event_feed_mouse_move(evas, event.motion.x, event.motion.y, 0, NULL);
             break;
          case SDL_MOUSEBUTTONDOWN:
             evas_event_feed_mouse_move(evas, event.button.x, event.button.y, 0, NULL);
             evas_event_feed_mouse_down(evas, event.button.state, EVAS_BUTTON_NONE, 0, NULL);
             break;
          case SDL_MOUSEBUTTONUP:
             evas_event_feed_mouse_move(evas, event.button.x, event.button.y, 0, NULL);
             evas_event_feed_mouse_up(evas, event.button.state, EVAS_BUTTON_NONE, 0, NULL);
             break;
          case SDL_VIDEORESIZE:
             evas_output_viewport_set(evas, 0, 0,
                                      event.resize.w, event.resize.w);
             evas_output_size_set(evas, event.resize.w, event.resize.w);
             evas_output_size_get(evas, &win_w, &win_h);
             break;
          case SDL_VIDEOEXPOSE:
             evas_output_size_get(evas, &win_w, &win_h);
             evas_damage_rectangle_add(evas, 0, 0, win_w, win_h);
             break;
          case SDL_KEYDOWN:
             switch (event.key.keysym.sym)
               {
               case SDLK_LSHIFT:
               case SDLK_RSHIFT:
                  evas_key_modifier_on(evas, "Shift");
                  break;
               case SDLK_RCTRL:
               case SDLK_LCTRL:
                  evas_key_modifier_on(evas, "Control");
                  break;
               case SDLK_MENU:
               case SDLK_RALT:
               case SDLK_LALT:
                  evas_key_modifier_on(evas, "Alt");
                  break;
               case SDLK_LSUPER:
               case SDLK_RSUPER:
                  evas_key_modifier_on(evas, "Super");
                  break;
               case SDLK_CAPSLOCK:
                  if (evas_key_lock_is_set(evas_key_lock_get(evas), "Caps_Lock"))
                    evas_key_lock_off(evas, "Caps_Lock");
                  else
                    evas_key_lock_on(evas, "Caps_Lock");
                  break;
               case SDLK_NUMLOCK:
                  if (evas_key_lock_is_set(evas_key_lock_get(evas), "Num_Lock"))
                    evas_key_lock_off(evas, "Num_Lock");
                  else
                    evas_key_lock_on(evas, "Num_Lock");
                  break;
               case SDLK_SCROLLOCK:
                  if (evas_key_lock_is_set(evas_key_lock_get(evas), "Scroll_Lock"))
                    evas_key_lock_off(evas, "Scroll_Lock");
                  else
                    evas_key_lock_on(evas, "Scroll_Lock");
                  break;
               case SDLK_s:
               case SDLK_ESCAPE:
                  evas_event_feed_key_down(evas, "Escape", "Escape", NULL, NULL, 0, NULL);
                  break;
               case SDLK_KP_ENTER:
               case SDLK_RETURN:
                  evas_event_feed_key_down(evas, "Return", "Return", NULL, NULL, 0, NULL);
                  break;
               case SDLK_LEFT: evas_event_feed_key_down(evas, "Left", "Left", NULL, NULL, 0, NULL); break;
               case SDLK_RIGHT: evas_event_feed_key_down(evas, "Right", "Right", NULL, NULL, 0, NULL); break;
               case SDLK_q:
                  if (evas_key_lock_is_set(evas_key_lock_get(evas), "Caps_Lock"))
                    evas_event_feed_key_down(evas, "Q", "Q", NULL, NULL, 0, NULL);
                  else
                    evas_event_feed_key_down(evas, "q", "q", NULL, NULL, 0, NULL);
                  break;
	       default:
		  break;
               }
             break;
          case SDL_KEYUP:
             switch (event.key.keysym.sym)
               {
               case SDLK_LSHIFT:
               case SDLK_RSHIFT:
                  evas_key_modifier_off(evas, "Shift");
                  break;
               case SDLK_RCTRL:
               case SDLK_LCTRL:
                  evas_key_modifier_off(evas, "Control");
                  break;
               case SDLK_MENU:
               case SDLK_RALT:
               case SDLK_LALT:
                  evas_key_modifier_off(evas, "Alt");
                  break;
               case SDLK_LSUPER:
               case SDLK_RSUPER:
                  evas_key_modifier_off(evas, "Super");
                  break;
               case SDLK_ESCAPE: evas_event_feed_key_up(evas, "Escape", "Escape", NULL, NULL, 0, NULL); break;
               case SDLK_RETURN: evas_event_feed_key_up(evas, "Return", "Return", NULL, NULL, 0, NULL); break;
               case SDLK_LEFT: evas_event_feed_key_up(evas, "Left", "Left", NULL, NULL, 0, NULL); break;
               case SDLK_RIGHT: evas_event_feed_key_up(evas, "Right", "Right", NULL, NULL, 0, NULL); break;
               case SDLK_q:
                  if (evas_key_lock_is_set(evas_key_lock_get(evas), "Caps_Lock"))
                    evas_event_feed_key_up(evas, "Q", "Q", NULL, NULL, 0, NULL);
                  else
                    evas_event_feed_key_up(evas, "q", "q", NULL, NULL, 0, NULL);
                  break;
	       default:
		  break;
               }
             break;
          case SDL_QUIT:
          case SDL_SYSWMEVENT:
          case SDL_USEREVENT:
          case SDL_ACTIVEEVENT:
          case SDL_JOYAXISMOTION:
          case SDL_JOYBALLMOTION:
          case SDL_JOYHATMOTION:
          case SDL_JOYBUTTONDOWN:
          case SDL_JOYBUTTONUP:
          default:
             break;
          }
     }
}

void
engine_gl_sdl_shutdown(void)
{
}

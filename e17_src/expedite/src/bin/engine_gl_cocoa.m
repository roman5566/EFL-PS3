/* NOTE: If you're using Expedite for performance testing,
   set "Disable Beam Synchronization" in GL_Cocoa Debug. */

#include "main.h"

#include <Cocoa/Cocoa.h>
#include <Evas_Engine_GL_Cocoa.h>

static NSView * evas_view;
static NSWindow * main_window;


int
engine_gl_cocoa_args(int argc, char **argv)
{
   Evas_Engine_Info_GL_Cocoa *einfo;
   int i;
   int ok = 0;

   /*
   for (i = 1; i < argc; i++)
   {
      if ((!strcmp(argv[i], "-e")) && (i < (argc - 1)))
      {
         i++;
         if (!strcmp(argv[i], "gl-cocoa")) ok = 1;
      }
   }
   if (!ok) return 0;
   */

   evas_output_method_set(evas, evas_render_method_lookup("gl_cocoa"));
   einfo = (Evas_Engine_Info_GL_Cocoa *)evas_engine_info_get(evas);
   if (!einfo)
   {
      printf("Evas is a goat and can't run GL_COCOA ... or .... it's me the goat\n");
      return 0;
   }

   // Set up the Cocoa runtime
   [[NSAutoreleasePool alloc] init];
   [NSApplication sharedApplication];

   // Register ourselves as a full-fledged Cocoa app, instead of a NSUIElement.
   // This gives benefits like window focus and a dock icon!
   ProcessSerialNumber psn = { 0, kCurrentProcess };
   TransformProcessType (&psn, kProcessTransformToForegroundApplication);

   [NSApp finishLaunching];
   // Create our main window, and embed an EvasGLView in it
   main_window = [[NSWindow alloc] initWithContentRect:NSMakeRect(20,500,win_w,win_h) styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask | NSMiniaturizableWindowMask) backing:NSBackingStoreBuffered defer:NO screen:nil];
   [main_window makeKeyAndOrderFront:NSApp];
   [main_window setTitle:@"Expedite"];
   [main_window makeMainWindow];
   [main_window setAcceptsMouseMovedEvents:YES];
   [NSApp activateIgnoringOtherApps:YES];

   evas_output_size_set(evas, win_w, win_h);
   evas_output_viewport_set(evas, 0, 0, win_w, win_h);

   einfo->window = main_window;
	
   //einfo->info.context = [evas_view context];
   if (!evas_engine_info_set(evas, (Evas_Engine_Info *) einfo))
     {
	printf("Evas can not setup the informations of the GL_Cocoa Engine\n");
        exit(-1);
     }

   evas_view = (NSView*)einfo->view;
   [[main_window contentView] addSubview:evas_view];
   [evas_view display];

   evas_damage_rectangle_add(evas,0,0, win_w ,win_h);
   return 1;
}

void
engine_gl_cocoa_loop(void)
{
   NSDate *date = [NSDate dateWithTimeIntervalSinceNow:0.001];

   NSEvent *event = [NSApp nextEventMatchingMask:NSAnyEventMask
                                       untilDate:date
                                          inMode:NSDefaultRunLoopMode
                                         dequeue:YES];
   [date release];

   if (!event) return;

   if([event type] == NSMouseMoved || [event type] == NSLeftMouseDragged || [event type] == NSRightMouseDragged)
   {
      evas_event_feed_mouse_move(evas, [event locationInWindow].x, [event locationInWindow].y, 0, NULL);

      // Also notify on entering or leaving the window
      NSPoint mouseLoc = [[event window] convertBaseToScreen:[event locationInWindow]];

      if(NSPointInRect(mouseLoc, [[event window] frame]))
         evas_event_feed_mouse_in(evas, 0, NULL);
      else
         evas_event_feed_mouse_out(evas, 0, NULL);

      [NSApp sendEvent:event];
   }
   else if([event type] == NSLeftMouseDown)
   {
      evas_event_feed_mouse_move(evas, [event locationInWindow].x, [event locationInWindow].y, 0, NULL);
      evas_event_feed_mouse_down(evas, 1, EVAS_BUTTON_NONE, 0, NULL);

      [NSApp sendEvent:event];
   }
   else if([event type] == NSLeftMouseUp)
   {
      evas_event_feed_mouse_move(evas, [event locationInWindow].x, [event locationInWindow].y, 0, NULL);
      evas_event_feed_mouse_up(evas, 1, EVAS_BUTTON_NONE, 0, NULL);

      [NSApp sendEvent:event];
   }
   else if([event type] == NSRightMouseDown)
   {
      evas_event_feed_mouse_move(evas, [event locationInWindow].x, [event locationInWindow].y, 0, NULL);
      evas_event_feed_mouse_down(evas, 3, EVAS_BUTTON_NONE, 0, NULL);
      [NSApp sendEvent:event];
   }
   else if([event type] == NSRightMouseUp)
   {
      evas_event_feed_mouse_move(evas, [event locationInWindow].x, [event locationInWindow].y, 0, NULL);
      evas_event_feed_mouse_up(evas, 3, EVAS_BUTTON_NONE, 0, NULL);
      [NSApp sendEvent:event];
   }
   else if([event type] == NSKeyDown)
   {
      NSString * chars = [event charactersIgnoringModifiers];

      switch([chars characterAtIndex:0])
      {
         case NSLeftArrowFunctionKey:
            evas_event_feed_key_down(evas, "Left", "Left", NULL, NULL, 0, NULL);
            break;
         case NSRightArrowFunctionKey:
            evas_event_feed_key_down(evas, "Right", "Right", NULL, NULL, 0, NULL);
            break;
         case NSEnterCharacter:
         case NSCarriageReturnCharacter:
            evas_event_feed_key_down(evas, "Return", "Return", NULL, NULL, 0, NULL);
            break;
         case 's':
         case '\e':
            evas_event_feed_key_down(evas, "Escape", "Escape", NULL, NULL, 0, NULL);
            break;
         case 'q':
            evas_event_feed_key_down(evas, "q", "q", NULL, NULL, 0, NULL);
            break;
      }

      [chars release];
   }
   else if([event type] == NSKeyUp)
   {
      NSString * chars = [event charactersIgnoringModifiers];

      switch([chars characterAtIndex:0])
      {
         case NSLeftArrowFunctionKey:
            evas_event_feed_key_up(evas, "Left", "Left", NULL, NULL, 0, NULL);
            break;
         case NSRightArrowFunctionKey:
            evas_event_feed_key_up(evas, "Right", "Right", NULL, NULL, 0, NULL);
            break;
         case NSEnterCharacter:
         case NSCarriageReturnCharacter:
            evas_event_feed_key_up(evas, "Return", "Return", NULL, NULL, 0, NULL);
            break;
         case '\e':
            evas_event_feed_key_up(evas, "Escape", "Escape", NULL, NULL, 0, NULL);
            break;
         case 'q':
            if (evas_key_lock_is_set(evas_key_lock_get(evas), "Caps_Lock"))
              evas_event_feed_key_up(evas, "Q", "Q", NULL, NULL, 0, NULL);
            else
              evas_event_feed_key_up(evas, "q", "q", NULL, NULL, 0, NULL);
            break;
      }

      [chars release];
   }
   else if([event type] == NSFlagsChanged)
   {
      int flags = [event modifierFlags];

      // Turn special key flags on
      if(flags & NSShiftKeyMask)
         evas_key_modifier_on(evas, "Shift");
      else if(flags & NSControlKeyMask)
         evas_key_modifier_on(evas, "Control");
      else if(flags & NSAlternateKeyMask)
         evas_key_modifier_on(evas, "Alt");
      else if(flags & NSCommandKeyMask)
         evas_key_modifier_on(evas, "Super");
      else if(flags & NSAlphaShiftKeyMask)
      {
         if (evas_key_lock_is_set(evas_key_lock_get(evas), "Caps_Lock"))
           evas_key_lock_off(evas, "Caps_Lock");
         else
           evas_key_lock_on(evas, "Caps_Lock");
      }

      // Turn special key flags off
      if(!(flags & NSShiftKeyMask))
         evas_key_modifier_off(evas, "Shift");
      else if(!(flags & NSControlKeyMask))
         evas_key_modifier_off(evas, "Control");
      else if(!(flags & NSAlternateKeyMask))
         evas_key_modifier_off(evas, "Alt");
      else if(!(flags & NSCommandKeyMask))
         evas_key_modifier_off(evas, "Super");
   }
   else
   {
      [NSApp sendEvent:event];
   }

   [event release];
   [NSAutoreleasePool release];
}

void
engine_gl_cocoa_shutdown(void)
{
  /* If someone knows what to do here... */
}

#include "main.h"

#include <windowsx.h>
#include <Evas_Engine_Direct3D.h>


static HWND window;
static HINSTANCE instance;


static LRESULT CALLBACK
MainWndProc(HWND   hwnd,
            UINT   uMsg,
            WPARAM wParam,
            LPARAM lParam)
{
   switch (uMsg)
     {
     case WM_CREATE:
       return 0;
     case WM_DESTROY:
       PostQuitMessage(0);
       return 0;
     case WM_CLOSE:
       PostQuitMessage(0);
       return 0;
     case WM_PAINT: {
       PAINTSTRUCT ps;
       HDC hdc;

       hdc = BeginPaint (window, &ps);
       evas_damage_rectangle_add(evas,
                                 ps.rcPaint.left, ps.rcPaint.top,
                                 ps.rcPaint.right - ps.rcPaint.left,
                                 ps.rcPaint.bottom - ps.rcPaint.top);
       EndPaint(window, &ps);
       return 0;
     }
     case WM_SIZING:
       {
          PRECT rect = (PRECT)lParam;

          evas_output_viewport_set(evas, 0, 0,
                                   rect->right - rect->left,
                                   rect->bottom - rect->top);
          evas_output_size_set(evas,
                               rect->right - rect->left,
                               rect->bottom - rect->top);
          win_w = rect->right - rect->left;
          win_h = rect->bottom - rect->top;
          return 0;
       }
     case WM_RBUTTONDOWN:
       evas_event_feed_mouse_move(evas, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, NULL);
       evas_event_feed_mouse_down(evas, 3, EVAS_BUTTON_NONE, 0, NULL);
       return 0;
     case WM_LBUTTONDOWN:
       evas_event_feed_mouse_move(evas, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, NULL);
       evas_event_feed_mouse_down(evas, 1, EVAS_BUTTON_NONE, 0, NULL);
       return 0;
     case WM_LBUTTONUP:
       evas_event_feed_mouse_move(evas, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, NULL);
       evas_event_feed_mouse_up(evas, 1, EVAS_BUTTON_NONE, 0, NULL);
       return 0;
     case WM_RBUTTONUP:
       evas_event_feed_mouse_move(evas, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, NULL);
       evas_event_feed_mouse_up(evas, 3, EVAS_BUTTON_NONE, 0, NULL);
       return 0;
     case WM_MOUSEMOVE:
       if (!evas_pointer_inside_get(evas)) evas_event_feed_mouse_in(evas, 0, NULL);
       evas_event_feed_mouse_move(evas, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, NULL);
       return 0;
     case WM_MOUSELEAVE:
       evas_event_feed_mouse_out(evas, 0, NULL);
       return 0;
       /* FIXME : can't find an event when the mouse is entering */
     case WM_KEYDOWN:
     case WM_SYSKEYDOWN: {
        int key;

        key = LOWORD(wParam);

        if ((key == VK_SHIFT) ||
            (key == VK_LSHIFT) ||
            (key == VK_RSHIFT))
          evas_key_modifier_on(evas, "Shift");
        if ((key == VK_CONTROL) ||
            (key == VK_LCONTROL) ||
            (key == VK_RCONTROL))
          evas_key_modifier_on(evas, "Control");
        if ((key == VK_MENU) ||
            (key == VK_LMENU) ||
            (key == VK_RMENU))
          evas_key_modifier_on(evas, "Alt");
        if ((key == VK_LWIN) ||
            (key == VK_RWIN))
          evas_key_modifier_on(evas, "Super");

        if (key == VK_CAPITAL)
          {
             if (evas_key_lock_is_set(evas_key_lock_get(evas), "Caps_Lock"))
               evas_key_lock_off(evas, "Caps_Lock");
             else
               evas_key_lock_on(evas, "Caps_Lock");
          }
        if (key == VK_NUMLOCK)
          {
             if (evas_key_lock_is_set(evas_key_lock_get(evas), "Num_Lock"))
               evas_key_lock_off(evas, "Num_Lock");
             else
               evas_key_lock_on(evas, "Num_Lock");
          }
        if (key == VK_SCROLL)
          {
             if (evas_key_lock_is_set(evas_key_lock_get(evas), "Scroll_Lock"))
               evas_key_lock_off(evas, "Scroll_Lock");
             else
               evas_key_lock_on(evas, "Scroll_Lock");
          }
        if (key == VK_ESCAPE)
          evas_event_feed_key_down(evas, "Escape", "Escape", NULL, NULL, 0, NULL);
        if (key == VK_RETURN)
          evas_event_feed_key_down(evas, "Return", "Return", NULL, NULL, 0, NULL);
        if (key == VK_LEFT)
          evas_event_feed_key_down(evas, "Left", "Left", NULL, NULL, 0, NULL);
        if (key == VK_RIGHT)
          evas_event_feed_key_down(evas, "Right", "Right", NULL, NULL, 0, NULL);
        if (key == 81)
          evas_event_feed_key_down(evas, "Q", "Q", NULL, NULL, 0, NULL);
        if (key == 113)
          evas_event_feed_key_down(evas, "q", "q", NULL, NULL, 0, NULL);
        return 0;
     }
     case WM_KEYUP:
     case WM_SYSKEYUP: {
        int key;

        key = LOWORD(wParam);

        if ((key == VK_SHIFT) ||
            (key == VK_LSHIFT) ||
            (key == VK_RSHIFT))
          evas_key_modifier_off(evas, "Shift");
        if ((key == VK_CONTROL) ||
            (key == VK_LCONTROL) ||
            (key == VK_RCONTROL))
          evas_key_modifier_off(evas, "Control");
        if ((key == VK_MENU) ||
            (key == VK_LMENU) ||
            (key == VK_RMENU))
          evas_key_modifier_off(evas, "Alt");
        if ((key == VK_LWIN) ||
            (key == VK_RWIN))
          evas_key_modifier_off(evas, "Super");
        if (key == VK_ESCAPE)
          evas_event_feed_key_up(evas, "Escape", "Escape", NULL, NULL, 0, NULL);
        if (key == VK_RETURN)
          evas_event_feed_key_up(evas, "Return", "Return", NULL, NULL, 0, NULL);
        if (key == VK_LEFT)
          evas_event_feed_key_up(evas, "Left", "Left", NULL, NULL, 0, NULL);
        if (key == VK_RIGHT)
          evas_event_feed_key_up(evas, "Right", "Right", NULL, NULL, 0, NULL);
        if (key == 81)
          evas_event_feed_key_up(evas, "Q", "Q", NULL, NULL, 0, NULL);
        if (key == 113)
          evas_event_feed_key_up(evas, "q", "q", NULL, NULL, 0, NULL);
        return 0;
     }
     default:
       return DefWindowProc(hwnd, uMsg, wParam, lParam);
     }
}

Eina_Bool
engine_direct3d_args(const char *engine, int width, int height)
{
   WNDCLASS                   wc;
   RECT                       rect;
   HDC                        dc;
   MSG                        msg;
   Evas_Engine_Info_Direct3D *einfo;
   DWORD                      style;
   int                        depth;
   int                        i;

   instance = GetModuleHandle(NULL);
   if (!instance) return EINA_FALSE;

   wc.style = 0;
   wc.lpfnWndProc = MainWndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = instance;
   wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
   wc.hCursor = LoadCursor (NULL, IDC_ARROW);
   wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
   wc.lpszMenuName =  NULL;
   wc.lpszClassName = "Evas_Direct3D_Test";

   if(!RegisterClass(&wc))
     goto free_library;

   rect.left = 0;
   rect.top = 0;
   rect.right = width;
   rect.bottom = height;
   AdjustWindowRect (&rect, WS_OVERLAPPEDWINDOW | WS_SIZEBOX, FALSE);

   window = CreateWindowEx(0,
                           "Evas_Direct3D_Test",
                           "Evas_Direct3D_Test",
                           WS_OVERLAPPEDWINDOW | WS_SIZEBOX,
                           CW_USEDEFAULT, CW_USEDEFAULT,
                           rect.right - rect.left, rect.bottom - rect.top,
                           NULL, NULL, instance, NULL);
   if (!window)
     goto unregister_class;

   /* make the window non resizable */
   style = GetWindowLong(window, GWL_STYLE);
   style &= ~WS_THICKFRAME;
   if (!SetWindowLong(window, GWL_STYLE, style))
     goto unregister_class;

   dc = GetDC(NULL);
   if (!dc)
     goto destroy_window;

   depth = GetDeviceCaps(dc, BITSPIXEL);
   ReleaseDC(NULL, dc);

   evas_output_method_set(evas, evas_render_method_lookup("direct3d"));
   einfo = (Evas_Engine_Info_Direct3D *)evas_engine_info_get(evas);
   if (!einfo)
     {
        fprintf(stderr, "Evas does not support the Direct3D Engine\n");
        goto destroy_window;
     }

   einfo->info.window = window;
   einfo->info.depth = depth;
   einfo->info.rotation = 0;
   if (!evas_engine_info_set(evas, (Evas_Engine_Info *)einfo))
     {
	printf("Evas can not setup the informations of the Direct3D Engine\n");
        goto destroy_window;
     }

   /* the second parameter is ignored, as it's the first call of ShowWindow */
   ShowWindow(window, SW_SHOWDEFAULT);
   UpdateWindow(window);

   return EINA_TRUE;

 destroy_window:
   DestroyWindow(window);
 unregister_class:
   UnregisterClass("Evas_Direct3D_Test", instance);
 free_library:
   FreeLibrary(instance);

   return EINA_FALSE;
}

void
engine_direct3d_loop(void)
{
   MSG msg;
   int res;

 again:
   if (!PeekMessage (&msg, window, 0, 0, PM_NOREMOVE))
     return;

   res = GetMessage (&msg, NULL, 0, 0);
   TranslateMessage (&msg);
   DispatchMessage (&msg);

   goto again;
}

void
engine_direct3d_shutdown(void)
{
   DestroyWindow(window);
   UnregisterClass("Evas_Direct3D_Test", instance);
   FreeLibrary(instance);
}

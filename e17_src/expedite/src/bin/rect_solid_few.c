#undef FNAME
#undef NAME
#undef ICON

/* metadata */
#define FNAME rect_solid_few_start
#define NAME "Rect Solid Few"
#define ICON "rect.png"

#ifndef PROTO
# ifndef UI
#  include "main.h"

#undef OBNUM
#define OBNUM 3

/* standard var */
static int done = 0;
/* private data */
static Evas_Object *o_images[OBNUM];

/* setup */
static void _setup(void)
{
   int i;
   Evas_Object *o;
   srnd();
   for (i = 0; i < OBNUM; i++)
     {
	int r, g, b, a;

	o = evas_object_rectangle_add(evas);
	o_images[i] = o;
	a = 0xff;
	r = ((rnd()&0xff) * a) / 255;
	g = ((rnd()&0xff) * a) / 255;
	b = ((rnd()&0xff) * a) / 255;
	evas_object_color_set(o, r, g, b, a);
	evas_object_show(o);
     }
   done = 0;
}

/* cleanup */
static void _cleanup(void)
{
   int i;
   for (i = 0; i < OBNUM; i++) evas_object_del(o_images[i]);
}

/* loop - do things */
static void _loop(double t, int f)
{
   int i;
   Evas_Coord x, y, w, h, w0, h0;
   for (i = 0; i < OBNUM; i++)
     {
        w0 = 80;
	h0 = 80;
	w = 5 + ((1.0 + cos((double)(f + (i * 10)) / (7.4 * SLOW) )) * w0 * 2);
	h = 5 + ((1.0 + sin((double)(f + (i * 19)) / (12.6 * SLOW) )) * h0 * 2);
	x = (win_w / 2) - (w / 2);
	x += sin((double)(f + (i * 113)) / (36.7 * SLOW)) * (w0 / 2);
	y = (win_h / 2) - (h / 2);
	y += cos((double)(f + (i * 228)) / (43.8 * SLOW)) * (h0 / 2);
	evas_object_move(o_images[i], x, y);
	evas_object_resize(o_images[i], w, h);
     }
   FPS_STD(NAME);
}

/* prepend special key handlers if interactive (before STD) */
static void _key(char *key)
{
   KEY_STD;
}












/* template stuff - ignore */
# endif
#endif

#ifdef UI
_ui_menu_item_add(ICON, NAME, FNAME);
#endif

#ifdef PROTO
void FNAME(void);
#endif

#ifndef PROTO
# ifndef UI
void FNAME(void)
{
   ui_func_set(_key, _loop);
   _setup();
}
# endif
#endif
#undef FNAME
#undef NAME
#undef ICON

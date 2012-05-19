#undef FNAME
#undef NAME
#undef ICON

/* metadata */
#define FNAME image_mask_2
#define NAME "Image Mask 2"
#define ICON "blend.png"

#ifndef PROTO
# ifndef UI
#  include "main.h"

/* standard var */
static int done = 0;
/* private data */
static Evas_Object *o_images[OBNUM];

/* setup */
static void _setup(void)
{
   int i;
   Evas_Object *o;
   for (i = 0; i < OBNUM; i+= 2)
     {
	o = evas_object_image_add(evas);
	o_images[i] = o;
	evas_object_image_file_set(o, build_path("e-logo.png"), NULL);
	evas_object_image_fill_set(o, 0, 0, 120, 160);
	evas_object_resize(o, 120, 160);
	evas_object_show(o);

	o = evas_object_image_add(evas);
	o_images[i + 1] = o;
	evas_object_image_file_set(o, build_path("e-logo-2.png"), NULL);
	evas_object_image_fill_set(o, 0, 0, 120, 160);
	evas_object_resize(o, 120, 160);
	evas_object_show(o);
	evas_object_clip_set(o_images[i], o);
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
   Evas_Coord x, y, w, h;
   for (i = 0; i < OBNUM; i+= 2)
     {
	w = 120;
	h = 160;
	x = (win_w / 2) - (w / 2);
	x += sin((double)(f + (i * 13)) / (36.7 * SLOW)) * (w / 2);
	y = (win_h / 2) - (h / 2);
	y += cos((double)(f + (i * 28)) / (43.8 * SLOW)) * (h / 2);
	evas_object_move(o_images[i], x, y);
	evas_object_move(o_images[i + 1], x, y);
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

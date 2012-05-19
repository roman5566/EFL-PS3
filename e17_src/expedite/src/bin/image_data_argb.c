#undef FNAME
#undef NAME
#undef ICON

/* metadata */
#define FNAME image_data_argb_start
#define NAME "Image Data ARGB"
#define ICON "data.png"

#ifndef PROTO
# ifndef UI
#  include "main.h"

/* standard var */
static int done = 0;

/* private data */
static Evas_Object *o_images[1];

/* setup */
static void _setup(void)
{
   int i;
   Evas_Object *o;
   for (i = 0; i < 1; i++)
     {
	o = evas_object_image_add(evas);
	o_images[i] = o;
        evas_object_image_content_hint_set(o, EVAS_IMAGE_CONTENT_HINT_DYNAMIC);
	evas_object_image_colorspace_set(o, EVAS_COLORSPACE_ARGB8888);
	evas_object_image_size_set(o, 640, 480);
	evas_object_image_alpha_set(o, 0);
	evas_object_image_fill_set(o, 0, 0, 640, 480);
	evas_object_resize(o, 640, 480);
	evas_object_show(o);
     }
   done = 0;
}

/* cleanup */
static void _cleanup(void)
{
   int i;
   for (i = 0; i < 1; i++) evas_object_del(o_images[i]);
}

/* loop - do things */
static void _loop(double t, int f)
{
   int i, st;
   Evas_Coord x, y, w, h;
   for (i = 0; i < 1; i++)
     {
	unsigned int *data, *p;

        w = 640;
	h = 480;
	x = (win_w / 2) - (w / 2);
	y = (win_h / 2) - (h / 2);
	evas_object_move(o_images[i], x, y);
	evas_object_resize(o_images[i], w, h);
	evas_object_image_fill_set(o_images[i], 0, 0, w, h);
	data = evas_object_image_data_get(o_images[i], 1);
        st = evas_object_image_stride_get(o_images[i]) >> 2;
	p = data;
	for (y = 0; y < h; y++)
	  {
	     for (x = 0; x < w; x++)
	       {
		  *p = ((((x * y) + f) << 8) ^ (x - y - f)) | 0xff000000;
		  p++;
	       }
             p += (st - w);
	  }
	evas_object_image_data_set(o_images[i], data);
	evas_object_image_data_update_add(o_images[i], 0, 0, w, h);
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

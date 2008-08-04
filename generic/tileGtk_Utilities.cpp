/*
 *  tileGtk_Utilities.cpp
 * ----------------------
 *
 * This file is part of the Tile-Gtk package, a Tk/Tile based theme that uses
 * Gtk/GNOME for drawing.
 *
 * Copyright (C) 2004-2008 by:
 * Georgios Petasis, petasis@iit.demokritos.gr,
 * Software and Knowledge Engineering Laboratory,
 * Institute of Informatics and Telecommunications,
 * National Centre for Scientific Research (NCSR) "Demokritos",
 * Aghia Paraskevi, 153 10, Athens, Greece.
 */

#include "tileGtk_GtkHeaders.h"
#include "tileGtk_TkHeaders.h"
extern gboolean   TileGtk_GtkInitialisedFlag;
extern GtkWidget *TileGtk_GtkWindow;

int TileGtk_GtkInitialised(void) {
  return TileGtk_GtkInitialisedFlag;
}; /* TileGtk_GtkInitialised */

GtkWidget *TileGtk_GetGtkWindow(void) {
  return TileGtk_GtkWindow;
}; /* TileGtk_GetGtkWindow */

GtkStyle *TileGtk_GetGtkWindowStyle(GtkWidget *gtkWindow) {
  if (gtkWindow) {
    return gtkWindow->style;
  }
  return NULL;
}; /* TileGtk_GetGtkWindowStyle */

GtkStyle *TileGtk_GetGtkStyle(void) {
  return TileGtk_GetGtkWindowStyle(TileGtk_GetGtkWindow());
}; /* TileGtk_GetGtkStyle */

void TileGtk_InitialiseGtkWidget(TileGtk_WidgetCache* wc, GtkWidget* widget) {
  if (!wc || !widget) return;
  if (!wc->protoLayout) {
    wc->protoLayout = gtk_fixed_new();
    gtk_container_add((GtkContainer*)(wc->gtkWindow), wc->protoLayout);
  }
  if (!wc->protoLayout) return;
  gtk_container_add((GtkContainer*)(wc->protoLayout), widget);
  gtk_widget_realize(widget);
}; /* TileGtk_InitialiseGtkWidget */

#define TILEGTK_CHECK_WIDGET(widget, allocator_function) \
  if (!wc) return 0; \
  if (!wc->widget) { \
    wc->widget = allocator_function; \
    TileGtk_InitialiseGtkWidget(wc, wc->widget); \
    return wc->widget; \
  } \
  return wc->widget;

GtkWidget *TileGtk_GetButton(TileGtk_WidgetCache* wc) {
  TILEGTK_CHECK_WIDGET(gtkButton, gtk_button_new());
}; /* TileGtk_GetButton */

GtkWidget *TileGtk_GetCheckButton(TileGtk_WidgetCache* wc) {
  TILEGTK_CHECK_WIDGET(gtkCheckButton, gtk_check_button_new());
}; /* TileGtk_GetCheckButton */

GtkWidget *TileGtk_GetRadioButton(TileGtk_WidgetCache* wc) {
  return TileGtk_GetCheckButton(wc);
}; /* TileGtk_GetRadioButton */

GtkWidget *TileGtk_GetFrame(TileGtk_WidgetCache* wc) {
  TILEGTK_CHECK_WIDGET(gtkFrame, gtk_frame_new(NULL));
}; /* TileGtk_GetFrame */

GtkWidget *TileGtk_GetEntry(TileGtk_WidgetCache* wc) {
  TILEGTK_CHECK_WIDGET(gtkEntry, gtk_entry_new());
}; /* TileGtk_GetEntry */

GtkWidget *TileGtk_GetComboboxEntry(TileGtk_WidgetCache* wc) {
  TILEGTK_CHECK_WIDGET(gtkComboboxEntry, gtk_combo_box_entry_new());
}; /* TileGtk_GetComboboxEntry */

GtkWidget *TileGtk_GetComboboxEntryButton(TileGtk_WidgetCache* wc) {
  return TileGtk_GetComboboxEntry(wc);
}; /* TileGtk_GetComboboxEntryButton */

GtkWidget *TileGtk_GetHScrollBar(TileGtk_WidgetCache* wc) {
  GtkAdjustment *adjustment = (GtkAdjustment *)
             gtk_adjustment_new(0.0, 0.0, 1.0, 0, 0, 0);
  TILEGTK_CHECK_WIDGET(gtkHScrollBar, gtk_hscrollbar_new(adjustment));
}; /* TileGtk_GetHScrollBar */

GtkWidget *TileGtk_GetVScrollBar(TileGtk_WidgetCache* wc) {
  TILEGTK_CHECK_WIDGET(gtkVScrollBar, gtk_vscrollbar_new(NULL));
}; /* TileGtk_GetVScrollBar */

GtkWidget *TileGtk_GetScrollBar(TileGtk_WidgetCache* wc) {
  if (wc->orientation == TTK_ORIENT_HORIZONTAL) {
    return TileGtk_GetHScrollBar(wc);
  }
  return TileGtk_GetVScrollBar(wc);
}; /* TileGtk_GetScrollBar */

const char *TileGtk_GtkStateStr(GtkStateType gtkState) {
  switch ((GtkStateType) gtkState) {
    case GTK_STATE_NORMAL:      return "GTK_STATE_NORMAL";
    case GTK_STATE_ACTIVE:      return "GTK_STATE_ACTIVE";
    case GTK_STATE_PRELIGHT:    return "GTK_STATE_PRELIGHT";
    case GTK_STATE_SELECTED:    return "GTK_STATE_SELECTED";
    case GTK_STATE_INSENSITIVE: return "GTK_STATE_INSENSITIVE";
  }
  return "invalid!";
}; /* TileGtk_GtkStateStr */
const char *TileGtk_GtkShadowStr(GtkShadowType gtkShadow) {
  switch ((GtkShadowType) gtkShadow) {
    case GTK_SHADOW_NONE:       return "GTK_SHADOW_NONE";
    case GTK_SHADOW_IN:         return "GTK_SHADOW_IN";
    case GTK_SHADOW_OUT:        return "GTK_SHADOW_OUT";
    case GTK_SHADOW_ETCHED_IN:  return "GTK_SHADOW_ETCHED_IN";
    case GTK_SHADOW_ETCHED_OUT: return "GTK_SHADOW_ETCHED_OUT";
  }
  return "invalid!";
}; /* TileGtk_GtkShadowStr */

void TileGtk_StateInfo(int state, GtkStateType gtkState,
             GtkShadowType gtkShadow, Tk_Window tkwin, GtkWidget *widget)
{
    printf("Widget: %s\n  ", Tk_PathName(tkwin));
    if (state & TTK_STATE_ACTIVE) {
      printf("TTK_STATE_ACTIVE %d ", TTK_STATE_ACTIVE);
    } 
    if (state & TTK_STATE_DISABLED) {
      printf("TTK_STATE_DISABLED %d ", TTK_STATE_DISABLED);
    } 
    if (state & TTK_STATE_FOCUS) {
      printf("TTK_STATE_FOCUS %d ", TTK_STATE_FOCUS);
    } 
    if (state & TTK_STATE_PRESSED) {
      printf("TTK_STATE_PRESSED %d ", TTK_STATE_PRESSED);
    } 
    if (state & TTK_STATE_SELECTED) {
      printf("TTK_STATE_SELECTED %d ", TTK_STATE_SELECTED);
    } 
    if (state & TTK_STATE_BACKGROUND) {
      printf("TTK_STATE_BACKGROUND %d ", TTK_STATE_BACKGROUND);
    } 
    if (state & TTK_STATE_ALTERNATE) {
      printf("TTK_STATE_ALTERNATE %d ", TTK_STATE_ALTERNATE);
    } 
    if (state & TTK_STATE_INVALID) {
      printf("TTK_STATE_INVALID %d ", TTK_STATE_INVALID);
    } 
    if (state & TTK_STATE_READONLY) {
      printf("TTK_STATE_READONLY %d ", TTK_STATE_READONLY);
    } 
    if (state & TTK_STATE_USER1) {
      printf("TTK_STATE_USER1 %d ", TTK_STATE_USER1);
    } 
    if (state & TTK_STATE_USER2) {
      printf("TTK_STATE_USER2 %d ", TTK_STATE_USER2);
    } 
    if (state & TTK_STATE_USER3) {
      printf("TTK_STATE_USER3 %d ", TTK_STATE_USER3);
    } 
    if (state & TTK_STATE_USER4) {
      printf("TTK_STATE_USER4 %d ", TTK_STATE_USER4);
    } 
    if (state & TTK_STATE_USER5) {
      printf("TTK_STATE_USER5 %d ", TTK_STATE_USER5);
    } 
    if (state & TTK_STATE_USER6) {
      printf("TTK_STATE_USER6 %d ", TTK_STATE_USER6);
    } 
    if (state & TTK_STATE_USER7) {
      printf("TTK_STATE_USER7 %d ", TTK_STATE_USER7);
    }
    printf(" state=%d\n", state);
    printf("  GTK state: %s, shadow: %s",
      TileGtk_GtkStateStr(gtkState), TileGtk_GtkShadowStr(gtkShadow));
    if (widget) {
      printf(", focus: %d, default: %d", GTK_WIDGET_HAS_FOCUS(widget),
                                         GTK_WIDGET_HAS_DEFAULT(widget));
    }
    printf("\n");
    fflush(0);
}; /* TileGtk_StateInfo */

void TileGtk_CopyGtkPixmapOnToDrawable(GdkPixmap *pixmap, Drawable d,
            Tk_Window tkwin, int x, int y, int w, int h, int x1, int x2)
{
#ifdef __WIN32__
    gdk_win32_drawable_get_handle(pixmap);
#else
    GdkPixbuf *imgb;
    XGCValues gcValues;
    gcValues.graphics_exposures = False;
    GC gc = Tk_GetGC(tkwin, GCForeground | GCBackground | GCGraphicsExposures,
                     &gcValues);
    imgb = gdk_pixbuf_new(GDK_COLORSPACE_RGB, true, 8, w, h);
    if (!imgb) {
      Tk_FreeGC(Tk_Display(tkwin), gc);
      return;
    }
    imgb = gdk_pixbuf_get_from_drawable(imgb, pixmap, NULL, 0, 0, 0, 0, w, h);
    gdk_pixbuf_xlib_render_to_drawable(imgb, d, gc,
         x, y, x1, x2, w, h, XLIB_RGB_DITHER_MAX, 0, 0);
    gdk_pixbuf_unref(imgb);
    Tk_FreeGC(Tk_Display(tkwin), gc);
#endif
}; /* TileGtk_CopyGtkPixmapOnToDrawable */

void TileGtk_StoreStyleNameLowers(TileGtk_WidgetCache *wc) {
}; /* TileGtk_StoreStyleName */

bool TileGtk_ThemeIs(TileGtk_WidgetCache *wc, const char* name) {
  return false;
}; /* TileGtk_ThemeIs */

/*
 * TileGtk_StateTableLookup --
 * Look up an index from a statically allocated state table.
 */
unsigned int TileGtk_StateTableLookup(Ttk_StateTable *map, unsigned int state) {
    return Ttk_StateTableLookup(map, state);
    int value = 0;
    while (map->onBits || map->offBits) {
      if (state & map->onBits) value |= map->index;
      ++map;
    }
    return value;
}; /* TileGtk_StateTableLookup */

/*
 * GTK_STATE_NORMAL:      State during normal operation.
 * GTK_STATE_ACTIVE:      State of a currently active widget, such as a
 *                        depressed button.
 * GTK_STATE_PRELIGHT:    State indicating that the mouse pointer is over the
 *                        widget and the widget will respond to mouse clicks.
 * GTK_STATE_SELECTED:    State of a selected item, such the selected row in
 *                        a list.
 * GTK_STATE_INSENSITIVE: State indicating that the widget is unresponsive
 *                        to user actions.
 *
 * GTK_SHADOW_NONE:       No outline.
 * GTK_SHADOW_IN:         The outline is bevelled inwards.
 * GTK_SHADOW_OUT:        The outline is bevelled outwards like a button.
 * GTK_SHADOW_ETCHED_IN:  The outline has a sunken 3d appearance.
 * GTK_SHADOW_ETCHED_OUT: The outline has a raised 3d appearance
 *
 * TTK_STATE_ACTIVE
 * TTK_STATE_DISABLED
 * TTK_STATE_FOCUS
 * TTK_STATE_PRESSED
 * TTK_STATE_SELECTED
 * TTK_STATE_BACKGROUND
 * TTK_STATE_ALTERNATE
 * TTK_STATE_INVALID
 * TTK_STATE_READONLY
 */
unsigned int TileGtk_StateShadowTableLookup(TileGtk_StateTable *map,
             unsigned int state, GtkStateType& gtkState,
             GtkShadowType& gtkShadow, unsigned int section) {
  static TileGtk_StateTable default_map[] = {
    /* Section for: Buttons */
    /* Section common to all widgets */
    {GTK_STATE_ACTIVE,      GTK_SHADOW_NONE, 0,
     TTK_STATE_ACTIVE,      0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_INSENSITIVE, GTK_SHADOW_NONE, 0,
     TTK_STATE_DISABLED,    0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_PRELIGHT,    GTK_SHADOW_NONE, 0,
     TTK_STATE_FOCUS,       0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_SELECTED,    GTK_SHADOW_NONE, 0,
     TTK_STATE_PRESSED,     0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_SELECTED,    GTK_SHADOW_NONE, 0,
     TTK_STATE_SELECTED,    0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_NORMAL,      GTK_SHADOW_NONE, 0,
     TTK_STATE_BACKGROUND,  0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_NORMAL,      GTK_SHADOW_NONE, 0,
     TTK_STATE_ALTERNATE,   0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_INSENSITIVE, GTK_SHADOW_NONE, 0,
     TTK_STATE_INVALID,     0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_INSENSITIVE, GTK_SHADOW_NONE, 0,
     TTK_STATE_READONLY,    0,               TILEGTK_SECTION_ALL},
    {GTK_STATE_NORMAL,      GTK_SHADOW_NONE, 0,
     0,                     0,               TILEGTK_SECTION_ALL}
  };
  unsigned int value = 0;
  gtkState  = GTK_STATE_NORMAL; 
  gtkShadow = GTK_SHADOW_NONE;
  if (!map) {
    map = default_map;
    /* Instead of writting huge tables, do some checks here... */
    if (section & TILEGTK_SECTION_STEPPERS) {
      gtkShadow = GTK_SHADOW_OUT;
      if (state & TTK_STATE_DISABLED) {
        gtkState = GTK_STATE_INSENSITIVE;
      } else if (state & TTK_STATE_PRESSED) {
        gtkState = GTK_STATE_ACTIVE;
        gtkShadow = GTK_SHADOW_IN;
      } else if (state & TTK_STATE_ACTIVE) {
        gtkState = GTK_STATE_PRELIGHT;
      }
      map = NULL; /* Do not search the table */
    } else if (section & TILEGTK_SECTION_BUTTONS ||
               section & TILEGTK_SECTION_ENTRY ||
               section & TILEGTK_SECTION_SCROLLBAR) {
      /* Whether the button is drawn pressed or not, is defined by shadow. */
      if (state & TTK_STATE_PRESSED || state & TTK_STATE_SELECTED) {
        gtkShadow = GTK_SHADOW_IN;
      } else {
        gtkShadow = GTK_SHADOW_OUT;
        if (state & TTK_STATE_DISABLED || state & TTK_STATE_READONLY)
                                           gtkState  = GTK_STATE_INSENSITIVE;
        else if (state & TTK_STATE_ACTIVE) gtkState  = GTK_STATE_PRELIGHT;
        else if (state & TTK_STATE_FOCUS)  gtkState  = GTK_STATE_ACTIVE;
      }
      map = NULL; /* Do not search the table */
    } else if (section & TILEGTK_SECTION_TROUGH) {
      if (state & TTK_STATE_PRESSED) {
        gtkState = GTK_STATE_ACTIVE;
      } else {
        gtkState = GTK_STATE_INSENSITIVE;
      }
      gtkShadow = GTK_SHADOW_IN;
      map = NULL; /* Do not search the table */
    }
  }
  if (map) {
    while ( (state & map->onBits)  != map->onBits  ||
           (~state & map->offBits) != map->offBits ||
           !(section & map->section)) {
      ++map; ++value;
    }
    gtkState  = map->state;
    gtkShadow = map->shadow;
  }
  return (map)? map->value : value;
}; /* TileGtk_StateShadowTableLookup */

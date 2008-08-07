/*
 *  tileGtk_CheckButton.cpp
 * ------------------------
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

#include "tileGtk_Utilities.h"
#include "tileGtk_TkHeaders.h"
#include "tileGtk_WidgetDefaults.h"

#if 0
/*
 * Map between Tk/Tile & Gtk/GNOME state flags.
 */
static Ttk_StateTable checkbutton_statemap[] =
{
    {GTK_STATE_INSENSITIVE,   TTK_STATE_DISABLED,  0},
    {GTK_STATE_SELECTED,      TTK_STATE_PRESSED,   0},
    {GTK_STATE_ACTIVE,        TTK_STATE_ACTIVE,    0},
    {GTK_STATE_PRELIGHT,      TTK_STATE_FOCUS,     0},
    {GTK_STATE_NORMAL,        TTK_STATE_ALTERNATE, 0},
    {GTK_STATE_NORMAL,        0,                   0}
};

static Ttk_StateTable checkbutton_shadowmap[] =
{
    {GTK_SHADOW_OUT,          TTK_STATE_DISABLED,  0},
    {GTK_SHADOW_IN,           TTK_STATE_PRESSED,   0},
    {GTK_SHADOW_OUT,          TTK_STATE_ACTIVE,    0},
    {GTK_SHADOW_OUT,          TTK_STATE_FOCUS,     0},
    {GTK_SHADOW_NONE,         TTK_STATE_ALTERNATE, 0},
    {GTK_SHADOW_OUT,          0,                   0}
};
#endif

typedef struct {
} CheckButtonIndicatorElement;


static Ttk_ElementOptionSpec CheckButtonIndicatorElementOptions[] = {
    {NULL}
};

static void CheckButtonIndicatorElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    TILEGTK_WIDGET_CACHE_DEFINITION;
    gint size;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    GtkWidget *widget = TileGtk_GetCheckButton(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TileGtk_gtk_widget_style_get(widget, "indicator-size", &size, NULL);
    *widthPtr = *heightPtr = size;
    *paddingPtr = Ttk_MakePadding(0, 0, CheckButtonHorizontalPadding, 0);
}

static void CheckButtonIndicatorElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    TILEGTK_GTK_DRAWABLE_DEFINITIONS;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    TILEGTK_SETUP_GTK_DRAWABLE;
    GtkWidget *widget = TileGtk_GetCheckButton(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TILEGTK_SETUP_WIDGET_SIZE(b.width, b.height);
    TILEGTK_WIDGET_SET_FOCUS(widget);
    TILEGTK_DEFAULT_BACKGROUND;
    TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    // TileGtk_StateInfo(state, gtkState, gtkShadow, tkwin, widget);
    TileGtk_gtk_paint_check(style, pixmap, gtkState, gtkShadow, NULL, widget,
                  "checkbutton", 0, 0, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    TILEGTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec CheckButtonIndicatorElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(CheckButtonIndicatorElement),
    CheckButtonIndicatorElementOptions,
    CheckButtonIndicatorElementGeometry,
    CheckButtonIndicatorElementDraw
};

typedef struct {
} CheckButtonBorderElement;


static Ttk_ElementOptionSpec CheckButtonBorderElementOptions[] = {
    {NULL}
};

static void CheckButtonBorderElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    TILEGTK_WIDGET_CACHE_DEFINITION;
    gint hpadding = 0;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    GtkWidget *widget = TileGtk_GetCheckButton(wc);
    TileGtk_gtk_widget_style_get(widget, "indicator-spacing", &hpadding, NULL);
    *paddingPtr = Ttk_UniformPadding(hpadding);
}

static void CheckButtonBorderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    TILEGTK_GTK_DRAWABLE_DEFINITIONS;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    TILEGTK_SETUP_GTK_DRAWABLE;
    GtkWidget *widget = TileGtk_GetCheckButton(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TILEGTK_DEFAULT_BACKGROUND;
    // TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
    //         TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    // TILEGTK_SETUP_WIDGET_SIZE(b.width, b.height);
    // TILEGTK_WIDGET_SET_FOCUS(widget);
    // TileGtk_gtk_paint_flat_box(style, pixmap, gtkState, gtkShadow, NULL, widget,
    //               "checkbutton", 0, 0, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    TILEGTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec CheckButtonBorderElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(CheckButtonBorderElement),
    CheckButtonBorderElementOptions,
    CheckButtonBorderElementGeometry,
    CheckButtonBorderElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(CheckbuttonLayout)
     TTK_GROUP("Checkbutton.border", TTK_FILL_BOTH,
	 TTK_GROUP("Checkbutton.padding", TTK_FILL_BOTH,
	     TTK_NODE("Checkbutton.indicator", TTK_PACK_LEFT)
	     TTK_GROUP("Checkbutton.focus", TTK_PACK_LEFT | TTK_STICK_W,
		 TTK_NODE("Checkbutton.label", TTK_FILL_BOTH))))
TTK_END_LAYOUT

int TileGtk_Init_CheckButton(Tcl_Interp *interp,
                       TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Checkbutton.border",
            &CheckButtonBorderElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Checkbutton.indicator",
            &CheckButtonIndicatorElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TCheckbutton", CheckbuttonLayout);
    
    return TCL_OK;
}; /* TileGtk_Init_CheckButton */

/*
 *  tileGtk_Menubutton.cpp
 * -------------------
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
 * Pushbuttons (Tk: "Menubutton")
 */
static Ttk_StateTable menubutton_statemap[] =
{
};
#endif

typedef struct {
} MenubuttonIndicatorElement;

static Ttk_ElementOptionSpec MenubuttonIndicatorElementOptions[] = {
    {NULL}
};

static void MenubuttonIndicatorElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    TILEGTK_WIDGET_CACHE_DEFINITION;
    gint size = 15;
    GtkWidget *widget = TileGtk_GetComboboxEntry(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TileGtk_gtk_widget_style_get(widget, "arrow-size", &size, NULL);

    *widthPtr = *heightPtr = size;
    *paddingPtr = Ttk_UniformPadding(3);
}

static void MenubuttonIndicatorElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    TILEGTK_GTK_DRAWABLE_DEFINITIONS;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    TILEGTK_SETUP_GTK_DRAWABLE;
    GtkWidget *widget = TileGtk_GetCombobox(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    TILEGTK_WIDGET_SET_FOCUS(widget);
    TileGtk_gtk_paint_flat_box(style, pixmap, gtkState, gtkShadow, NULL, widget,
            "button", 0, 0, b.width, b.height);
    TileGtk_gtk_paint_arrow(style, pixmap, gtkState, gtkShadow, NULL, widget,
            "combo", GTK_ARROW_DOWN, FALSE, 0, 0, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    TILEGTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec MenubuttonIndicatorElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonIndicatorElement),
    MenubuttonIndicatorElementOptions,
    MenubuttonIndicatorElementGeometry,
    MenubuttonIndicatorElementDraw
};

typedef struct {
} MenubuttonElement;

static Ttk_ElementOptionSpec MenubuttonElementOptions[] = {
    {NULL}
};

static void MenubuttonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    TILEGTK_WIDGET_CACHE_DEFINITION;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    GtkWidget *widget = TileGtk_GetCombobox(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TILEGTK_GET_WIDGET_SIZE(*widthPtr, *heightPtr);
    *paddingPtr = Ttk_UniformPadding(PushButtonUniformPadding);
}

static void MenubuttonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    TILEGTK_GTK_DRAWABLE_DEFINITIONS;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    TILEGTK_SETUP_GTK_DRAWABLE;
    GtkWidget *widget = TileGtk_GetCombobox(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    TILEGTK_WIDGET_SET_FOCUS(widget);
    TileGtk_gtk_paint_box(style, pixmap, gtkState, gtkShadow, NULL, widget,
                  "button", 0, 0, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                  0, 0, b.width, b.height, b.x, b.y);
    TILEGTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec MenubuttonElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonElement),
    MenubuttonElementOptions,
    MenubuttonElementGeometry,
    MenubuttonElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(MenubuttonLayout)
    TTK_GROUP("Menubutton.border", TTK_FILL_BOTH,
	TTK_GROUP("Menubutton.focus", TTK_FILL_BOTH,
	    TTK_NODE("Menubutton.indicator", TTK_PACK_RIGHT)
	    TTK_GROUP("Menubutton.padding", TTK_PACK_LEFT|TTK_EXPAND|TTK_FILL_X,
	        TTK_NODE("Menubutton.label", TTK_PACK_LEFT))))
TTK_END_LAYOUT

int TileGtk_Init_Menubutton(Tcl_Interp *interp,
                       TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Menubutton.indicator",
            &MenubuttonIndicatorElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Menubutton.border",
            &MenubuttonElementSpec, (void *) wc[0]);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TMenubutton", MenubuttonLayout);
    return TCL_OK;
}; /* TileGtk_Init_Menubutton */

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
} MenubuttonDropdownElement;

static Ttk_ElementOptionSpec MenubuttonDropdownElementOptions[] = {
    {NULL}
};

static void MenubuttonDropdownElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    *paddingPtr = Ttk_UniformPadding(0);
}

static void MenubuttonDropdownElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
}

static Ttk_ElementSpec MenubuttonDropdownElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(MenubuttonDropdownElement),
    MenubuttonDropdownElementOptions,
    MenubuttonDropdownElementGeometry,
    MenubuttonDropdownElementDraw
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
    GtkWidget *widget = TileGtk_GetButton(wc);
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
    GtkWidget *widget = TileGtk_GetButton(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    // TILEGTK_SETUP_STATE_SHADOW(pushbutton_statemap, pushbutton_shadowmap);
    TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    TILEGTK_SETUP_WIDGET_SIZE(b.width, b.height);
    TILEGTK_WIDGET_SET_FOCUS(widget);
    TILEGTK_DEFAULT_BACKGROUND;
    // TileGtk_StateInfo(state, gtkState, gtkShadow, tkwin, widget);
    gtk_paint_box(style, pixmap, gtkState, gtkShadow, NULL, widget,
                  GTK_WIDGET_HAS_DEFAULT(widget) ? "buttondefault" : "button",
                  0, 0, b.width, b.height);
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
    TTK_GROUP("Menubutton.button", TTK_FILL_BOTH,
	    TTK_GROUP("Menubutton.padding", TTK_FILL_BOTH,
                TTK_NODE("Menubutton.dropdown", TTK_PACK_RIGHT|TTK_FILL_Y)
		TTK_NODE("Menubutton.label", TTK_FILL_BOTH)))
TTK_END_LAYOUT

int TileGtk_Init_Menubutton(Tcl_Interp *interp,
                       TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Menubutton.dropdown",
            &MenubuttonDropdownElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Menubutton.button",
            &MenubuttonElementSpec, (void *) wc[0]);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TMenubutton", MenubuttonLayout);
    return TCL_OK;
}; /* TileGtk_Init_Menubutton */

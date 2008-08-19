/*
 *  tileGtk_ToolButton.cpp
 * -----------------------
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
 * Toolbuttons (Tk: "Button")
 */
static Ttk_StateTable toolbutton_statemap[] =
{
};
#endif

typedef struct {
    Tcl_Obj        *defaultStateObj;
} ToolButtonElement;

static Ttk_ElementOptionSpec ToolButtonElementOptions[] = {
    { (char *) "-default", TK_OPTION_ANY, 
        Tk_Offset(ToolButtonElement, defaultStateObj), (char *) "normal" },
    {NULL}
};

static void ToolButtonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    TILEGTK_WIDGET_CACHE_DEFINITION;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    GtkWidget *widget = TileGtk_GetToolButton(wc);
    ToolButtonElement *bd = (ToolButtonElement *) elementRecord;
    TILEGTK_ENSURE_WIDGET_OK;
    TILEGTK_WIDGET_SETUP_DEFAULT(bd->defaultStateObj);
    TILEGTK_GET_WIDGET_SIZE(*widthPtr, *heightPtr);
    if (defaultState != TTK_BUTTON_DEFAULT_DISABLED) {
      *paddingPtr = Ttk_UniformPadding(PushButtonUniformPaddingDefaulted);
    } else {
      *paddingPtr = Ttk_UniformPadding(PushButtonUniformPadding);
    }
}

static void ToolButtonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    TILEGTK_GTK_DRAWABLE_DEFINITIONS;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    /* TILEGTK_SETUP_GTK_DRAWABLE; */
    GtkWidget *widget = TileGtk_GetToolButton(wc);
    ToolButtonElement *bd = (ToolButtonElement *) elementRecord;
    TILEGTK_ENSURE_WIDGET_OK;
    TILEGTK_STYLE_FROM_WIDGET;
    TILEGTK_DRAWABLE_FROM_WIDGET;
    // TILEGTK_SETUP_STATE_SHADOW(pushbutton_statemap, pushbutton_shadowmap);
    TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    // TILEGTK_SETUP_WIDGET_SIZE(b.width, b.height);
    TILEGTK_WIDGET_SET_FOCUS(widget);
    TILEGTK_WIDGET_SET_DEFAULT(widget, bd->defaultStateObj);
    TILEGTK_DEFAULT_BACKGROUND;
    // TileGtk_StateInfo(state, gtkState, gtkShadow, tkwin, widget);
    TileGtk_gtk_paint_box(style, gdkDrawable, gtkState, gtkShadow, NULL, widget,
                  has_default ? "buttondefault" : "button",
                  0, 0, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(gdkDrawable, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    TILEGTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec ToolButtonElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ToolButtonElement),
    ToolButtonElementOptions,
    ToolButtonElementGeometry,
    ToolButtonElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(ToolbuttonLayout)
    TTK_GROUP("Toolbutton.border", TTK_FILL_BOTH,
	    TTK_GROUP("Toolbutton.padding", TTK_FILL_BOTH,
		TTK_NODE("Toolbutton.label", TTK_FILL_BOTH)))
TTK_END_LAYOUT

int TileGtk_Init_ToolButton(Tcl_Interp *interp,
                       TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Toolbutton.border",
            &ToolButtonElementSpec, (void *) wc[0]);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TToolbutton", ToolbuttonLayout);
    return TCL_OK;
}; /* TileGtk_Init_ToolButton */

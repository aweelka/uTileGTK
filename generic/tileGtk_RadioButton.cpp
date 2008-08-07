/*
 *  tileGtk_RadioButton.cpp
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
static Ttk_StateTable radiobutton_statemap[] =
{
};
#endif

typedef struct {
} RadioButtonIndicatorElement;


static Ttk_ElementOptionSpec RadioButtonIndicatorElementOptions[] = {
    {NULL}
};

static void RadioButtonIndicatorElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    TILEGTK_WIDGET_CACHE_DEFINITION;
    gint size;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    GtkWidget *widget = TileGtk_GetRadioButton(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TileGtk_gtk_widget_style_get(widget, "indicator-size", &size, NULL);
    *widthPtr = *heightPtr = size;
    *paddingPtr = Ttk_MakePadding(0, 0, RadioButtonHorizontalPadding, 0);
}

static void RadioButtonIndicatorElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    TILEGTK_GTK_DRAWABLE_DEFINITIONS;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    TILEGTK_SETUP_GTK_DRAWABLE;
    GtkWidget *widget = TileGtk_GetRadioButton(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TILEGTK_SETUP_WIDGET_SIZE(b.width, b.height);
    TILEGTK_WIDGET_SET_FOCUS(widget);
    TILEGTK_DEFAULT_BACKGROUND;
    TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    // TileGtk_StateInfo(state, gtkState, gtkShadow, tkwin, widget);
    TileGtk_gtk_paint_option(style, pixmap, gtkState, gtkShadow, NULL, widget,
                     "radiobutton", 0, 0, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    TILEGTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec RadioButtonIndicatorElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(RadioButtonIndicatorElement),
    RadioButtonIndicatorElementOptions,
    RadioButtonIndicatorElementGeometry,
    RadioButtonIndicatorElementDraw
};

typedef struct {
} RadioButtonBorderElement;


static Ttk_ElementOptionSpec RadioButtonBorderElementOptions[] = {
    {NULL}
};

static void RadioButtonBorderElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    TILEGTK_WIDGET_CACHE_DEFINITION;
    gint hpadding = 0;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    GtkWidget *widget = TileGtk_GetRadioButton(wc);
    TileGtk_gtk_widget_style_get(widget, "indicator-spacing", &hpadding, NULL);
    *paddingPtr = Ttk_UniformPadding(hpadding);
}

static void RadioButtonBorderElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    TILEGTK_GTK_DRAWABLE_DEFINITIONS;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    TILEGTK_SETUP_GTK_DRAWABLE;
    GtkWidget *widget = TileGtk_GetRadioButton(wc);
    TILEGTK_ENSURE_WIDGET_OK;
    TILEGTK_DEFAULT_BACKGROUND;
    // TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
    //         TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    // TILEGTK_SETUP_WIDGET_SIZE(b.width, b.height);
    // TILEGTK_WIDGET_SET_FOCUS(widget);
    // TileGtk_gtk_paint_flat_box(style, pixmap, gtkState, gtkShadow, NULL, widget,
    //               "radiobutton", 0, 0, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    TILEGTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec RadioButtonBorderElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(RadioButtonBorderElement),
    RadioButtonBorderElementOptions,
    RadioButtonBorderElementGeometry,
    RadioButtonBorderElementDraw
};


/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(RadiobuttonLayout)
     TTK_GROUP("Radiobutton.border", TTK_FILL_BOTH,
         TTK_GROUP("Radiobutton.padding", TTK_FILL_BOTH,
             TTK_NODE("Radiobutton.indicator", TTK_PACK_LEFT)
             TTK_GROUP("Radiobutton.focus", TTK_PACK_LEFT,
                 TTK_NODE("Radiobutton.label", TTK_FILL_BOTH))))
TTK_END_LAYOUT

int TileGtk_Init_RadioButton(Tcl_Interp *interp,
                       TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Radiobutton.border",
            &RadioButtonBorderElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Radiobutton.indicator",
            &RadioButtonIndicatorElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TRadiobutton", RadiobuttonLayout);
    
    return TCL_OK;
}; /* TileGtk_Init_RadioButton */

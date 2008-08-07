/*
 *  tileGtk_Button.cpp
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

/*
 * Pushbuttons (Tk: "Button")
 */
#if 0
static Ttk_StateTable pushbutton_statemap[] =
{
    {GTK_STATE_INSENSITIVE,   TTK_STATE_DISABLED,  0},
    {GTK_STATE_SELECTED,      TTK_STATE_PRESSED,   0},
    {GTK_STATE_ACTIVE,        TTK_STATE_ACTIVE,    0},
    {GTK_STATE_PRELIGHT,      TTK_STATE_FOCUS,     0},
    {GTK_STATE_NORMAL,        TTK_STATE_ALTERNATE, 0},
    {GTK_STATE_NORMAL,        0,                   0}
};

static Ttk_StateTable pushbutton_shadowmap[] =
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
    Tcl_Obj        *defaultStateObj;
} ButtonElement;

static Ttk_ElementOptionSpec ButtonElementOptions[] = {
    { (char *) "-default", TK_OPTION_ANY, 
        Tk_Offset(ButtonElement, defaultStateObj), (char *) "normal" },
    {NULL}
};

static void ButtonElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    TILEGTK_WIDGET_CACHE_DEFINITION;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    GtkWidget *widget = TileGtk_GetButton(wc);
    ButtonElement *bd = (ButtonElement *) elementRecord;
    TILEGTK_ENSURE_WIDGET_OK;
    TILEGTK_WIDGET_SETUP_DEFAULT(bd->defaultStateObj);
    // GtkBorder border = {0, 0, 0, 0};
    // TileGtk_gtk_widget_style_get(widget, "inner-border", &border, NULL);
    // printf("inner-border left: %d, right: %d, top: %d, bottom: %d\n",
    //   border.left, border.right, border.top, border.bottom);
    // TileGtk_gtk_widget_style_get(widget, "default-border", &border, NULL);
    // printf("default-border left: %d, right: %d, top: %d, bottom: %d\n",
    //   border.left, border.right, border.top, border.bottom);
    // TILEGTK_GET_WIDGET_SIZE(*widthPtr, *heightPtr);
    if (defaultState != TTK_BUTTON_DEFAULT_DISABLED) {
      *paddingPtr = Ttk_UniformPadding(PushButtonUniformPaddingDefaulted);
    } else {
      *paddingPtr = Ttk_UniformPadding(PushButtonUniformPadding);
    }
}

static void ButtonElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned int state)
{
    TILEGTK_GTK_DRAWABLE_DEFINITIONS;
    TILEGTK_ENSURE_GTK_STYLE_ENGINE_ACTIVE;
    TILEGTK_SETUP_GTK_DRAWABLE;
    GtkWidget *widget = TileGtk_GetButton(wc);
    ButtonElement *bd = (ButtonElement *) elementRecord;
    TILEGTK_ENSURE_WIDGET_OK;
    // TILEGTK_SETUP_STATE_SHADOW(pushbutton_statemap, pushbutton_shadowmap);
    TileGtk_StateShadowTableLookup(NULL, state, gtkState, gtkShadow,
            TILEGTK_SECTION_BUTTONS|TILEGTK_SECTION_ALL);
    // TILEGTK_SETUP_WIDGET_SIZE(b.width, b.height);
    TILEGTK_WIDGET_SET_FOCUS(widget);
    TILEGTK_WIDGET_SET_DEFAULT(widget, bd->defaultStateObj);
    TILEGTK_DEFAULT_BACKGROUND;
    // TileGtk_StateInfo(state, gtkState, gtkShadow, tkwin, widget);
    TileGtk_gtk_paint_box(style, pixmap, gtkState, gtkShadow, NULL, widget,
                  GTK_WIDGET_HAS_DEFAULT(widget) ? "buttondefault" : "button",
                  0, 0, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                   0, 0, b.width, b.height, b.x, b.y);
    TILEGTK_CLEANUP_GTK_DRAWABLE;
}

static Ttk_ElementSpec ButtonElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ButtonElement),
    ButtonElementOptions,
    ButtonElementGeometry,
    ButtonElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(ButtonLayout)
    TTK_GROUP("Button.border", TTK_FILL_BOTH,
        TTK_GROUP("Button.focus", TTK_FILL_BOTH, 
            TTK_GROUP("Button.padding", TTK_FILL_BOTH,
                TTK_NODE("Button.label", TTK_FILL_BOTH))))
TTK_END_LAYOUT

int TileGtk_Init_Button(Tcl_Interp *interp,
                        TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Button.border",
            &ButtonElementSpec, (void *) wc[0]);

    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TButton", ButtonLayout);
    return TCL_OK;
}; /* TileGtk_Init_Button */

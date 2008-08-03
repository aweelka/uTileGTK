/*
 *  tileGtk_Paned.cpp
 * ---------------------
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
 * Map between Tk/Tile & Gtk/GNOME state flags.
 */
static Ttk_StateTable paned_statemap[] =
{
#ifdef TILEGTK_GTK_VERSION_3
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled|QStyle::Style_Down,      TTK_STATE_PRESSED, 0},
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS, 0},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TK_STATE_ACTIVE, 0},
    {QStyle::Style_Enabled,                         0, 0}
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    {QStyle::State_None,                            TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled|QStyle::State_Sunken,    TTK_STATE_PRESSED, 0},
    {QStyle::State_Enabled|QStyle::State_HasFocus,  TTK_STATE_FOCUS, 0},
    {QStyle::State_Enabled|QStyle::State_MouseOver, TK_STATE_ACTIVE, 0},
    {QStyle::State_Enabled,                         0, 0}
#endif /* TILEGTK_GTK_VERSION_4 */
};

typedef struct {
} PanedSashGripElement;

static Ttk_ElementOptionSpec PanedSashGripElementOptions[] = {
    {NULL}
};

static void PanedSashGripElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_ORIENTED_WIDGET(TileGtk_QWidget_Widget);
    if (orient == TTK_ORIENT_HORIZONTAL) {
      *widthPtr = PMW(PM_SplitterWidth, 0);
    } else {
      *heightPtr = PMW(PM_SplitterWidth, 0);
    }
    *paddingPtr = Ttk_UniformPadding(PanedUniformPadding);
}

static void PanedSashGripElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_ORIENTED_WIDGET(TileGtk_QWidget_Widget);
    Tcl_MutexLock(&tilegtkMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TILEGTK_PAINT_BACKGROUND(b.width, b.height);
    TILEGTK_SET_FOCUS(state);
#ifdef TILEGTK_GTK_VERSION_3
    QStyle::SFlags sflags = TileGtk_StateTableLookup(paned_statemap, state);
    if (orient == TTK_ORIENT_HORIZONTAL) {
    } else {
      sflags |= QStyle::Style_Horizontal;
    }
    wc->TileGtk_Style->drawPrimitive(QStyle::PE_Splitter, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    QStyleOption option;
    option.state |= 
      (QStyle::StateFlag) TileGtk_StateTableLookup(paned_statemap, state);
    wc->TileGtk_Style->drawControl(QStyle::CE_Splitter, &option,
                                    &painter);
#endif /* TILEGTK_GTK_VERSION_4 */
    TILEGTK_CLEAR_FOCUS(state);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tilegtkMutex);
}; /* PanedSashGripElementDraw */

static Ttk_ElementSpec PanedSashGripElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(PanedSashGripElement),
    PanedSashGripElementOptions,
    PanedSashGripElementGeometry,
    PanedSashGripElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(HorizontalSashLayout)
    TTK_GROUP("Sash.hsash", TTK_FILL_BOTH,
	TTK_NODE("Sash.hgrip", TTK_FILL_BOTH))
TTK_END_LAYOUT

TTK_BEGIN_LAYOUT(VerticalSashLayout)
    TTK_GROUP("Sash.vsash", TTK_FILL_BOTH,
	TTK_NODE("Sash.vgrip", TTK_FILL_BOTH))
TTK_END_LAYOUT

int TileGtk_Init_Paned(Tcl_Interp *interp,
                       TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "hgrip",
	    &PanedSashGripElementSpec,  (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "vgrip",
	    &PanedSashGripElementSpec,  (void *) wc[1]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "Horizontal.Sash", HorizontalSashLayout);
    Ttk_RegisterLayout(themePtr, "Vertical.Sash", VerticalSashLayout);

    return TCL_OK;
}; /* TileGtk_Init_Paned */

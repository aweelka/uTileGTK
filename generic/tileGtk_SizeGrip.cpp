/*
 *  tileGtk_SizeGrip.cpp
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
static Ttk_StateTable size_grip_statemap[] =
{
#ifdef TILEGTK_GTK_VERSION_3
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled,                         0, 0}
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    {QStyle::State_None,                            TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled,                         0, 0}
#endif /* TILEGTK_GTK_VERSION_4 */
};

typedef struct {
} SizeGripElement;

static Ttk_ElementOptionSpec SizeGripElementOptions[] = {
    {NULL}
};

static void SizeGripElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_WIDGET(TileGtk_QWidget_Widget);
    QSizeGrip widget(wc->TileGtk_QWidget_Widget);
    QSize size = widget.sizeHint();
    *widthPtr = size.width();
    *heightPtr = size.height();
    *paddingPtr = Ttk_UniformPadding(0);
}

static void SizeGripElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_WIDGET(TileGtk_QWidget_Widget);
    Tcl_MutexLock(&tilegtkMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TILEGTK_PAINT_BACKGROUND(b.width, b.height);
    TILEGTK_SET_FOCUS(state);
#ifdef TILEGTK_GTK_VERSION_3
    QStyle::SFlags sflags = TileGtk_StateTableLookup(size_grip_statemap, state);
    wc->TileGtk_Style->drawPrimitive(QStyle::PE_SizeGrip, &painter,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    QStyleOption option;
    option.state |= 
      (QStyle::StateFlag) TileGtk_StateTableLookup(size_grip_statemap, state);
    wc->TileGtk_Style->drawControl(QStyle::CE_SizeGrip, &option,
                                    &painter);
#endif /* TILEGTK_GTK_VERSION_4 */
    TILEGTK_CLEAR_FOCUS(state);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tilegtkMutex);
}; /* SizeGripElementDraw */

static Ttk_ElementSpec SizeGripElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(SizeGripElement),
    SizeGripElementOptions,
    SizeGripElementGeometry,
    SizeGripElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

TTK_BEGIN_LAYOUT(SizegripLayout)
    TTK_NODE("Sizegrip.sizegrip", TTK_PACK_BOTTOM|TTK_STICK_S|TTK_STICK_E)
TTK_END_LAYOUT

int TileGtk_Init_SizeGrip(Tcl_Interp *interp,
                       TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "sizegrip",
	    &SizeGripElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */
    Ttk_RegisterLayout(themePtr, "TSizegrip", SizegripLayout);

    return TCL_OK;
}; /* TileGtk_Init_SizeGrip */

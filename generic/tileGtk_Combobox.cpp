/*
 *  tileGtk_Combobox.cpp
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

#if 0
/*
 * Map between Tk/Tile & Gtk/GNOME state flags.
 */
static Ttk_StateTable combotext_statemap[] =
{
};
#endif

typedef struct {
} ComboboxFieldElement;


static Ttk_ElementOptionSpec ComboboxFieldElementOptions[] = {
    {NULL}
};

static void ComboboxFieldElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
#endif /* TILEGTK_GTK_VERSION_4 */
    Tcl_MutexUnlock(&tilegtkMutex);
    *widthPtr  = wc->TileGtk_QComboBox_RO_Widget->minimumWidth();
    *heightPtr = wc->TileGtk_QComboBox_RO_Widget->minimumHeight();
#if 0
    printf("left=%d, top=%d, right=%d, bottom=%d\n",
            ef_rc.x() - fr_rc.x(), ef_rc.y() - fr_rc.y(),
            fr_rc.width()  - ef_rc.width()  - ef_rc.x(),
            fr_rc.height() - ef_rc.height() - ef_rc.y());
#endif
    *paddingPtr = Ttk_MakePadding(ef_rc.x() - fr_rc.x()           /* left   */,
                                  ef_rc.y() - fr_rc.y()           /* top    */,
#if 0
                     fr_rc.width()  - ef_rc.width()  - ef_rc.x()  /* right  */,
#else
                     ef_rc.x() - fr_rc.x()                        /* right  */,
#endif
                     fr_rc.height() - ef_rc.height() - ef_rc.y()  /* bottom */);
}

static void ComboboxFieldElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    QComboBox*   widget;
    /* According to the state, select either the read-only or the read-write
     * widget. */
    NULL_PROXY_WIDGET(TileGtk_QComboBox_RO_Widget);
    if (state & (TTK_STATE_DISABLED|TTK_STATE_READONLY)) {
      widget = wc->TileGtk_QComboBox_RO_Widget;
    } else {
      if (wc->TileGtk_QComboBox_RW_Widget) {
        widget = wc->TileGtk_QComboBox_RW_Widget;
      } else {
        widget = wc->TileGtk_QComboBox_RO_Widget;
      }
    }
    Tcl_MutexLock(&tilegtkMutex);
    widget->resize(b.width, b.height);
    TILEGTK_PAINT_BACKGROUND(b.width, b.height);
    TILEGTK_SET_FOCUS(state);
#ifdef TILEGTK_GTK_VERSION_3
    widget->setBackgroundOrigin(QWidget::ParentOrigin);
    QStyle::SFlags sflags = TileGtk_StateTableLookup(combotext_statemap, state);
    QStyle::SCFlags scflags = QStyle::SC_ComboBoxFrame|QStyle::SC_ComboBoxArrow|
                              QStyle::SC_ComboBoxEditField;
    QStyle::SCFlags activeflags = QStyle::SC_ComboBoxFrame;
    wc->TileGtk_Style->drawComplexControl(QStyle::CC_ComboBox, &painter, widget,
          QRect(0, 0, b.width, b.height), qApp->palette().active(), sflags,
          scflags, activeflags);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    QStyleOptionComboBox option;
    option.initFrom(widget); option.state |= 
      (QStyle::StateFlag) TileGtk_StateTableLookup(combotext_statemap, state);
    wc->TileGtk_Style->drawComplexControl(QStyle::CC_ComboBox, &option,
                                         &painter, widget);
#endif /* TILEGTK_GTK_VERSION_4 */
    TILEGTK_CLEAR_FOCUS(state);
    // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                                    0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tilegtkMutex);
}

static Ttk_ElementSpec ComboboxFieldElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ComboboxFieldElement),
    ComboboxFieldElementOptions,
    ComboboxFieldElementGeometry,
    ComboboxFieldElementDraw
};

/*
 * Map between Tk/Tile & Gtk/GNOME state flags.
 */
#if 0
static Ttk_StateTable combobox_statemap[] =
{
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_PRESSED, 0 },
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE, 0 },
    {QStyle::Style_Enabled,                         0, 0 }
};
#endif

typedef struct {
} ComboboxArrowElement;


static Ttk_ElementOptionSpec ComboboxArrowElementOptions[] = {
    {NULL}
};

static void ComboboxArrowElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_WIDGET(TileGtk_QComboBox_RO_Widget);
    Tcl_MutexLock(&tilegtkMutex);
#ifdef TILEGTK_GTK_VERSION_3
    QRect rc = wc->TileGtk_Style->querySubControlMetrics(QStyle::CC_ComboBox,
                   wc->TileGtk_QComboBox_RO_Widget, QStyle::SC_ComboBoxArrow);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    QStyleOptionComboBox option;
    option.initFrom(wc->TileGtk_QComboBox_RO_Widget);
    option.subControls = QStyle::SC_ComboBoxFrame;
    QRect rc = wc->TileGtk_Style->subControlRect(QStyle::CC_ComboBox,
         &option, QStyle::SC_ComboBoxArrow, wc->TileGtk_QComboBox_RO_Widget);
#endif /* TILEGTK_GTK_VERSION_4 */
    *widthPtr = rc.width();
    Tcl_MutexUnlock(&tilegtkMutex);
    *paddingPtr = Ttk_UniformPadding(0);
}

static void ComboboxArrowElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    // There is no need to re-paint the button. It has been paint along with the
    // field element (ComboboxFieldElementDraw). This is because Gtk's Combobox
    // is a complex widget.
    // QPixmap      pixmap(b.x+b.width, b.y+b.height);
    // QPainter     painter(&pixmap);
    // QComboBox& widget = *TileGtk_QComboBox_RO_Widget;
    // widget.resize(b.x+b.width, b.y+b.height);
    // QStyle::SFlags sflags = TileGtk_StateTableLookup(combobox_statemap, state);
    // QStyle::SCFlags scflags = QStyle::SC_ComboBoxArrow;
    // QStyle::SCFlags activeflags = QStyle::SC_None;
    // 
    // painter.fillRect(0, 0, b.width, b.height,
    //                 qApp->palette().active().brush(QColorGroup::Background));
    // // printf("x=%d, y=%d, w=%d, h=%d\n", b.x, b.y, b.width, b.height);
    // qApp->style().drawComplexControl(QStyle::CC_ComboBox, &painter, &widget,
    //       QRect(0, 0, b.x+b.width, b.y+b.height),
    //       qApp->palette().active(), sflags, scflags, activeflags);
    // TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
    //                                 b.x, b.y, b.width, b.height, b.x, b.y);
}

static Ttk_ElementSpec ComboboxArrowElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(ComboboxArrowElement),
    ComboboxArrowElementOptions,
    ComboboxArrowElementGeometry,
    ComboboxArrowElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

int TileGtk_Init_Combobox(Tcl_Interp *interp,
                       TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Combobox.field",
            &ComboboxFieldElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Combobox.downarrow",
            &ComboboxArrowElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */

    return TCL_OK;
}; /* TileGtk_Init_Combobox */

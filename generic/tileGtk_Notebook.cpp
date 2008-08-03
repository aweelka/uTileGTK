/*
 *  tileGtk_Notebook.cpp
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
static Ttk_StateTable notebook_statemap[] =
{
#ifdef TILEGTK_GTK_VERSION_3
    {QStyle::Style_Default,                         TTK_STATE_DISABLED, 0},
    {QStyle::Style_Enabled|QStyle::Style_Selected,  TTK_STATE_SELECTED, 0},
    {QStyle::Style_Enabled|QStyle::Style_MouseOver, TTK_STATE_ACTIVE,   0},
    {QStyle::Style_Enabled|QStyle::Style_HasFocus,  TTK_STATE_FOCUS,    0},
    {QStyle::Style_Enabled,                         0,                  0},
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    {QStyle::State_None,                            TTK_STATE_DISABLED, 0},
    {QStyle::State_Enabled|QStyle::State_Selected,  TTK_STATE_SELECTED, 0},
    {QStyle::State_Enabled|QStyle::State_MouseOver, TTK_STATE_ACTIVE,   0},
    {QStyle::State_Enabled|QStyle::State_HasFocus,  TTK_STATE_FOCUS,    0},
    {QStyle::State_Enabled,                         0,                  0},
#endif /* TILEGTK_GTK_VERSION_4 */
};

#ifdef TILEGTK_GTK_VERSION_3
#define PM(pm) (wc->TileGtk_Style->pixelMetric(QStyle::pm, \
                                              wc->TileGtk_GTKabBar_Widget))
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
#ifndef QStyleOptionTabV2
#define QStyleOptionTabV2 QStyleOptionTab
#endif /* QStyleOptionTabV2 */
#define PM(pm) (wc->TileGtk_Style->pixelMetric(QStyle::pm, &option, \
                                              wc->TileGtk_GTKabBar_Widget))
#endif /* TILEGTK_GTK_VERSION_4 */

typedef struct {
} NotebookTabElement;


static Ttk_ElementOptionSpec NotebookTabElementOptions[] = {
    {NULL}
};

static void NotebookTabElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_WIDGET(TileGtk_GTKabBar_Widget);
    Tcl_MutexLock(&tilegtkMutex);
#ifdef TILEGTK_GTK_VERSION_4
    QStyleOptionTab option;
    option.initFrom(wc->TileGtk_GTKabBar_Widget);
#endif /* TILEGTK_GTK_VERSION_4 */
    int PM_TabBarTabVSpace          = PM(PM_TabBarTabVSpace),
        PM_TabBarTabHSpace          = PM(PM_TabBarTabHSpace);
    Tcl_MutexUnlock(&tilegtkMutex);
    *paddingPtr = Ttk_MakePadding(
           PM_TabBarTabHSpace/2,
#ifdef TILEGTK_GTK_VERSION_3
           PM_TabBarTabVSpace/2,
           PM_TabBarTabHSpace/2,
           PM_TabBarTabVSpace/2
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
           PM_TabBarTabVSpace,
           PM_TabBarTabHSpace/2,
           0
#endif /* TILEGTK_GTK_VERSION_4 */
           );
}

static void NotebookTabElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_WIDGET(TileGtk_GTKabBar_Widget);
    int width = b.width, height = b.height;
    Tcl_MutexLock(&tilegtkMutex);
    int PM_DefaultFrameWidth = 0, PM_TabBarBaseOverlap = 0;

    // TileGtk_StateInfo(state, tkwin);
#ifdef TILEGTK_GTK_VERSION_3
    GTKab* tab = new GTKab;
    GTKab* tab1 = NULL, *tab2 = NULL;
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    QStyleOptionTab::TabPosition position;
    int position_int;
    QStyleOptionTabV2 option;
    option.initFrom(wc->TileGtk_GTKabBar_Widget); option.state |= 
      (QStyle::StateFlag) TileGtk_StateTableLookup(notebook_statemap, state);
#endif /* TILEGTK_GTK_VERSION_4 */

    PM_DefaultFrameWidth = PM(PM_DefaultFrameWidth);

    if (TileGtk_ThemeIs(wc, "bluecurve")) {
      PM_DefaultFrameWidth = 2;
    }

    PM_TabBarBaseOverlap = PM(PM_TabBarBaseOverlap);
    height += PM_TabBarBaseOverlap;

    if ((state & TTK_STATE_USER1) && (state & TTK_STATE_USER2)) {
      /* Only tab */
#ifdef TILEGTK_GTK_VERSION_3
      wc->TileGtk_GTKabBar_Widget->addTab(tab);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
      wc->TileGtk_GTKabBar_Widget->addTab("");
      position = QStyleOptionTab::OnlyOneTab;
      position_int = 0;
#endif /* TILEGTK_GTK_VERSION_4 */
    } else if (state & TTK_STATE_USER1) {
      /* Left-most tab */
#ifdef TILEGTK_GTK_VERSION_3
      wc->TileGtk_GTKabBar_Widget->addTab(tab);
      tab1 = new GTKab;
      wc->TileGtk_GTKabBar_Widget->addTab(tab1);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
      wc->TileGtk_GTKabBar_Widget->addTab("");
      wc->TileGtk_GTKabBar_Widget->addTab("");
      position = QStyleOptionTab::Beginning;
      position_int = 0;
#endif /* TILEGTK_GTK_VERSION_4 */
    } else if (state & TTK_STATE_USER2) {
      /* Right-most tab */
#ifdef TILEGTK_GTK_VERSION_3
      tab1 = new GTKab;
      wc->TileGtk_GTKabBar_Widget->addTab(tab1);
      wc->TileGtk_GTKabBar_Widget->addTab(tab);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
      wc->TileGtk_GTKabBar_Widget->addTab("");
      wc->TileGtk_GTKabBar_Widget->addTab("");
      position = QStyleOptionTab::End;
      position_int = 1;
#endif /* TILEGTK_GTK_VERSION_4 */
    } else {
      /* A regular tab, in the middle of tab bar */
#ifdef TILEGTK_GTK_VERSION_3
      tab1 = new GTKab;
      wc->TileGtk_GTKabBar_Widget->addTab(tab1);
      wc->TileGtk_GTKabBar_Widget->addTab(tab);
      tab2 = new GTKab;
      wc->TileGtk_GTKabBar_Widget->addTab(tab2);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
      wc->TileGtk_GTKabBar_Widget->addTab("");
      wc->TileGtk_GTKabBar_Widget->addTab("");
      wc->TileGtk_GTKabBar_Widget->addTab("");
      position = QStyleOptionTab::Middle;
      position_int = 1;
#endif /* TILEGTK_GTK_VERSION_4 */
    }
#ifdef TILEGTK_GTK_VERSION_3
    if (state & TTK_STATE_DISABLED) tab->setEnabled(false);
    else tab->setEnabled(true);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    if (state & TTK_STATE_DISABLED) {
      wc->TileGtk_GTKabBar_Widget->setTabEnabled(position_int, false);
    } else wc->TileGtk_GTKabBar_Widget->setTabEnabled(position_int, true);
#endif /* TILEGTK_GTK_VERSION_4 */

    QPixmap      pixmap(width, height);
    QPainter     painter(&pixmap);
    TILEGTK_PAINT_BACKGROUND(width, height);
    TILEGTK_SET_FOCUS(state);
#ifdef TILEGTK_GTK_VERSION_3
    QStyle::SFlags sflags = TileGtk_StateTableLookup(notebook_statemap, state);
    wc->TileGtk_Style->drawControl(QStyle::CE_TabBarTab, &painter,
          wc->TileGtk_GTKabBar_Widget, QRect(0, 0, width, height),
          qApp->palette().active(), sflags, QStyleOption(tab));
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    option.rect = QRect(0, 0, width, height);
    option.position = position;
    option.selectedPosition = QStyleOptionTab::NotAdjacent;
    wc->TileGtk_Style->drawControl(QStyle::CE_TabBarTabShape, &option,
                                  &painter, wc->TileGtk_GTKabBar_Widget);
#endif /* TILEGTK_GTK_VERSION_4 */
    TILEGTK_CLEAR_FOCUS(state);
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
           0, 0, width, height, b.x, b.y + PM_DefaultFrameWidth);
#ifdef TILEGTK_GTK_VERSION_3
    if ((state & TTK_STATE_USER1) && (state & TTK_STATE_USER2)) {
      wc->TileGtk_GTKabBar_Widget->removeTab(tab);
    } else if (state & TTK_STATE_USER1) {
      wc->TileGtk_GTKabBar_Widget->removeTab(tab);
      wc->TileGtk_GTKabBar_Widget->removeTab(tab1);
    } else if (state & TTK_STATE_USER2) {
      wc->TileGtk_GTKabBar_Widget->removeTab(tab1);
      wc->TileGtk_GTKabBar_Widget->removeTab(tab);
    } else {
      wc->TileGtk_GTKabBar_Widget->removeTab(tab1);
      wc->TileGtk_GTKabBar_Widget->removeTab(tab);
      wc->TileGtk_GTKabBar_Widget->removeTab(tab2);
    }
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    for (int i = 0; i < wc->TileGtk_GTKabBar_Widget->count(); ++i) {
      wc->TileGtk_GTKabBar_Widget->removeTab(i);
    }
#endif /* TILEGTK_GTK_VERSION_4 */
    Tcl_MutexUnlock(&tilegtkMutex);
}

static Ttk_ElementSpec NotebookTabElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(NotebookTabElement),
    NotebookTabElementOptions,
    NotebookTabElementGeometry,
    NotebookTabElementDraw
};

typedef struct {
} NotebookClientElement;


static Ttk_ElementOptionSpec NotebookClientElementOptions[] = {
    {NULL}
};

static void NotebookClientElementGeometry(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_WIDGET(TileGtk_GTKabWidget_Widget);
    int tabBarBaseHeight =
        wc->TileGtk_Style->pixelMetric(QStyle::PM_TabBarBaseHeight,
#ifdef TILEGTK_GTK_VERSION_4
                                      0,
#endif /* TILEGTK_GTK_VERSION_4 */
                                      wc->TileGtk_GTKabWidget_Widget);
    *paddingPtr = Ttk_MakePadding(NotebookClientUniformPadding,
           NotebookClientUniformPadding + tabBarBaseHeight,
           NotebookClientUniformPadding, NotebookClientUniformPadding);
}

static void NotebookClientElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned state)
{
    if (!TileGtk_GtkInitialised()) NO_GTK_STYLE_ENGINE;
    NULL_PROXY_WIDGET(TileGtk_GTKabBar_Widget);
    Tcl_MutexLock(&tilegtkMutex);
    QPixmap      pixmap(b.width, b.height);
    QPainter     painter(&pixmap);
    TILEGTK_PAINT_BACKGROUND(b.width, b.height);
#ifdef TILEGTK_GTK_VERSION_3
    QStyle::SFlags sflags = TileGtk_StateTableLookup(notebook_statemap, state);
    wc->TileGtk_Style->drawPrimitive(QStyle::PE_PanelTabWidget, &painter,
            QRect(0, 0, b.width, b.height),
            qApp->palette().active(), sflags);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
    QStyleOptionTabWidgetFrame option;
    option.initFrom(wc->TileGtk_GTKabBar_Widget);
    option.rect = QRect(0, 0, b.width, b.height);
    option.state |= 
      (QStyle::StateFlag) TileGtk_StateTableLookup(notebook_statemap, state);
    wc->TileGtk_Style->drawPrimitive(QStyle::PE_FrameTabWidget, &option,
                                    &painter);
#endif /* TILEGTK_GTK_VERSION_4 */
    int tabBarBaseHeight =
        wc->TileGtk_Style->pixelMetric(QStyle::PM_TabBarBaseHeight,
#ifdef TILEGTK_GTK_VERSION_4
                                      0,
#endif /* TILEGTK_GTK_VERSION_4 */
                                      wc->TileGtk_GTKabWidget_Widget);
    if (tabBarBaseHeight) {
      TILEGTK_PAINT_BACKGROUND(b.width, tabBarBaseHeight);
#ifdef TILEGTK_GTK_VERSION_3
      wc->TileGtk_Style->drawPrimitive(QStyle::PE_TabBarBase, &painter,
              QRect(0, 0, b.width, tabBarBaseHeight),
              qApp->palette().active(), sflags);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
      QStyleOptionTabBarBase optTabBase;
      optTabBase.initFrom(wc->TileGtk_GTKabBar_Widget);
      optTabBase.rect = QRect(0, 0, b.width, tabBarBaseHeight);
      wc->TileGtk_Style->drawPrimitive(QStyle::PE_FrameTabBarBase, &optTabBase,
                                      &painter);
#endif /* TILEGTK_GTK_VERSION_4 */
    }
    TileGtk_CopyGtkPixmapOnToDrawable(pixmap, d, tkwin,
                               0, 0, b.width, b.height, b.x, b.y);
    Tcl_MutexUnlock(&tilegtkMutex);
}

static Ttk_ElementSpec NotebookClientElementSpec = {
    TK_STYLE_VERSION_2,
    sizeof(NotebookClientElement),
    NotebookClientElementOptions,
    NotebookClientElementGeometry,
    NotebookClientElementDraw
};

/*------------------------------------------------------------------------
 * +++ Widget layout.
 */

int TileGtk_Init_Notebook(Tcl_Interp *interp,
                         TileGtk_WidgetCache **wc, Ttk_Theme themePtr)
{
    /*
     * Register elements:
     */
    Ttk_RegisterElement(interp, themePtr, "Notebook.tab",
                &NotebookTabElementSpec, (void *) wc[0]);
    Ttk_RegisterElement(interp, themePtr, "Notebook.client",
                &NotebookClientElementSpec, (void *) wc[0]);
    
    /*
     * Register layouts:
     */

    return TCL_OK;
}; /* TileGtk_Init_Notebook */

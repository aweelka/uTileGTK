/*
 *  tileGtk_GtkHeaders.h
 * --------------------
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
#ifndef _TILEGTK_GTKHEADERS
#define _TILEGTK_GTKHEADERS

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk-pixbuf-xlib/gdk-pixbuf-xlib.h>
#include <gdk/gdkx.h>
#include <tk.h>

typedef struct TileGtk_WidgetCache {
  Tk_Window      TileGtk_tkwin;
  Display*       TileGtk_MainDisplay;
  Tcl_Interp*    TileGtk_MainInterp;
  int            orientation;
  GtkOrientation gtkOrientation;
  GdkDisplay*    gdkDisplay;
  GtkStyle*      gtkStyle;
  GtkWidget*     gtkNotebook;
  GtkWidget*     gtkEntry;
  GtkWidget*     hScaleWidget;
  GtkWidget*     vScaleWidget;
  GtkWidget*     gtkProgressBar;
  GtkWidget*     gtkComboBox;
  GtkWidget*     gtkHScrollBar;
  GtkWidget*     gtkVScrollBar;
  GtkWidget*     gtkButton;
  GtkWidget*     gtkCheckButton;
  GtkWidget*     gtkSpinButton;
  GtkWidget*     gtkToolbar;
  GtkWidget*     gtkMenuItem;
  GtkWidget*     gtkMenubarItem;
  GtkWidget*     gtkMenubar;
  GtkWidget*     gtkMenu;
  GtkWidget*     gtkTreeView;
  GtkWidget*     gtkTreeHeader;
  GtkWidget*     gtkMenuSeparator;
  GtkWidget*     gtkCheckMenuItem;
  GtkWidget*     gtkFrame;
  GtkWidget*     gtkComboboxEntry;
  //GtkWidget*     gtkComboboxEntryButton;
  GtkWidget*     gtkWindow;
  GtkWidget*     protoLayout;
} TileGtk_WidgetCache;

typedef struct {
    GtkStateType  state;    /* State value to return if this entry matches */
    GtkShadowType shadow;   /* Shadow value to return if this entry matches */
    unsigned int  value;    /* Value to return if this entry matches */
    unsigned int  onBits;   /* Bits which must be set */
    unsigned int  offBits;  /* Bits which must be cleared */
    unsigned int  section;  /* Table section to match */
} TileGtk_StateTable;

#define TILEGTK_SECTION_ALL       (1<<0)
#define TILEGTK_SECTION_BUTTONS   (1<<1)
#define TILEGTK_SECTION_ENTRY     (1<<2)
#define TILEGTK_SECTION_SCROLLBAR (1<<3)
#define TILEGTK_SECTION_STEPPERS  (1<<4)
#define TILEGTK_SECTION_TROUGH    (1<<5)

#endif

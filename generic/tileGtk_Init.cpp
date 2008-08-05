/*
 * $Id$
 *
 * Copyright (C) 2004-2008 Georgios Petasis
 *
 * The Tile-Gtk theme is a Tk/Tile theme that uses Gtk/GNOME for drawing.
 */

#include "tileGtk_Utilities.h"
#include "tileGtk_TkHeaders.h"
#include <string.h>

static int TileGtk_GtkAppCreated = 0;

extern TileGtk_WidgetCache **TileGtk_CreateGtkApp(Tcl_Interp *interp);
extern void TileGtk_DestroyGtkApp(void);

static char initScript[] =
    "namespace eval tilegtk { };"
    "namespace eval ttk::theme::tilegtk { variable version "
                                                   PACKAGE_VERSION " };"
    "tcl_findLibrary tilegtk $ttk::theme::tilegtk::version "
    "$ttk::theme::tilegtk::version tilegtk.tcl TILEGTK_LIBRARY tilegtk::library;";

/*
 * Exit Handler.
 */
static void TileGtk_ExitProc(ClientData data) {
  //Tcl_MutexLock(&tilegtkMutex);
  //TileGtk_DestroyGtkApp();
  //Tcl_MutexUnlock(&tilegtkMutex);
  Tcl_MutexLock(&tilegtkMutex);
  // printf("TileGtk_ExitProc: %d\n", TileGtk_GtkAppCreated); fflush(NULL);
  if (TileGtk_GtkAppCreated < 0) {
    Tcl_MutexUnlock(&tilegtkMutex);
    return;
  }
  --TileGtk_GtkAppCreated;
  if (TileGtk_GtkAppCreated == 0) {
    // printf("TileGtk_ExitProc: %d <- TileGtk_DestroyGtkApp();\n",
    //       TileGtk_GtkAppCreated); fflush(NULL);
    TileGtk_DestroyGtkApp();
  }
  Tcl_MutexUnlock(&tilegtkMutex);
  return;
}; /* TileGtk_ExitProc */

/*
 * Helper Functions
 */
int Tileqt_ThemeName(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  // TileGtk_WidgetCache **wc_array = (TileGtk_WidgetCache **) clientData;
  // TileGtk_WidgetCache *wc;
  // if (!wc_array || !wc_array[0]) {
  //   Tcl_SetResult(interp, (char *) "empty wc_array!", TCL_STATIC);
  //   return TCL_ERROR;
  // }
  // wc = wc_array[0];
  // if (!wc->gtkStyle) {
  //   Tcl_SetResult(interp, (char *) "empty wc->gtkStyle!", TCL_STATIC);
  //   return TCL_ERROR;
  // }
  GtkSettings *settings = NULL;
  gchar       *strval = NULL;
  if (objc != 1) {Tcl_WrongNumArgs(interp, 1, objv, ""); return TCL_ERROR;}

  Tcl_MutexLock(&tilegtkMutex);
  settings = gtk_settings_get_default();
  if (settings) {
    g_object_get(settings, "gtk-theme-name", &strval, NULL);
    if (strval) {
      Tcl_SetResult(interp, (char *) strval, TCL_VOLATILE);
      g_free(strval);
    }
  }
  Tcl_MutexUnlock(&tilegtkMutex);
  return TCL_OK;
}; /* Tileqt_ThemeName */

int Tileqt_SettingsProperty(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  static const char *Methods[] = {
    "integer", "boolean", "string", (char *) NULL
  };
  enum methods {
    INTEGER, BOOLEAN, STRING
  };
  int type = STRING;
  GtkSettings *settings = NULL;
  gchar       *s_val = NULL;
  gboolean     b_val = FALSE;
  gint         i_val = 0;
  if (objc != 2 && objc != 3) {
    Tcl_WrongNumArgs(interp, 1, objv, "property ?integer|boolean|string?");
    return TCL_ERROR;
  }
  if (objc == 3) {
    if (Tcl_GetIndexFromObj(interp, objv[2], (const char **) Methods,
                            "method", 0, &type) != TCL_OK) {
      return TCL_ERROR;
    }
  }

  Tcl_MutexLock(&tilegtkMutex);
  settings = gtk_settings_get_default();
  if (settings) {
    switch ((enum methods) type) {
      case INTEGER:
        g_object_get(settings, Tcl_GetString(objv[1]), &i_val, NULL);
        Tcl_SetObjResult(interp, Tcl_NewIntObj(i_val));
        break;
      case BOOLEAN:
        g_object_get(settings, Tcl_GetString(objv[1]), &b_val, NULL);
        if (b_val == TRUE) Tcl_SetObjResult(interp, Tcl_NewBooleanObj(1));
        else Tcl_SetObjResult(interp, Tcl_NewBooleanObj(0));
        break;
      case STRING:
        g_object_get(settings, Tcl_GetString(objv[1]), &s_val, NULL);
        if (s_val) {
          Tcl_SetResult(interp, (char *) s_val, TCL_VOLATILE);
          g_free (s_val);
        }
        break;
    }
  }
  Tcl_MutexUnlock(&tilegtkMutex);
  return TCL_OK;
}; /* Tileqt_SettingsProperty */

int Tileqt_WidgetStyleProperty(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  static const char *Methods[] = {
    "integer", "boolean", "string", (char *) NULL
  };
  enum methods {
    INTEGER, BOOLEAN, STRING
  };
  static const char *Widgets[] = {
    "GtkHScrollbar" , "GtkVScrollbar", (char *) NULL
  };
  enum widgets {
    W_HSCROLLBAR, W_VSCROLLBAR
  };
  int          type  = STRING;
  gchar       *s_val = NULL;
  gboolean     b_val = FALSE;
  gint         i_val = 0;
  GtkWidget   *widget = NULL;
  TileGtk_WidgetCache **wc_array = (TileGtk_WidgetCache **) clientData;
  TileGtk_WidgetCache *wc;
  if (!wc_array || !wc_array[0]) {
    Tcl_SetResult(interp, (char *) "empty wc_array!", TCL_STATIC);
    return TCL_ERROR;
  }
  wc = wc_array[0];
  if (objc != 3 && objc != 4) {
    Tcl_WrongNumArgs(interp, 1, objv,
       "widget property ?integer|boolean|string?");
    return TCL_ERROR;
  }
  /* Get widget... */
  if (Tcl_GetIndexFromObj(interp, objv[1], (const char **) Widgets,
                                 "widget", 0, &type) != TCL_OK) {
    return TCL_ERROR;
  }
  switch ((enum widgets) type) {
    case W_HSCROLLBAR: {widget = TileGtk_GetHScrollBar(wc); break;}
    case W_VSCROLLBAR: {widget = TileGtk_GetVScrollBar(wc); break;}
  }
  /* Get property type, which defaults to "string"... */
  if (objc == 4) {
    if (Tcl_GetIndexFromObj(interp, objv[3], (const char **) Methods,
                            "method", 0, &type) != TCL_OK) {
      return TCL_ERROR;
    }
  }

  Tcl_MutexLock(&tilegtkMutex);
  if (widget) {
    switch ((enum methods) type) {
      case INTEGER:
        gtk_widget_style_get(widget, Tcl_GetString(objv[2]), &i_val, NULL);
        Tcl_SetObjResult(interp, Tcl_NewIntObj(i_val));
        break;
      case BOOLEAN:
        gtk_widget_style_get(widget, Tcl_GetString(objv[2]), &b_val, NULL);
        if (b_val == TRUE) Tcl_SetObjResult(interp, Tcl_NewBooleanObj(1));
        else Tcl_SetObjResult(interp, Tcl_NewBooleanObj(0));
        break;
      case STRING:
        gtk_widget_style_get(widget, Tcl_GetString(objv[2]), &s_val, NULL);
        if (s_val) {
          Tcl_SetResult(interp, (char *) s_val, TCL_VOLATILE);
          g_free (s_val);
        }
        break;
    }
  }
  Tcl_MutexUnlock(&tilegtkMutex);
  return TCL_OK;
}; /* Tileqt_WidgetStyleProperty */

int Tileqt_GtkDirectory(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  static const char *Methods[] = {
    "theme", "default_files", (char *) NULL
  };
  enum methods {
    THEME, DEFAULT_FILES
  };
  int type;
  gchar *dir = NULL, **dirs = NULL;
  
  if (objc != 2 && objc != 3) {
    Tcl_WrongNumArgs(interp, 1, objv, "category ?value?");
    return TCL_ERROR;
  }
  if (Tcl_GetIndexFromObj(interp, objv[1], (const char **) Methods,
                          "method", 0, &type) != TCL_OK) {
    return TCL_ERROR;
  }

  Tcl_MutexLock(&tilegtkMutex);
  switch ((enum methods) type) {
    case THEME:
      dir = gtk_rc_get_theme_dir();
      break;
    case DEFAULT_FILES:
      if (objc == 3) {
        int mobjc; Tcl_Obj **mobjv;
        if (Tcl_ListObjGetElements(interp, objv[2], &mobjc, &mobjv) != TCL_OK) {
          return TCL_ERROR;
        }
        dirs = g_new0(gchar *, mobjc+1);
        for (int i = 0; i < mobjc; ++i) {
          dirs[i] = Tcl_GetString(mobjv[i]);
        }
        gtk_rc_set_default_files(dirs);
        g_free(dirs); dirs = NULL;
      } else {
        dirs = gtk_rc_get_default_files();
      }
      break;
  }
  if (dir) {
    Tcl_SetResult(interp, (char *) dir, TCL_VOLATILE);
    g_free(dir);
  }
  if (dirs) {
    Tcl_Obj *list = Tcl_NewListObj(0, NULL);
    while (*dirs) {
      Tcl_ListObjAppendElement(NULL, list, Tcl_NewStringObj(*dirs, -1));
      ++dirs;
    }
    Tcl_SetObjResult(interp, list);
  }
  Tcl_MutexUnlock(&tilegtkMutex);
  return TCL_OK;
}; /* Tileqt_GtkDirectory */

int Tileqt_gtk_method(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  static const char *Methods[] = {
    "gtk_rc_reparse_all_for_settings", "gtk_rc_reset_styles", (char *) NULL
  };
  enum methods {
    GTK_RC_REPARSE_ALL_FOR_SETTINGS, GTK_RC_RESET_STYLES
  };
  int type;
  
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "method"); return TCL_ERROR;
  }
  if (Tcl_GetIndexFromObj(interp, objv[1], (const char **) Methods,
                          "method", 0, &type) != TCL_OK) {
    return TCL_ERROR;
  }

  Tcl_MutexLock(&tilegtkMutex);
  switch ((enum methods) type) {
    case GTK_RC_REPARSE_ALL_FOR_SETTINGS:
      gtk_rc_reparse_all_for_settings(gtk_settings_get_default(), TRUE);
      break;
    case GTK_RC_RESET_STYLES:
      gtk_rc_reset_styles(gtk_settings_get_default());
      break;
  }
  Tcl_MutexUnlock(&tilegtkMutex);
  return TCL_OK;
}; /* Tileqt_gtk_method */

int Tileqt_ThemeColour(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  TileGtk_WidgetCache **wc = (TileGtk_WidgetCache **) clientData;
  GdkColor colour;
  gchar* colour_str;
  if (!wc) {
    Tcl_SetResult(interp, (char *) "empty wc!", TCL_STATIC);
    return TCL_ERROR;
  }
  if (!wc[0]->gtkStyle) {
    Tcl_SetResult(interp, (char *) "empty wc[0]->gtkStyle!", TCL_STATIC);
    return TCL_ERROR;
  }
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "colour");
    return TCL_ERROR;
  }

  if (gtk_style_lookup_color(wc[0]->gtkStyle, Tcl_GetString(objv[1]), &colour)
       == TRUE) {
    colour_str = gdk_color_to_string(&colour);
    Tcl_SetResult(interp, (char *) colour_str, TCL_VOLATILE);
    g_free(colour_str);
    return TCL_OK;
  }
  Tcl_SetResult(interp, (char *) "colour not found: ", TCL_STATIC);
  Tcl_AppendResult(interp, (char *) Tcl_GetString(objv[1]), NULL);
  return TCL_ERROR;
}; /* Tileqt_ThemeColour */

int Tileqt_SetPalette(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
#if 0
  static const char *Methods[] = {
    "-background",       "-foreground",
    "-buttonBackground", "-buttonForeground",
    "-selectBackground", "-selectForeground",
    "-windowBackground", "-windowForeground",
    "-linkColor",        "-visitedLinkColor",
    "-contrast",
    (char *) NULL
  };
  enum methods {
    CLR_background,       CLR_foreground,
    CLR_buttonBackground, CLR_buttonForeground,
    CLR_selectBackground, CLR_selectForeground,
    CLR_windowBackground, CLR_windowForeground,
    CLR_linkColor,        CLR_visitedLinkColor,
    CLR_contrast
  };
  int index, contrast_;
  char *value;
  if ((objc-1)%2) {
    Tcl_WrongNumArgs(interp, 1, objv, "?-key value?");
    return TCL_ERROR;
  }
  Tcl_MutexLock(&tilegtkMutex);
  Tcl_MutexUnlock(&tilegtkMutex);
#endif
  return TCL_OK;
}; /* Tileqt_SetPalette */

int Tileqt_SetStyle(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {Tcl_WrongNumArgs(interp, 1, objv, "style"); return TCL_ERROR;}
  Tcl_MutexLock(&tilegtkMutex);
#if 0
  TileGtk_WidgetCache **wc_array = (TileGtk_WidgetCache **) clientData;
  TileGtk_WidgetCache *wc = wc_array[0];
  if (qApp) {
    int len;
    const char* str = Tcl_GetStringFromObj(objv[1], &len);
    QString style = QString::fromUtf8(str, len);
    QStyle *new_style = QStyleFactory::create(style);
    QStyle *todelete = NULL;
    if (new_style == NULL) {
      Tcl_SetResult(interp, (char *) "unknwon style: \"", TCL_STATIC);
      Tcl_AppendResult(interp, str, "\"", NULL);
      Tcl_MutexUnlock(&tilegtkMutex);
      return TCL_ERROR;
    }
    //qApp->setStyle(style);
    /* Is this style the qApp style? */
    if (wc->TileGtk_Style_Owner) todelete = wc->TileGtk_Style;

#ifdef TILEGTK_GTK_VERSION_3                    
    if (strcmp(qApp->style().name(), str) == 0) {
      wc->TileGtk_Style = &(qApp->style());
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4                    
    if (qApp->style()->objectName() == style) {
      wc->TileGtk_Style = qApp->style();
#endif /* TILEGTK_GTK_VERSION_4 */
      wc->TileGtk_Style_Owner = false;
    } else {
      wc->TileGtk_Style = QStyleFactory::create(style);
      wc->TileGtk_Style_Owner = true;
    }
    TileGtk_StoreStyleNameLowers(wc);
    wc->TileGtk_QScrollBar_Widget->setStyle(wc->TileGtk_Style);
    wc->TileGtk_QComboBox_RW_Widget->setStyle(wc->TileGtk_Style);
    wc->TileGtk_QComboBox_RO_Widget->setStyle(wc->TileGtk_Style);
    wc->TileGtk_QWidget_WidgetParent->setStyle(wc->TileGtk_Style);
    wc->TileGtk_QWidget_Widget->setStyle(wc->TileGtk_Style);
#ifdef TILEGTK_GTK_VERSION_3
    wc->TileGtk_QWidget_Widget->polish();
#endif /* TILEGTK_GTK_VERSION_3 */
    wc->TileGtk_QSlider_Hor_Widget->setStyle(wc->TileGtk_Style);
    wc->TileGtk_QSlider_Ver_Widget->setStyle(wc->TileGtk_Style);
    wc->TileGtk_QProgressBar_Hor_Widget->setStyle(wc->TileGtk_Style);
    wc->TileGtk_GTKabWidget_Widget->setStyle(wc->TileGtk_Style);
    wc->TileGtk_QPixmap_BackgroundTile = 
#ifdef TILEGTK_GTK_VERSION_3
                     (wc->TileGtk_QWidget_Widget)->paletteBackgroundPixmap();
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
                     (wc->TileGtk_QWidget_Widget)->palette().window().texture();
#endif /* TILEGTK_GTK_VERSION_4 */
    wc->TileGtk_Style->polish(wc->TileGtk_QWidget_Widget);
    if (todelete) delete todelete;
#if 0
    // Print Scrollbar statistics...
#define SC_PRINT_INFO(subcontrol) \
    wc->TileGtk_Style->querySubControlMetrics(QStyle::CC_ScrollBar,\
        wc->TileGtk_QScrollBar_Widget, subcontrol).x(),\
    wc->TileGtk_Style->querySubControlMetrics(QStyle::CC_ScrollBar,\
        wc->TileGtk_QScrollBar_Widget, subcontrol).y(),\
    wc->TileGtk_Style->querySubControlMetrics(QStyle::CC_ScrollBar,\
        wc->TileGtk_QScrollBar_Widget, subcontrol).width(),\
    wc->TileGtk_Style->querySubControlMetrics(QStyle::CC_ScrollBar,\
        wc->TileGtk_QScrollBar_Widget, subcontrol).height()
    printf("SC_ScrollBarAddLine: x=%d, y=%d, w=%d, h=%d\n", SC_PRINT_INFO(QStyle::SC_ScrollBarAddLine));
    printf("SC_ScrollBarSubLine: x=%d, y=%d, w=%d, h=%d\n", SC_PRINT_INFO(QStyle::SC_ScrollBarSubLine));
    printf("SC_ScrollBarAddPage: x=%d, y=%d, w=%d, h=%d\n", SC_PRINT_INFO(QStyle::SC_ScrollBarAddPage));
    printf("SC_ScrollBarSubPage: x=%d, y=%d, w=%d, h=%d\n", SC_PRINT_INFO(QStyle::SC_ScrollBarSubPage));
    printf("SC_ScrollBarFirst: x=%d, y=%d, w=%d, h=%d\n", SC_PRINT_INFO(QStyle::SC_ScrollBarFirst));
    printf("SC_ScrollBarLast: x=%d, y=%d, w=%d, h=%d\n", SC_PRINT_INFO(QStyle::SC_ScrollBarLast));
#endif
  }
  memcpy(wc_array[1], wc_array[0], sizeof(TileGtk_WidgetCache));
  wc_array[0]->orientation = TTK_ORIENT_HORIZONTAL;
  wc_array[1]->orientation = TTK_ORIENT_VERTICAL;
  /* Save the name of the current theme... */
  Tcl_SetVar(interp, "ttk::theme::tilegtk::theme",
#ifdef TILEGTK_GTK_VERSION_3                    
             wc->TileGtk_Style->name(), TCL_GLOBAL_ONLY);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4                    
             wc->TileGtk_Style->objectName().toUtf8().data(), TCL_GLOBAL_ONLY);
#endif /* TILEGTK_GTK_VERSION_4 */
#endif
  Tcl_MutexUnlock(&tilegtkMutex);
  return TCL_OK;
}; /* Tileqt_SetStyle */

int Tileqt_GetPixelMetric(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
/*
  PM_TabBarTabOverlap         - number of pixels the tabs should overlap.
  PM_TabBarTabHSpace          - extra space added to the tab width.
  PM_TabBarTabVSpace          - extra space added to the tab height.
  PM_TabBarBaseHeight         - height of the area between the tab bar and the
                                tab pages.
  PM_TabBarBaseOverlap        - number of pixels the tab bar overlaps the
                                tab bar base.
  PM_TabBarScrollButtonWidth
  PM_TabBarTabShiftHorizontal - horizontal pixel shift when a tab is selected.
  PM_TabBarTabShiftVertical   - vertical pixel shift when a tab is selected.
*/
  static const char *Methods[] = {
    "-PM_TabBarTabOverlap",       "-PM_TabBarTabHSpace",
    "-PM_TabBarTabVSpace",        "-PM_TabBarBaseHeight",
    "-PM_TabBarBaseOverlap",      "-PM_TabBarTabShiftHorizontal",
    "-PM_TabBarTabShiftVertical", "-PM_TabBarScrollButtonWidth",
    "-PM_DefaultFrameWidth",
    (char *) NULL
  };
  enum methods {
    PM_TabBarTabOverlap,       PM_TabBarTabHSpace,
    PM_TabBarTabVSpace,        PM_TabBarBaseHeight,
    PM_TabBarBaseOverlap,      PM_TabBarTabShiftHorizontal,
    PM_TabBarTabShiftVertical, PM_TabBarScrollButtonWidth,
    PM_DefaultFrameWidth
  };
  int index, pixels = 0;
  TileGtk_WidgetCache **wc_array = (TileGtk_WidgetCache **) clientData;
  TileGtk_WidgetCache *wc = wc_array[0];
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "pixel_metric_identifier");
    return TCL_ERROR;
  }
  if (Tcl_GetIndexFromObj(interp, objv[1], (const char **) Methods,
                            "method", 0, &index) != TCL_OK) {
    return TCL_ERROR;
  }
#ifdef TILEGTK_GTK_VERSION_3
#define PM(pm) (wc->TileGtk_Style->pixelMetric(QStyle::pm, \
                                              wc->TileGtk_GTKabBar_Widget))
#define PM2(pm) (wc->TileGtk_Style->pixelMetric(QStyle::pm, \
                                              wc->TileGtk_GTKabWidget_Widget))
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
#ifndef QStyleOptionTabV2
#define QStyleOptionTabV2 QStyleOptionTab
#endif /* QStyleOptionTabV2 */
#define PM(pm) (wc->TileGtk_Style->pixelMetric(QStyle::pm, &option, \
                                              wc->TileGtk_GTKabBar_Widget))
#define PM2(pm) (wc->TileGtk_Style->pixelMetric(QStyle::pm, &option, \
                                              wc->TileGtk_GTKabWidget_Widget))
#endif /* TILEGTK_GTK_VERSION_4 */
  Tcl_MutexLock(&tilegtkMutex);
#if 0
#ifdef TILEGTK_GTK_VERSION_4
  QStyleOptionTabV2 option;
  option.initFrom(wc->TileGtk_GTKabBar_Widget);
#endif /* TILEGTK_GTK_VERSION_4 */
  switch ((enum methods) index) {
    case PM_TabBarTabOverlap:  {pixels = PM(PM_TabBarTabOverlap);  break;}
    case PM_TabBarTabHSpace:   {pixels = PM(PM_TabBarTabHSpace);   break;}
    case PM_TabBarTabVSpace:   {pixels = PM(PM_TabBarTabVSpace);   break;}
    case PM_TabBarBaseOverlap: {pixels = PM(PM_TabBarBaseOverlap); break;}
    case PM_TabBarBaseHeight:  {pixels = PM2(PM_TabBarBaseHeight); break;}
    case PM_TabBarTabShiftHorizontal: {pixels = PM(PM_TabBarTabShiftHorizontal);
                                       break;}
    case PM_TabBarTabShiftVertical:   {pixels = PM(PM_TabBarTabShiftVertical);
                                       break;}
    case PM_TabBarScrollButtonWidth:  {pixels = PM(PM_TabBarScrollButtonWidth);
                                       break;}
    case PM_DefaultFrameWidth:        {pixels = PM(PM_DefaultFrameWidth);
                                       break;}
  }
#endif
  Tcl_MutexUnlock(&tilegtkMutex);
  Tcl_SetObjResult(interp, Tcl_NewIntObj(pixels));
  return TCL_OK;
}; /* Tileqt_GetPixelMetric */

int Tileqt_GetStyleHint(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
/*
  SH_TabBar_Alignment         - The alignment for tabs in a GTKabBar.
                                Possible values are Gtk::AlignLeft,
                                Gtk::AlignCenter and Gtk::AlignRight.
*/
  static const char *Methods[] = {
    "-SH_TabBar_Alignment",
    (char *) NULL
  };
  enum methods {
    SH_TabBar_Alignment
  };
  int index, hint = 0;
  const char *pstr = "";
  TileGtk_WidgetCache **wc_array = (TileGtk_WidgetCache **) clientData;
  TileGtk_WidgetCache *wc = wc_array[0];
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "style_hint_identifier");
    return TCL_ERROR;
  }
  if (Tcl_GetIndexFromObj(interp, objv[1], (const char **) Methods,
                            "method", 0, &index) != TCL_OK) {
    return TCL_ERROR;
  }
#if 0
  switch ((enum methods) index) {
    case SH_TabBar_Alignment:  {stylehint = QStyle::SH_TabBar_Alignment; break;}
  }
  Tcl_MutexLock(&tilegtkMutex);
  hint = wc->TileGtk_Style->styleHint(stylehint);
  Tcl_MutexUnlock(&tilegtkMutex);
  switch (hint) {
    case Gtk::AlignLeft:    {pstr = "Gtk::AlignLeft";    break;}
    case Gtk::AlignRight:   {pstr = "Gtk::AlignRight";   break;}
    case Gtk::AlignCenter:  {pstr = "Gtk::AlignCenter";  break;}
#ifdef TILEGTK_GTK_VERSION_3
    case Gtk::AlignAuto:    {pstr = "Gtk::AlignAuto";    break;}
#endif /* TILEGTK_GTK_VERSION_3 */
    case Gtk::AlignJustify: {pstr = "Gtk::AlignJustify"; break;}
    case Gtk::AlignTop:     {pstr = "Gtk::AlignTop";     break;}
    case Gtk::AlignBottom:  {pstr = "Gtk::AlignBottom";  break;}
    case Gtk::AlignVCenter: {pstr = "Gtk::AlignVCenter"; break;}
    case Gtk::AlignHCenter: {pstr = "Gtk::AlignHCenter"; break;}
    default: {
      Tcl_SetObjResult(interp, Tcl_NewIntObj(hint));
      return TCL_OK;
    }
  }
#endif
  Tcl_SetResult(interp, (char *) pstr, TCL_STATIC);
  return TCL_OK;
}; /* Tileqt_GetStyleHint */

int Tileqt_GetSubControlMetrics(ClientData clientData, Tcl_Interp *interp,
                                 int objc, Tcl_Obj *const objv[]) {
  /*
   * QStyle::SC_ScrollBarAddLine - scrollbar add line (i.e. down/right arrow). 
   * QStyle::SC_ScrollBarSubLine - scrollbar sub line (i.e. up/left arrow). 
   * QStyle::SC_ScrollBarAddPage - scrollbar add page (i.e. page down). 
   * QStyle::SC_ScrollBarSubPage - scrollbar sub page (i.e. page up). 
   * QStyle::SC_ScrollBarFirst   - scrollbar first line (i.e. home). 
   * QStyle::SC_ScrollBarLast    - scrollbar last line (i.e. end). 
   * QStyle::SC_ScrollBarSlider  - scrollbar slider handle. 
   * QStyle::SC_ScrollBarGroove  - special subcontrol which contains the area
   *                               in which the slider handle may move.
   */
  static const char *Methods[] = {
    "-SC_ScrollBarAddLine",       "-SC_ScrollBarSubLine",
    "-SC_ScrollBarAddPage",       "-SC_ScrollBarSubPage",
    "-SC_ScrollBarFirst",         "-SC_ScrollBarLast",
    "-SC_ScrollBarSlider",        "-SC_ScrollBarGroove",
    (char *) NULL
  };
  enum methods {
    SC_ScrollBarAddLine,       SC_ScrollBarSubLine,
    SC_ScrollBarAddPage,       SC_ScrollBarSubPage,
    SC_ScrollBarFirst,         SC_ScrollBarLast,
    SC_ScrollBarSlider,        SC_ScrollBarGroove
  };
  int index;
  Tcl_Obj *result;
  TileGtk_WidgetCache **wc_array = (TileGtk_WidgetCache **) clientData;
  TileGtk_WidgetCache *wc = wc_array[0];
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "sub_control_identifier");
    return TCL_ERROR;
  }
  if (Tcl_GetIndexFromObj(interp, objv[1], (const char **) Methods,
                            "method", 0, &index) != TCL_OK) {
    return TCL_ERROR;
  }
#if 0
  QStyle::ComplexControl control = QStyle::CC_ScrollBar;
  QWidget *widget = 0;
  QStyle::SubControl subcontrol = QStyle::SC_None;
#ifdef TILEGTK_GTK_VERSION_4
  QStyleOptionComplex *option = NULL;
#endif /* TILEGTK_GTK_VERSION_4 */

  if ((enum methods) index >= SC_ScrollBarAddLine &&
      (enum methods) index <= SC_ScrollBarGroove) {
    widget  = wc->TileGtk_QScrollBar_Widget;
    control = QStyle::CC_ScrollBar;
#ifdef TILEGTK_GTK_VERSION_4
    option  = new QStyleOptionComplex();
    if (option) option->initFrom(widget);
#endif /* TILEGTK_GTK_VERSION_4 */
  }
  switch ((enum methods) index) {
    case SC_ScrollBarAddLine: {
      subcontrol = QStyle::SC_ScrollBarAddLine; break;
    }
    case SC_ScrollBarSubLine: {
      subcontrol = QStyle::SC_ScrollBarSubLine; break;
    }
    case SC_ScrollBarAddPage: {
      subcontrol = QStyle::SC_ScrollBarAddPage; break;
    }
    case SC_ScrollBarSubPage: {
      subcontrol = QStyle::SC_ScrollBarSubPage; break;
    }
    case SC_ScrollBarFirst: {
      subcontrol = QStyle::SC_ScrollBarFirst;   break;
    }
    case SC_ScrollBarLast: {
      subcontrol = QStyle::SC_ScrollBarLast;    break;
    }
    case SC_ScrollBarSlider: {
      subcontrol = QStyle::SC_ScrollBarSlider;  break;
    }
    case SC_ScrollBarGroove: {
      subcontrol = QStyle::SC_ScrollBarGroove;  break;
    }
  }
  Tcl_MutexLock(&tilegtkMutex);
#ifdef TILEGTK_GTK_VERSION_3
  QRect rc = wc->TileGtk_Style->
    querySubControlMetrics(control, widget, subcontrol);
#endif /* TILEGTK_GTK_VERSION_3 */
#ifdef TILEGTK_GTK_VERSION_4
  QRect rc = wc->TileGtk_Style->
    subControlRect(control, option, subcontrol, widget);
  if (option) delete option;
#endif /* TILEGTK_GTK_VERSION_4 */
  Tcl_MutexUnlock(&tilegtkMutex);
  result = Tcl_NewListObj(0, NULL);
  Tcl_ListObjAppendElement(interp, result, Tcl_NewIntObj(rc.x()));
  Tcl_ListObjAppendElement(interp, result, Tcl_NewIntObj(rc.y()));
  Tcl_ListObjAppendElement(interp, result, Tcl_NewIntObj(rc.width()));
  Tcl_ListObjAppendElement(interp, result, Tcl_NewIntObj(rc.height()));
#endif
  Tcl_SetObjResult(interp, result);
  return TCL_OK;
}; /* Tileqt_GetSubControlMetrics */

extern "C" int DLLEXPORT
Tilegtk_Init(Tcl_Interp *interp)
{
    Ttk_Theme themePtr;
    Tk_Window tkwin;
    char tmpScript[1024];
    TileGtk_WidgetCache **wc = NULL;
    GtkSettings *settings = NULL;
    gchar       *strval = NULL;

    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL)
        return TCL_ERROR;
    if (Tk_InitStubs(interp,  TK_VERSION,  0) == NULL)
        return TCL_ERROR;
    if (Ttk_InitStubs(interp) == NULL)
        return TCL_ERROR;

    tkwin = Tk_MainWindow(interp);
    if (tkwin == NULL) return TCL_ERROR;

    themePtr  = Ttk_CreateTheme(interp, "tilegtk", NULL);
    if (!themePtr) return TCL_ERROR;

    /*
     * Initialise Gtk:
     */
    Tcl_MutexLock(&tilegtkMutex);
    wc = TileGtk_CreateGtkApp(interp);
    ++TileGtk_GtkAppCreated;

    /*
     * Register the various widgets...
     */
    TileGtk_Init_Background(interp, wc, themePtr);
    TileGtk_Init_Button(interp, wc, themePtr);
    TileGtk_Init_CheckButton(interp, wc, themePtr);
    TileGtk_Init_RadioButton(interp, wc, themePtr);
    TileGtk_Init_Labelframe(interp, wc, themePtr);
    TileGtk_Init_Entry(interp, wc, themePtr);
    TileGtk_Init_Menubutton(interp, wc, themePtr);
    TileGtk_Init_Scrollbar(interp, wc, themePtr);
    TileGtk_Init_Scale(interp, wc, themePtr);
    TileGtk_Init_Progress(interp, wc, themePtr);
#if 0
    TileGtk_Init_ToolButton(interp, wc, themePtr);
    TileGtk_Init_Combobox(interp, wc, themePtr);
    TileGtk_Init_Notebook(interp, wc, themePtr);
    TileGtk_Init_TreeView(interp, wc, themePtr);
    TileGtk_Init_Paned(interp, wc, themePtr);
    TileGtk_Init_SizeGrip(interp, wc, themePtr);
    //TileGtk_Init_Separator(interp, wc, themePtr);
    //TileGtk_Init_Arrows(interp, wc, themePtr);
#endif
    Tcl_CreateExitHandler(&TileGtk_ExitProc, 0);
    //Tcl_CreateThreadExitHandler(&TileGtk_ExitProc, 0);
    
    /*
     * Register the TileGtk package...
     */
    Tcl_CreateObjCommand(interp, "ttk::theme::tilegtk::settingsProperty",
                         Tileqt_SettingsProperty, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp, "ttk::theme::tilegtk::widgetStyleProperty",
                         Tileqt_WidgetStyleProperty, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp, "ttk::theme::tilegtk::currentThemeName",
                         Tileqt_ThemeName, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp, "ttk::theme::tilegtk::gtkDirectory",
                         Tileqt_GtkDirectory, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp, "ttk::theme::tilegtk::setStyle",
                         Tileqt_SetStyle, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp, "ttk::theme::tilegtk::gtk_method",
                         Tileqt_gtk_method, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp,
                         "ttk::theme::tilegtk::currentThemeColour",
                         Tileqt_ThemeColour, (ClientData) wc, NULL);
#if 0
    Tcl_CreateObjCommand(interp,
                         "ttk::theme::tilegtk::setPalette",
                         Tileqt_SetPalette, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp,
                         "ttk::theme::tilegtk::getPixelMetric",
                         Tileqt_GetPixelMetric, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp,
                         "ttk::theme::tilegtk::getStyleHint",
                         Tileqt_GetStyleHint, (ClientData) wc, NULL);
    Tcl_CreateObjCommand(interp,
                         "ttk::theme::tilegtk::getSubControlMetrics",
                         Tileqt_GetSubControlMetrics, (ClientData) wc, NULL);
#endif
    /* Save the name of the current theme... */
    strcpy(tmpScript, "namespace eval ttk::theme::tilegtk { variable theme ");
    settings = gtk_settings_get_default();
    if (settings) {
      g_object_get(settings, "gtk-theme-name", &strval, NULL);
      strcat(tmpScript, "{");
      if (strval) {
        strcat(tmpScript, strval);
        g_free (strval);
      }
      strcat(tmpScript, "}");
    } else {
      strcat(tmpScript, "{}");
    }
    strcat(tmpScript, " };");
    Tcl_MutexUnlock(&tilegtkMutex);
    
    if (Tcl_Eval(interp, tmpScript) != TCL_OK) {
      return TCL_ERROR;
    }
    if (Tcl_Eval(interp, initScript) != TCL_OK) {
      return TCL_ERROR;
    }
    Tcl_PkgProvide(interp, "ttk::theme::tilegtk", PACKAGE_VERSION);
    Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION);
    return TCL_OK;
}; /* TileGtk_Init */

int DLLEXPORT
TileGtk_Finish(Tcl_Interp *interp)
{
    Tcl_MutexLock(&tilegtkMutex);
    if (TileGtk_GtkAppCreated < 0) {Tcl_MutexUnlock(&tilegtkMutex); return 0;}
    --TileGtk_GtkAppCreated;
    if (TileGtk_GtkAppCreated == 0) TileGtk_DestroyGtkApp();
    Tcl_MutexUnlock(&tilegtkMutex);
    return 0;
}; /* TileGtk_Finish */

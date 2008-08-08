# - try to find GTK (and glib) and GTKGLArea
#  GTK_INCLUDE_DIR   - Directories to include to use GTK
#  GTK_LIBRARIES     - Files to link against to use GTK
#  GTK_FOUND         - GTK was found
#  GTK_GL_FOUND      - GTK's GL features were found

SET ( GTK_ADDITIONAL_PATHS "C:/Program Files (x86)/gtk+-bundle-2.12.11" )

FOREACH ( path ${GTK_ADDITIONAL_PATHS} )
  SET ( GTK_ADDITIONAL_INCLUDE_PATHS ${GTK_ADDITIONAL_INCLUDE_PATHS}
                                     "${path}/include" )
  SET ( GTK_ADDITIONAL_LIBRARY_PATHS ${GTK_ADDITIONAL_LIBRARY_PATHS}
                                     "${path}/lib" )
ENDFOREACH ( path )

FIND_PATH( GTK_gtk_INCLUDE_PATH NAMES gtk/gtk.h
  PATH_SUFFIXES gtk-2.0 gtk-1.2 gtk20 gtk12 gtk
  PATHS
  /usr/include
  /usr/include/gtk-2.0
  /usr/openwin/share/include
  /usr/openwin/include
  /opt/gnome/include
  ${GTK_ADDITIONAL_INCLUDE_PATHS}
)

FIND_PATH( GTK_gdk_INCLUDE_PATH NAMES gdkconfig.h
  PATH_SUFFIXES gtk-2.0 gtk-1.2 gtk20 gtk12
  PATHS
  /usr/lib/gtk-2.0/include/
  /usr/include
  /usr/include/gtk-2.0
  /usr/openwin/share/include
  /usr/openwin/include
  /opt/gnome/include
  ${GTK_ADDITIONAL_LIBRARY_PATHS}/gtk-2.0/include
)

# Some Linux distributions (e.g. Red Hat) have glibconfig.h
# and glib.h in different directories, so we need to look
# for both.
#  - Atanas Georgiev <atanas@cs.columbia.edu>

FIND_PATH( GTK_glibconfig_INCLUDE_PATH NAMES glibconfig.h
  PATHS
  /usr/lib/glib-2.0/include
  /usr/openwin/share/include
  /usr/local/include/glib12
  /usr/lib/glib/include
  /usr/local/lib/glib/include
  /opt/gnome/include
  /opt/gnome/lib/glib/include
  ${GTK_ADDITIONAL_LIBRARY_PATHS}/glib-2.0/include
)

FIND_PATH( GTK_glib_INCLUDE_PATH NAMES glib.h
  PATH_SUFFIXES gtk-2.0 glib-2.0 gtk-1.2 glib-1.2 glib20 glib12
  PATHS
  /usr/include
  /usr/openwin/share/include
  /usr/lib/glib/include
  /opt/gnome/include
  ${GTK_ADDITIONAL_INCLUDE_PATHS}
)

FIND_PATH( GTK_gtkgl_INCLUDE_PATH NAMES gtkgl/gtkglarea.h
  PATHS /usr/openwin/share/include
        /opt/gnome/include
  ${GTK_ADDITIONAL_INCLUDE_PATHS}
)

FIND_PATH( GTK_cairo_INCLUDE_PATH NAMES cairo.h
  PATH_SUFFIXES cairo
  PATHS
  /usr/include
  /usr/include/gtk-2.0
  /usr/openwin/share/include
  /usr/openwin/include
  /opt/gnome/include
  ${GTK_ADDITIONAL_INCLUDE_PATHS}
)

FIND_PATH( GTK_pango_INCLUDE_PATH NAMES pango/pango.h
  PATH_SUFFIXES pango pango-1.0
  PATHS
  /usr/include
  /usr/include/gtk-2.0
  /usr/openwin/share/include
  /usr/openwin/include
  /opt/gnome/include
  ${GTK_ADDITIONAL_INCLUDE_PATHS}
)

FIND_PATH( GTK_atk_INCLUDE_PATH NAMES atk/atkobject.h
  PATH_SUFFIXES atk atk-1.0
  PATHS
  /usr/include
  /usr/include/gtk-2.0
  /usr/openwin/share/include
  /usr/openwin/include
  /opt/gnome/include
  ${GTK_ADDITIONAL_INCLUDE_PATHS}
)

FIND_LIBRARY( GTK_gtkgl_LIBRARY gtkgl
  /usr/openwin/lib
  /opt/gnome/lib
  /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

#
# The 12 suffix is thanks to the FreeBSD ports collection
#

FIND_LIBRARY( GTK_gtk_LIBRARY
  NAMES gtk-x11-2.0 gtk-win32-2.0 gtk-2.0 gtk20 gtk-win32
        gtk-x11-1.2 gtk-win32-1.2 gtk-1.2 gtk12 gtk-x11 gtk
  PATHS /usr/openwin/lib
        /opt/gnome/lib
        /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_gdk_LIBRARY
  NAMES  gdk-x11-2.0 gdk-win32-2.0 gdk-2.0 gdk20 gdk-win32
         gdk-x11-1.2 gdk-win32-1.2 gdk-1.2 gdk12 gdk-x11 gdk
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_gmodule_LIBRARY
  NAMES  gmodule-2.0 gmodule20 gmodule-1.2 gmodule12 gmodule
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_gobject_LIBRARY
  NAMES  gobject-2.0 gobject20 gobject-1.2 gobject12 gobject
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_glib_LIBRARY
  NAMES  glib-2.0 glib20 glib-1.2 glib12 glib
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_Xi_LIBRARY 
  NAMES Xi 
  PATHS /usr/openwin/lib 
        /opt/gnome/lib 
        /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
  ) 

FIND_LIBRARY( GTK_gthread_LIBRARY
  NAMES  gthread-2.0 gthread20 gthread-1.2 gthread12 gthread
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_cairo_LIBRARY
  NAMES  cairo-2.0 cairo20 cairo-1.2 cairo12 cairo
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_pango_LIBRARY
  NAMES  pango-2.0 pango20 pango-1.2 pango12 pango
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_atk_LIBRARY
  NAMES  atk-2.0 atk20 atk-1.2 atk12 atk
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

FIND_LIBRARY( GTK_gio_LIBRARY
  NAMES  gio-2.0 gio20 gio-1.2 gio12 gio
  PATHS  /usr/openwin/lib
         /opt/gnome/lib
         /usr/lib
  ${GTK_ADDITIONAL_LIBRARY_PATHS}
)

IF ( GTK_LOGGING_ENABLED )
  MESSAGE ( STATUS "   + gtk.h:        ${GTK_gtk_INCLUDE_PATH}" )
  MESSAGE ( STATUS "   + gdkconfig.h:  ${GTK_gdk_INCLUDE_PATH}" )
  MESSAGE ( STATUS "   + glibconfig.h: ${GTK_glibconfig_INCLUDE_PATH}" )
  MESSAGE ( STATUS "   + glib.h:       ${GTK_glib_INCLUDE_PATH}" )
  MESSAGE ( STATUS "   + gtkglarea.h:  ${GTK_gtkgl_INCLUDE_PATH}" )
  MESSAGE ( STATUS "   + cairo.h:      ${GTK_cairo_INCLUDE_PATH}" )
  MESSAGE ( STATUS "   + pango.h:      ${GTK_pango_INCLUDE_PATH}" )
  MESSAGE ( STATUS "   + atkobject.h:  ${GTK_atk_INCLUDE_PATH}" )
  MESSAGE ( STATUS "   + gtk:          ${GTK_gtk_LIBRARY}" )
  MESSAGE ( STATUS "   + gdk:          ${GTK_gdk_LIBRARY}" )
  MESSAGE ( STATUS "   + glib:         ${GTK_glib_LIBRARY}" )
  MESSAGE ( STATUS "   + gmodule:      ${GTK_gmodule_LIBRARY}" )
  MESSAGE ( STATUS "   + gobject:      ${GTK_gobject_LIBRARY}" )
  MESSAGE ( STATUS "   + gthread:      ${GTK_gthread_LIBRARY}" )
  MESSAGE ( STATUS "   + gio:          ${GTK_gio_LIBRARY}" )
  MESSAGE ( STATUS "   + cairo:        ${GTK_cairo_LIBRARY}" )
  MESSAGE ( STATUS "   + pango:        ${GTK_pango_LIBRARY}" )
  MESSAGE ( STATUS "   + atk:          ${GTK_atk_LIBRARY}" )
  MESSAGE ( STATUS "   + gtkgl:        ${GTK_gtkgl_LIBRARY}" )
  MESSAGE ( STATUS "   + Xi:           ${GTK_Xi_LIBRARY}" )
ENDIF ( GTK_LOGGING_ENABLED )

# MESSAGE ( STATUS "    GTK_gtk_INCLUDE_PATH: "
#                     ${GTK_gtk_INCLUDE_PATH} )
# MESSAGE ( STATUS "    GTK_glibconfig_INCLUDE_PATH: "
#                     ${GTK_glibconfig_INCLUDE_PATH} )
# MESSAGE ( STATUS "    GTK_glib_INCLUDE_PATH: "
#                     ${GTK_glib_INCLUDE_PATH} )
# MESSAGE ( STATUS "    GTK_gtk_LIBRARY: "
#                     ${GTK_gtk_LIBRARY} )
# MESSAGE ( STATUS "    GTK_glib_LIBRARY: "
#                     ${GTK_glib_LIBRARY} )

IF(GTK_gtk_INCLUDE_PATH
   AND GTK_glibconfig_INCLUDE_PATH
   AND GTK_glib_INCLUDE_PATH
   AND GTK_gtk_LIBRARY
   AND GTK_glib_LIBRARY)

  # Assume that if gtk and glib were found, the other
  # supporting libraries have also been found.

  SET( GTK_FOUND "YES" )
  SET( GTK_INCLUDE_DIR  ${GTK_gtk_INCLUDE_PATH}
                        ${GTK_glibconfig_INCLUDE_PATH}
                        ${GTK_glib_INCLUDE_PATH} )

  IF(GTK_gdk_INCLUDE_PATH)
    SET(GTK_INCLUDE_DIR ${GTK_INCLUDE_DIR} ${GTK_gdk_INCLUDE_PATH})
  ENDIF(GTK_gdk_INCLUDE_PATH)
  IF(GTK_cairo_INCLUDE_PATH)
    SET(GTK_INCLUDE_DIR ${GTK_INCLUDE_DIR} ${GTK_cairo_INCLUDE_PATH})
  ENDIF(GTK_cairo_INCLUDE_PATH)
  IF(GTK_pango_INCLUDE_PATH)
    SET(GTK_INCLUDE_DIR ${GTK_INCLUDE_DIR} ${GTK_pango_INCLUDE_PATH})
  ENDIF(GTK_pango_INCLUDE_PATH)
  IF(GTK_atk_INCLUDE_PATH)
    SET(GTK_INCLUDE_DIR ${GTK_INCLUDE_DIR} ${GTK_atk_INCLUDE_PATH})
  ENDIF(GTK_atk_INCLUDE_PATH)

  SET( GTK_LIBRARIES  ${GTK_gtk_LIBRARY}
                      ${GTK_glib_LIBRARY} )

  # IF(GTK_gdk_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_gdk_LIBRARY})
  # ENDIF(GTK_gdk_LIBRARY)
  # IF(GTK_gmodule_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_gmodule_LIBRARY})
  # ENDIF(GTK_gmodule_LIBRARY)
  # IF(GTK_gobject_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_gobject_LIBRARY})
  # ENDIF(GTK_gobject_LIBRARY)
  # IF(GTK_gthread_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_gthread_LIBRARY})
  # ENDIF(GTK_gthread_LIBRARY)
  # IF(GTK_Xi_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_Xi_LIBRARY})
  # ENDIF(GTK_Xi_LIBRARY)
  # IF(GTK_cairo_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_cairo_LIBRARY})
  # ENDIF(GTK_cairo_LIBRARY)
  # IF(GTK_pango_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_pango_LIBRARY})
  # ENDIF(GTK_pango_LIBRARY)
  # IF(GTK_atk_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_atk_LIBRARY})
  # ENDIF(GTK_atk_LIBRARY)
  # IF(GTK_gio_LIBRARY)
  #   SET(GTK_LIBRARIES ${GTK_LIBRARIES} ${GTK_gio_LIBRARY})
  # ENDIF(GTK_gio_LIBRARY)

  IF(GTK_gtkgl_INCLUDE_PATH AND GTK_gtkgl_LIBRARY)
    SET( GTK_GL_FOUND "YES" )
    SET( GTK_INCLUDE_DIR  ${GTK_INCLUDE_DIR}
                          ${GTK_gtkgl_INCLUDE_PATH} )
    SET( GTK_LIBRARIES  ${GTK_gtkgl_LIBRARY} ${GTK_LIBRARIES} )
    MARK_AS_ADVANCED(
      GTK_gtkgl_LIBRARY
      GTK_gtkgl_INCLUDE_PATH
      )
  ENDIF(GTK_gtkgl_INCLUDE_PATH AND GTK_gtkgl_LIBRARY)

ENDIF(GTK_gtk_INCLUDE_PATH
   AND GTK_glibconfig_INCLUDE_PATH
   AND GTK_glib_INCLUDE_PATH
   AND GTK_gtk_LIBRARY
   AND GTK_glib_LIBRARY)

MARK_AS_ADVANCED(
  GTK_gdk_LIBRARY
  GTK_glib_INCLUDE_PATH
  GTK_glib_LIBRARY
  GTK_glibconfig_INCLUDE_PATH
  GTK_gmodule_LIBRARY
  GTK_gthread_LIBRARY
  GTK_Xi_LIBRARY
  GTK_gtk_INCLUDE_PATH
  GTK_gtk_LIBRARY
  GTK_gtkgl_INCLUDE_PATH
  GTK_gtkgl_LIBRARY
)

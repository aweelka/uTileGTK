CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )

## ===========================================================================
##  Project Information
## ===========================================================================
PROJECT ( tilegtk )
## Package version information.
SET ( PKG_NAME          ${PROJECT_NAME} )
SET ( PKG_MAJOR_VERSION 0 )
SET ( PKG_MINOR_VERSION 1 )
SET ( PKG_BUILD_VERSION 0 )
SET ( PKG_VERSION
     "${PKG_MAJOR_VERSION}.${PKG_MINOR_VERSION}" )
SET ( PKG_NAME_VERSION  ${PKG_NAME}-${PKG_VERSION} )
SET ( PKG_VENDOR        "Georgios Petasis" )
SET ( PKG_HOME_DIR      ${PROJECT_SOURCE_DIR} )

SET ( NO_MSVCRT ON )

SET ( PKG_SOURCES generic/tileGtk_Init.cpp
                  generic/tileGtk_GtkApp.cpp
                  generic/tileGtk_Utilities.cpp
                  generic/tileGtk_Button.cpp
                  generic/tileGtk_CheckButton.cpp
                  generic/tileGtk_RadioButton.cpp
                  generic/tileGtk_Menubutton.cpp
                  generic/tileGtk_ToolButton.cpp
                  generic/tileGtk_Combobox.cpp
                  generic/tileGtk_Scrollbar.cpp
                  generic/tileGtk_Notebook.cpp
                  generic/tileGtk_TreeView.cpp
                  generic/tileGtk_Progress.cpp
                  generic/tileGtk_Paned.cpp
                  generic/tileGtk_SizeGrip.cpp
                  generic/tileGtk_Separator.cpp
                  generic/tileGtk_Arrows.cpp )

SET ( PKG_SOURCES generic/tileGtk_Init.cpp
                  generic/tileGtk_GtkApp.cpp
                  generic/tileGtk_Utilities.cpp
                  generic/tileGtk_Background.cpp
                  generic/tileGtk_Button.cpp
                  generic/tileGtk_CheckButton.cpp
                  generic/tileGtk_RadioButton.cpp
                  generic/tileGtk_Labelframe.cpp
                  generic/tileGtk_Entry.cpp
                  generic/tileGtk_Menubutton.cpp
                  generic/tileGtk_Scrollbar.cpp
                  generic/tileGtk_Scale.cpp
                  generic/tileGtk_Progress.cpp
)

MESSAGE ( STATUS "===========================================================" )
MESSAGE ( STATUS " Welcome to the ${PKG_NAME} ${PKG_VERSION} build system!" )
MESSAGE ( STATUS "  * Selected generator:  ${CMAKE_GENERATOR}" )
MESSAGE ( STATUS "  * Operating System ID: "
        ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_VERSION}-${CMAKE_SYSTEM_PROCESSOR} )
MESSAGE ( STATUS "  * Installation Directory: " ${CMAKE_INSTALL_PREFIX} )
MESSAGE ( STATUS "===========================================================" )

## ===========================================================================
##  Locate Tcl/Tk
## ===========================================================================
MESSAGE ( STATUS "Searching for Tcl/Tk..." )
FIND_PACKAGE ( TCL REQUIRED )
FIND_PACKAGE ( TclStub REQUIRED )
MESSAGE ( STATUS "  TCL_TCLSH:               " ${TCL_TCLSH} )
MESSAGE ( STATUS "  TCL_INCLUDE_PATH:        " ${TCL_INCLUDE_PATH} )
MESSAGE ( STATUS "  TCL_STUB_LIBRARY:        " ${TCL_STUB_LIBRARY} )
MESSAGE ( STATUS "  TCL_LIBRARY:             " ${TCL_LIBRARY} )
MESSAGE ( STATUS "  TK_WISH:                 " ${TK_WISH} )
MESSAGE ( STATUS "  TK_INCLUDE_PATH:         " ${TK_INCLUDE_PATH} )
MESSAGE ( STATUS "  TK_STUB_LIBRARY:         " ${TK_STUB_LIBRARY} )
MESSAGE ( STATUS "  TTK_STUB_LIBRARY:        " ${TTK_STUB_LIBRARY} )
MESSAGE ( STATUS "  TK_LIBRARY:              " ${TK_LIBRARY} )
STRING  ( REPLACE stub "" TCL_LIBRARY_STATIC   ${TCL_STUB_LIBRARY} )
STRING  ( REPLACE stub "" TK_LIBRARY_STATIC    ${TK_STUB_LIBRARY} )
MESSAGE ( STATUS "  TCL_LIBRARY_STATIC:      " ${TCL_LIBRARY_STATIC} )
MESSAGE ( STATUS "  TK_LIBRARY_STATIC:       " ${TK_LIBRARY_STATIC} )

IF ( WIN32 AND NO_MSVCRT )
  STRING ( REPLACE /MD  /MT  CMAKE_C_FLAGS_RELEASE   ${CMAKE_C_FLAGS_RELEASE} )
  STRING ( REPLACE /MDd /MTd CMAKE_C_FLAGS_DEBUG     ${CMAKE_C_FLAGS_DEBUG} )
  STRING ( REPLACE /MD  /MT  CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  STRING ( REPLACE /MDd /MTd CMAKE_CXX_FLAGS_DEBUG   ${CMAKE_CXX_FLAGS_DEBUG} )
  SET (    CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:MSVCRT.LIB" )
  SET (    CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} LIBCMT.LIB" )
  SET (    CMAKE_EXE_LINKER_FLAGS_DEBUG
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG} LIBCMTD.LIB" )
  SET (    CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} /nodefaultlib:MSVCRT.LIB" )
  SET (    CMAKE_SHARED_LINKER_FLAGS_RELEASE
        "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} LIBCMT.LIB" )
  SET (    CMAKE_SHARED_LINKER_FLAGS_DEBUG
        "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}
         /nodefaultlib:LIBCMT.LIB LIBCMTD.LIB" )
  ADD_DEFINITIONS ( -D_STATIC_CPPLIB )
  ADD_DEFINITIONS ( -D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1 )
  ADD_DEFINITIONS ( -D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT=1 )
ENDIF ( WIN32 AND NO_MSVCRT )

IF ( WIN32 )
  ADD_DEFINITIONS ( -DWIN32 )
  ADD_DEFINITIONS ( -D_WIN32 )
  ADD_DEFINITIONS ( -D_WINDOWS )
  ADD_DEFINITIONS ( -D__WIN32__ )
ENDIF ( WIN32 )

ADD_DEFINITIONS     ( -DUSE_TCL_STUBS )
ADD_DEFINITIONS     ( -DUSE_TK_STUBS )
ADD_DEFINITIONS     ( -DUSE_TTK_STUBS )
ADD_DEFINITIONS     ( -DPACKAGE_NAME="${PKG_NAME}" )
ADD_DEFINITIONS     ( -DPACKAGE_VERSION="${PKG_VERSION}" )
INCLUDE_DIRECTORIES ( ${TCL_INCLUDE_PATH} )
INCLUDE_DIRECTORIES ( ${TK_INCLUDE_PATH} )
INCLUDE_DIRECTORIES ( ${PROJECT_SOURCE_DIR}/generic )
LINK_LIBRARIES      ( ${TCL_STUB_LIBRARY} )
LINK_LIBRARIES      ( ${TK_STUB_LIBRARY} )
IF ( UNIX )
  LINK_LIBRARIES      ( gdk_pixbuf_xlib-2.0 )
ENDIF ( UNIX )

## ===========================================================================
##  Locate GTK...
## ===========================================================================
MESSAGE ( STATUS "Searching for GTK..." )
FIND_PACKAGE ( GTK REQUIRED )

IF ( GTK_FOUND )
  MESSAGE ( STATUS "  GTK Found:" )
  INCLUDE_DIRECTORIES ( ${GTK_INCLUDE_DIR} )
  LINK_LIBRARIES      ( ${GTK_LIBRARIES} )
ENDIF ( GTK_FOUND )
MESSAGE ( STATUS "  GTK_INCLUDE_DIR:         " ${GTK_INCLUDE_DIR} )
MESSAGE ( STATUS "  GTK_LIBRARIES:           " ${GTK_LIBRARIES} )

FIND_PACKAGE ( X11 )

IF   ( WIN32 )
  SET ( PKG_TARGET_LIB_NAME lib${PKG_NAME}${PKG_VERSION} )
ELSE ( WIN32 )
  SET ( PKG_TARGET_LIB_NAME ${PKG_NAME}${PKG_VERSION} )
ENDIF ( WIN32 )
MESSAGE ( STATUS "      + Shared Library: ${PKG_TARGET_LIB_NAME}" )
ADD_LIBRARY ( ${PKG_TARGET_LIB_NAME} SHARED ${PKG_SOURCES} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${TK_STUB_LIBRARY} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${TTK_STUB_LIBRARY} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${TK_LIBRARY_STATIC} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${TCL_STUB_LIBRARY} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${TCL_LIBRARY_STATIC} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${GTK_LIBRARIES} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${X11_Xft_LIB} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${X11_Xscreensaver_LIB} )

FILE ( WRITE library/pkgIndex.tcl 
"package ifneeded ttk::theme::tilegtk ${PKG_VERSION} \\
  [list load [file join $dir lib${PKG_NAME}${PKG_VERSION}[info sharedlibextension]] tilegtk]" )

INSTALL ( TARGETS ${PKG_TARGET_LIB_NAME}
          RUNTIME DESTINATION ${PKG_TARGET_LIB_NAME}
          LIBRARY DESTINATION ${PKG_TARGET_LIB_NAME}
          ARCHIVE DESTINATION ${PKG_TARGET_LIB_NAME} )
INSTALL ( FILES library/pkgIndex.tcl library/tilegtk.tcl DESTINATION ${PKG_TARGET_LIB_NAME} )

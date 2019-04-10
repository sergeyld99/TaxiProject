# 

# - Try to find lpthread
# Once done this will define
#  LPTHREAD_FOUND - System has lpthread
#  LPTHREAD_INCLUDE_DIRS - The lpthread include directories
#  LPTHREAD_LIBRARIES - The libraries needed to use lpthread
#  LPTHREAD_DEFINITIONS - Compiler switches required for using lpthread

find_package(PkgConfig)
pkg_check_modules(PC_LPTHREAD QUIET )
set(LPTHREAD_DEFINITIONS ${PC_LPTHREAD_CFLAGS_OTHER})

find_path(LPTHREAD_INCLUDE_DIR pthread.h
          HINTS ${PC_LPTHREAD_INCLUDEDIR} ${PC_LPTHREAD_INCLUDE_DIRS}
          PATH_SUFFIXES lpthread )

find_library(LPTHREAD_LIBRARY NAMES 
             HINTS ${PC_LPTHREAD_LIBDIR} ${PC_LPTHREAD_LIBRARY_DIRS} )

set(LPTHREAD_LIBRARIES ${LPTHREAD_LIBRARY} )
set(LPTHREAD_INCLUDE_DIRS ${LPTHREAD_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LPTHREAD_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(lpthread  DEFAULT_MSG
                                  LPTHREAD_LIBRARY LPTHREAD_INCLUDE_DIR)
mark_as_advanced(LPTHREAD_INCLUDE_DIR LPTHREAD_LIBRARY )

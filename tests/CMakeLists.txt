project( simple )
cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

# header files
set (MAIN_INCLUDE ${PROJECT_SOURCE_DIR}) 
set (LIBBUDDY_INCLUDE ${PROJECT_SOURCE_DIR}/../lib/libbuddy) 
set (HIDAPI_INCLUDE ${PROJECT_SOURCE_DIR}/../lib/hidapi/hidapi) 
set (BUDDY_INCLUDE_DIRS ${MAIN_INCLUDE} ${LIBBUDDY_INCLUDE} ${HIDAPI_INCLUDE})

set( LIBBUDDY_SOURCES
    ${PROJECT_SOURCE_DIR}/../lib/libbuddy/support.c
    ${PROJECT_SOURCE_DIR}/../lib/libbuddy/utility.c
    ${PROJECT_SOURCE_DIR}/../lib/libbuddy/usbhid_buddy.c
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(HIDAPI_SOURCES ${PROJECT_SOURCE_DIR}/../lib/hidapi/windows/hid.c)
    set(EXTRA_LIBS ${IOKIT_LIBRARY} setupapi.lib)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(HIDAPI_SOURCES ${PROJECT_SOURCE_DIR}/../lib/hidapi/linux/hid.c)
    set(EXTRA_LIBS ${IOKIT_LIBRARY} udev)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(HIDAPI_SOURCES ${PROJECT_SOURCE_DIR}/../lib/hidapi/mac/hid.c)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
    mark_as_advanced(IOKIT_LIBRARY CORE_FOUNDATION_LIBRARY)
    set(EXTRA_LIBS ${IOKIT_LIBRARY} ${CORE_FOUNDATION_LIBRARY})
else ()
    message( FATAL_ERROR "The host build platform is not supported." )
endif()

set (BUDDY_SOURCES ${LIBBUDDY_SOURCES} ${HIDAPI_SOURCES})

include_directories(${BUDDY_INCLUDE_DIRS})
add_executable (testLibBuddy testLibBuddy.cpp ${BUDDY_SOURCES})
target_link_libraries(testLibBuddy ${EXTRA_LIBS})
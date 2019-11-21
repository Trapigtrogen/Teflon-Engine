cmake_minimum_required(VERSION 3.4.1)

# build native_app_glue as a static lib
add_library(app-glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -frtti")

file(GLOB ANDROID_SOURCES ../../../../../../source/android/*.cpp)

file(GLOB ENGINE_SOURCES ../../../../../../source/*.cpp)

file(GLOB OGL_SOURCES ../../../../../../source/OGL/*.cpp)

add_library(native-activity SHARED
            ${ANDROID_SOURCES}
            ${ENGINE_SOURCES}
            ${OGL_SOURCES}
            ../../../../../../GraphicsTest/TestApplication.cpp
            main.cpp)

target_include_directories(native-activity PRIVATE
                            ../../../../../../include
                            ../../../../../../GraphicsTest
                            ../../../../../../include/android
                           ${ANDROID_NDK}/sources/android/native_app_glue)

# add lib dependencies
target_link_libraries(native-activity
                      android
                      app-glue
                      EGL
                      GLESv2
                      log)




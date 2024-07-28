# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("videoplayer")
add_definitions("
-DGL_GLEXT_PROTOTYPES
-DEGL_EGLEXT_PROTOTYPES
")

add_subdirectory(lib/fdk-aac)
add_subdirectory(lib/vo-aacenc)

set(VERSION 2.7.7)
set(TYPE STATIC)
set(LIB_EXT a)
set(POSTPROC OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg/${VERSION}/${ANDROID_ABI}/include)

set(ffmpeg_lib_path ${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg/${VERSION}/${ANDROID_ABI}/lib)

add_library( avcodec
        ${TYPE}
        IMPORTED )
add_library( avfilter
        ${TYPE}
        IMPORTED )
add_library( avformat
        ${TYPE}
        IMPORTED )
add_library( avutil
        ${TYPE}
        IMPORTED )
add_library( swresample
        ${TYPE}
        IMPORTED )
add_library( swscale
        ${TYPE}
        IMPORTED )



set_target_properties( avcodec
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavcodec.${LIB_EXT} )
set_target_properties( avfilter
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavfilter.${LIB_EXT}  )
set_target_properties( avformat
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavformat.${LIB_EXT}  )
set_target_properties( avutil
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavutil.${LIB_EXT}  )
set_target_properties( swresample
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libswresample.${LIB_EXT}  )
set_target_properties( swscale
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libswscale.${LIB_EXT}  )



include_directories(common/)
include_directories(video_player/)

file(GLOB FILES_LIB_COMMON "./common/*.cpp")
file(GLOB FILES_LIB_COMMON_EGL_CORE "./common/egl_core/*.cpp")
file(GLOB FILES_LIB_COMMON_EGL_CORE "./common/egl_core/*.cpp")
file(GLOB FILES_LIB_COMMON_RESAMPLER "./common/libresampler/*.cpp")
file(GLOB FILES_LIB_COMMON_MSG_Q "./common/message_queue/*.cpp")
file(GLOB FILES_LIB_COMMON_OPENGL_MEDIA "./common/opengl_media/*.cpp")
file(GLOB FILES_LIB_COMMON_OPENGL_MEDIA_RENDER "./common/opengl_media/render/*.cpp")
file(GLOB FILES_LIB_COMMON_OPENGL_MEDIA_TEXTURE "./common/opengl_media/texture/*.cpp")
file(GLOB FILES_LIB_COMMON_OPENGL_MEDIA_TEX_COPIER "./common/opengl_media/texture_copier/*.cpp")
file(GLOB FILES_LIB_COMMON_OPENSL "./common/opensl_media/*.cpp")
file(GLOB FILES_LIB_VIDEO_PLAYER "./video_player/*.cpp")
file(GLOB FILES_LIB_VIDEO_PLAYER_COMMON "./video_player/common/*.cpp")
file(GLOB FILES_LIB_VIDEO_PLAYER_DECODER "./video_player/decoder/*.cpp")
file(GLOB FILES_LIB_VIDEO_PLAYER_SYNC "./video_player/sync/*.cpp")
file(GLOB FILES_LIB_VIDEO_PLAYER_TEX_UPLOADER "./video_player/texture_uploader/*.cpp")


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.

        ${FILES_LIB_COMMON}
        ${FILES_LIB_COMMON_EGL_CORE}
        ${FILES_LIB_COMMON_MSG_Q}
        ${FILES_LIB_COMMON_RESAMPLER}
        ${FILES_LIB_COMMON_OPENSL}
        ${FILES_LIB_COMMON_OPENGL_MEDIA}
        ${FILES_LIB_COMMON_OPENGL_MEDIA_RENDER}
        ${FILES_LIB_COMMON_OPENGL_MEDIA_TEXTURE}
        ${FILES_LIB_COMMON_OPENGL_MEDIA_TEX_COPIER}
        ${FILES_LIB_VIDEO_PLAYER}
        ${FILES_LIB_VIDEO_PLAYER_COMMON}
        ${FILES_LIB_VIDEO_PLAYER_DECODER}
        ${FILES_LIB_VIDEO_PLAYER_SYNC}
        ${FILES_LIB_VIDEO_PLAYER_TEX_UPLOADER}
        native-lib.cpp
)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        avcodec
        avfilter
        avformat
        avutil
        swresample
        swscale
        fdk-aac
        vo-aacenc
        GLESv2
        EGL
        z
        OpenSLES
        android
        log)
#include <jni.h>
#include <string>
#include "video_player_controller.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#ifdef __cplusplus
}
#endif

#define LOG_TAG "VideoPlayer_JNI"
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_videoplayer_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    avcodec_register_all();
    av_register_all();
    return env->NewStringUTF(hello.c_str());
}

VideoPlayerController* videoPlayerController = NULL;

static ANativeWindow *window = 0;
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_onSurfaceCreated(JNIEnv *env, jobject thiz,
                                                                     jobject surface) {
    if (NULL != videoPlayerController) {
        window = ANativeWindow_fromSurface(env, surface);
        int width = ANativeWindow_getWidth(window);
        int height = ANativeWindow_getHeight(window);
        videoPlayerController->onSurfaceCreated(window, width, height);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_onSurfaceDestroyed(JNIEnv *env, jobject thiz,
                                                                       jobject surface) {
    if (NULL != videoPlayerController) {
        videoPlayerController->onSurfaceDestroyed();
    }
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_videoplayer_MainActivity_prepare(JNIEnv *env, jobject obj,
                                                            jstring videoMergeFilePathParam,
                                                            jintArray max_analyze_duration,
                                                            jint size, jint probesize,
                                                            jboolean fpsProbeSizeConfigured,
                                                            jfloat minBufferedDuration,
                                                            jfloat maxBufferedDuration,
                                                            jint width, jint height,
                                                            jobject surface) {
    LOGI("Enter Java_com_changba_songstudio_video_player_ChangbaPlayer_prepare...");
    JavaVM *g_jvm = NULL;
    env->GetJavaVM(&g_jvm);
    jobject g_obj = env->NewGlobalRef(obj);
    char* videoMergeFilePath = (char*) env->GetStringUTFChars(videoMergeFilePathParam, NULL);
    if(NULL == videoPlayerController) {
        videoPlayerController = new VideoPlayerController();
    }
    window = ANativeWindow_fromSurface(env, surface);
    jint* max_analyze_duration_params = env->GetIntArrayElements(max_analyze_duration, 0);
    jboolean initCode = videoPlayerController->init(videoMergeFilePath, g_jvm, g_obj, max_analyze_duration_params,
                                                    size, probesize, fpsProbeSizeConfigured, minBufferedDuration, maxBufferedDuration);
    videoPlayerController->onSurfaceCreated(window, width, height);
    env->ReleaseIntArrayElements(max_analyze_duration, max_analyze_duration_params, 0);
    env->ReleaseStringUTFChars(videoMergeFilePathParam, videoMergeFilePath);

    return initCode;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_pause(JNIEnv *env, jobject thiz) {
    if(NULL != videoPlayerController) {
        videoPlayerController->pause();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_play(JNIEnv *env, jobject thiz) {
    if(NULL != videoPlayerController) {
        videoPlayerController->play();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_stop(JNIEnv *env, jobject thiz) {
    if(NULL != videoPlayerController) {
        videoPlayerController->destroy();
        delete videoPlayerController;
        videoPlayerController = NULL;
    }
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_videoplayer_MainActivity_getBufferedProgress(JNIEnv *env, jobject thiz) {
    if (NULL != videoPlayerController) {
        return videoPlayerController->getBufferedProgress();
    }
    return 0.0f;
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_videoplayer_MainActivity_getPlayProgress(JNIEnv *env, jobject thiz) {
    if (NULL != videoPlayerController) {
        return videoPlayerController->getPlayProgress();
    }
    return 0.0f;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_seekToPosition(JNIEnv *env, jobject thiz,
                                                                   jfloat position) {
    if(NULL != videoPlayerController) {
        videoPlayerController->seekToPosition(position);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_seekCurrent(JNIEnv *env, jobject thiz,
                                                                jfloat position) {
    if(NULL != videoPlayerController) {
//		videoPlayerController->seekCurrent(position);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_beforeSeekCurrent(JNIEnv *env, jobject thiz) {
    if(NULL != videoPlayerController) {
//		videoPlayerController->beforeSeekCurrent();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_afterSeekCurrent(JNIEnv *env, jobject thiz) {
    if(NULL != videoPlayerController) {
//		videoPlayerController->afterSeekCurrent();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplayer_MainActivity_resetRenderSize(JNIEnv *env, jobject thiz,
                                                                    jint left, jint top, jint width,
                                                                    jint height) {
    if(NULL != videoPlayerController) {
        videoPlayerController->resetRenderSize(left, top, width, height);
    }
}

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnLoad called");
    JNIEnv *env = nullptr;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    LOGI("jni onload called end...");
    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnUnload called");
    JNIEnv *env = nullptr;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return;
    }
}
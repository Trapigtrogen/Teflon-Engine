#ifndef _ENGINE_LOG_H_
#define _ENGINE_LOG_H_

// Define LOGI, LOGW and LOGE depending on platform
#if defined(_WIN32)
	// Win32
#include <stdio.h>
#define  LOGI(...)  printf(__VA_ARGS__)
#define  LOGW(...)  printf(__VA_ARGS__)
#define  LOGE(...)  printf(__VA_ARGS__)	
#else
	// Android
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "EngineApp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

#endif


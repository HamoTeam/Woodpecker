//
// Created by 邱顺明 on 2019-07-29.
//

#ifndef WOODPECKER_APPLOG_H
#define WOODPECKER_APPLOG_H

#define LOG_TAG "jvmti"
#include <android/log.h>

#define APPLOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define APPLOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define APPLOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define APPLOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define APPLOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //WOODPECKER_APPLOG_H

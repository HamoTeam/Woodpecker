//
// Created by qiushunming on 2019-07-29.
//

#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_owl_woodepckerlib_WoodpeckerJni_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string helloWork = "Hello form C++";
    return env->NewStringUTF(helloWork.c_str());
}
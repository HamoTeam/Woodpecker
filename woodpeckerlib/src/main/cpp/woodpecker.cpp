//
// Created by qiushunming on 2019-07-29.
//

#include <jni.h>
#include <string>
#include "jvmti.h"
#include "applog.h"


//创建jvmti虚拟机
jvmtiEnv *CreateJvmtiVm(JavaVM *pVm) {
    jvmtiEnv *jvmti;
    jint result = pVm->GetEnv((void **) &jvmti, JVMTI_VERSION_1_2);

    if (result != JNI_OK) {
        return nullptr;
    }

    return jvmti;
}

void ObjectAllocEventCallback(jvmtiEnv *jvmti_env,
                              JNIEnv *jni_env,
                              jthread thread,
                              jobject object,
                              jclass object_klass,
                              jlong size) {

    jclass cls = jni_env->FindClass("java/lang/Class");
    jmethodID mid_getName = jni_env->GetMethodID(cls, "getName", "()Ljava/lang/String;");
    jstring name = static_cast<jstring>(jni_env->CallObjectMethod(object_klass, mid_getName));
    const char *className = jni_env->GetStringUTFChars(name, JNI_FALSE);
    APPLOGI("ObjectAllocEventCallback %s {size:%ld}", className, size);
    jni_env->ReleaseStringUTFChars(name, className);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_owl_woodepckerlib_WoodpeckerJni_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string helloWork = "Hello form C++";
    return env->NewStringUTF(helloWork.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Agent_OnAttach(JavaVM* vm, char* options, void* reserved){
    jvmtiEnv *jvmti = CreateJvmtiVm(vm);

    if (jvmti == nullptr) {
        return JNI_ERR;
    }

    //设置能力
    jvmtiCapabilities capabilities;
    jvmtiError jtiErr;
    jtiErr = jvmti->GetPotentialCapabilities(&capabilities);
    APPLOGI("GetPotentialCapabilities:%d", jtiErr);
    if (jtiErr == JVMTI_ERROR_NONE) {
        jtiErr = jvmti->AddCapabilities(&capabilities);
        APPLOGI("AddCapabilities:%d", jtiErr);
    }

    //设置回调事件监听
    jvmtiEventCallbacks eventCallbacks;
    memset(&eventCallbacks, 0, sizeof(eventCallbacks));
    eventCallbacks.VMObjectAlloc = &ObjectAllocEventCallback;

    //设置回调
    jtiErr = jvmti->SetEventCallbacks(&eventCallbacks, sizeof(eventCallbacks));
    APPLOGI("SetEventCallbacks:%d", jtiErr);

    jtiErr = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_OBJECT_ALLOC, nullptr);
    APPLOGI("SetEventNotificationMode:%d", jtiErr);

    return JNI_OK;
}
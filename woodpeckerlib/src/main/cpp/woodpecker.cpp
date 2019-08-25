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

int g_tag = 10086;

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
    int res = strcmp("com.owl.woodpecker.FreeObj", className);
    if (res == 0){
        int errcode = jvmti_env->SetTag(object, g_tag);
        g_tag += 1;
        APPLOGI("SetTag:%d", errcode);

        jlong pTag ;
        errcode = jvmti_env->GetTag(object, &pTag);
        APPLOGI("GetTag:%d %ld", errcode, pTag);
    }
    if(size > 1024){
        APPLOGW("ObjectAllocEventCallback %s {size:%ld}", className, size);
    } else {
        APPLOGI("ObjectAllocEventCallback %s {size:%ld}", className, size);
    }
    jni_env->ReleaseStringUTFChars(name, className);
}

void ObjectFreeEventCallback(jvmtiEnv *jvmti_env,
         jlong tag){
    APPLOGI("ObjectFreeEventCallback %ld", tag);
}

void GCStartEventCallback(jvmtiEnv *jvmti_env){
    APPLOGI("GCStartEventCallback");
}

void GCFinishEventCallback(jvmtiEnv *jvmti_env){
    APPLOGI("GCFinishEventCallback");
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
    eventCallbacks.ObjectFree = &ObjectFreeEventCallback;
    eventCallbacks.GarbageCollectionStart = &GCStartEventCallback;
    eventCallbacks.GarbageCollectionFinish = &GCFinishEventCallback;

    //设置回调
    jtiErr = jvmti->SetEventCallbacks(&eventCallbacks, sizeof(eventCallbacks));
    APPLOGI("SetEventCallbacks:%d", jtiErr);

    jtiErr = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_OBJECT_ALLOC, nullptr);
    APPLOGI("SetEventNotificationMode JVMTI_EVENT_VM_OBJECT_ALLOC:%d", jtiErr);
    jtiErr = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_OBJECT_FREE, nullptr);
    APPLOGI("SetEventNotificationMode JVMTI_EVENT_OBJECT_FREE:%d", jtiErr);
    jtiErr = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_START, nullptr);
    APPLOGI("SetEventNotificationMode GC_START:%d", jtiErr);
    jtiErr = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_FINISH, nullptr);
    APPLOGI("SetEventNotificationMode GC_FINISH:%d", jtiErr);

    return JNI_OK;
}
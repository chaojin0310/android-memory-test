/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_memorytestcpp_MainActivity */
#include <malloc.h>
#include <string.h>
#include <android/log.h>
#include <new>

#define LOG_TAG "System.out"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#ifndef _Included_com_example_memorytest_MainActivity
#define _Included_com_example_memorytest_MainActivity
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_memorytestcpp_MainActivity
 * Method:    _checkCpp_manually
 * Signature: ()Ljava/lang/String;
 */

//JNIEXPORT jstring JNICALL Java_com_example_memorytest_MainActivity__1checkCpp_1manually
//        (JNIEnv *env, jobject instance) {
//    int seg_size_MB = 10, MB_size = 1024 * 1024;
//    char *p = new char[1250 * MB_size];
//    return env->NewStringUTF("hello from cpp\n");
//}

//JNIEXPORT jstring JNICALL Java_com_example_memorytest_MainActivity__1checkCpp_1manually
//        (JNIEnv *env, jobject instance) {
//    unsigned int seg_size_MB = 10;
//    unsigned int MB_size = 1024 * 1024;
//    long long usedMemory = 0, allocatedMemory = 0, PreviousUsedMemory = 0;
//    char *ptrArray[1024];
//    char useless_str[1024];
//
//    jclass mainActivity = env->FindClass("com/example/memorytest/MainActivity");
//    jfieldID usedFieldID = env->GetFieldID(mainActivity, "usedMemory", "J");
//    jfieldID allocatedID = env->GetFieldID(mainActivity, "allocatedMemory", "J");
//
//    int i = 0;
//    try {
//        for (; i < 1024; ++i) {
//            // ptrArray[i] = new char[seg_size_MB * MB_size];
//            char *ptr = (char *)malloc(seg_size_MB * MB_size);
//            ptrArray[i] = ptr;
//            if (ptrArray[i] == nullptr) {  // OOM has occurred already
//                std::bad_alloc alloc_exception;
//                throw alloc_exception;
//            }
//            struct mallinfo mm = mallinfo();
//            PreviousUsedMemory = usedMemory;
//            usedMemory = (long long) (mm.uordblks) / MB_size;
//            if (usedMemory == 0) {  // OOM has occurred already
//                std::bad_alloc alloc_exception;
//                throw alloc_exception;
//            }
//            allocatedMemory += seg_size_MB;
//            LOGI("heap memory used: %lld MB (%lld)", usedMemory, allocatedMemory);
//        }
//    }
//    catch(std::bad_alloc &e) {
//        for (int j = 0; j <= i; ++j) {
//            delete(ptrArray[j]);
//        }
//        // Set values
//        env->SetLongField(instance, usedFieldID, PreviousUsedMemory);
//        env->SetLongField(instance, allocatedID, allocatedMemory);
//        env->DeleteLocalRef(mainActivity);
//        return env->NewStringUTF("OOM Error(cpp):\n");
//    }
//    for (int j = 0; j <= i; ++j) {
//        delete(ptrArray[j]);
//    }
//    env->SetLongField(instance, usedFieldID, usedMemory);
//    env->SetLongField(instance, allocatedID, allocatedMemory);
//    env->DeleteLocalRef(mainActivity);
//    return env->NewStringUTF("no OOM:\n");
//}

JNIEXPORT jstring JNICALL Java_com_example_memorytest_MainActivity__1checkCpp_1manually
        (JNIEnv *env, jobject instance) {
    unsigned int MB_size = 1024 * 1024;
    long long maximum_size = 0;
    long long usedMemory = 0, allocatedMemory = 0;
    // 10MB, 1MB, 1KB, 1B
    unsigned long long block_size[4] = {10 * MB_size, MB_size, 1024, 1};

    jclass mainActivity = env->FindClass("com/example/memorytest/MainActivity");
    jfieldID usedFieldID = env->GetFieldID(mainActivity, "usedMemory", "J");
    jfieldID allocatedID = env->GetFieldID(mainActivity, "allocatedMemory", "J");

    try {
        for (int i = 0; i < 4; i++) {
            for (unsigned int cnt = 0;; cnt++) {
                char *ptr = nullptr;
                ptr = new char[maximum_size + block_size[i]]; // Overflow?

                if (ptr) {
                    maximum_size += block_size[i];
                    // memset(ptr, 0, maximum_size);
                    struct mallinfo mm = mallinfo();
                    long long used = usedMemory = (long long) (mm.uordblks) / MB_size;
                    if (used == 0) {  // OOM has occurred already
                        std::bad_alloc alloc_exception;
                        throw alloc_exception;
                    }
                    usedMemory = used;
                    delete (ptr);
                    allocatedMemory = maximum_size / MB_size;
                    LOGI("heap memory used: %lld MB (%lld)", usedMemory, allocatedMemory);
                } else {
                    break;
                }
            }
        }
    }
    catch (std::bad_alloc &e) {
        LOGI("maximum size = %lld bytes, %lld MB", maximum_size, allocatedMemory);
        env->SetLongField(instance, usedFieldID, usedMemory);
        env->SetLongField(instance, allocatedID, allocatedMemory);
        env->DeleteLocalRef(mainActivity);
        return env->NewStringUTF("OOM Error(cpp):\n");
    }
    return env->NewStringUTF("no OOM Error!\n");
}

#ifdef __cplusplus
}
#endif
#endif

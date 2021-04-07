LOCAL_PATH:=$(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := memory_test_cpp
LOCAL_SRC_FILES := com_example_memorytestcpp_MainActivity.cpp

LOCAL_LDLIBS += -llog
LOCAL_CPPFLAGS += -fexceptions

include $(BUILD_SHARED_LIBRARY)
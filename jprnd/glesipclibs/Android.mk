
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libGLESv1_CM_ipc
#LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR)/lib/egl
LOCAL_SRC_FILES := cutil.c vmcutil.c GLESv1_CM.c
LOCAL_C_INCLUDES += \
        $(LOCAL_PATH) \
        bionic \
        $(call include-path-for, audio-effects)
#LOCAL_SHARED_LIBRARIES := liblog
LOCAL_CFLAGS += -DDEFAULT_CLIENT_CONTEXT=libgles -DLOG_TAG=\"GLESv2\"
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libGLESv2_ipc
#LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR)/lib/egl
LOCAL_SRC_FILES := cutil.c vmcutil.c GLESv2.c
LOCAL_C_INCLUDES += \
        $(LOCAL_PATH) \
        bionic \
        $(call include-path-for, audio-effects)
#LOCAL_SHARED_LIBRARIES := liblog
LOCAL_CFLAGS += -DDEFAULT_CLIENT_CONTEXT=libgles -DLOG_TAG=\"GLESv2\"
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libEGL_ipc
#LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR)/lib/egl
LOCAL_SRC_FILES := cutil.c vmcutil.c EGL.c
LOCAL_C_INCLUDES += \
        $(LOCAL_PATH) \
        bionic \
        $(call include-path-for, audio-effects)
#LOCAL_SHARED_LIBRARIES := liblog
LOCAL_CFLAGS += -DDEFAULT_CLIENT_CONTEXT=libgles -DLOG_TAG=\"GLESv2\"
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

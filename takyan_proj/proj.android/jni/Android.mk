LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

$(info $(NDK_MODULE_PATH))

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/managers_caches/AssortedUtils.cpp \
                   ../../Classes/managers_caches/EventCustomMapped.cpp \
                   ../../Classes/managers_caches/ObserverManager.cpp \
                   ../../Classes/managers_caches/UILockManager.cpp \
                   ../../Classes/nodes/BattleInfoMenu.cpp \
                   ../../Classes/nodes/ConfirmDialog.cpp \
                   ../../Classes/nodes/FirstDialog.cpp \
                   ../../Classes/nodes/InstructionsDialog.cpp \
                   ../../Classes/nodes/MainMenuScene.cpp \
                   ../../Classes/nodes/PauseDialog.cpp \
                   ../../Classes/nodes/PlaceSelect.cpp \
                   ../../Classes/nodes/PlayerCreate.cpp \
                   ../../Classes/nodes/PlayerSelect.cpp \
                   ../../Classes/nodes/PlayerSelectEntry.cpp \
                   ../../Classes/nodes/PostGameDialog.cpp \
                   ../../Classes/nodes/PostGameVersusDialog.cpp \
                   ../../Classes/nodes/RecordsDialog.cpp \
                   ../../Classes/nodes/RecordsDialogEntry.cpp \
                   ../../Classes/nodes/SinglePlayerScene.cpp \
                   ../../Classes/nodes/TriviaContents.cpp \
                   ../../Classes/nodes/TriviaDialog.cpp \
                   ../../Classes/nodes/VersusScene.cpp \
                   ../../Classes/objects/GameData.cpp \
                   ../../Classes/objects/PlayerData.cpp \
                   ../../Classes/objects/PlayerManager.cpp \
                   ../../Classes/objects/SingleGameData.cpp \
                   ../../Classes/objects/VersusGameConfig.cpp \
                   ../../Classes/objects/VersusGameData.cpp \
                   ../../Classes/objects/VersusPlayerGameData.cpp \
                   ../../Classes/plugins/AnimatingNumber.cpp \
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += spritebuilder_static

include $(BUILD_SHARED_LIBRARY)


$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,editor-support/spritebuilder)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)

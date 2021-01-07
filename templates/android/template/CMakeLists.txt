cmake_minimum_required(VERSION 3.8)

option(APP_NAME "Project Name" "CocosGame")
project(${APP_NAME} CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../common/CMakeLists.txt)


set(LIB_NAME cocos)
set(PROJ_SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

set(PROJ_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/../common/Classes/Game.h
    ${CMAKE_CURRENT_LIST_DIR}/../common/Classes/Game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/jni/main.cpp
)


if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../common/Classes/jsb_module_register.cpp)
    file(COPY "${COCOS_X_PATH}/cocos/bindings/manual/jsb_module_register.cpp"
        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../common/Classes/)
endif()

list(APPEND PROJ_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/../common/Classes/jsb_module_register.cpp
)

add_library(${LIB_NAME} SHARED ${PROJ_SOURCES})

set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u ANativeActivity_onCreate")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onCreateNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onSurfaceCreateNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onStartNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onPauseNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onResumeNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onStopNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onLowMemoryNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onWindowFocusChangedNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onSurfaceChangedNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosActivity_onSurfaceDestroyNative")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosTouchHandler_handleActionDown")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosTouchHandler_handleActionUp")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosTouchHandler_handleActionMove")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosTouchHandler_handleActionCancel")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosKeyCodeHandler_handleKeyDown")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosKeyCodeHandler_handleKeyUp")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosSurfaceView_nativeOnSizeChanged")
set_property(TARGET ${LIB_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -u Java_com_cocos_lib_CocosOrientationHelper_nativeOnOrientationChanged")

target_link_libraries(${LIB_NAME} cocos2d)

target_include_directories(${LIB_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../common/Classes
)

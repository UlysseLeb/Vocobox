cmake_minimum_required(VERSION 3.19)
project(Vocobox VERSION 1.0.2025)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0")
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

find_library(AUDIOUNIT_FRAMEWORK AudioUnit)
find_library(AUDIOTOOLBOX_FRAMEWORK AudioToolbox)
find_library(COREAUDIO_FRAMEWORK CoreAudio)
find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
find_library(CARBON_FRAMEWORK Carbon)

set(AU_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vendor/CoreAudio")

set(SOURCES
    src/talkbox.cpp
)

include_directories(
    ${AU_SDK_PATH}/AudioUnits/AUPublic/AUBase
    ${AU_SDK_PATH}/AudioUnits/AUPublic/Utility
    ${AU_SDK_PATH}/AudioUnits/AUPublic/OtherBases
    ${AU_SDK_PATH}/PublicUtility
    src
)

set(AU_BASE_SOURCES
    ${AU_SDK_PATH}/PublicUtility/CADebugMacros.cpp
    ${AU_SDK_PATH}/PublicUtility/CAHostTimeBase.cpp
    ${AU_SDK_PATH}/PublicUtility/CAVectorUnit.cpp
    ${AU_SDK_PATH}/PublicUtility/CAAudioChannelLayout.cpp
    ${AU_SDK_PATH}/PublicUtility/CAStreamBasicDescription.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/AUBase/AUBase.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/AUBase/AUDispatch.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/AUBase/AUInputElement.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/AUBase/AUOutputElement.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/AUBase/AUScopeElement.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/AUBase/ComponentBase.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/AUBase/AUPlugInDispatch.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/OtherBases/AUEffectBase.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/OtherBases/AUMIDIEffectBase.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/OtherBases/AUMIDIBase.cpp
    ${AU_SDK_PATH}/AudioUnits/AUPublic/Utility/AUBuffer.cpp
)

add_library(Vocobox MODULE
    ${SOURCES}
    ${AU_BASE_SOURCES}
)

set_target_properties(Vocobox PROPERTIES
    BUNDLE TRUE
    BUNDLE_EXTENSION component
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
    XCODE_ATTRIBUTE_WRAPPER_EXTENSION component
)

target_link_libraries(Vocobox
    ${AUDIOUNIT_FRAMEWORK}
    ${AUDIOTOOLBOX_FRAMEWORK}
    ${COREAUDIO_FRAMEWORK}
    ${COREFOUNDATION_FRAMEWORK}
    ${CARBON_FRAMEWORK}
)

target_compile_definitions(Vocobox PRIVATE
    PLUGIN_VERSION=0x00010000
    PLUGIN_MANUFACTURER_ID=0x76636278
    PLUGIN_MANUFACTURER_NAME="Vocobox"
)

add_custom_command(TARGET Vocobox POST_BUILD
    COMMAND /bin/echo -n "BNDLvcbx" > "$<TARGET_BUNDLE_CONTENT_DIR:Vocobox>/PkgInfo"
    COMMENT "Creating PkgInfo file"
)

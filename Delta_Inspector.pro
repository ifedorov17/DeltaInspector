QT       += core gui sql quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG += qzxing_multimedia \
          enable_decoder_1d_barcodes \
          enable_decoder_qr_code \
          enable_decoder_data_matrix \
          enable_decoder_aztec \
          enable_decoder_pdf17

CONFIG += enable_encoder_qr_code

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminmenu.cpp \
    generaldao.cpp \
    lesson.cpp \
    main.cpp \
    mainwindow.cpp \
    student.cpp \
    visitings.cpp

HEADERS += \
    QrEncoder.h \
    adminmenu.h \
    generaldao.h \
    lesson.h \
    mainwindow.h \
    student.h \
    visitings.h

include(src/QZXing.pri)
include(src/QZXing-components.pri)
include(deployment.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    form.ui


CONFIG(debug, debug|release) {
    CONFIG+=qml_debug
} else {
    DEFINES += QT_NO_DEBUG
    DEFINES += QT_NO_DEBUG_OUTPUT
}

android {
    QT += androidextras

    DISTFILES += \
        android/AndroidManifest.xml \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat \
        android/AndroidManifest.xml \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

else:ios {
  QMAKE_INFO_PLIST=Info.plist
}

RESOURCES += \
    qml.qrc

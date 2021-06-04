import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtMultimedia 5.5

import QZXing 3.1

Item
{
    id: window
    signal qmlSignal(string msg)
    visible: true
    width: 640
    height: 480

    property int detectedTags: 0
    property string lastTag: ""



    Connections {
        target: w
    }

    Rectangle
    {
        id: bgRect
        color: "black"
        anchors.fill: videoOutput
    }


    Camera
    {
        id:camera
        focus {
            focusMode: CameraFocus.FocusContinuous
            focusPointMode: CameraFocus.FocusPointAuto
        }
    }

    VideoOutput
    {
        id: videoOutput
        source: camera
        anchors.top: text1.bottom
        anchors.bottom: text2.top
        anchors.left: parent.left
        anchors.right: parent.right
        autoOrientation: true
        fillMode: VideoOutput.Stretch
        filters: [ zxingFilter ]
        MouseArea {
            anchors.fill: parent
            onClicked: {
                camera.focus.customFocusPoint = Qt.point(mouse.x / width,  mouse.y / height);
                camera.focus.focusMode = CameraFocus.FocusMacro;
                camera.focus.focusPointMode = CameraFocus.FocusPointCustom;
            }
        }
        Rectangle {
                    id: captureZone
                    color: "#3037eb34"
                    radius: 10
                    border.color: "green"
                    border.width: 3
                    opacity: 1
                    width: parent.width / 2
                    height: parent.height / 2
                    anchors.centerIn: parent
                }
    }

    QZXingFilter
    {
        id: zxingFilter
        captureRect: {
            // setup bindings
            videoOutput.contentRect;
            videoOutput.sourceRect;
            return videoOutput.mapRectToSource(videoOutput.mapNormalizedRectToItem(Qt.rect(
                0.25, 0.25, 0.5, 0.5
            )));
        }



        decoder {
            enabledDecoders: QZXing.DecoderFormat_EAN_13 | QZXing.DecoderFormat_CODE_39 | QZXing.DecoderFormat_QR_CODE

            onTagFound: {

                w.onTagGot(tag)
                console.log(tag + " | " + decoder.foundedFormat() + " | " + decoder.charSet());



                window.detectedTags++;
                window.lastTag = tag;
            }

            tryHarder: false
        }

        onDecodingStarted:
        {
//            console.log("started");
        }

        property int framesDecoded: 0
        property real timePerFrameDecode: 0

        onDecodingFinished:
        {
           timePerFrameDecode = (decodeTime + framesDecoded * timePerFrameDecode) / (framesDecoded + 1);
           framesDecoded++;
           if(succeeded)
            console.log("frame finished: " + succeeded, decodeTime, timePerFrameDecode, framesDecoded);
        }
    }

}

import QtQuick 2.0
import org.shotcut.qml 1.0

Metadata {
    type: Metadata.Filter
    name: qsTr("Color Grading")
    mlt_service: "lift_gamma_gain"
    qml: "ui.qml"
    isFavorite: true
    gpuAlt: "movit.lift_gamma_gain"
    keyframes {
        parameters: [
            Parameter {
                name: qsTr('Shadows (Lift)')
                property: 'lift_r'
            },
            Parameter {
                name: qsTr('Midtones (Gamma)')
                property: 'gamma_r'
            },
            Parameter {
                name: qsTr('Highlights (Gain)')
                property: 'gain_r'
            }
        ]
    }
}

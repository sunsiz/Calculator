include(config.pri)

LIBS+=-fopenmp

CONFIG(release, debug|release) {
    message("Release Mode")
    unix{
        INCLUDEPATH += /opt/local/include
        LIBS += -L/opt/local/lib/ -lopencv_core -lopencv_imgproc
        CUDA_AVAILABLE{LIBS += -L/opt/local/lib/akil -lanIntrusion-cu -laVideoStreamer-cu -laVisionUtils-cu}
        else{LIBS += -L/opt/local/lib/akil -lanIntrusion-cl -laVideoStreamer-cl -laVisionUtils-cl -laDetector-cl -laTracker-cl -laDarknet-cl}
    }
}

CONFIG(debug, debug|release) {
    message("Debug Mode")
    unix{
        INCLUDEPATH += /opt/local/debug/include
        LIBS += -L/opt/local/debug/lib -lopencv_core -lopencv_imgproc
        CUDA_AVAILABLE{LIBS += -L/opt/local/debug/lib/akil -lanIntrusion-cu+dbg -laVideoStreamer-cu+dbg -laVisionUtils-cu+dbg}
        else{LIBS += -L/opt/local/debug/lib/akil -lanIntrusion-cl+dbg -laVideoStreamer-cl+dbg -laVisionUtils-cl+dbg -laDetector-cl+dbg -laTracker-cl+dbg -laDarknet-cl+dbg}
    }
}

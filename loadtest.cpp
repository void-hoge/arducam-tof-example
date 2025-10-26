#include <ArducamTOFCamera.hpp>
#include <cstdio>
#include <cstdint>

using namespace Arducam;

int main() {
    ArducamTOFCamera tof;
    if (tof.open(Connection::CSI)) {
        fprintf(stderr, "failed to initialize.\n");
        return -1;
    }
    if (tof.start(FrameType::DEPTH_FRAME)) {
        fprintf(stderr, "failed to start.\n");
        return -1;
    }
    for (int i = 0; i < 30 * 10; i++) {
        auto frame = tof.requestFrame(2000);
        auto depth = (float*)frame->getData(FrameType::DEPTH_FRAME);
        auto amplitude = (float*)frame->getData(FrameType::CONFIDENCE_FRAME);
        tof.releaseFrame(frame);
    }
    if (tof.stop()) {
        return -1;
    }
    if (tof.close()) {
        return -1;
    }
}

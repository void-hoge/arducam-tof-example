#include <ArducamTOFCamera.hpp>
#include <iostream>
#include <chrono>
#include <cstdint>

using namespace Arducam;

class Timer {
public:
    Timer() : start(std::chrono::system_clock::now()) {}

    uint32_t elapsed_us() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now() - start).count();
    }
private:
    std::chrono::system_clock::time_point start;
};

int main() {
    ArducamTOFCamera tof;
    if (tof.open(Connection::CSI)) {
        fprintf(stderr, "failed to initialize.\n");
        return -1;
    }
    if (tof.start(FrameType::RAW_FRAME)) {
        fprintf(stderr, "failed to start.\n");
        return -1;
    }
    int max_range = 4000;
    printf("call setControl\n");
    tof.setControl(Control::RANGE, max_range);
    printf("call getControl\n");
    tof.getControl(Control::RANGE, &max_range);
    printf("call getCameraInfo\n");
    CameraInfo info = tof.getCameraInfo();
    printf("size: %dx%d\n", info.width, info.height);
    printf("range: %d\n", max_range);

    {
        auto timer = Timer();
        ArducamFrameBuffer* frame;
        frame = tof.requestFrame(2000);
        printf("frame captured:   %4d us\n", timer.elapsed_us());

        FrameFormat format;
        printf("raw frame:        %4d us\n", timer.elapsed_us());

        float* depth = (float*)frame->getData(FrameType::DEPTH_FRAME);
        printf("depth frame:      %4d us\n", timer.elapsed_us());

        float* confidence = (float*)frame->getData(FrameType::CONFIDENCE_FRAME);
        printf("confidence frame: %4d us\n", timer.elapsed_us());

        tof.releaseFrame(frame);
        printf("frame released:   %4d us\n", timer.elapsed_us());
        printf("\n");
    }

    if (tof.stop()) {
        return -1;
    }
    if (tof.close()) {
        return -1;
    }
}

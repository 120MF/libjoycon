#include "Device.hpp"

int main() {
    auto device = JoyCon::Device::getInstance();
    device->print_imu_event();
    free(device);

    return 0;
}

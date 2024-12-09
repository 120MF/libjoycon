#include "Device.h"

int main() {
    auto device = JoyCon::Device::getInstance();
    free(device);

    return 0;
}

#include "Device.h"

namespace JoyCon {
    Device::Device() {
        joycon_key_device_name = "Joy-Con (" + std::string(JOYCON_SIDE) + ")";
        joycon_imu_device_name = joycon_key_device_name + " (IMU)";

        for (int i = 0; i < 50; i++) {
            char device_path[20];
            sprintf(device_path, "/dev/input/event%d", i);
            if (const int fd = get_fd_if_valid(device_path); fd > 0) {
                std::string name = get_device_name(fd);
                if (name == joycon_key_device_name) joycon_key_device_fd = fd;
                else if (name == joycon_imu_device_name) joycon_imu_device_fd = fd;
            }
        }
        if (!joycon_key_device_fd || !joycon_imu_device_fd) {
            throw std::runtime_error("Can't find valid JoyCon device.");
            exit(-1);
        }
    }


    int Device::get_fd_if_valid(const char device_path[]) {
        const int fd = open(device_path, O_RDONLY);
        if (fd < 0) {
            return -1;
        }
        return fd;
    }

    std::string Device::get_device_name(const int fd) {
        char buf[256] = {};
        try {
            if (fd < 0) {
                throw std::runtime_error("Bad File Descriptor");
            }
            if (ioctl(fd, EVIOCGNAME(sizeof(buf) - 1), buf) < 0 || !buf) {
                throw std::runtime_error("Get device name failed.");
            }
            return buf;
        } catch (error_t err) {
            std::cerr << err;
            return "";
        }
    }
}


#ifndef DEVICE_H
#define DEVICE_H

#ifdef JOYCON_LEFT
#define JOYCON_SIDE "L"
#endif
#ifdef JOYCON_RIGHT
#define JOYCON_SIDE "R"
#endif

#include <string>
#include <cstring>
#include <iostream>
#include <linux/input.h>


class Device {
public:
    Device() {
        joycon_key_device_name = "Joy-Con (" + std::string(JOYCON_SIDE) + ")";
        joycon_imu_device_name = joycon_key_device_name + " (IMU)";
    }

protected:
    const std::string &get_device_name(int fd) {
        int rc;
        char buf[256] = {};
        if (fd < 0) {
            throw new std::runtime_error("Bad File Descriptor");
        }
        rc = ioctl(fd, EVIOCGNAME(sizeof(buf) - 1), buf);
        if (rc < 0) {
            return "Error";
        }
    }

private:
    int fd = 0;
    std::string joycon_key_device_name;
    std::string joycon_imu_device_name;
    std::string filename;
};

#endif

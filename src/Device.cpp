#include "Device.hpp"

#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h>
#include <cstring>

#include "utils.hpp"

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

    Device *Device::getInstance() {
        static Device device;
        return &device;
    }

    Device::~Device() {
        ioctl(fd, EVIOCGRAB, static_cast<void *>(nullptr));
    }

    void Device::print_imu_event() {
        std::cout << "Printing!" << std::endl;
        bool stop;
        struct input_event ev[64];
        long rd;
        fd_set rdfs;

        FD_ZERO(&rdfs);
        FD_SET(joycon_imu_device_fd, &rdfs);
        while (1) {
            select(joycon_imu_device_fd + 1, &rdfs, NULL, NULL, NULL);
            rd = read(joycon_imu_device_fd, ev, sizeof(ev));

            if (rd < static_cast<int>(sizeof(struct input_event))) {
                printf("expected %d bytes, got %ld\n", static_cast<int>(sizeof(struct input_event)), rd);
                throw std::runtime_error("Error reading");
                return;
            }

            for (int i = 0; i < rd / sizeof(struct input_event); i++) {
                unsigned int type = ev[i].type;
                unsigned int code = ev[i].code;

                printf("Event: time %ld.%06ld, ", ev[i].input_event_sec, ev[i].input_event_usec);

                if (type == EV_SYN) {
                    if (code == SYN_MT_REPORT)
                        printf("++++++++++++++ %d, %s ++++++++++++\n", code, to_code_name(type, code));
                    else if (code == SYN_DROPPED)
                        printf(">>>>>>>>>>>>>> %d, %s <<<<<<<<<<<<\n", code, to_code_name(type, code));
                    else
                        printf("-------------- %d, %s ------------\n", code, to_code_name(type, code));
                } else {
                    printf("type %d (%s), code %d (%s), ",
                           type, to_type_name(type),
                           code, to_code_name(type, code));
                    if (type == EV_MSC && (code == MSC_RAW || code == MSC_SCAN))
                        printf("value %02x\n", ev[i].value);
                    else
                        printf("value %d\n", ev[i].value);
                }
            }
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

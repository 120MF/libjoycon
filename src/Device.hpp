
#ifndef DEVICE_H
#define DEVICE_H

#ifdef JOYCON_LEFT
#define JOYCON_SIDE "L"
#endif
#ifdef JOYCON_RIGHT
#define JOYCON_SIDE "R"
#endif

#define EV_MAX 0x1f

#include <string>
#include <iostream>


namespace JoyCon {
    class Device {
    public:
        Device(const Device &obj) = delete;

        Device &operator=(const Device &obj) = delete;

        ~Device();

        static Device *getInstance();

        void print_imu_event();

    protected:
        int get_fd_if_valid(const char device_path[]);

        std::string get_device_name(int fd);

    private:
        Device();

        static Device *_instance;

        int fd = 0;
        std::string joycon_key_device_name;
        std::string joycon_imu_device_name;
        int joycon_key_device_fd = 0;
        int joycon_imu_device_fd = 0;
    };
}

#endif

#ifndef UTILS_HPP
#define UTILS_HPP

namespace JoyCon {
    inline const char *to_type_name(const unsigned int type_id) {
        switch (type_id) {
            case 0:
                return "EV_SYN";
            case 1:
                return "EV_KEY";
            case 3:
                return "EV_ABS";
            case 4:
                return "EV_MSC";

            default: return "";
        }
    };

    inline const char *to_code_name(const unsigned int type_id, const unsigned int code_id) {
        switch (type_id) {
            case 0:
                return "SYN_REPORT";
            case 1: switch (code_id) {
                    case 309:
                        return "BTN_Z";
                    case 310:
                        return "BTN_TL";
                    case 311:
                        return "BTN_TR";
                    case 312:
                        return "BTN_TL2";
                    case 313:
                        return "BTN_TR2";
                    case 314:
                        return "BTN_SELECT";
                    case 317:
                        return "BTN_THUMBL";
                    case 544:
                        return "BTN_DPAD_UP";
                    case 545:
                        return "BTN_DPAD_DOWN";
                    case 546:
                        return "BTN_DPAD_LEFT";
                    case 547:
                        return "BTN_DPAD_RIGHT";
                    default: return "";
                }
            case 3: switch (code_id) {
                    case 0:
                        return "ABS_X";
                    case 1:
                        return "ABS_Y";
                    case 2:
                        return "ABS_Z";
                    case 3:
                        return "ABS_RX";
                    case 4:
                        return "ABS_RY";
                    case 5:
                        return "ABS_RZ";
                    default:
                        return "";
                }
            case 4:
                return code_id == 5 ? "MSC_TIMESTAMP" : "";
            default: return "";
        }
    }
}

#endif //UTILS_HPP

#include "main.h"

// argv[0]: program name
// argv[1]: print star height
// argv[2]: print star count
// argv[3]: print mode (normal: 1 or reverse: 0)
int main(int argc, char* argv[])
{
    SETTING setting = {0,}; 

    init(argc, argv, setting);
    std::cout << "Height: " << setting.height << std::endl;
    std::cout << "Count : " << setting.count << std::endl;
    std::cout << "Mode  : " << (setting.mode ? "normal" : "reverse") << std::endl;

    char output[20480] = {0,};
    int  pos = 0;
    int  cnt = 0;
    while(setting.y <= setting.height) {
        if(setting.mode) {
            printNormalStar(setting, pos, output);
        } else {
            printReverseStar(setting, pos, output);
        }
        output[pos++] = '\n';

        setting.x         += 2;
        setting.reverse_x -= 2;
        setting.y         += 1;
    }

    std::cout << output << std::endl;

    return 0;
}

void init(int& argc, char* argv[], SETTING& setting) noexcept
{
    enum {
        HEIGHT = 1,
        COUNT  = 2,
        MODE   = 3
    };

    int apos;
    int itemp;
    for(apos = 1; apos < argc; apos++) {
        itemp = atoi(argv[apos]);

        switch(apos) {
            case HEIGHT:
                setting.height = itemp != 0 ? itemp : 3;
            break;
            case COUNT :
                setting.count  = itemp != 0 ? itemp : 3;
            break;
            case MODE :
                setting.mode   = itemp != 0 ? true : false;
            break;
            default:
                std::cout << "Invalid argument type: " << argv[apos] << std::endl;
            break;
        }
    }

    setting.x         = 1;
    setting.reverse_x = setting.height * 2 - 1;
    setting.y         = 1;
    setting.offset    = setting.height - 1;
}

int addStr(char* output, int& pos, const std::string str) noexcept
{
    std::strncpy(&output[pos], str.c_str(), str.size());
    return str.size();
}

void printNormalStar(SETTING& setting, int& pos, char* output) noexcept
{
    pos += addStr(output, pos, std::string(setting.height - setting.y, 0x20));
    pos += addStr(output, pos, std::string(setting.x, '*'));

    int cnt;
    for(cnt = 1; cnt < setting.count; cnt++) {
        pos += addStr(output, pos, std::string(setting.offset, 0x20));
        pos += addStr(output, pos, std::string(cnt % 2 == 1 ? setting.reverse_x : setting.x, '*'));
    }
}

void printReverseStar(SETTING& setting, int& pos, char* output) noexcept
{
    pos += addStr(output, pos, std::string(setting.y, 0x20));
    pos += addStr(output, pos, std::string(setting.reverse_x, '*'));

    int cnt;
    for(cnt = 1; cnt < setting.count; cnt++) {
        pos += addStr(output, pos, std::string(setting.offset, 0x20));
        pos += addStr(output, pos, std::string(cnt % 2 == 1 ? setting.x : setting.reverse_x, '*'));
    }
}

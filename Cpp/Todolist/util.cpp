#include "main.h"

void showTitle() noexcept
{
    // system("cls");
    std::cout << TODOLIST << std::endl;
}

void printList(const LIST& list) noexcept
{
    std::cout << "ID         : " << list.id       << std::endl;
    std::cout << "Index      : " << list.index    << std::endl;
    std::cout << "Input Date : " << list.in_date  << std::endl;
    std::cout << "Input Time : " << list.in_time  << std::endl;
    std::cout << "Title      : " << list.title    << std::endl;
    std::cout << "Description: " << list.desc     << std::endl;
    std::cout << "Clear Date : " << list.clr_date << std::endl;
    std::cout << "Clear Time : " << list.clr_time << std::endl;
    std::cout << "Tag Count  : " << list.tag_cnt  << std::endl;
    std::cout << std::endl;
}

int onClickKeyEvent(const char* message) noexcept
{
    if(strlen(message) != 0) {
        std::cout << message << std::endl;
    }

    int key = static_cast<int>(getch());
    if(65 <= key && key <= 90) {
        key += 32;
    }

    return key;
}

int inputValueStr(const char* name, int max_size, char* output) noexcept
{
    int size = 0;
    std::string input;

    while(true) {
        std::cout << "Input now   " << name << '.' << std::endl;
        std::cin >> input;
        if(input.length() > max_size) {
            std::cout << "Input value too long: " << input << "(" << input.length() << "byte)" << std::endl;
            std::cout << "Please try again." << std::endl;
            continue;
        }
        break;
    }
    strcpy(output, input.c_str());

    return strlen(output);
}

int inputValueUInt(const char* name, uint& output) noexcept
{
    uint input;
    while(true) {
        std::cout << "Input now   " << name << '.' << std::endl;
        std::cin >> input;
        if(input) {
            std::cout << "Input value too small or big: " << input << std::endl;
            std::cout << "Please try again." << std::endl;
            continue;
        }
        break;
    }

    return input;
}

int confirm(const char* message) noexcept
{
    int rtn = -1;
    int key;
    while(true) {
        std::cout << message << " (y/n)" << std::endl;
        key = onClickKeyEvent(NULL);
        if(key == ANSWER_YES) {
            rtn = 1;
            break;
        }
        else
        if(key == ANSWER_NO) {
            rtn = 0;
            break;
        }
        else {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }

    return rtn;
}

int getNowDate(char* format, int size, char* output) noexcept
{
    char dformat[32] = {0,};
    if(format == NULL) {
        std::strcpy(dformat, "%Y%m%d");
    } else {
        std::strcpy(dformat, format);
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);

    std::strftime(output, size, dformat, now_tm);
    return 0;
}

int getNowTime(char* format, int size, char* output) noexcept
{
    char dformat[32] = {0,};
    if(format == NULL) {
        std::strcpy(dformat, "%H%M%S");
    } else {
        std::strcpy(dformat, format);
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);

    std::strftime(output, size, dformat, now_tm);
    return 0;
}

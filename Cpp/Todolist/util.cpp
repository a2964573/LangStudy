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

int onClickKeyEvent() noexcept
{
    int key = static_cast<int>(getch());
    if(65 <= key && key <= 90) {
        key += 32;
    }

    return key;
}

int inputValue(const char* name, int max_size, char* output) noexcept
{
    int size = 0;
    std::string input;

    while(true) {
        std::cout << "Input now list " << name << '.' << std::endl;
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

int confirm(const char* message) noexcept
{
    int rtn = -1;
    int key;
    while(true) {
        std::cout << message << " (y/n)" << std::endl;
        key = onClickKeyEvent();
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
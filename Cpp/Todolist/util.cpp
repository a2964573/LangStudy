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
    int pos;
    for(pos = 0; pos < list.tag_cnt; pos++) {
        std::cout << "Tag        : #" << list.tags[pos].id << " " << list.tags[pos].name << std::endl;
    }
    std::cout << std::endl;
}

int onClickKeyEvent(const char* message) noexcept
{
    if(message != NULL) {
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
        std::cout << "Input now " << name << '.' << std::endl;
        std::cin >> input;
        size = input.size();
        if(size >= max_size) {
            std::cout << "Input value too long: " << input << "(" << size << "byte)" << std::endl;
            std::cout << "Please try again." << std::endl;
            continue;
        }
        break;
    }
    strcpy(output, input.c_str());

    return size;
}

int inputValueUInt(const char* name, uint& output) noexcept
{
    std::cout << "Input now " << name << '.' << std::endl;
    std::cin >> output;

    return output;
}

int confirm(const char* message) noexcept
{
    if(message != NULL) {
        std::cout << message << " (y/n)" << std::endl;
    }

    int rtn;
    int key;
    while(true) {
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

int showAllTags() noexcept
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        std::cerr << "Error: Failed to open '" << TAG_FILE_NAME << "'" << std::endl;
        return -1;
    }

    TAG tag = {0,};
    std::string tagLine;
    while(std::getline(inTagConf, tagLine)) {
        tag.id = std::stoi(tagLine.substr(0, tagLine.find(',')));
        std::strcpy(tag.name, tagLine.substr(tagLine.find(',') + 1).c_str());
        std::cout << '#' << tag.id << ' ' << tag.name << std::endl;
    }
    inTagConf.close();
}

int findTag(int tag_id, TAG& output)
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        std::cerr << "Error: Failed to open '" << TAG_FILE_NAME << "'" << std::endl;
        return -1;
    }

    std::string tagLine;
    while(std::getline(inTagConf, tagLine)) {
        output.id = std::stoi(tagLine.substr(0, tagLine.find(',')));
        if(output.id == tag_id) {
            std::strcpy(output.name, tagLine.substr(tagLine.find(',') + 1).c_str());
            break;
        }
    }
    inTagConf.close();

    if(output.name[0] == 0x00) {
        output.id = 0x00;
    }

    return output.id == 0x00 ? 0 : 1;
}
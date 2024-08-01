#include "main.h"

int showTitle() noexcept
{
    // system("cls");
    std::cout << TODOLIST << std::endl;

    return 0;
}

int showList(GLOBAL& _global) noexcept
{
    int pos = 0;
    LIST* list = new LIST[_global.list_lastIdx];
    std::ifstream inTodoFile(_global.filename);
    std::string todoLine;
    while(std::getline(inTodoFile, todoLine)) {
        list[pos].id        = std::stoi(todoLine.substr(0, todoLine.find(','))         );
        list[pos].index     = std::stoi(todoLine.substr(todoLine.find(',') + 1)        );
        list[pos].status    = std::stoi(todoLine.substr(todoLine.find(',') + 2)        );
        std::strcpy(list[pos].in_date , todoLine.substr(todoLine.find(',') + 3).c_str());
        std::strcpy(list[pos].in_time , todoLine.substr(todoLine.find(',') + 4).c_str());
        std::strcpy(list[pos].title   , todoLine.substr(todoLine.find(',') + 5).c_str());
        std::strcpy(list[pos].desc    , todoLine.substr(todoLine.find(',') + 6).c_str());
        std::strcpy(list[pos].clr_date, todoLine.substr(todoLine.find(',') + 7).c_str());
        std::strcpy(list[pos].clr_time, todoLine.substr(todoLine.find(',') + 8).c_str());
        list[pos].tag_cnt   = std::stoi(todoLine.substr(todoLine.find(',') + 9)        );
    }

    return 0;
}

int printList(const LIST& list) noexcept
{
    std::cout << "ID         : " << list.id       << std::endl;
    std::cout << "Index      : " << list.index    << std::endl;
    std::cout << "Status     : " << list.status   << std::endl;
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

    return 0;
}

int parseCSVLine(const LIST& list, char* output)
{
    int len = sprintf(output, "%d,%d,%d,%s,%s,%s,%s,%s,%s,%d"
                , list.id      , list.index   , list.status
                , list.in_date , list.in_time , list.title
                , list.desc    , list.clr_date, list.clr_time
                , list.tag_cnt);
    int pos = 0;
    while(true) {
        if(pos >= list.tag_cnt) {
            break;
        }

        len += sprintf(&output[len], ",%d,%s", list.tags[pos].id, list.tags[pos].name);
        pos++;
    }

    return len;
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

int inputValueUInt(const char* name, uint& output) noexcept
{
    std::cout << "Input now " << name << '.' << std::endl;
    std::string input;
    std::getline(std::cin, input);

    try {
        int rtn = std::stoi(input.substr(0, input.find(' ')));
        output = static_cast<uint>(rtn);
    } catch(const std::invalid_argument& e) {
        std::cout << "ID를 입력해주세요" << std::endl << std::endl;
    }

    return output;
}

int inputValueWord(const char* name, int max_size, char* output) noexcept
{
    int size = 0;
    std::string input;

    while(true) {
        std::cout << "Input now " << name << '.' << std::endl;
        std::getline(std::cin, input);
        input = input.substr(0, input.find(' '));
        size = input.size();
        if(size >= max_size) {
            std::cout << "Input value too long: " << input << "(" << size << "byte)" << std::endl;
            std::cout << "Please try again." << std::endl << std::endl << std::endl;
            continue;
        }
        break;
    }
    strcpy(output, input.c_str());

    return size;
}

int inputValueString(const char* name, int max_size, char* output) noexcept
{
    int size = 0;
    std::string input;

    while(true) {
        std::cout << "Input now " << name << '.' << std::endl;
        std::getline(std::cin, input);
        size = input.size();
        if(size >= max_size) {
            std::cout << "Input value too long: " << input << "(" << size << "byte)" << std::endl;
            std::cout << "Please try again." << std::endl << std::endl;
            continue;
        }
        break;
    }
    strcpy(output, input.c_str());

    return size;
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
            std::cout << "Invalid input. Please try again." << std::endl << std::endl;
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
        std::cerr << "Error: Failed to open '" << TAG_FILE_NAME << "'" << std::endl << std::endl;
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

    return 0;
}

int findTag(int tag_id, TAG& output)
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        std::cerr << "Error: Failed to open '" << TAG_FILE_NAME << "'" << std::endl << std::endl;
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

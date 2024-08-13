#include "main.h"

int showTitle() noexcept
{
    system("cls");
    std::cout << TODOLIST << std::endl;

    return 0;
}

int showList(GLOBAL& _global)
{
    if(_global.list_count == 0) {
        
        return 0;
    }

    LIST* lists = new LIST[_global.list_lastId];
    memset(lists, 0x00, sizeof(LIST) * _global.list_lastId);

    int rtn = getListAll(_global, lists);
    if(rtn < 0) {
        alert("Error: Get List All Failed", 1000);
    }
    else
    if(rtn == 0) {
        alert("표시할 리스트가 없습니다.", 500);
    }
    else {
        std::cout << std::setw(10) << std::left << "ID"    << '|';
        std::cout << std::setw(1 ) << std::left << "S"     << '|';
        std::cout <<                  std::left << "Title" << std::endl;

        int pos;
        for(pos = 0; pos < rtn; pos++) {
            if(lists[pos].status == -1) {
                continue;
            }

            std::cout << std::setw(10                          )  << std::left << (lists[pos].id                ) << '|';
            std::cout << std::setw(1                           )  << std::left << (lists[pos].status ? 'V' : 'O') << '|';
            std::cout << std::setw(std::strlen(lists[pos].title)) << std::left << (lists[pos].title             ) << std::endl << std::endl;
        }
    }
    delete[] lists;

    return rtn;
}

int getListById(GLOBAL& _global, int id, LIST& output)
{
    LIST* lists = new LIST[_global.list_lastId];
    memset(lists, 0x00, sizeof(LIST) * _global.list_lastId);

    int rtn = getListAll(_global, lists);
    if(rtn < 0) {
        alert("Error: Get List All Failed", 500);
        return -1;
    }

    int pos = 0;
    while(true) {
        output = lists[pos];
        if(output.id == 0x00) {
            pos = -1;
            break;
        }
        else
        if(output.id == id) {
            break;
        }

        pos++;
    }
    delete[] lists;

    return pos;
}

int getListAll(GLOBAL& _global, LIST* output)
{
    int  pos    = 0;
    int  tpos   = 0;
    int  start  = 0;
    int  end    = 0;

    LIST list   = {0,};
    TAG  tag    = {0,};

    std::ifstream inTodoFile(_global.filename);
    std::string todoLine;
    std::string result;

    while(std::getline(inTodoFile, todoLine)) {
        start = 0;
        end   = 0;
        memset(&list, 0x00, sizeof(list));
        memset(&tag , 0x00, sizeof(tag ));

        end = findString(todoLine, end    , LINE_DECIMAL, result);
        if(end == 0) {
            continue;
        }
        list.id        = std::stoi(result        );

        end = findString(todoLine, end + 1, LINE_DECIMAL, result);
        if(end == 0) {
            continue;
        }
        list.status    = std::stoi(result        );

        end = findString(todoLine, end + 1, LINE_DECIMAL, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.in_date , result.c_str());

        end = findString(todoLine, end + 1, LINE_DECIMAL, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.in_time , result.c_str());

        end = findString(todoLine, end + 1, LINE_DECIMAL, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.title   , result.c_str());

        end = findString(todoLine, end + 1, LINE_DECIMAL, result);
        if(result.length() > 0) {
            std::strcpy(list.desc, result.c_str());
        }

        end = findString(todoLine, end + 1, LINE_DECIMAL, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.clr_date, result.c_str());

        end = findString(todoLine, end + 1, LINE_DECIMAL, result);
        if(end == 0) {
            continue;
        }
        std::strcpy(list.clr_time, result.c_str());

        end = findString(todoLine, end + 1, LINE_DECIMAL, result);
        if(end == 0) {
            continue;
        }
        list.tag_cnt   = std::stoi(result        );

        for(tpos = 0; tpos < list.tag_cnt; tpos++) {
            end = findString(todoLine, end + 1, LINE_DECIMAL, result);
            if(end == 0) {
                continue;
            }
            tag.id    = std::stoi(result         );

            end = findString(todoLine, end + 1, LINE_DECIMAL, result);
            if(end == 0) {
                continue;
            }
            std::strcpy(tag.name, result.c_str() );

            list.tags[tpos] = tag;
        }

        output[pos] = list;
        pos++;
    }
    inTodoFile.close();

    return pos;
}

int getListAllCnt(GLOBAL& _global)
{
    std::ifstream inTodoFile(_global.filename);
    if(!inTodoFile.good()) {
        return -1;
    }

    int count = 0;
    int len   = 0;

    std::string todoLine;
    std::string result;

    while(std::getline(inTodoFile, todoLine)) {
        len = getFieldValue(todoLine, LISTSTATUS, LINE_DECIMAL, result);
        if(len <= 0) {
            continue;
        }

        if(std::stoi(result) == -1) {
            continue;
        }   

        count++;
    }
    inTodoFile.close();

    return count;
}

int printList(const LIST list) noexcept
{
    std::cout << "ID         : " << list.id       << std::endl;
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

int parseLineByList(const LIST list, char* output)
{
    int len = sprintf(output, "%d\\%d\\%s\\%s\\%s\\%s\\%s\\%s\\%d"
                , list.id      , list.status  , list.in_date
                , list.in_time , list.title   , list.desc
                , list.clr_date, list.clr_time, list.tag_cnt);
    int pos = 0;
    while(true) {
        if(pos >= list.tag_cnt) {
            break;
        }

        len += sprintf(&output[len], "\\%d\\%s", list.tags[pos].id, list.tags[pos].name);
        pos++;
    }

    return len;
}

int parseLineByTag(const TAG tag, char* output)
{
    std::cout << "Tag ID     : " << tag.id     << std::endl;
    std::cout << "Tag Name   : " << tag.name  << std::endl;
    return sprintf(output, "%d\\%s", tag.id, tag.name);
}

int showTagsByListId(GLOBAL& _global, int id)
{
    LIST list = {0,};
    int rtn = getListById(_global, id, list);
    if(rtn < 0) {
        alert("해당하는 리스트가 없습니다.", 1000);
        return -1;
    }

    if(list.tag_cnt > 0) {
        std::cout     << "- Tags ----------------------------------------------------------" << std::endl;

        int pos;
        for(pos = 0; pos < list.tag_cnt; pos++) {
            std::cout << "Tag        : #" << list.tags[pos].id << " " << list.tags[pos].name << std::endl;
        }
        std::cout     << "Tag Count  : "  << list.tag_cnt      << std::endl << std::endl;
    } else {
        alert("태그가 없습니다.", 1000);
    }

    return list.tag_cnt;
}

int showTagsByArray(int tag_cnt, const TAG* tags)
{
    if(tag_cnt > 0) {
        std::cout     << "- Tags ----------------------------------------------------------" << std::endl;

        int pos;
        for(pos = 0; pos < tag_cnt; pos++) {
            std::cout << "Tag        : #" << tags[pos].id << " " << tags[pos].name << std::endl;
        }
        std::cout     << "Tag Count  : "  << tag_cnt      << std::endl << std::endl;
    } else {
        alert("태그가 없습니다.", 1000);
    }

    return 0;
}

int showAllTags() noexcept
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        alert("Error: Failed to open '_tag.ini'", 500);
        return -1;
    }

    TAG tag = {0,};
    int len = 0;
    std::string result;
    std::string tagLine;
    while(std::getline(inTagConf, tagLine)) {
        len = getFieldValue(tagLine, TAGID, LINE_DECIMAL, result);
        if(len == 0) {
            break;
        }
        tag.id = std::stoi(result);

        len = getFieldValue(tagLine, TAGNAME, LINE_DECIMAL, result);
        if(len == 0) {
            break;
        }
        std::strcpy(tag.name, result.c_str());
        std::cout << PRINT_TAG_FORMAT(tag) << std::endl;
    }
    inTagConf.close();

    return 0;
}

int getTagAll(GLOBAL& _global, TAG* output)
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        alert("Error: Failed to open '_tag.ini'", 500);
        return -1;
    }

    int len = 0;
    int pos = 0;

    TAG tag = {0,};

    std::string result;
    std::string tagLine;
    while(std::getline(inTagConf, tagLine)) {
        len = getFieldValue(tagLine, TAGID, LINE_DECIMAL, result);
        if(len == 0) {
            break;
        }
        tag.id = std::stoi(result);

        len = getFieldValue(tagLine, TAGNAME, LINE_DECIMAL, result);
        if(len == 0) {
            break;
        }
        std::strcpy(tag.name, result.c_str());

        output[pos] = tag;
        pos++;
    }
    inTagConf.close();

    return pos;
}

int getTagAllCnt(GLOBAL& _global)
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        return -1;
    }

    int count = 0;
    int len   = 0;

    std::string tagLine;
    std::string result;

    while(std::getline(inTagConf, tagLine)) {
        len = getFieldValue(tagLine, TAGID, LINE_DECIMAL, result);
        if(len <= 0) {
            continue;
        }

        if(std::stoi(result) == -1) {
            continue;
        }   

        count++;
    }
    inTagConf.close();

    return count;
}

int getTagLastIdByFile(GLOBAL& _global)
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        return -1;
    }

    int id  = 0;
    int len = 0;

    std::string tagLine;
    std::string result;

    while(std::getline(inTagConf, tagLine)) {
        len = getFieldValue(tagLine, TAGID, LINE_DECIMAL, result);
        if(len <= 0) {
            continue;
        }

        id = std::stoi(result);
        if(id < _global.tag_lastId) {
            continue;
        }   

        _global.tag_lastId = id;
    }
    inTagConf.close();

    return id;
}

int getTagLastIdByArray(TAG* tag_array, int count)
{
    int id = 0;
    int pos;
    for(pos = 0; pos < count; pos++) {
        if(tag_array[pos].id > id) {
            id = tag_array[pos].id;
        }
    }

    return id;
}

int findTag(int tag_id, TAG& output)
{
    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        alert("Error: Failed to open ' _tag.ini'", 500);
        return -1;
    }

    int len = 0;
    std::string result;
    std::string tagLine;
    while(std::getline(inTagConf, tagLine)) {
        len = getFieldValue(tagLine, TAGID, LINE_DECIMAL, result);
        if(len == 0) {
            break;
        }
        output.id = std::stoi(result);
        if(output.id == tag_id) {
            len = getFieldValue(tagLine, TAGNAME, LINE_DECIMAL, result);
            if(len == 0) {
                break;
            }
            std::strcpy(output.name, result.c_str());
            break;
        }
    }
    inTagConf.close();

    if(output.name[0] == 0x00) {
        output.id = 0x00;
    }

    return output.id == 0x00 ? 0 : 1;
}

int findString(std::string str, int start, char target, std::string& output)
{
    int end = str.find(target, start);
    if(end == std::string::npos) {
        end = str.length();
    }

    output = str.substr(start, end - start);

    return end;
}

int getFieldValue(std::string str, int column, char target, std::string& output)
{
    int start = 0;
    int end   = 0;
    int pos;
    for(pos = 0; pos < column; pos++) {
        end = str.find(target, start);
        if(end == std::string::npos) {
            return -1;
        }

        if(pos != 0) {
            start = end + 1;
        }
    }

    output = str.substr(start, end - start);

    return output.length();
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

int confirm(const char* message) noexcept
{
    int rtn;
    int key;
    while(true) {
        key = onClickKeyEvent(message);
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
            alert("Invalid input. Please try again.", 1000);
        }
    }

    return rtn;
}

int inputValueUInt(const char* message, uint& output) noexcept
{
    if(message != NULL) {
        std::cout << message << std::endl;
    }
    std::string input;
    std::getline(std::cin, input);

    try {
        int rtn = std::stoi(input.substr(0, input.find(' ')));
        output = static_cast<uint>(rtn);
    } catch(const std::invalid_argument& e) {
        alert("0 이상의 수를 입력해주세요.", 1000);
    }

    return output;
}

int inputValueWord(const char* message, int max_size, char* output) noexcept
{
    if(message != NULL) {
        std::cout << message << std::endl;
    }

    int size = 0;
    std::string input;
    while(true) {
        std::getline(std::cin, input);
        input = input.substr(0, input.find(' '));
        size = input.size();
        if(size >= max_size) {
            alert("Input value too long, please try again...", 1000);
            continue;
        }
        break;
    }
    strcpy(output, input.c_str());

    return size;
}

int inputValueString(const char* message, int max_size, char* output) noexcept
{
    if(message != NULL) {
        std::cout << message << std::endl;
    }

    int size = 0;
    std::string input;
    while(true) {
        std::getline(std::cin, input);
        size = input.size();
        if(size >= max_size) {
            alert("Input value too long, please try again...", 1000);
            continue;
        }
        break;
    }
    strcpy(output, input.c_str());

    return size;
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

int alert(const char* message, uint ms) noexcept
{
    char buffer[1024] = {0,};

    if(message == NULL) {
        strcpy(buffer, "다시 확인해주세요...");
    } else {
        strcpy(buffer, message);
    }

    std::cout << message << std::endl << std::endl;
    Sleep(ms);

    return 0;
}

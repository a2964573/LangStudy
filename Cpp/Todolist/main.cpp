#include "main.h"

// argv[0]: program name
// argv[1]: filename
int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cerr << "Please enter more Arguments..." << std::endl;
        return -1;
    }

    GLOBAL _global = {0,};
    if(init(argc, argv, _global) < 0) {
        std::cerr << "Initialize failed." << std::endl;
        return -1;
    }

    LIST list = {0,};

    int rtn;
    int key;
    while(true) {
        showTitle();
        showList(_global);

        memset(&list, 0x00, sizeof(list));

        key = onClickKeyEvent(MENU_GUIDE);
        switch(key) {
            case MODE_LIST_INSERT :
                rtn = insertList(_global, list);
            break;
            case MODE_LIST_UPDATE :
                continue;
            // break;
            case MODE_LIST_DELETE :
                rtn = deleteList(_global, list);
                if(rtn < 0) {
                    continue;
                }

                printList(list);
            break;
            case MODE_REFRESH:
                continue;
            case MODE_QUIET  :
                std::cout << "Bye" << std::endl;
                return 0;
            default:
                std::cout << "Invalid input. Please try again." << std::endl << std::endl;
                continue;
        }

        if(rtn <= 0) {
            std::cout << "해당 리스트를 저장하지 않습니다.." << std::endl << std::endl;
            continue;
        }

        if(saveList(_global, list) < 0) {
            std::cout << "Error: Save Failed" << std::endl;
        }
        std::cout << "저장완료" << std::endl << std::endl;
    }

    return 0;
}

int init(int argc, char *argv[], GLOBAL& _global)
{
    if(strlen(argv[1]) > 1024) {
        std::cerr << "파일명이 너무 깁니다..: " << argv[1] << "(" << strlen(argv[1]) << "byte)"<< std::endl << std::endl;
        return -1;
    }

    sprintf(_global.filename, "%s.txt"    , argv[1]);
    sprintf(_global.bkupname, "%s_bak.txt", argv[1]);
    sprintf(_global.tempname, "%s_tmp.txt", argv[1]);

    std::ifstream inTodoFile(_global.filename);
    if(!inTodoFile.good()) {
        std::cout << _global.filename << " not found." << std::endl;
        std::cout << "create new file: " << _global.filename << std::endl;

        std::ofstream outTodoFile(_global.filename);
        if(!outTodoFile.good()) {
            std::cerr << "cannot create file: " << _global.filename << std::endl << std::endl;
            return -1;
        }
        outTodoFile.close();
    } else {
        LIST list = {0,};
        std::string todoLine;
        while(std::getline(inTodoFile, todoLine)) {
            list.id = std::stoi(todoLine.substr(0, todoLine.find(',')));
            if(_global.list_lastId < list.id) {
                _global.list_lastId = list.id;
            }

            list.index = std::stoi(todoLine.substr(todoLine.find(',') + 1));
            if(_global.list_lastIdx < list.index) {
                _global.list_lastIdx = list.index;
            }
        }
    }
    inTodoFile.close();

    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        std::cout << _global.filename << " not found." << std::endl;
        std::cout << "create new file: " << TAG_FILE_NAME << std::endl;

        std::ofstream outTagConf(TAG_FILE_NAME);
        if(!outTagConf.good()) {
            std::cerr << "cannot create file: " << TAG_FILE_NAME << std::endl << std::endl;
            return -1;
        }
        outTagConf.close();
    } else {
        TAG tag = {0,};
        std::string tagLine;
        while(std::getline(inTagConf, tagLine)) {
            tag.id = std::stoi(tagLine.substr(0, tagLine.find(',')));
            if(_global.tag_lastId < tag.id) {
                _global.tag_lastId = tag.id;
            }
            _global.tag_lastIdx++;
        }
    }
    inTagConf.close();

    return 0;
}

int saveList(GLOBAL& _global, LIST& list)
{
    if(_global.list_lastId < list.id) {
        _global.list_lastId = list.id;
    }

    if(_global.list_lastIdx < list.index) {
        _global.list_lastIdx = list.index;
    }

    char appendLine[LIST_SIZE] = {0,};
    int  rtn;
    // Insert
    if(_global.list_lastId == list.id) {
        rtn = parseCSVLine(list, appendLine);
        if(rtn < 0) {
            std::cout << "Error: Parse CSV string failed" << std::endl << std::endl;
            return -1;
        }

        std::ofstream outTodoFile;
        outTodoFile.open(_global.filename, std::ios::app);
        if(!outTodoFile) {
            std::cerr << "Error: " << _global.filename << "can not open" << std::endl << std::endl;
            return -1;
        }

        outTodoFile << appendLine << '\n';
        outTodoFile.close();
    } 
    // update / delete
    else {
        std::ifstream inTodoFile;
        inTodoFile.open(_global.filename, std::ios::app);
        if(!inTodoFile.good()) {
            std::cerr << "Error: " << _global.filename << "can not open" << std::endl << std::endl;
            return -1;
        }
std::cout << "01" << std::endl;

        std::ofstream outTodoTemp;
        outTodoTemp.open(_global.tempname, std::ios::app);
        if(!outTodoTemp) {
            std::cerr << "Error: " << _global.filename << "can not open" << std::endl << std::endl;
            inTodoFile.close();
            return -1;
        }
std::cout << "02" << std::endl;

        char changeLine[LIST_SIZE] = {0,};
        rtn = parseCSVLine(list, changeLine);
        if(rtn < 0) {
            std::cout << "Error: Parse CSV string failed" << std::endl << std::endl;
            inTodoFile.close();
            outTodoTemp.close();
            return -1;
        }
std::cout << "03" << std::endl;

        std::string line;
        while(std::getline(inTodoFile, line)) {
            if(atoi(&line[0]) != list.id) {
                outTodoTemp << appendLine << '\n';
            } else {
                outTodoTemp << changeLine << '\n';
            }
        }
        inTodoFile.close();
        outTodoTemp.close();
std::cout << "04" << std::endl;

        if(std::rename(_global.filename, _global.bkupname) != 0) {
            std::cout << "Error: " << _global.filename << "Backup is Failed." << std::endl << std::endl;
            return -1;
        }
std::cout << "05" << std::endl;

        if(std::rename(_global.tempname, _global.filename) != 0) {
            std::cout << "Error: " << _global.filename << "Save is Failed, Rollback..." << std::endl << std::endl;
            std::rename(_global.bkupname, _global.filename);
            return -1;
        }
std::cout << "06" << std::endl;

        if(std::remove(_global.bkupname) != 0) {
            std::cout << "Error: " << _global.filename << "Save is Failed, Rollback..." << std::endl << std::endl;
            std::rename(_global.bkupname, _global.filename);
            return -1;
        }
std::cout << "07" << std::endl;
    }

    return 0;
}

int insertList(GLOBAL& _global, LIST& output)
{
    int  len;
    char title  [256 ] = {0,};
    char desc   [1024] = {0,};
    char nowDate[16  ] = {0,};
    char nowTime[16  ] = {0,};

    while(true) {
        len = inputValueString("표시될 제목을 입력해주세요.", sizeof(title), title);
        if(len > 0) {
            break;
        }

        std::cout << "제목은 필수 입력 값입니다. 다시 입력해주세요..." << std::endl;
    }

    len = inputValueString("상세 설명을 입력해주세요.", sizeof(desc), desc);
    if(len <= 0) {
        strcpy(desc, "<내용없음>");
    }

    if(confirm("태그를 입력하시겠습니까? (y/n)") > 0) {
        TAG tags[MAX_TAG_COUNT] = {0,};
        int tag_cnt = editTags(_global, output.tag_cnt, tags);
        
        output.tag_cnt = tag_cnt;
        std::memcpy(output.tags, tags, sizeof(tags[0]) * tag_cnt);
    }

    getNowDate(NULL, sizeof(nowDate), nowDate);
    getNowTime(NULL, sizeof(nowTime), nowTime);

    output.id      = _global.list_lastId  + 1;
    output.index   = _global.list_lastIdx + 1;
    output.status  = 0;

    strcpy(output.in_date , nowDate   );
    strcpy(output.in_time , nowTime   );
    strcpy(output.title   , title     );
    strcpy(output.desc    , desc      );
    strcpy(output.clr_date, "00000000");
    strcpy(output.clr_time, "00000000");

    return confirm("해당 리스트를 저장하시겠습니까? (y/n)");
}

int updateList(GLOBAL& _global, LIST& list)
{
    

    return confirm("해당 리스트를 수정하시겠습니까? (y/n)");
}

int deleteList(GLOBAL& _global, LIST& list)
{
    LIST* lists = new LIST[_global.list_lastId];
    memset(lists, 0x00, sizeof(LIST) * _global.list_lastId);

    int rtn = getListAll(_global, lists);
    if(rtn < 0) {
        std::cout << "Error: Get List All Failed" << std::endl << std::endl;
        return -1;
    }
    else
    if(rtn == 0) {
        std::cout << "리스트가 없습니다." << std::endl << std::endl;
        return -1;
    }

    uint id = 0;

    rtn = inputValueUInt("삭제할 리스트의 ID를 입력해주세요.", id);
    if(rtn == 0) {
        return -1;
    }

    int pos = 0;
    while(true) {
        list = lists[pos];
        if(list.id == 0x00) {
            pos = -1;
            break;
        }
        else
        if(list.id == id) {
            break;
        }

        pos++;
    }
    delete[] lists;

    if(pos < 0) {
        std::cout << "해당하는 리스트가 없습니다." << std::endl << std::endl;
        return -1;
    } else {
        list.index = -1;
        return confirm("해당 리스트를 삭제하시겠습니까? (y/n)");
    }
}

int editTags(GLOBAL& _global, int count, TAG* output)
{
    TAG tag = {0,};

    int tag_cnt = count;
    int rtn;
    int key;

    while(true) {
        memset(&tag, 0x00, sizeof(tag));

        key = onClickKeyEvent("a: Add, d: Del, e: End");
        if(key == MODE_TAG_ADD || key == MODE_TAG_DEL) {
            rtn = key == MODE_TAG_ADD ? addTag(tag_cnt, output) : delTag(tag_cnt, output);
            if(rtn < 0) {
                continue;
            }

            tag_cnt = rtn;
        }
        else
        if(key == MODE_TAG_END) {
            break;
        }
        else {
            std::cout << "Invalid input. Please try again." << std::endl << std::endl;
        }
    }

    return tag_cnt;
}

int addTag(int count, TAG* output)
{
    TAG tag = {0,};
    int rtn;
    if(count >= MAX_TAG_COUNT) {
        std::cout << "더 이상 추가할 수 없습니다." << std::endl << std::endl;
        return -1;
    }

    showAllTags();
    rtn = inputValueUInt("태그 ID를 입력해주세요.", tag.id);
    if(rtn == 0) {
        return -1;
    }

    int pos;
    for(pos = 0; pos < count; pos++) {
        if(output[pos].id == tag.id) {
            std::cout << "중복된 태그입니다." << std::endl << std::endl;
            return -1;
        }
    }

    if(confirm("태그를 추가하시겠습니까? (y/n)") <= 0) {
        return -1;
    }

    rtn = findTag(tag.id, tag);
    if(rtn < 0) {
        std::cout << "Find Tag Error." << std::endl << std::endl;
    }
    else
    if(rtn == 0) {
        std::cout << "Not Found Tag." << std::endl << std::endl;
        rtn = -1;
    }
    else {
        std::memcpy(&output[count], &tag, sizeof(tag));
        rtn = count + 1;
    }

    return rtn;
}

int delTag(int count, TAG* output)
{
    TAG tag = {0,};
    int rtn;
    if(count <= 0) {
        std::cout << "삭제할 태그가 없습니다." << std::endl << std::endl;
        return -1;
    }

    rtn = inputValueUInt("태그 ID를 입력해주세요.", tag.id);
    if(rtn == 0) {
        return -1;
    }

    if(confirm("태그를 삭제하시겠습니까? (y/n)") <= 0) {
        return -1;
    }

    int apos = 0; // after index(updated)
    int bpos = 0; // before index(original)
    while(true) {
        if(output[bpos].id == tag.id) {
            bpos++;
            continue;
        }
        else
        if(bpos >= count) {
            break;
        }

        if(apos != bpos) {
            std::memcpy(&output[apos], &output[bpos], sizeof(output[0]));
        }
        apos++;
        bpos++;
    }
    std::memset(&output[count], 0x00, sizeof(output[count]));
    count -= 1;

    return count;
}
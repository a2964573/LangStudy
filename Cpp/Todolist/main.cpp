#include "main.h"

// argv[0]: program name
// argv[1]: TodoList file name
int main(int argc, char *argv[])
{
    GLOBAL _global = {0,};
    LIST   list    = {0,};

    if(init(argc, argv, _global) < 0) {
        std::cerr << "Initialize failed." << std::endl;
        return -1;
    }

    int rtn;
    int key;
    while(true) {
        showTitle();

        rtn = showList(_global);
        if( rtn < 0) {
            return -1;
        }

        memset(&list, 0x00, sizeof(list));

        key = onClickKeyEvent(MENU_GUIDE);

        // List
        if( key == MODE_LIST_INSERT ||
            key == MODE_LIST_UPDATE ||
            key == MODE_LIST_DELETE )   {
            if( key == MODE_LIST_INSERT ) {
                rtn = insertList(_global, list);
                if(rtn < 0) {
                    continue;
                }
            }
            else
            if( key == MODE_LIST_UPDATE ||
                key == MODE_LIST_DELETE ) {
                if(_global.list_count == 0) {
                    alert("����Ʈ�� �����ϴ�.", 1000);
                    continue;
                }

                switch(key) {
                    case MODE_LIST_UPDATE:
                        rtn = updateList(_global, list);
                        if(rtn < 0) {
                            continue;
                        }
                    break;
                    case MODE_LIST_DELETE:
                        rtn = deleteList(_global, list);
                        if(rtn < 0) {
                            continue;
                        }
                    break;
                }
            }

            if(rtn <= 0) {
                alert("�ش� ����Ʈ�� �������� �ʽ��ϴ�..", 1000);
                continue;
            }

            if(saveList(_global, list) < 0) {
                alert("Error: Save Failed", 1000);
                continue;
            }
            alert("����Ϸ�", 500);
        }
        else
        // tag
        if( key == MODE_TAG_EDIT ) {
            int tag_cnt = 0;

            TAG* tags = new TAG[MAX_TAG_COUNT];
            memset(tags, 0x00, sizeof(TAG) * MAX_TAG_COUNT);

            rtn = getTagAll(_global, tags);
            if(rtn < 0) {
                alert("Error: Get All Tags Failed", 1000);
                continue;
            }

            tag_cnt = editTags(_global, 1, rtn, tags);

            rtn = saveTagsFile(_global, tag_cnt, tags);
            if(rtn < 0) {
                alert("Error: Save Failed", 1000);
                continue;
            }
            alert("����Ϸ�", 500);
        }
        else
        if( key == MODE_LIST_SHOW ) {
            if(_global.list_count == 0) {
                alert("����Ʈ�� �����ϴ�.", 1000);
                continue;
            }

            showListDetail(_global);
            continue;
        }
        else
        if( key == MODE_REFRESH ) {
            continue;
        }
        else
        if( key == MODE_QUIET ) {
            alert("Bye", 1000);
            return 0;
        }
        else {
            alert("Invalid input. Please try again.", 1000);
            continue;
        }
    }

    return 0;
}

int init(int argc, char *argv[], GLOBAL& _global)
{
    char filename[1024];
    if(argc < 2) {
        sprintf(filename, "todo");
    }
    else
    if(strlen(argv[1]) > 1024) {
        alert("���ϸ��� �ʹ� ��ϴ�..", 0);
        return -1;
    }
    else {
        sprintf(filename, "%s", argv[1]);
    }

    int len = 0;
    std::string result;

    sprintf(_global.filename, "%s.txt"    , filename);
    sprintf(_global.bkupname, "%s_bak.txt", filename);
    sprintf(_global.tempname, "%s_tmp.txt", filename);

    std::ifstream inTodoFile(_global.filename);
    if(!inTodoFile.good()) {
        std::cout << _global.filename << " not found." << std::endl;
        std::cout << "create new file: " << _global.filename << std::endl;

        std::ofstream outTodoFile(_global.filename);
        if(!outTodoFile.good()) {
            alert("Error: Create File Failed", 0);
            return -1;
        }
        outTodoFile.close();
    } else {
        LIST list = {0,};
        std::string todoLine;
        while(std::getline(inTodoFile, todoLine)) {
            len = getFieldValue(todoLine, LISTID, LINE_DECIMAL, result);
            if(len == 0) {
                continue;
            }
            list.id = std::stoi(result);
            if(_global.list_lastId < list.id) {
                _global.list_lastId = list.id;
            }

            len = getFieldValue(todoLine, LISTSTATUS, LINE_DECIMAL, result);
            if(len == 0) {
                continue;
            }
            list.status = std::stoi(result);
            if(list.status != -1) {
                _global.list_count++;
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
            alert("Error: Create File Failed", 0);
            return -1;
        }
        outTagConf.close();
    } else {
        _global.tag_count  = getTagAllCnt(_global);
        _global.tag_lastId = getTagLastIdByFile(_global);
    }
    inTagConf.close();

    return 0;
}

int saveList(GLOBAL& _global, LIST& list)
{
    char appendLine[LIST_SIZE] = {0,};
    int  rtn;
    // Insert
    if(_global.list_lastId < list.id) {
        _global.list_lastId = list.id;

        rtn = parseLineByList(list, appendLine);
        if(rtn < 0) {
            alert("Error: String Line Parsing Failed", 1000);
            return -1;
        }

        std::ofstream outTodoFile;
        outTodoFile.open(_global.filename, std::ios::app);
        if(!outTodoFile) {
            alert("Error: TodoList File Open Failed", 1000);
            return -1;
        }

        outTodoFile << appendLine << '\n';
        outTodoFile.close();
    } 
    // update / delete
    else {
        std::ifstream inTodoFile;
        inTodoFile.open(_global.filename);
        if(!inTodoFile.good()) {
            alert("Error: TodoList File Open Failed", 1000);
            return -1;
        }

        std::ofstream outTodoTemp;
        outTodoTemp.open(_global.tempname, std::ios::app);
        if(!outTodoTemp) {
            alert("Error: TodoList File Open Failed", 1000);
            inTodoFile.close();
            return -1;
        }

        char changeLine[LIST_SIZE] = {0,};
        rtn = parseLineByList(list, changeLine);
        if(rtn < 0) {
            alert("Error: String Line Parsing Failed", 1000);
            inTodoFile.close();
            outTodoTemp.close();
            return -1;
        }

        std::string result;
        std::string line;
        while(std::getline(inTodoFile, line)) {
            rtn = getFieldValue(line, LISTID, LINE_DECIMAL, result);
            if(rtn == 0) {
                continue;
            }

            if(std::stoi(result) == list.id) {
                outTodoTemp << changeLine << '\n';
            } else {
                outTodoTemp << line       << '\n';
            }
        }
        inTodoFile.close();
        outTodoTemp.close();

        if(std::rename(_global.filename, _global.bkupname) != 0) {
            alert("Error: TodoList File Backup is Failed.", 1000);
            return -1;
        }

        if(std::rename(_global.tempname, _global.filename) != 0) {
            alert("Error: TodoList File Save is Failed, Rollback...", 1000);
            std::rename(_global.bkupname, _global.filename);
            return -1;
        }

        if(std::remove(_global.bkupname) != 0) {
            alert("Error: TodoList File Save is Failed, Rollback...", 1000);
            std::rename(_global.bkupname, _global.filename);
            return -1;
        }
    }

    rtn = getListAllCnt(_global);
    if(rtn < 0) {
        alert("Error: Get List Count Failed", 1000);
    } else {
        _global.list_count = rtn;
    }

    return rtn;
}

int insertList(GLOBAL& _global, LIST& output)
{
    int  len;
    char title  [256 ] = {0,};
    char desc   [1024] = {0,};
    char nowDate[16  ] = {0,};
    char nowTime[16  ] = {0,};

    while(true) {
        len = inputValueString("ǥ�õ� ������ �Է����ּ���.", sizeof(title), title);
        if(len > 0) {
            break;
        }

        std::cout << "������ �ʼ� �Է� ���Դϴ�. �ٽ� �Է����ּ���..." << std::endl;
    }

    len = inputValueString("�� ������ �Է����ּ���.", sizeof(desc), desc);
    if(len <= 0 && output.desc[0] == 0x00) {
        strcpy(desc, "<�������>");
    }

    if(confirm("�±׸� �Է��Ͻðڽ��ϱ�? (y/n)") > 0) {
        TAG tags[MAX_TAG_COUNT] = {0,};
        output.tag_cnt = editTags(_global, 0, output.tag_cnt, tags);
        std::memcpy(output.tags, tags, sizeof(tags));
    }

    getNowDate(NULL, sizeof(nowDate), nowDate);
    getNowTime(NULL, sizeof(nowTime), nowTime);

    if(output.id == 0x00) {
        output.id  =  _global.list_lastId + 1;
    }
    output.status  = 0;

    strcpy(output.in_date , nowDate   );
    strcpy(output.in_time , nowTime   );
    strcpy(output.title   , title     );
    strcpy(output.desc    , desc      );
    strcpy(output.clr_date, "00000000");
    strcpy(output.clr_time, "00000000");

    return confirm("�ش� ����Ʈ�� �����Ͻðڽ��ϱ�? (y/n)");
}

int updateList(GLOBAL& _global, LIST& output)
{
    uint id = 0;
    int  rtn;

    rtn = inputValueUInt("�����Ϸ��� ����Ʈ�� ID�� �Է����ּ���.", id);
    if(rtn == 0) {
        return -1;
    }

    rtn = getListById(_global, id, output);
    if(rtn < 0) {
        alert("�ش��ϴ� ����Ʈ�� �����ϴ�.", 1000);
        return -1;
    }

    int key = onClickKeyEvent(LIST_UPDATE_GUIDE);
    switch(key) {
        case LIST_UPDATE_ALL: {
            if(output.status == LIST_CLEAR) {
                alert("�̿Ϸ� ������ ����Ʈ�� ���� �����մϴ�.", 1000);
                return 0;
            }

            return insertList(_global, output);
        }
        break;
        case LIST_UPDATE_STATUS: {
            rtn = confirm("����Ʈ�� ���¸� ��ȯ�Ͻðڽ��ϱ�? (y/n)");
            if(rtn == 0) {
                return 0;
            }

            if(output.status == LIST_UNCLEAR) {
                char nowDate[16] = {0,};
                char nowTime[16] = {0,};

                getNowDate(NULL, sizeof(nowDate), nowDate);
                getNowTime(NULL, sizeof(nowTime), nowTime);

                output.status = LIST_CLEAR;
                strcpy(output.clr_date, nowDate);
                strcpy(output.clr_time, nowTime);
            } else {
                output.status = LIST_UNCLEAR;
                strcpy(output.clr_date, "00000000");
                strcpy(output.clr_time, "00000000");
            }
        }
        break;
        case LIST_UPDATE_TITLE: {
            if(output.status == LIST_CLEAR) {
                alert("�̿Ϸ� ������ ����Ʈ�� ���� �����մϴ�.", 1000);
                return 0;
            }

            char title[256] = {0,};
            rtn = inputValueString("�����Ϸ��� �������� �Է����ּ���.", sizeof(title), title);
            if(rtn <= 0) {
                std::cout << "������ �ʼ� �Է� ���Դϴ�." << std::endl;
                return 0;
            }

            strcpy(output.title, title);
        }
        break;
        case LIST_UPDATE_DESC: {
            if(output.status == LIST_CLEAR) {
                alert("�̿Ϸ� ������ ����Ʈ�� ���� �����մϴ�.", 1000);
                return 0;
            }

            char desc[1024] = {0,};
            rtn = inputValueString("�����Ϸ��� �������� �Է����ּ���.", sizeof(desc), desc);
            if(rtn <= 0) {
                strcpy(desc, "<�������>");
            }

            strcpy(output.desc, desc);
        }
        break;
        case LIST_UPDATE_TAG: {
            if(output.status == LIST_CLEAR) {
                alert("�̿Ϸ� ������ ����Ʈ�� ���� �����մϴ�.", 1000);
                return 0;
            }

            output.tag_cnt = editTags(_global, 0, output.tag_cnt, output.tags);
        }
        break;
        default:
            alert("Invalid input. Please try again.", 500);
            return 0;
    }

    return confirm("�ش� ����Ʈ�� �����Ͻðڽ��ϱ�? (y/n)");
}

int deleteList(GLOBAL& _global, LIST& output)
{
    uint id = 0;
    int rtn = inputValueUInt("�����Ϸ��� ����Ʈ�� ID�� �Է����ּ���.", id);
    if(rtn == 0) {
        return -1;
    }

    rtn = getListById(_global, id, output);
    if(rtn < 0) {
        alert("�ش��ϴ� ����Ʈ�� �����ϴ�.", 1000);
        return -1;
    } else {
        output.status = -1;
        return confirm("�ش� ����Ʈ�� �����Ͻðڽ��ϱ�? (y/n)");
    }
}

int showListDetail(GLOBAL& _global)
{
    uint id = 0;
    int rtn = inputValueUInt("Ȯ���Ϸ��� ����Ʈ�� ID�� �Է����ּ���.", id);
    if(rtn == 0) {
        return -1;
    }

    LIST list = {0,};
    rtn = getListById(_global, id, list);
    if(rtn < 0) {
        alert("�ش��ϴ� ����Ʈ�� �����ϴ�.", 1000);
        return -1;
    }

    printList(list);

    while(true) {
        if(confirm("����Ʈ �󼼺��⸦ �����Ͻðڽ��ϱ�? (y/n)") == 1) {
            break;
        }
    }

    return 0;
}

int saveTagsFile(GLOBAL& _global, int count, TAG* tags)
{
    std::ifstream inTagConf;
    inTagConf.open(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        alert("Error: Tag Config File Open Failed", 500);
        return -1;
    }

    std::ofstream outTagTemp;
    outTagTemp.open(TAG_TEMP_NAME, std::ios::app);
    if(!outTagTemp) {
        alert("Error: Tag Config File Open Failed", 500);
        inTagConf.close();
        return -1;
    }

    int rtn;
    int pos;

    char changeLine[TAG_SIZE] = {0,};
    TAG  tag                  = {0,};

    for(pos = 0; pos < count; pos++) {
        memset(changeLine, 0x00, sizeof(changeLine));

        if(tags[pos].id == 0) {
            break;
        }

        tag = tags[pos];
        rtn = parseLineByTag(tag, changeLine);
        std::cout << "Tag: " << changeLine << std::endl;
        if(rtn < 0) {
            alert("Error: String Line Parsing Failed", 500);
            break;
        }

        outTagTemp << changeLine << '\n';
    }

    inTagConf.close();
    outTagTemp.close();

    if(std::rename(TAG_FILE_NAME, TAG_BKUP_NAME) != 0) {
        alert("Error: Tag Config File Backup is Failed.", 500);
        return -1;
    }

    if(std::rename(TAG_TEMP_NAME, TAG_FILE_NAME) != 0) {
        alert("Error: Tag Config File Save is Failed, Rollback...", 500);
        std::rename(TAG_BKUP_NAME, TAG_FILE_NAME);
        return -1;
    }

    if(std::remove(TAG_BKUP_NAME) != 0) {
        alert("Error: Tag Config File Save is Failed, Rollback...", 500);
        std::rename(TAG_BKUP_NAME, TAG_FILE_NAME);
        return -1;
    }

    rtn = getTagAllCnt(_global);
    if(rtn < 0) {
        alert("Error: Get Tag Count Failed", 1000);
    } else {
        _global.tag_count = rtn;
    }

    rtn = getTagLastIdByFile(_global);
    if(rtn < 0) {
        alert("Error: Get Tag Last ID Failed", 1000);
    } else {
        _global.tag_lastId = rtn;
    }

    return pos;
}

int editTags(GLOBAL& _global, int isFile, int count, TAG* output)
{
    TAG tag = {0,};

    int tag_cnt = count;
    int rtn;
    int key;

    while(true) {
        memset(&tag, 0x00, sizeof(tag));

        showTagsByArray(tag_cnt, output);

        key = onClickKeyEvent(TAG_EDIT_GUIDE);
        if( key == MODE_TAG_INSERT ||
            key == MODE_TAG_DELETE ) {

            switch(key) {
                case MODE_TAG_INSERT :
                    if(isFile) {
                        rtn = insertTagFile(_global, tag_cnt, output);
                    } else {
                        rtn = insertTagById(tag_cnt, output);
                    }
                break;
                case MODE_TAG_DELETE :
                    rtn = deleteTagById(tag_cnt, output);
                break;
            }

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
            alert("Invalid input. Please try again.", 1000);
        }
    }

    return tag_cnt;
}

int insertTagFile(GLOBAL& _global, int count, TAG* output)
{
    showTagsByArray(count, output);

    char name[64] = {0,};
    if(inputValueString("�±׸� �Է����ּ���.", sizeof(name), name) <= 0) {
        std::cout << "�ʼ� �Է� ���Դϴ�." << std::endl;
        return -1;
    }

    int pos;
    for(pos = 0; pos < count; pos++) {
        if(strcmp(output[pos].name, name) == 0) {
            alert("�ߺ��� �±��Դϴ�.", 1000);
            return -1;
        }
    }

    TAG tag = {0,};
    strcpy(tag.name, name);
    tag.id = getTagLastIdByArray(output, count) + 1;

    std::memcpy(&output[count], &tag, sizeof(tag));
    return count + 1;
}

int insertTagById(int count, TAG* output)
{
    showAllTags();

    uint id = 0;
    if(inputValueUInt("�±� ID�� �Է����ּ���.", id) <= 0) {
        std::cout << "�ʼ� �Է� ���Դϴ�." << std::endl;
        return -1;
    }

    int pos;
    for(pos = 0; pos < count; pos++) {
        if(output[pos].id == id) {
            alert("�ߺ��� �±� ID�Դϴ�.", 1000);
            return -1;
        }
    }

    TAG tag = {0,};
    if(findTag(id, tag) == 0) {
        alert("�ش��ϴ� �±װ� �����ϴ�.", 1000);
        return -1;
    }

    std::memcpy(&output[count], &tag, sizeof(tag));
    return count + 1;
}

int deleteTagById(int count, TAG* output)
{
    if(count <= 0) {
        alert("������ �±װ� �����ϴ�.", 1000);
        return -1;
    }

    TAG tag = {0,};
    int rtn = inputValueUInt("�±� ID�� �Է����ּ���.", tag.id);
    if(rtn == 0) {
        return -1;
    }

    if(confirm("�±׸� �����Ͻðڽ��ϱ�? (y/n)") <= 0) {
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

    if(apos < count) {
        count -= 1;
    }

    return count;
}

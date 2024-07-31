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

        memset(&list, 0x00, sizeof(list));

        key = onClickKeyEvent(NULL);
        switch(key) {
            case MODE_LIST_INSERT :
                rtn = insertList(_global, list);
            break;
            case MODE_LIST_UPDATE :
            break;
            case MODE_LIST_DELETE :
            break;
            case MODE_REFRESH:
                continue;
            case MODE_QUIET  :
                std::cout << "Bye" << std::endl;
                return 0;
        }

        if(rtn <= 0) {
            std::cout << "No save this list." << std::endl;
            continue;
        }

        printList(list);

        saveList(_global, list);
    }

    return 0;
}

int init(int argc, char *argv[], GLOBAL& _global)
{
    if(strlen(argv[1]) > 1024) {
        std::cerr << "filename too long: " << argv[1] << "(" << strlen(argv[1]) << "byte)"<< std::endl;
        return -1;
    }

    sprintf(_global.filename, "%s.txt", argv[1]);

    std::ifstream inTodoFile(_global.filename);
    if(!inTodoFile.good()) {
        std::cout << _global.filename << " not found." << std::endl;
        std::cout << "create new file: " << _global.filename << "..." << std::endl;

        std::ofstream outTodoFile(_global.filename);
        if(!outTodoFile.good()) {
            std::cerr << "cannot create file: " << _global.filename << std::endl;
            return -1;
        }
        outTodoFile.close();
    } else {
        std::string todoLine;
        while(std::getline(inTodoFile, todoLine)) {
            // 가장 큰 lastId와 가장 큰 index를 가져와 _global에 저장한다
        }
    }


    std::ifstream inTagConf(TAG_FILE_NAME);
    if(!inTagConf.good()) {
        std::cout << _global.filename << " not found." << std::endl;
        std::cout << "create new file: " << TAG_FILE_NAME << "..." << std::endl;

        std::ofstream outTagConf(TAG_FILE_NAME);
        if(!outTagConf.good()) {
            std::cerr << "cannot create file: " << TAG_FILE_NAME << std::endl;
            return -1;
        }
        outTagConf.close();
    } else {
        std::string tagLine;
        while(std::getline(inTagConf, tagLine)) {
            // 가장 큰 lastId와 가장 큰 index를 가져와 _global에 저장한다.
        }
    }

    return 0;
}

int saveList(GLOBAL& _global, LIST& list)
{
    if(_global.list_lastId > list.id) {
        _global.list_lastId = list.id;
    }

    if(_global.list_lastIdx > list.index) {
        _global.list_lastIdx = list.index;
    }

    return 0;
}


int insertList(GLOBAL& _global, LIST& list)
{
    int  rtn;
    uint tag_cnt       =  0;
    char title  [512 ] = {0,};
    char desc   [2048] = {0,};
    char nowDate[16  ] = {0,};
    char nowTime[16  ] = {0,};
    std::string input;

    inputValueStr("title"      , sizeof(title), title);
    inputValueStr("description", sizeof(desc) , desc );

    rtn = confirm("Want to add a tag?");
    if(rtn <= 0) {
        std::cout << "Skip adding tag." << std::endl;
    } else {
        tag_cnt = editTags(list);
    }

    getNowDate(NULL, sizeof(nowDate), nowDate);
    getNowTime(NULL, sizeof(nowTime), nowTime);

    list.id      = _global.list_lastId  + 1;
    list.index   = _global.list_lastIdx + 1;
    list.tag_cnt = tag_cnt;

    strcpy(list.in_date , nowDate   );
    strcpy(list.in_time , nowTime   );
    strcpy(list.title   , title     );
    strcpy(list.desc    , desc      );
    strcpy(list.clr_date, "00000000");
    strcpy(list.clr_time, "00000000");

    return confirm("Insert this list?");
}

int updateList(GLOBAL& _global, LIST& list)
{


    return confirm("Update this list?");
}

int deleteList(GLOBAL& _global, LIST& list)
{


    return confirm("Delete this list?");
}

int editTags(LIST& list)
{
    int tag_cnt = list.tag_cnt;
    if(tag_cnt == 0) {
        // 태그 추가 진행
    } else {
        int key;
        key = onClickKeyEvent(NULL);
        switch(key) {
            case MODE_TAG_ADD:
                addTag(list);
            break;
            case MODE_TAG_DEL:
                delTag(list);
            break;
        }
    }

    return tag_cnt;
}

int addTag(LIST& list)
{
    char name[64] = {0,};
    inputValueStr("tag name", sizeof(name), name);

    return 0;
}

int delTag(LIST& list)
{
    TAG tag = {0,};
    uint id;
    inputValueUInt("tag id", id);

    while(true) {

    }

    return 0;
}

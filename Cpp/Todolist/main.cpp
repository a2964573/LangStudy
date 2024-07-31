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


int insertList(GLOBAL& _global, LIST& output)
{
    char title  [256 ] = {0,};
    char desc   [1024] = {0,};
    char nowDate[16  ] = {0,};
    char nowTime[16  ] = {0,};

    inputValueStr("title"      , sizeof(title), title);
    inputValueStr("description", sizeof(desc) , desc );

    if(confirm("Edit tag?") > 0) {
        TAG tags[MAX_TAG_COUNT] = {0,};
        int tag_cnt = editTags(_global, output.tag_cnt, tags);
        
        output.tag_cnt = tag_cnt;
        std::memcpy(output.tags, tags, sizeof(tags[0]) * tag_cnt);
    }

    getNowDate(NULL, sizeof(nowDate), nowDate);
    getNowTime(NULL, sizeof(nowTime), nowTime);

    output.id      = _global.list_lastId  + 1;
    output.index   = _global.list_lastIdx + 1;

    strcpy(output.in_date , nowDate   );
    strcpy(output.in_time , nowTime   );
    strcpy(output.title   , title     );
    strcpy(output.desc    , desc      );
    strcpy(output.clr_date, "00000000");
    strcpy(output.clr_time, "00000000");

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

int editTags(GLOBAL& _global, int count, TAG* output)
{
    int tag_cnt = count;
    int apos;
    int bpos;
    int rtn;
    int key;

    TAG tag = {0,};

    while(true) {
        memset(&tag, 0x00, sizeof(tag));

        key = onClickKeyEvent("Input mode the Edit tag (a: Add, d: Del, e: End)");
        if(key == MODE_TAG_ADD) {
            if(tag_cnt >= MAX_TAG_COUNT) {
                std::cout << "Tag count over." << std::endl;
                continue;
            }

            inputValueUInt("tag id", tag.id);
            if(confirm("Add this tag?") <= 0) {
                continue;
            }

            rtn = findTag(tag.id, tag);
            if(rtn < 0) {
                std::cout << "find tag error." << std::endl;
            }
            else
            if(rtn == 0) {
                std::cout << "not found tag." << std::endl;
            }
            else {
                std::memcpy(&output[tag_cnt], &tag, sizeof(tag));
                tag_cnt++;
            }
        }
        else
        if(key == MODE_TAG_DEL) {
            if(tag_cnt <= 0) {
                std::cout << "Tag is zero." << std::endl;
                continue;
            }

            inputValueUInt("tag id", tag.id);
            if(confirm("Delete this tag?") <= 0) {
                continue;
            }

            apos = 0; // before index(original)
            bpos = 0; // after index(updated)
            while(true) {
                if(output[bpos].id == tag.id) {
                    bpos++;
                    continue;
                }
                else
                if(apos == bpos) {
                    continue;
                }
                else
                if(bpos >= tag_cnt) {
                    break;
                }

                std::memcpy(&output[apos], &output[bpos], sizeof(output[0]));
                apos++;
                bpos++;
            }

            tag_cnt--;
        }
        else
        if(key == MODE_TAG_END) {
            break;
        }
        else {
            std::cout << "Unknown key: " << key << std::endl;
        }
    }

    return tag_cnt;
}

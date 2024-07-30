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

        key = onClickKeyEvent();
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

        if(rtn < 0) {
            std::cerr << "Error: " << rtn << std::endl;
            continue;
        }

        printList(list);
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

    std::ifstream inputFile(_global.filename);
    if(!inputFile.good()) {
        std::cout << _global.filename << " not found." << std::endl;
        std::cout << "create new file: " << _global.filename << "..." << std::endl;

        std::ofstream outputFile(_global.filename);
        if(!outputFile.good()) {
            std::cerr << "cannot create file: " << _global.filename << std::endl;
            return -1;
        }
        outputFile.close();
    }

    return 0;
}

int insertList(GLOBAL& _global, LIST& list)
{
    int rtn;
    uint tag_cnt    = 0;
    char title[512] = {0,};
    char desc[2048] = {0,};
    std::string input;

    inputValue("title"      , sizeof(title), title);
    inputValue("description", sizeof(desc) , desc );

    rtn = confirm("Want to add a tag?");
    if(rtn <= 0) {
        std::cout << "Skip adding tag." << std::endl;
    } else {
        // tag_cnt = editTags(list);
    }

    list.id      = ++_global.last_id;
    list.index   = ++_global.list_count;
    list.tag_cnt = tag_cnt;

    strcpy(list.in_date , "00000000");
    strcpy(list.in_time , "00000000");
    strcpy(list.title   , title     );
    strcpy(list.desc    , desc      );
    strcpy(list.clr_date, "00000000");
    strcpy(list.clr_time, "00000000");

    rtn = confirm("Save this list?");
    if(rtn <= 0) {
        std::cout << "No save this list." << std::endl;
    } else {
        // saveList(list);
    }
}

int editTags(LIST& list)
{
    int tag_cnt = 0;

    return tag_cnt;
}
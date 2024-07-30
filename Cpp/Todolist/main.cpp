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

void showTitle() noexcept
{
    // system("cls");
    std::cout << TODOLIST << std::endl;
}

int onClickKeyEvent() noexcept
{
    int key = static_cast<int>(getch());
    if(65 <= key && key <= 90) {
        key += 32;
    }

    return key;
}

int insertList(GLOBAL& _global, LIST& list)
{
    uint tag_cnt    = 0;
    char title[512] = {0,};
    char desc[2048] = {0,};
    std::string input;

    std::cout << "Input now list title." << std::endl;
    std::cin >> input;
    if(input.length() > 256) {
        std::cerr << "list title too long: " << input << "(" << input.length() << "byte)" << std::endl;
        return -1;
    }
    strcpy(title, input.c_str());

    std::cout << "Input now list description." << std::endl;
    std::cin >> input;
    if(input.length() > 1024) {
        std::cerr << "list description too long: " << input << "(" << input.length() << "byte)" << std::endl;
        return -1;
    }
    strcpy(desc, input.c_str());

    std::cout << "Want to add a tag? (y/n)" << std::endl;
    int key = onClickKeyEvent();
    switch(key) {
        case ANSWER_YES :
            // tag_cnt = editTags(list);
        break;
        case ANSWER_NO  :
            std::cout << "No tag added." << std::endl;
        break;
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

    return 0;
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

int editTags(LIST& list)
{
    int tag_cnt = 0;

    return tag_cnt;
}
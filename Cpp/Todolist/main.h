#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iomanip>

#include <conio.h>

#define TODOLIST \
    "############################################\n" \
    "# #####      ###         #           ##### #\n" \
    "#   #        #  #        #             #   #\n" \
    "#   #        #   #       #             #   #\n" \
    "#   #   ###  #   #  ###  #     #  ###  #   #\n" \
    "#   #  #   # #   # #   # #       #     #   #\n" \
    "#   #  #   # #   # #   # #     #  ###  #   #\n" \
    "#   #  #   # #  #  #   # #     #     # #   #\n" \
    "#   #   ###  ###    ###  ##### #  ###  #   #\n" \
    "############################################\n"

#define TAG_FILE_NAME "_tag.ini"

#define ANSWER_YES        121
#define ANSWER_NO         110
#define MODE_LIST_INSERT  105
#define MODE_LIST_UPDATE  117
#define MODE_LIST_DELETE  100
#define MODE_TAG_ADD      97
#define MODE_TAG_DEL      100
#define MODE_TAG_END      101
#define MODE_REFRESH      114
#define MODE_QUIET        113

using uint = unsigned int;

typedef struct {
    char filename [1024];
    uint list_lastIdx;
    uint list_lastId;
    uint tag_lastIdx;
    uint tag_lastId;
} GLOBAL;

typedef struct {
    uint id;
    char name     [64  ];
} TAG;

#define MAX_TAG_COUNT 10
typedef struct {
    uint id;
    int  index;
    int  status;
    char in_date  [16  ];
    char in_time  [16  ];
    char title    [256 ];
    char desc     [1024];
    char clr_date [16  ];
    char clr_time [16  ];
    uint tag_cnt;
    TAG  tags     [MAX_TAG_COUNT];
} LIST;
#define LIST_SIZE sizeof(LIST)

// main
int init(int argc, char* argv[], GLOBAL& _global);
int saveList(GLOBAL& _global, LIST& list);
int insertList(GLOBAL& _global, LIST& list);
int editTags(GLOBAL& _global, int count, TAG* output);
int addTag(int count, TAG* output);
int delTag(int count, TAG* output);

// util
int showTitle() noexcept;
int showList(GLOBAL& _global);
int getListAll(GLOBAL& _global, LIST* output);
int parseCSVLine(const LIST& list, char* output);
int printList(const LIST& list) noexcept;
int showAllTags() noexcept;
int findTag(int tag_id, TAG& output);
int onClickKeyEvent(const char* message) noexcept;
int confirm(const char* message) noexcept;
int inputValueUInt(const char* name, uint& output) noexcept;
int inputValueWord(const char* name, int max_size, char* output) noexcept;
int inputValueString(const char* name, int max_size, char* output) noexcept;
int getNowDate(char* format, int size, char* output) noexcept;
int getNowTime(char* format, int size, char* output) noexcept;

#endif // MAIN_H

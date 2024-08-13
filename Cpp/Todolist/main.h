#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include <conio.h>
#include <windows.h>

// text
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
#define MENU_GUIDE \
    "q: Quit                r: Refresh             i: Insert List         u: Update List  \n" \
    "s: Show List Detail    d: Delete List         g: Edit Tags                           \n"
#define LIST_UPDATE_GUIDE \
    "                                                                     t: List Title   \n" \
    "a: List Content All    s: List Status         d: List Description    g: List Tags    \n"
#define TAG_EDIT_GUIDE \
    "                       e: End                 i: Insert Tag                          \n" \
    "                       d: Delete Tag                                                 \n"

// config
#define TAG_FILE_NAME         "_tag.ini"
#define TAG_BKUP_NAME         "_tag_bak.ini"
#define TAG_TEMP_NAME         "_tag_tmp.ini"
#define LINE_DECIMAL          (char)92
#define PRINT_TAG_FORMAT(tag) "#" << tag.id << ' ' << tag.name

// key confirm
#define ANSWER_YES         121
#define ANSWER_NO          110

// key menu
#define MODE_LIST_INSERT   105
#define MODE_LIST_UPDATE   117
#define MODE_LIST_DELETE   100
#define MODE_LIST_SHOW     115
#define MODE_TAG_EDIT      103
#define MODE_REFRESH       114
#define MODE_QUIET         113

// key list update
#define LIST_UPDATE_ALL    97
#define LIST_UPDATE_STATUS 115
#define LIST_UPDATE_TITLE  116
#define LIST_UPDATE_DESC   100
#define LIST_UPDATE_TAG    103

// key tag
#define MODE_TAG_INSERT    105
#define MODE_TAG_INSTID    105
#define MODE_TAG_INSTNM    110
#define MODE_TAG_UPDATE    117
#define MODE_TAG_DELETE    100
#define MODE_TAG_END       101

// value
#define LIST_CLEAR         1
#define LIST_UNCLEAR       0

using uint = unsigned int;

typedef struct {
    char filename [1024];
    char bkupname [1024];
    char tempname [1024];
    int  list_count;
    uint list_lastId;
    int  tag_count;
    uint tag_lastId;
} GLOBAL;

// tag
typedef struct {
    uint id;
    char name     [64  ];
} TAG;
#define TAG_SIZE sizeof(TAG)

enum {
    TAGID        = 1,
    TAGNAME      = 2
};

// list
#define MAX_TAG_COUNT 10
typedef struct {
    uint id;
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

enum {
    LISTID       = 1,
    LISTSTATUS   = 2,
    LISTIN_DATE  = 3,
    LISTIN_TIME  = 4,
    LISTTITLE    = 5,
    LISTDESC     = 6,
    LISTCLR_DATE = 7,
    LISTCLR_TIME = 8,
    LISTTAG_CNT  = 9
};


// main
int init(int argc, char* argv[], GLOBAL& _global);
int saveList(GLOBAL& _global, LIST& list);
int insertList(GLOBAL& _global, LIST& output);
int updateList(GLOBAL& _global, LIST& output);
int deleteList(GLOBAL& _global, LIST& output);
int showListDetail(GLOBAL& _global);
int saveTagsFile(GLOBAL& _global, int count, TAG* tags);
int editTags(GLOBAL& _global, int isFile, int count, TAG* output);
int insertTagFile(GLOBAL& _global, int count, TAG* output);
int insertTagById(int count, TAG* output);
int deleteTagById(int count, TAG* output);

// util
int showTitle() noexcept;
int showList(GLOBAL& _global);
int getListById(GLOBAL& _global, int id, LIST& output);
int getListAll(GLOBAL& _global, LIST* output);
int getListAllCnt(GLOBAL& _global);
int printList(const LIST list) noexcept;
int parseLineByList(const LIST list, char* output);
int parseLineByTag(const TAG tag, char* output);
int showTagsByListId(GLOBAL& _global, int id);
int showTagsByArray(int tag_cnt, const TAG* tags);
int showAllTags() noexcept;
int getTagAll(GLOBAL& _global, TAG* output);
int getTagAllCnt(GLOBAL& _global);
int getTagLastIdByFile(GLOBAL& _global);
int getTagLastIdByArray(TAG* tag_array, int count);
int findTag(int tag_id, TAG& output);
int findString(std::string str, int start, char target, std::string& output);
int getFieldValue(std::string str, int column, char target, std::string& output);
int onClickKeyEvent(const char* message) noexcept;
int confirm(const char* message) noexcept;
int inputValueUInt(const char* name, uint& output) noexcept;
int inputValueWord(const char* name, int max_size, char* output) noexcept;
int inputValueString(const char* name, int max_size, char* output) noexcept;
int getNowDate(char* format, int size, char* output) noexcept;
int getNowTime(char* format, int size, char* output) noexcept;
int alert(const char* message, uint second) noexcept;

#endif // MAIN_H

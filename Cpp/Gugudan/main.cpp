#include "main.h"

// argv[0]: program name
// argv[1]: start number
// argv[2]: end number
// argv[3]: maximum calculations
// argv[4]: columns
int main(int argc, char *argv[])
{
    if(argc < 5) {
        std::cerr << "Please enter more Arguments..." << std::endl;
        return -1;
    }

    SETTING setting = {0,};

    init(argc, argv, setting);
    std::cout << "Number              : " << setting.s_num    << " ~ " << setting.e_num << std::endl;
    std::cout << "Maximum calculations: " << setting.max_calc << std::endl;
    std::cout << "Columns             : " << setting.cols     << std::endl;

    if(validateSettings(setting) < 0) {
        return -1;
    }

    char output[20480] = {0,};

    int len = 0;
    int rpos;
    int mpos;
    int cpos;

    for(rpos = 1; rpos <= setting.rows; rpos++) {
        for(mpos = 1; mpos <= setting.max_calc; mpos++) {
            for(cpos = 0; cpos < setting.cols; cpos++) {
                if(setting.c_num + cpos > setting.e_num) {
                    continue;
                }

                len += multiply(setting.c_num + cpos, mpos, setting.digit, len, output);
            }
            output[len++] = '\n';
        }
        setting.c_num += setting.cols;
        output[len++] = '\n';
    }

    std::cout << output << std::endl;

    return 0;
}

void init(int argc, char *argv[], SETTING& setting)
{
    enum {
        S_NUM    = 1,
        E_NUM    = 2,
        MAX_CALC = 3,
        COLS     = 4
    };

    int pos;
    int itemp;
    for(pos = 1; pos < argc; pos++) {
        itemp = atoi(argv[pos]);

        switch(pos) {
            case S_NUM   :
                setting.s_num    = itemp != 0 ? itemp : 1;
            break;
            case E_NUM   :
                setting.e_num    = itemp != 0 ? itemp : 9;
            break;
            case MAX_CALC:
                setting.max_calc = itemp != 0 ? itemp : 9;
            break;
            case COLS    :
                setting.cols     = itemp != 0 ? itemp : 3;
            break;
            default:
                std::cerr << "Invalid argument: " << argv[pos] << std::endl;
            break;
        }
    }

    int offset = setting.e_num - setting.s_num + 1;

    setting.c_num = setting.s_num;
    setting.rows  = (offset / setting.cols) + (offset % setting.cols > 0 ? 1 : 0);
    setting.digit = getDigit(setting.e_num * setting.max_calc);
}

int validateSettings(SETTING& setting)
{
    if(setting.s_num > setting.e_num) {
        std::cerr << "Error: Start number must be less than or equal to end number." << std::endl;
        return -1;
    }

    if(setting.max_calc <= 0) {
        std::cerr << "Error: Maximum calculations must be greater than zero." << std::endl;
        return -1;
    }

    if(setting.cols <= 0) {
        std::cerr << "Error: Columns must be greater than zero." << std::endl;
        return -1;
    }

    return 0;
}

int getDigit(int number)
{
    int digit = 0;

    if(number % DIGIT_1       < DIGIT_1      ) {
        digit = 2;
    }
    else
    if(number % DIGIT_10      < DIGIT_10     ) {
        digit = 3;
    }
    else
    if(number % DIGIT_100     < DIGIT_100    ) {
        digit = 4;
    }
    else
    if(number % DIGIT_1000    < DIGIT_1000   ) {
        digit = 5;
    }
    else
    if(number % DIGIT_10000   < DIGIT_10000  ) {
        digit = 6;
    }
    else
    if(number % DIGIT_100000  < DIGIT_100000 ) {
        digit = 7;
    }
    else
    if(number % DIGIT_1000000 < DIGIT_1000000) {
        digit = 8;
    }

    return digit;
}

int multiply(int a, int b, int digit, int len, char* output)
{
    return std::sprintf(&output[len], "%*d * %-*d = %-*d"
        , digit, a
        , digit, b 
        , digit + 1, a * b);
}

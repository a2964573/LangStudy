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

    int key;
    while(true) {
        showTitle();

        key = static_cast<int>(getch());
        if(65 <= key && key <= 90) {
            key += 32;
        }

        switch(key) {
            case MODE_INSERT :
            break;
            case MODE_UPDATE :
            break;
            case MODE_DELETE :
            break;
            case MODE_REFRESH:
                continue;
            case MODE_QUIET  :
                std::cout << "Bye" << std::endl;
                return 0;
        }
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
    system("cls");
    std::cout << "#########################################"   << std::endl;
    std::cout << "# #####     ###        #          ##### #"   << std::endl;
    std::cout << "#   #       #  #       #            #   #"   << std::endl;
    std::cout << "#   #       #   #      #            #   #"   << std::endl;
    std::cout << "#   #   ##  #   #  ##  #     #  ##  #   #"   << std::endl;
    std::cout << "#   #  #  # #   # #  # #       #    #   #"   << std::endl;
    std::cout << "#   #  #  # #   # #  # #     #  ##  #   #"   << std::endl;
    std::cout << "#   #  #  # #  #  #  # #     #    # #   #"   << std::endl;
    std::cout << "#   #   ##  ###    ##  ##### #  ##  #   #"   << std::endl;
    std::cout << "#########################################\n" << std::endl;
}
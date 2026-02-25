#include <iostream>

int main(int argc, char* argv[]) {
    bool repeat = true;
    do {
        std::cout << "Enter command: ";
        int input;
        std::cin >> input;
        switch (input)
        {
            case 1:
                std::cout << "Number of arguments: " << (argc - 1) << "\n";
                break;
            case 2:
                std::cout << "Choose an argument: ";
                int args;
                std::cin >> args;
                if ((args > 0) && (args < argc)) {
                    std::cout << "Argument " << args << ": " << argv[args] << "\n";
                }
                else {
                    std::cerr << "Error: Argument out of range.\n";
                }
                break;
            case 3:
                std::cout << "All arguments: ";
                for (int i = 1; i < argc; i++) {
                    std::cout << argv[i] << ((i != argc - 1) ? ", " : ".\n");
                }
                break;
            case 4:
                std::cout << "Ending program.\n";
                repeat = false;
                break;
            default:
                std::cerr << "Error: Invalid command.\n";
                break;
        }
    } while (repeat);
    
    return 0;
}
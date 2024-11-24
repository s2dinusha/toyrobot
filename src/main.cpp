#include <fstream>
#include "nlohmann/json.hpp"
#include "robot.h"
#include "table.h"

using json = nlohmann::json;

void displayHelp() {
    std::cout << "Usage: ./robot [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --help        Display this help message\n";
    std::cout << "Usage: ./robot\n";
    std::cout << "Commands:\n";
    std::cout << "  PLACE x,y,d   Place robot on the table at (x, y) facing a given direction (d)\n";
    std::cout << "  MOVE          Move robot forward one unit in the current direction\n";
    std::cout << "  LEFT          Turn robot 90 degrees counter-clockwise\n";
    std::cout << "  RIGHT         Turn robot 90 degrees clockwise\n";
    std::cout << "  REPORT        Print the robot's current position and direction, then exit application\n";
    std::cout << "Valid directions are NORTH,EAST,SOUTH and WEST\n";
}

int main(int argc, char* argv[]) {

    if(argc > 1) {
        std::string option = argv[1];
        if (option == "--help")
            displayHelp();
        else
            std::cout << "Invalid args. For help run ./robot --help"  << std::endl;
        return 0;
    }

    displayHelp();

    int table_width = 5;
    int table_lenght = 5;

    try {
        std::ifstream config_file("./config/config.json");
        if (config_file.is_open()) {
            json config;
            config_file >> config;
            table_width = config["width"];
            table_lenght = config["length"];
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    Table table(table_width, table_lenght);
    Robot robot(table);
    std::string command;

    while (true) {
        std::getline(std::cin, command);
        robot.handleCommand(command);
        if (command == "REPORT") {
            break;
        }
    }

    return 0;
}

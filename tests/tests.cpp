#include <climits>
#include "gtest/gtest.h"
#include "robot.h"

// === Table Tests === //

TEST(TableTest1, TableDefaultDimentionTest) {
    Table table;
    EXPECT_EQ(table.getWidth(), 5);
    EXPECT_EQ(table.getHeight(), 5);
}

class TableTest2 : public ::testing::TestWithParam<std::tuple<int, int, int, int>> {};

INSTANTIATE_TEST_SUITE_P(
    TableDimentionTestParam,
    TableTest2,
    ::testing::Values(
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(-1, -1, 0, 0),
        std::make_tuple(-1, 1, 0, 1),
        std::make_tuple(1, -1, 1, 0),
        std::make_tuple(4, 4, 4, 4),
        std::make_tuple((INT_MAX + 1), (INT_MAX + 1), 0, 0) // Overflow test
    )
);

TEST_P(TableTest2, TableDimentionTest) {
    int x, y, width, height;
    std::tie(x, y, width, height) = GetParam();
    std::cout << "Running test with parameters (" << x << ", " << y << ", " << width << ", " << height <<")" << std::endl;
    Table table(x, y);
    EXPECT_EQ(table.getWidth(), width);
    EXPECT_EQ(table.getHeight(), height);
}

class TableTest3 : public ::testing::TestWithParam<std::tuple<int, int, bool>> {};

INSTANTIATE_TEST_SUITE_P(
    IsOn5x5TableTestParam,
    TableTest3,
    ::testing::Values(
        std::make_tuple(0, 0, true),
        std::make_tuple(-1, -1, false),
        std::make_tuple(-1, 0, false),
        std::make_tuple(0, -1, false),
        std::make_tuple(-1, 1, false),
        std::make_tuple(1, 1, true),
        std::make_tuple(4, 4, true),
        std::make_tuple(4, 5, false),
        std::make_tuple(5, 4, false),
        std::make_tuple((INT_MAX + 1), (INT_MAX + 1), false) // Overflow test
    )
);

TEST_P(TableTest3, IsOn5x5TableTest) {
    int x, y;
    bool isOn;
    std::tie(x, y, isOn) = GetParam();
    std::cout << std::boolalpha; 
    std::cout << "Running test with parameters (" << x << ", " << y << ", " << isOn << ")" << std::endl;
    Table table;
    EXPECT_EQ(table.isOnTable(x,y), isOn);
}

// === Robot Tests === //

class RobotTest1 : public ::testing::TestWithParam<std::tuple<int, int, Robot::Direction, Robot::Direction>> {};

INSTANTIATE_TEST_SUITE_P(
    RobotRotateRightOn5x5TableTestParam,
    RobotTest1,
    ::testing::Values(
        std::make_tuple(0, 0, Robot::Direction::EAST, Robot::Direction::SOUTH),
        std::make_tuple(0, 4, Robot::Direction::SOUTH, Robot::Direction::WEST),
        std::make_tuple(4, 4, Robot::Direction::WEST, Robot::Direction::NORTH),
        std::make_tuple(4, 0, Robot::Direction::NORTH, Robot::Direction::EAST)
    )
);

TEST_P(RobotTest1, RobotRotateRightOn5x5TableTest) {
    int x, y;
    Robot::Direction dir, right;
    std::tie(x, y, dir, right) = GetParam();
    std::cout << "Running test with parameters (" << x << ", " << y << ", " << dir << ", " << right << ")" << std::endl;
    Table table;
    Robot robot(table); 
    robot.commandPlace(x, y, dir);
    robot.commandRight();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(x, y, right));
}

class RobotTest2 : public ::testing::TestWithParam<std::tuple<int, int, Robot::Direction, Robot::Direction>> {};

INSTANTIATE_TEST_SUITE_P(
    CommandRotateLeftOn5x5TableTestParam,
    RobotTest2,
    ::testing::Values(
        std::make_tuple(0, 0, Robot::Direction::NORTH, Robot::Direction::WEST),
        std::make_tuple(0, 4, Robot::Direction::EAST, Robot::Direction::NORTH),
        std::make_tuple(4, 4, Robot::Direction::SOUTH, Robot::Direction::EAST),
        std::make_tuple(4, 0, Robot::Direction::WEST, Robot::Direction::SOUTH)
    )
);

TEST_P(RobotTest2, CommandRotateLeftOn5x5TableTest) {
    int x, y;
    Robot::Direction dir, left;
    std::tie(x, y, dir, left) = GetParam();
    std::cout << "Running test with parameters (" << x << ", " << y << ", " << dir << ", " << left << ")" << std::endl;
    Table table;
    Robot robot(table); 
    robot.commandPlace(x, y, dir);
    robot.commandLeft();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(x, y, left));
}

class RobotTest3 : public ::testing::TestWithParam<std::tuple<int, int, Robot::Direction>> {};

INSTANTIATE_TEST_SUITE_P(
    CommandMoveOutFailFromCornerOn5x5TableTestParam,
    RobotTest3,
    ::testing::Values(
        // move from south-west corner
        std::make_tuple(0, 0, Robot::Direction::SOUTH),
        std::make_tuple(0, 0, Robot::Direction::WEST),
        // move from north-west corner
        std::make_tuple(0, 4, Robot::Direction::NORTH),
        std::make_tuple(0, 4, Robot::Direction::WEST),
        // move from north-east corner
        std::make_tuple(4, 4, Robot::Direction::NORTH),
        std::make_tuple(4, 4, Robot::Direction::EAST),
        // move from south-east corner
        std::make_tuple(4, 0, Robot::Direction::SOUTH),
        std::make_tuple(4, 0, Robot::Direction::EAST)
    )
);

TEST_P(RobotTest3, CommandMoveOutFailFromCornerOn5x5TableTest) {
    int x, y;
    Robot::Direction dir;
    std::tie(x, y, dir) = GetParam();
    std::cout << "Running test with parameters (" << x << ", " << y << ", " << dir  << ")" << std::endl;
    Table table;
    Robot robot(table); 
    robot.commandPlace(x, y, dir);
    robot.commandMove();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(x, y, dir));
}

class RobotTest4 : public ::testing::TestWithParam<std::tuple<int, int, Robot::Direction, int, int>> {};

INSTANTIATE_TEST_SUITE_P(
    CommandMoveInSuccessFromCornerOn5x5TableTestParam,
    RobotTest4,
    ::testing::Values(
        // move from south-west corner
        std::make_tuple(0, 0, Robot::Direction::NORTH, 0, 1),
        std::make_tuple(0, 0, Robot::Direction::EAST, 1, 0),
        // move from north-west corner
        std::make_tuple(0, 4, Robot::Direction::SOUTH, 0, 3),
        std::make_tuple(0, 4, Robot::Direction::EAST, 1, 4),
        // move from north-east corner
        std::make_tuple(4, 4, Robot::Direction::SOUTH, 4, 3),
        std::make_tuple(4, 4, Robot::Direction::WEST, 3, 4),
        // move from south-east corner
        std::make_tuple(4, 0, Robot::Direction::NORTH, 4, 1),
        std::make_tuple(4, 0, Robot::Direction::WEST, 3, 0)
    )
);

TEST_P(RobotTest4, CommandMoveInSuccessFromCornerOn5x5TableTest) {
    int x, y, xNew, yNew;
    Robot::Direction dir;
    std::tie(x, y, dir, xNew, yNew) = GetParam();
    std::cout << "Running test with parameters (" << x << ", " << y << ", " << dir << ", " << xNew << ", " << yNew << ")" << std::endl;
    Table table;
    Robot robot(table); 
    robot.commandPlace(x, y, dir);
    robot.commandMove();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(xNew, yNew, dir));
}

TEST(RobotTest5, DoNotMoveOrRotateUntilPlacedOn5x5TableTest) {
    Table table;
    Robot robot(table); 
    robot.commandMove();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(-1, -1, Robot::Direction::NORTH));
    robot.commandLeft();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(-1, -1, Robot::Direction::NORTH));
    robot.commandRight();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(-1, -1, Robot::Direction::NORTH));
    robot.commandPlace(2, 2, Robot::Direction::EAST);
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(2, 2, Robot::Direction::EAST));
    robot.commandMove();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(3, 2, Robot::Direction::EAST));
    robot.commandLeft();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(3, 2, Robot::Direction::NORTH));
    robot.commandRight();
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(3, 2, Robot::Direction::EAST));
}

TEST(RobotTest6, PlaceOnMultiplePositionsOn5x5TableTest) {
    Table table;
    Robot robot(table);
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(-1, -1, Robot::Direction::NORTH));
    robot.commandPlace(2, 2, Robot::Direction::WEST);
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(2, 2, Robot::Direction::WEST));
    robot.commandPlace(10, 10, Robot::Direction::WEST); // Will not change position - Out of bounds
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(2, 2, Robot::Direction::WEST));
    robot.commandPlace(4, 4, Robot::Direction::SOUTH);
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(4, 4, Robot::Direction::SOUTH));
    robot.commandPlace(-1, -1, Robot::Direction::EAST); // Will not change position - Out of bounds
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(4, 4, Robot::Direction::SOUTH));
}

TEST(RobotTest7, ValidDirectionOn5x5TableTest) {
    Table table;
    Robot robot(table);
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(-1, -1, Robot::Direction::NORTH));
    robot.commandPlace(2, 2, Robot::Direction::WEST);
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(2, 2, Robot::Direction::WEST));
    robot.commandPlace(10, 10, Robot::Direction::WEST); // Will not change position - Out of bounds
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(2, 2, Robot::Direction::WEST));
    robot.commandPlace(4, 4, Robot::Direction::SOUTH);
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(4, 4, Robot::Direction::SOUTH));
    robot.commandPlace(-1, -1, Robot::Direction::EAST); // Will not change position - Out of bounds
    EXPECT_EQ(robot.getCurrentPosition(), std::make_tuple(4, 4, Robot::Direction::SOUTH));
}


TEST(RobotTest8, HandleCommandsOn5x5TableTest) {
    Table table;
    Robot robot(table);
    robot.handleCommand("PLACE 1,2,EAST"); // (1,2,EAST)
    robot.handleCommand("MOVE");           // (2,2,EAST)
    robot.handleCommand("MOVED");          // Invalid command
    robot.handleCommand("MOVE");           // (3,2,EAST)
    robot.handleCommand("LEFT");           // (3,2,NORTH)
    robot.handleCommand("LEFT");           // (3,2,WEST)
    robot.handleCommand("LIFT");           // Invalid command
    robot.handleCommand("LEFT");           // (3,2,SOUTH)
    robot.handleCommand("MOVE");           // (3,1,SOUTH)
    robot.handleCommand("RRIGHT");         // Invalid command
    robot.handleCommand("RIGHT");          // (3,1,WEST)
    robot.handleCommand("MOVE");           // (2,1,WEST)
    robot.handleCommand("REPORT");         // (2,1,WEST)
}
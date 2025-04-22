#include "processes.hpp"
#include "windowmanager.h"
#include "parser.h"
#include "parserConstants.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Parser parser({"10", "20", "100"}, "sum", parserConstants::test2, "130");
    //Parser parser({"10", "20", "100"}, "sum", parserConstants::test1, "130");
    // parser.addExpectEqual();
    // parser.addExpectEqual("15", "20");
    //parser.tokenize();
    Parser parser{};
    parser.tokenize_v2(parserConstants::test1);
    parser.createMock(parserConstants::class1);
     //parser.generateTestWithInputAndOutput("SumTests", "NegativeNumbersTest", {"10", "9", "14"}, "33");
    WindowManager* windowManager = WindowManager::init();
    windowManager->openStartMenu();
    return a.exec();
}


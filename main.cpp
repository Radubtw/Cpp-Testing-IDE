#include "GTestSetupFunctions.hpp"
#include "windowmanager.h"
#include "parser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Parser parser({"10", "20", "100"}, "sum", "a+b+c", "130");
    parser.addExpectEqual();
    parser.addExpectEqual("15", "20");
    WindowManager* windowManager = WindowManager::init();
    windowManager->openStartMenu();
    //QString zipFilePath = "C:\\Users\\Radu\\Desktop\\googletest-1.15.2.zip";
    //QString extractPath = "C:\\Users\\Radu\\Desktop";
    //unzipWithTar(zipFilePath, extractPath);
    //compileGTest(extractPath + "\\googletest-1.15.2");

    return a.exec();
}

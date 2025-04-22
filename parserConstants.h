#pragma once
#ifndef PARSERCONSTANTS_H
#define PARSERCONSTANTS_H
#include <QVector>
namespace parserConstants
{
inline const  QVector<QString> keywords{"alignas","alignof","and","and_eq","asm","auto"
        ,"bitand","bitor","bool","break","case","catch","char","char8_t","char16_t"
        ,"char32_t","class","compl","concept","const","consteval","constexpr","constinit"
        ,"const_cast","continue","co_await","co_return","co_yield","decltype","default"
        ,"delete","do","double","dynamic_cast","else","enum","explicit","export","extern"
        ,"false","final","float","for","friend","goto","if","inline","int","long","mutable"
        ,"namespace","new","noexcept","not","not_eq","nullptr","operator","or","or_eq","private"
        ,"protected","public","register","reinterpret_cast","requires","return","short","signed"
        ,"sizeof","static","static_assert","static_cast","struct","switch","template","this"
        ,"thread_local","throw","true","try","typedef","typeid","typename","union","unsigned"
        ,"using","virtual","void","volatile","wchar_t","while","xor","xor_eq"};

inline const QVector<QString> symbols{" ",";","::","++","--","++","--","+","-","!","~","*","&","+","-"
                               ,"*","/","%","==","!=",">","<",">=","<=","&&","||"
                               ,"&","|","^","<<",">>","+=","-=","*=","/=","%=",">>="
                               ,"<<=","&=","^=","|=","->*",",","=","[]","{}", "()","->","."
                                ,".*", "[", "]", "(",")", "?", "{", "}", ":"};

inline const QString test1{R"(
void CreateNewProjectWindow::saveFileContent(int xCoord, int yCoord, double zCoord, string name)
{
    if(not QFileInfo(currentFilePath).isFile())
    {
        return;
    }
    QFile file(currentFilePath);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << codeField->toPlainText();
    }
})"};

inline const QString test2{"a void lala::xx()aaaa/lala=aa;"};

inline const QString class1{R"(
class Turtle {
  virtual void PenUp() = 0;
  virtual void PenDown() = 0;
  virtual void Forward(int distance, int speed) = 0;
  virtual void Turn(int degrees, double something) = 0;
  virtual void GoTo(int x, int y) = 0;
  virtual int GetX() const = 0;
  virtual int GetY() const = 0;
};
)"};

inline const QString outputFile{R"(
Running TestsUpdateCTestConfiguration  from :D:/Testing_2/build/DartConfiguration.tcl
UpdateCTestConfiguration  from :D:/Testing_2/build/DartConfiguration.tcl
Test project D:/Testing_2/build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: MyProject_tests

1: Test command: D:\Testing_2\build\Component1\tests\MyProject_tests.exe
1: Working Directory: D:/Testing_2/build/Component1/tests
1: Test timeout computed to be: 10000000
1: [==========] Running 5 tests from 3 test suites.
1: [----------] Global test environment set-up.
1: [----------] 1 test from myCount
1: [ RUN      ] myCount.test
1: D:/Testing_2/Component1/tests/tests.cpp:40: Failure
1: Actual function call count doesn't match EXPECT_CALL(mockObj, myStrlen(input))...
1:          Expected: to be called once
1:            Actual: never called - unsatisfied and active
1:
1: [  FAILED  ] myCount.test (5004 ms)
1: [----------] 1 test from myCount (5004 ms total)
1:
1: [----------] 3 tests from sumTest
1: [ RUN      ] sumTest.positives
1: [       OK ] sumTest.positives (0 ms)
1: [ RUN      ] sumTest.negatives
1: [       OK ] sumTest.negatives (0 ms)
1: [ RUN      ] sumTest.positiveAndNegative
1: [       OK ] sumTest.positiveAndNegative (0 ms)
1: [----------] 3 tests from sumTest (0 ms total)
1:
1: [----------] 1 test from MathSuite
1: [ RUN      ] MathSuite.computeResult10and25Test
1: [       OK ] MathSuite.computeResult10and25Test (0 ms)
1: [----------] 1 test from MathSuite (0 ms total)
1:
1: [----------] Global test environment tear-down
1: [==========] 5 tests from 3 test suites ran. (5005 ms total)
1: [  PASSED  ] 4 tests.
1: [  FAILED  ] 1 test, listed below:
1: [  FAILED  ] myCount.test
1:
1:  1 FAILED TEST
1/1 Test #1: MyProject_tests ..................***Failed    5.02 sec

0% tests passed, 1 tests failed out of 1

Total Test time (real) =   5.02 sec

The following tests FAILED:
      1 - MyProject_tests (Failed)
Tests ran successfully!
)"};

}
#endif // PARSERCONSTANTS_H

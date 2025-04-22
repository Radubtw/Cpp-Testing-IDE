#include "testwrapper.h"

TestWrapper::TestWrapper() {}

TestWrapper::TestWrapper(QString testSuite, QString testName, QString output, bool isFailed, int timeInMs) :
    testSuite(testSuite), testName(testName), output(output), isFailed(isFailed), timeInMs(timeInMs) {}

QString TestWrapper::toString() const
{
    QString testString = "Test Suite: " + testSuite + "\n";
    testString += "Test Name: " + testName + "\n";
    testString += "Test Restult: ";
    isFailed ? testString += "FAILED\n" : testString += "PASSED\n";
    testString += "Time: " + QString::number(timeInMs) + "ms\n";
    testString += "Output:\n" + output + "\n";
    return testString;
}

float TestWrapper::calculatePercentFailed(QVector<TestWrapper> tests)
{
    int failedTests{0};
    for(const auto& test : tests)
    {
        if(test.isFailed)
        {
            failedTests++;
        }
    }
    return (float(failedTests) / float(tests.size())) * 100;
}

int TestWrapper::numberOfFailedTestsInSuite(QVector<TestWrapper> tests)
{
    int failedTests{0};
    for(const auto& test : tests)
    {
        if(test.isFailed)
        {
            failedTests++;
        }
    }
    return failedTests;
}

QVector<QString> TestWrapper::failedTestSuites(QVector<TestWrapper> tests)
{
    QVector<QString> failedTestSuites{};
    for(const auto& test : tests)
    {
        if(test.isFailed && !failedTestSuites.contains(test.testSuite))
        {
            failedTestSuites.push_back(test.testSuite);
        }
    }
    return failedTestSuites;
}

QVector<QString> TestWrapper::passedTestSuites(QVector<TestWrapper> tests)
{
    QVector<QString> passedTestSuites{};
    QVector<QString> failedTestSuites{TestWrapper::failedTestSuites(tests)};
    for(const auto& test : tests)
    {
        if(!failedTestSuites.contains(test.testSuite) && !passedTestSuites.contains(test.testSuite))
        {
            passedTestSuites.push_back(test.testSuite);
        }
    }
    return passedTestSuites;
}

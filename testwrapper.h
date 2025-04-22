#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <QString>
#include <QVector>
class TestWrapper
{
public:
    TestWrapper();
    TestWrapper(QString testSuite, QString testName, QString output, bool isFailed, int timeInMs);
    QString testSuite;
    QString testName;
    QString output;
    bool isFailed;
    int timeInMs;

    QString toString() const;
    static float calculatePercentFailed(QVector<TestWrapper> tests);
    static QVector<QString> failedTestSuites(QVector<TestWrapper> tests);
    static QVector<QString> passedTestSuites(QVector<TestWrapper> tests);
    static int numberOfFailedTestsInSuite(QVector<TestWrapper> tests);
};

#endif // TESTWRAPPER_H

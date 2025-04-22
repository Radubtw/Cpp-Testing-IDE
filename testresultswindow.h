#ifndef TESTRESULTSWINDOW_H
#define TESTRESULTSWINDOW_H

#include <QWidget>
#include <QDir>
#include <QVector>
#include <QString>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QVector>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include "testwrapper.h"

class TestResultsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TestResultsWindow(QDir projectPath, QWidget *parent = nullptr);
    void initLayout();
    void interpretOutputFile();
private:
    QDir projectPath;
    QString testsOutputString;
    QString currentSuite;
    QPieSeries* series;
    QPieSeries* testsSeries;
    QPieSeries* singleTestSeries;
    QChart* allSuitesChart;
    QChart* currentSuiteChart;
    QChart* singleTestChart;
    QChartView* chartView;
    QVector<TestWrapper> tests;
    QGridLayout* layout;
    QTextEdit* testOutput;
    QPushButton* backButton;
    QVector<QString> failedTestSuites;
    QVector<QString> passedTestSuites;

    void setCurrentSuiteOutputText(QString suite);
    void setBaseTestOutputText(QVector<QString> failedTestSuites, QVector<QString> passedTestSuites);
    float calculatePassedSuitesPercentage(QVector<QString> passedSuites, QVector<QString> failedSuites);
signals:
private slots:
    void back();
    void openTestSuite(QPieSlice* slice);
    void openSingleTest(QPieSlice* slice);
};

#endif // TESTRESULTSWINDOW_H

#include "testresultswindow.h"
#include <QDebug>
#include <QFile>
#include <QLegend>
#include <QLegendMarker>
#include <QHBoxLayout>
#include <QScrollBar>

TestResultsWindow::TestResultsWindow(QDir projectPath, QWidget *parent)
    : QWidget{parent}
    , projectPath(projectPath)
{
    setWindowTitle("Test Results");
    setMinimumSize(600,600);
    qDebug() << "WINDOW OPENED";
    initLayout();
    connect(series, &QPieSeries::clicked, this, &TestResultsWindow::openTestSuite);
    connect(backButton, &QPushButton::clicked, this, &TestResultsWindow::back);
}

void TestResultsWindow::initLayout()
{
    layout = new QGridLayout(this);

    interpretOutputFile();
    failedTestSuites = TestWrapper::failedTestSuites(tests);
    passedTestSuites = TestWrapper::passedTestSuites(tests);
    auto passedPercentage = calculatePassedSuitesPercentage(passedTestSuites, failedTestSuites);
    series = new QPieSeries();
    for(const auto& suite : failedTestSuites)
    {
        series->append(suite, (100 - passedPercentage) / failedTestSuites.size());
        series->slices().back()->setBrush(Qt::red);
        series->slices().back()->setLabelVisible(true);
    }
    for(const auto& suite : passedTestSuites)
    {
        series->append(suite, passedPercentage / passedTestSuites.size());
        series->slices().back()->setBrush(Qt::green);
        series->slices().back()->setLabelVisible(true);
    }

    allSuitesChart = new QChart();
    allSuitesChart->addSeries(series);
    allSuitesChart->setTitle("Results of test suites");
    allSuitesChart->legend()->setAlignment(Qt::AlignBottom);
    QList<QLegendMarker*> markers = allSuitesChart->legend()->markers();
    QList<QLegendMarker*> passedAndFailedMarkers;
    bool greenOk = false;
    bool redOk = false;
    for(auto marker : markers)
    {
        if(!greenOk && marker->brush() == Qt::green)
        {
            greenOk = true;
            marker->setLabel("Passed");
            passedAndFailedMarkers.push_back(marker);
        }
        else if(!redOk && marker->brush() == Qt::red)
        {
            redOk = true;
            marker->setLabel("Failed");
            passedAndFailedMarkers.push_back(marker);
        }
        else
        {
            marker->setVisible(false);
        }
    }
    if(passedAndFailedMarkers.size() == 2 && passedAndFailedMarkers[0]->label() == "Failed")
    {
        passedAndFailedMarkers[0]->setLabel("Passed");
        passedAndFailedMarkers[0]->setBrush(Qt::green);
        passedAndFailedMarkers[1]->setLabel("Failed");
        passedAndFailedMarkers[1]->setBrush(Qt::red);
    }
    chartView = new QChartView(allSuitesChart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(500, 400);
    chartView->show();

    testOutput = new QTextEdit();
    testOutput->setReadOnly(true);
    backButton = new QPushButton("Back");
    infoSection = new QLabel();
    infoSection->setWordWrap(true);

    baseInfoSectionText += "Passed Percentage: " + QString::number(passedPercentage) + "%\n";
    baseInfoSectionText += "Total time: " + QString::number(TestWrapper::calculateTotalTime(tests)) + " ms";
    infoSection->setText(baseInfoSectionText);

    layout->addWidget(chartView, 0, 0, 11, 4);
    layout->addWidget(testOutput, 1, 4, 10, 2);
    layout->addWidget(infoSection, 0, 4, 1, 1);
    layout->addWidget(backButton, 0, 5, 1, 1);

    backButton->setText("Close");
    qDebug() << "TIME IN MS: " << TestWrapper::calculateTotalTime(tests);

    setBaseTestOutputText(failedTestSuites, passedTestSuites);
    testOutput->verticalScrollBar()->setValue(testOutput->verticalScrollBar()->maximum());
}

void TestResultsWindow::openTestSuite(QPieSlice* slice)
{
    QVector<TestWrapper> testsInSuite{};
    testsSeries = new QPieSeries();
    connect(testsSeries, &QPieSeries::clicked, this, &TestResultsWindow::openSingleTest);
    currentSuiteChart = new QChart();
    for(const auto& test : tests)
    {
        if(test.testSuite == slice->label())
        {
            testsInSuite.push_back(test);
        }
    }
    currentSuite = slice->label();

    for(const auto& test : testsInSuite)
    {
        testsSeries->append(test.testName, (100.0f / testsInSuite.size()));
        if(!test.isFailed)
        {
            testsSeries->slices().back()->setBrush(Qt::green);
        }
        else if(test.isFailed)
        {
            testsSeries->slices().back()->setBrush(Qt::red);
        }
        testsSeries->slices().back()->setLabelVisible(true);
    }
    currentSuiteChart = new QChart();
    currentSuiteChart->addSeries(testsSeries);
    currentSuiteChart->setTitle("Results of tests from " + testsInSuite.front().testSuite + " suite");
    currentSuiteChart->legend()->setAlignment(Qt::AlignBottom);
    //currentSuiteChart->legend()->hide();
    chartView->setChart(currentSuiteChart);
    testOutput->clear();
    for(const auto& test : testsInSuite)
    {
        if(test.isFailed == true)
        {
            testOutput->append(test.toString());
        }
    }

    for(const auto& test : testsInSuite)
    {
        if(test.isFailed == false)
        {
            testOutput->append(test.toString());
        }
    }

    QList<QLegendMarker*> markers = currentSuiteChart->legend()->markers();
    QList<QLegendMarker*> passedAndFailedMarkers;
    bool greenOk = false;
    bool redOk = false;
    for(auto marker : markers)
    {
        if(!greenOk && marker->brush() == Qt::green)
        {
            greenOk = true;
            marker->setLabel("Passed");
            passedAndFailedMarkers.push_back(marker);
        }
        else if(!redOk && marker->brush() == Qt::red)
        {
            redOk = true;
            marker->setLabel("Failed");
            passedAndFailedMarkers.push_back(marker);
        }
        else
        {
            marker->setVisible(false);
        }
    }
    if(passedAndFailedMarkers.size() == 2 && passedAndFailedMarkers[0]->label() == "Failed")
    {
        passedAndFailedMarkers[0]->setLabel("Passed");
        passedAndFailedMarkers[0]->setBrush(Qt::green);
        passedAndFailedMarkers[1]->setLabel("Failed");
        passedAndFailedMarkers[1]->setBrush(Qt::red);
    }
    qDebug() << "SUITE TIME IN MS: " << TestWrapper::calculateTotalTimePerSuite(tests, currentSuite);

    suiteInfoSectionText.clear();
    suiteInfoSectionText += "Passed Percentage: " + QString::number(100.00f - TestWrapper::calculatePercentFailed(testsInSuite)) + "%\n";
    suiteInfoSectionText += "Total time: " + QString::number(TestWrapper::calculateTotalTimePerSuite(tests, currentSuite)) + " ms";
    infoSection->setText(suiteInfoSectionText);

    backButton->setText("Back");
}

void TestResultsWindow::openSingleTest(QPieSlice* slice)
{
    for(const auto& test : tests)
    {
        qDebug() << "LHS: " << test.testName.trimmed() << " == " << "RHS: " << slice->label().trimmed();
        if(test.testName.trimmed() == slice->label().trimmed())
        {
            testOutput->clear();
            testOutput->append(test.toString());
            singleTestSeries = new QPieSeries();
            singleTestSeries->append(test.testName, 100);
            if(test.isFailed)
            {
                singleTestSeries->slices().front()->setBrush(Qt::red);
            }
            else
            {
                singleTestSeries->slices().front()->setBrush(Qt::green);
            }
            singleTestChart = new QChart();
            singleTestChart->setTitle("Result of " + test.testName);
            singleTestChart->addSeries(singleTestSeries);
            chartView->setChart(singleTestChart);
            test.isFailed ? singleTestChart->legend()->markers(singleTestSeries).front()->setLabel("Failed") :
                singleTestChart->legend()->markers(singleTestSeries).front()->setLabel("Passed");
            singleTestChart->legend()->setAlignment(Qt::AlignBottom);

            testInfoSectionText.clear();
            test.isFailed ? testInfoSectionText += "Failed\n" : testInfoSectionText += "Passed\n";
            testInfoSectionText += "Total time: " + test.timeInMs+ " ms";
            infoSection->setText(testInfoSectionText);

            return;
        }
    }


}

void TestResultsWindow::interpretOutputFile()
{
    QFile file(projectPath.absolutePath() + "/testsOutput.log");
    file.open(QIODevice::ReadOnly); //TODO: check if it does not exist
    testsOutputString.append(file.readAll());
    qDebug() << testsOutputString;
    file.close();

    const QString    run{"[ RUN      ]"};
    const QString     ok{"[       OK ]"};
    const QString failed{"[  FAILED  ]"};
    QString testSuite;
    QString testName;
    QString output;
    bool isFailed = false;
    QString timeInMs;
    QHash<QString, QString> nameAndOutput;
    int i = 0;
    int offset = 0;
    while(i < testsOutputString.length())
    {
        testSuite = "";
        testName = "";
        output = "";
        timeInMs = "";
        QString slice = testsOutputString.sliced(i);
        if(slice.indexOf(run) != -1)
        {
            offset = slice.indexOf(run) + run.length();
            slice = testsOutputString.sliced(i);
            qDebug() << "I:" << i;
            offset++;
            while((offset < slice.length()) && (slice[offset] != '.'))
            {
                testSuite += slice[offset++];
            }
            offset++;
            while((offset < slice.length()) && (slice[offset] != '\n'))
            {
                testName += slice[offset++];
            }
            slice = slice.sliced(offset);
            qDebug() << "SLICE-----------------";
            qDebug() << slice;
            qDebug() << "-----------------------------------";
            if(slice.indexOf(failed) != -1 && (slice.indexOf(failed) < slice.indexOf(ok)))
            {
                isFailed = true;
            }
            else
            {
                isFailed = false;
            }
            i+= offset;
            offset = 0;
            while(offset < slice.length())
            {
                if(offset >= slice.indexOf(failed) || offset >= slice.indexOf(ok))
                {
                    break;
                }

                output += slice[offset++];
            }
            if(output.size() == 4)
            {
                output = "NO OUTPUT\n";
            }
            offset += ok.length();
            while((offset < slice.length()) && (slice[offset] != '('))
            {
                offset++;
            }
            while((offset < slice.length()) && (slice[offset] != ' '))
            {
                timeInMs+= slice[++offset];
            }

            tests.append(TestWrapper{testSuite,testName, output.trimmed(), isFailed, timeInMs});
            i+= offset;
        }
        else
        {
            break;
        }
    }

    for(const auto& test : tests)
    {
        qDebug() << "TestSuite:" << test.testSuite;
        qDebug() << "TestName:"  << test.testName;
        qDebug() << "Output:"    << test.output;
        qDebug() << "isFailed:" << test.isFailed;
        qDebug() << "Time:" << test.timeInMs;
        qDebug() << "--------------";
    }
    qDebug() << "Failed Tests:"<<TestWrapper::calculatePercentFailed(tests) << "%";
}

float TestResultsWindow::calculatePassedSuitesPercentage(QVector<QString> passedSuites, QVector<QString> failedSuites)
{
    return (float(passedSuites.size()) / float(passedSuites.size() + failedSuites.size())) * 100;
}

void TestResultsWindow::setBaseTestOutputText(QVector<QString> failedTestSuites, QVector<QString> passedTestSuites)
{
    for(const auto& suite : failedTestSuites)
    {
        for(const auto& test : tests)
        {
            if(test.testSuite == suite)
            {
                testOutput->append(test.toString());
            }
        }
    }

    for(const auto& suite : passedTestSuites)
    {
        for(const auto& test : tests)
        {
            if(test.testSuite == suite)
            {
                testOutput->append(test.toString());
            }
        }
    }
}
void TestResultsWindow::setCurrentSuiteOutputText(QString suite)
{
    for(const auto& test : tests)
    {
        if(test.testSuite == suite)
        {
            testOutput->append(test.toString());
        }
    }
}
void TestResultsWindow::back()
{
    testOutput->clear();
    if(chartView->chart() == allSuitesChart)
    {
        close();
    }
    else if(chartView->chart() == currentSuiteChart)
    {
        setBaseTestOutputText(failedTestSuites, passedTestSuites);
        chartView->setChart(allSuitesChart);
        backButton->setText("Close");

        infoSection->setText(baseInfoSectionText);
    }
    else if(chartView->chart() == singleTestChart)
    {
        chartView->setChart(currentSuiteChart);
        setCurrentSuiteOutputText(currentSuite);
        singleTestSeries->slices().front()->label();

        infoSection->setText(suiteInfoSectionText);
    }
}

#include "generatetestdialog.h"

#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>


namespace
{

}

GenerateTestDialog::GenerateTestDialog(QWidget* parent) : QDialog(parent)
{
    initLayout();
}

void GenerateTestDialog::initLayout()
{
    layout = new QGridLayout(this);
    QLabel* testSuiteNameLabel = new QLabel("Test Suite Name:", this);
    testSuiteNameEdit = new QLineEdit(this);
    QLabel* testCaseNameLabel = new QLabel("Testcase Name:", this);
    testCaseNameEdit = new QLineEdit(this);
    QLabel* functionInputsLabel = new QLabel("Inputs:", this);
    functionInputsEdit = new QLineEdit(this);
    QLabel* functionOutputLabel = new QLabel("Output:", this);
    functionOutputEdit = new QLineEdit(this);

    layout->addWidget(testSuiteNameLabel,rowCounter,0);
    layout->addWidget(testSuiteNameEdit, rowCounter,1);
    rowCounter++;
    layout->addWidget(testCaseNameLabel,rowCounter,0);
    layout->addWidget(testCaseNameEdit, rowCounter,1);
    rowCounter++;
    layout->addWidget(functionInputsLabel,rowCounter,0);
    layout->addWidget(functionInputsEdit, rowCounter,1);
    rowCounter++;
    layout->addWidget(functionOutputLabel,rowCounter,0);
    layout->addWidget(functionOutputEdit, rowCounter,1);
    rowCounter++;
    setLayout(layout);
    resize(200, 200);
    setStyleSheet(R"(background : #FFFFFF)");



    buttonBox = new QDialogButtonBox
        ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
         Qt::Horizontal, this );

    addExpectCallButton = new QPushButton("Add EXPECT_CALL");
    layout->addWidget(addExpectCallButton);
    layout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &GenerateTestDialog::onAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GenerateTestDialog::reject);
    connect(addExpectCallButton, &QPushButton::clicked, this, &GenerateTestDialog::addExpectCall);
}

void GenerateTestDialog::addExpectCall()
{
    QLabel* expectCallLabel = new QLabel("EXPECT CALL: ", this);

    layout->addWidget(expectCallLabel);
    QLineEdit* expectedObjectName = new QLineEdit(this);
    QLineEdit* expectedFunctionCall = new QLineEdit(this);
    QLineEdit* times = new QLineEdit(this);
    QLineEdit* returnValue = new QLineEdit(this);

    expectedObjectName->setPlaceholderText("Object");
    expectedFunctionCall->setPlaceholderText("Function");
    times->setPlaceholderText("Times");
    returnValue->setPlaceholderText("Return Value");


    expectCallFields.push_back(expectedObjectName);
    expectCallFields.push_back(expectedFunctionCall);
    expectCallFields.push_back(times);
    expectCallFields.push_back(returnValue);


    layout->addWidget(expectCallLabel, rowCounter, 0);
    layout->addWidget(expectedObjectName, rowCounter, 1);
    layout->addWidget(expectedFunctionCall, rowCounter, 2);
    layout->addWidget(times, rowCounter, 3);
    layout->addWidget(returnValue, rowCounter, 4);
    rowCounter++;
    layout->removeWidget(addExpectCallButton);
    layout->removeWidget(buttonBox);
    layout->addWidget(addExpectCallButton, rowCounter++, 1);
    layout->addWidget(buttonBox);
}

void GenerateTestDialog::onAccept()
{
    for(int i = 0; i < expectCallFields.size(); i = i + 4)
    {
        ExpectCall expectCallObj{};

        expectCallObj.object = expectCallFields[i]->text();
        expectCallObj.function = expectCallFields[i + 1]->text();
        expectCallObj.times = expectCallFields[i + 2]->text();
        expectCallObj.returnValue = expectCallFields[i + 3]->text();
        expectCalls.push_back(expectCallObj);
    }
    accept();
}

QString GenerateTestDialog::getTestSuiteName()
{
    return testSuiteNameEdit->text();
}

QString GenerateTestDialog::getTestCaseName()
{
    return testCaseNameEdit->text();
}

QString GenerateTestDialog::getFunctionInputs()
{
    return functionInputsEdit->text();
}

QString GenerateTestDialog::getFunctionOutput()
{
    return functionOutputEdit->text();
}

QVector<ExpectCall> GenerateTestDialog::getExpectCalls()
{
    return expectCalls;
}

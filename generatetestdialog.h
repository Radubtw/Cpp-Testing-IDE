#ifndef GENERATETESTDIALOG_H
#define GENERATETESTDIALOG_H

#include <QDialog>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDialogButtonBox>
#include "ExpectCall.h"

class GenerateTestDialog : public QDialog
{
    Q_OBJECT
public:
    GenerateTestDialog(QWidget* parent = nullptr);
    void initLayout();
    QString getTestSuiteName();
    QString getTestCaseName();
    QString getFunctionInputs();
    QString getFunctionOutput();
    QVector<ExpectCall> getExpectCalls();

private:
    QVector<ExpectCall> expectCalls;
    QVector<QLineEdit*> expectCallFields;
    QGridLayout* layout;
    QLineEdit* testSuiteNameEdit;
    QLineEdit* testCaseNameEdit;
    QLineEdit* functionInputsEdit;
    QLineEdit* functionOutputEdit;
    QPushButton* addExpectCallButton;
    QDialogButtonBox *buttonBox;
    int rowCounter{0};
private slots:
    void addExpectCall();
    void onAccept();
};

#endif // GENERATETESTDIALOG_H

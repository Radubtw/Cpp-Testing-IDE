#pragma once
#ifndef PARSER_H
#define PARSER_H
#include <QMap>
#include <QVector>
#include "ExpectCall.h"
/*
 *types:
 * 1 - non-void function without mocks
 * 2 - non-void function with mocks
 * 3 - void function without mocks
 * 4 - void function with mocks
*/
class Parser
{
public:
    Parser(QVector<QString> inputs, QString functionName, QString function, QString output);
    Parser(QString classImplementation);
    Parser();
    QVector<QString> tokenize(QString input);//TODO important
    QVector<QString> tokenize_v2(QString input);
    void addExpectEqual(QVector<QString>& inputs, QString& output);
    void addExpectEqual(QString lhs, QString rhs);
    void addExpectCall(QString objectName, QString functionName, QVector<QString> functionParameters);
    void addGTestInclude();
    void addGMockInclude();
    void writeTestToFile(int testType);

    QVector<QString> findPossibleMocks();
    QString getGeneratedTest();
    QString createMock(QString classDefinition);
    QString addMockMethod(QString methodName, QString methodType, QString methodParameters, bool isConst);
    QString addTestName(QString& testSuiteName, QString& testCaseName);
    QString addExpectCalls(QVector<ExpectCall> expectCalls);

    void generateTestWithInputAndOutput(QString functionBody, QString testSuiteName, QString testCaseName, QVector<QString> inputs, QString output, QVector<ExpectCall> expectCalls);

    int containsSymbol(QString input);
    bool isSymbol(QString input);

public:
    //QVector<QString> tokens;
private:
    bool isTest;
    QString filePath;
    QVector<QString> inputs;
    QString functionName;
    QString function;
    QString output;
    QString generatedTest;
    QString classImplementation;
    QString generatedMock;
};

#endif // PARSER_H

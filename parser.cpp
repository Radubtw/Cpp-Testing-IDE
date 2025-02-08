#include "parser.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
Parser::Parser(QVector<QString> inputs, QString functionName, QString function, QString output) :
    inputs(inputs),functionName(functionName), function(function), output(output)
{
    isTest = true;
    generatedTest = "";
}

Parser::Parser(QString className, QString classImplementation) : className(className), classImplementation(classImplementation)
{
    isTest = false;
    generatedMock = "";
}

void Parser::tokenize()
{
    //TODO
}

void Parser::addGTestInclude()
{
    generatedTest.append("#include<gtest/gtest.h>");
}

void Parser::addGMockInclude()
{
    generatedTest.append("#include<gmock/gmock.h>");
}

void Parser::addExpectEqual()
{
    QString stringifiedInputs;
    for(const auto &input : inputs)
    {
        stringifiedInputs += input;
        if(inputs.indexOf(input) != inputs.size() - 1)
        {
            stringifiedInputs += ",";
        }
    }
    generatedTest.append("EXPECT_EQ("+functionName+"(" + stringifiedInputs + "), " + output + ")" + "\n");
    qDebug() << "GeneratedTest: " << generatedTest;
}

void Parser::addExpectEqual(QString lhs, QString rhs)
{
    generatedTest.append("EXPECT_EQ("+ lhs + ","  + rhs + ")" + "\n");
    qDebug() << "GeneratedTest: " << generatedTest;
}

void Parser::createMock()
{

}



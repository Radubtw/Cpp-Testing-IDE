#include "parser.h"
#include "parserConstants.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
Parser::Parser(QVector<QString> inputs, QString functionName, QString function, QString output) :
    inputs(inputs),functionName(functionName), function(function), output(output)
{
    isTest = true;
    generatedTest = "";
}

Parser::Parser(QString classImplementation) : classImplementation(classImplementation)
{
    isTest = false;
    generatedMock = "";
}

Parser::Parser() {}

bool Parser::isSymbol(QString input)
{
    for(const auto& symbol : parserConstants::symbols)
    {
        if(input == symbol)
        {
            return true;
        }
    }
    return false;
}

int Parser::containsSymbol(QString input)
{
    for(const auto& symbol : parserConstants::symbols)
    {
        if(input.contains(symbol))
        {
            return symbol.size();
        }
    }
    return -1;
}

QVector<QString> Parser::tokenize_v2(QString input)
{
    QVector<QString> tokens;
    QString word = "";
    input = input.simplified();
    int pos = 0;

    while(pos < input.size())
    {
        qDebug() << "WORD: " << word;
        qDebug() << "POS: " << pos;
        qDebug() << "----------------";

        int symbolSize = containsSymbol(word);
        if(symbolSize != -1)
        {
            QString compositeSymbol = word.right(symbolSize);
            compositeSymbol += input[pos];
            if(isSymbol(compositeSymbol))
            {
                word+=input[pos++];
                if(word.chopped(compositeSymbol.size()) != "")
                {
                    tokens.push_back(word.chopped(compositeSymbol.size()));
                }
                tokens.push_back(compositeSymbol);
            }
            else
            {
                if(word.chopped(symbolSize) != "")
                {
                    tokens.push_back(word.chopped(symbolSize));
                }
                tokens.push_back(word.right(symbolSize));
            }
            word = "";
            continue;
        }
        if(not input[pos].isSpace())
        {
            word += input[pos];
        }
        else
        {
            if(word != "")
                tokens.push_back(word);
            word = "";
        }
        ++pos;
    }
    for(const auto& token : tokens)
    {
        qDebug() << "TOKEN:" << token;
    }
    return tokens;
}

void Parser::addExpectEqual(QVector<QString>& inputs, QString& output)
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
    generatedTest.append("EXPECT_EQ("+functionName+"(" + stringifiedInputs + "), " + output + ");" + "\n");
    qDebug() << "GeneratedTest: " << generatedTest;
}

void Parser::addExpectEqual(QString lhs, QString rhs)
{
    generatedTest.append("EXPECT_EQ("+ lhs + ","  + rhs + ");" + "\n");
    qDebug() << "GeneratedTest: " << generatedTest;
}

QString Parser::createMock(QString classDefinition)
{
    QVector<QString> tokens{tokenize_v2(classDefinition)};
    int numberOfMockedFunctions = 0;
    for(const auto& token : tokens)
    {
        qDebug() <<"TOKEN: "<<token;
    }
    QString mockClassDefinition = "";
    int i = 0;
    qDebug() << "tokensSize:" << tokens.size();
    while(i < tokens.size())
    {
        if(tokens[i] == "class")
        {
            QString className = tokens[++i];
            mockClassDefinition += "class ";
            mockClassDefinition += "Mock" + className;
            mockClassDefinition += "\n{\npublic:\n";
            break;
        }
        ++i;
    }
    if(mockClassDefinition == "")
    {
        return "NOT A CLASS";
    }
    while(i < tokens.size())
    {
        if(tokens[i] == "virtual")
        {
            while(tokens[i] != "(" and tokens[i] != "()")
            {
                ++i;
            }
            QString methodName = tokens[i-1];
            QString methodType = tokens[i-2];
            QString methodParameters = "";
            bool isConst = false;
            if(tokens[i] == "(")
            {
                ++i;
                while(tokens[i] != ")")
                {
                    methodParameters += tokens[i++];
                    if(tokens[i] != "," and tokens[i] != ")")
                    {
                        methodParameters += " ";
                    }
                }
            }
            if(tokens[i + 1] == "const")
            {
                isConst = true;
            }
            if(methodType != "~")
            {
                numberOfMockedFunctions++;
                mockClassDefinition += addMockMethod(methodName, methodType, methodParameters, isConst);
                mockClassDefinition += '\n';
            }
        }
        ++i;
    }
    mockClassDefinition += "};\n";
    qDebug() << mockClassDefinition;
    if(numberOfMockedFunctions == 0)
        return "NO VIRTUAL FUNCTIONS AVAILABLE";
    return mockClassDefinition;
}

QString Parser::addMockMethod(QString methodName, QString methodType, QString methodParameters, bool isConst)
{
    QString method = "MOCK_METHOD(";
    method += methodType;
    method += ',';
    method += methodName;
    method += ",(";
    method+= methodParameters;
    method += "),";
    method += '(';
    if(isConst)
    {
        method += "const,";
    }
    method += "override));";
    return method;
}

QString Parser::addTestName(QString& testSuiteName, QString& testCaseName)
{
    QString testName{"TEST(" + testSuiteName + ", " + testCaseName + ")"};
    return testName;
}

void Parser::generateTestWithInputAndOutput(QString functionBody, QString testSuiteName, QString testCaseName, QVector<QString> inputs, QString output, QVector<ExpectCall> expectCalls)
{
    QVector<QString> tokens = tokenize_v2(functionBody);
    if(tokens.size() < 3)
    {
        generatedTest = "NOT A VALID FUNCTION\n";
        return;
    }
    int i = 0;
    while(i < tokens.size() && tokens[i] != "(")
    {
        ++i;
        if(i == tokens.size())
        {
            generatedTest = "NOT A VALID FUNCTION\n";
            return;
        }
    }
    functionName = tokens[i-1];
    generatedTest = addTestName(testSuiteName, testCaseName);
    generatedTest+="\n{\n";
    generatedTest += addExpectCalls(expectCalls);
    addExpectEqual(inputs, output);
    generatedTest+="}\n";
    qDebug() << "GeneratedTest:";
    qDebug() << generatedTest;
}

QString Parser::addExpectCalls(QVector<ExpectCall> expectCalls)
{
    QString expectCallsString = "";
    for(const auto& expectCall : expectCalls)
    {
        if(expectCall.object == "" || expectCall.function == "")
        {
            continue;
        }

        expectCallsString += "EXPECT_CALL(";
        expectCallsString += expectCall.object;
        expectCallsString += ", ";
        expectCallsString += expectCall.function;
        expectCallsString += ")";
        if(expectCall.times != "")
        {
            expectCallsString += ".Times(";
            expectCallsString += expectCall.times;
            expectCallsString += ")";
        }
        if(expectCall.returnValue != "")
        {
            if(expectCall.times == "1")
            {
                expectCallsString += ".WillOnce(Return(";
            }
            else
            {
                expectCallsString += ".WillRepeatedly(Return(";
            }
            expectCallsString += expectCall.returnValue;
            expectCallsString += "))";
        }
        expectCallsString += ";\n";
    }
    return expectCallsString;
}

void Parser::addExpectCall(QString objectName, QString functionName, QVector<QString> functionParameters)
{
    generatedTest.append("EXPECT_CALL(" + objectName + ", " + functionName + "(");
    if(functionParameters.size() == 0)
    {
        generatedTest.append(")");
        return;
    }
    for(int i = 0; i < functionParameters.size(); ++i)
    {
        generatedTest.append(functionParameters[i]);
        if(i < functionParameters.size() - 1)
        {
            generatedTest.append(",");
        }
    }
    generatedTest.append(")");
}



QString Parser::getGeneratedTest()
{
    return generatedTest;
}

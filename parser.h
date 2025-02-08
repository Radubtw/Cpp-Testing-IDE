#ifndef PARSER_H
#define PARSER_H
#include <QMap>
#include <QVector>

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
    Parser(QString className, QString classImplementation);

    void tokenize();//TODO important
    void addExpectEqual();
    void addExpectEqual(QString lhs, QString rhs);
    void addGTestInclude();
    void addGMockInclude();
    void writeTestToFile(int testType);

    void createMock();
private:
    bool isTest;
    QString filePath;
    QVector<QString> tokens;
    QVector<QString> inputs;
    QString functionName;
    QString function;
    QString output;
    QString generatedTest;
    QString className;
    QString generatedMock;
};

#endif // PARSER_H


#include "terminal.h"
#include "StyleSheets.h"
Terminal::Terminal(QString workingDir, QWidget *parent)
    : QWidget{parent}
{
    widget = new QWidget(this);
    mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    inputLine = new QLineEdit(this);
    terminalOutput = new QTextEdit(this);
    mainLayout->addWidget(terminalOutput);
    mainLayout->addWidget(inputLine);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    terminalOutput->setContentsMargins(0, 0, 0, 0);
    inputLine->setContentsMargins(0, 0, 0, 0);

    terminalOutput->setStyleSheet(stylesheets::terminal);
    inputLine->setStyleSheet(stylesheets::inputLine);
    startProcess(workingDir);
    terminalOutput->setReadOnly(true);
    connect(inputLine, &QLineEdit::returnPressed, this, &Terminal::sendCommand);
    connect(process, &QProcess::readyReadStandardOutput, this, &Terminal::readOutput);
}

void Terminal::startProcess(QString workingDir)
{
    process = new QProcess(this);
    QString program = "powershell.exe";
    process->setWorkingDirectory(workingDir);
    process->start(program);
    terminalOutput->append(process->readAllStandardOutput());
}

void Terminal::sendCommand()
{
    QString command = inputLine->text() + '\n';
    process->write(command.toUtf8());
    inputLine->clear();
}

void Terminal::readOutput()
{
    terminalOutput->append(process->readAllStandardOutput());
    terminalOutput->append(process->readAllStandardError());
}

void Terminal::toggleTerminal()
{
    setHidden(isHidden() ^ 1);
}

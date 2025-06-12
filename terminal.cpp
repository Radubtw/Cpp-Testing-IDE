
#include "terminal.h"
#include "StyleSheets.h"
#include <QApplication>

Terminal::Terminal(QString workingDir, QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    inputLine = new QLineEdit(this);
    terminalOutput = new QTextEdit(this);
    mainLayout->addWidget(terminalOutput);
    mainLayout->addWidget(inputLine);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    terminalOutput->setContentsMargins(0, 0, 0, 0);
    inputLine->setContentsMargins(0, 0, 0, 0);

    terminalOutput->setStyleSheet(stylesheets::terminal);
    terminalOutput->installEventFilter(this);

    inputLine->setStyleSheet(stylesheets::inputLine);
    inputLine->setFocusPolicy(Qt::StrongFocus);
    inputLine->setFixedSize(0,0);
    startProcess(workingDir);
    terminalOutput->setReadOnly(true);
    connect(inputLine, &QLineEdit::returnPressed, this, &Terminal::sendCommand);
    connect(process, &QProcess::readyReadStandardOutput, this, &Terminal::readOutput);
    connect(process, &QProcess::readyReadStandardError, this, &Terminal::readOutput);
    connect(inputLine, &QLineEdit::textChanged, this, &Terminal::appendText);
    terminalOutput->setOverwriteMode(true);
}

void Terminal::startProcess(QString workingDir)
{
    process = new QProcess(this);
#ifdef WIN32
    QString program = "powershell.exe";
#elif
    QString program = "/bin/bash";
#endif
    process->setWorkingDirectory(workingDir);
    process->start(program);
    terminalOutput->append(process->readAllStandardOutput());
    terminalOutput->moveCursor(QTextCursor::End);
}

void Terminal::sendCommand()
{
    QString command = inputLine->text() + '\n';
    process->write(command.toUtf8());
    inputLine->clear();
    terminalOutput->moveCursor(QTextCursor::End);
    lastLineEditText.clear();
    terminalOutput->insertPlainText(process->readAllStandardOutput());
    terminalOutput->insertPlainText(process->readAllStandardError());
}

void Terminal::readOutput()
{
    terminalOutput->insertPlainText(process->readAllStandardOutput());
    terminalOutput->insertPlainText(process->readAllStandardError());
    terminalOutput->moveCursor(QTextCursor::End);
}

void Terminal::appendText()
{
    QTextCursor cursor = terminalOutput->textCursor();
    cursor.movePosition(QTextCursor::End);
    terminalOutput->setTextCursor(cursor);

    if (!lastLineEditText.isEmpty()) {
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, lastLineEditText.length());
        cursor.removeSelectedText();
    }
    QString currentText = inputLine->text();
    terminalOutput->insertPlainText(currentText);
    lastLineEditText = currentText;
}

bool Terminal::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == terminalOutput) {
        if (event->type() == QEvent::FocusIn || event->type() == QEvent::MouseButtonPress) {
            inputLine->setFocus();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Terminal::setLineEditFocus()
{
    if(QApplication::focusWidget() == terminalOutput)
    {
        inputLine->setFocus();
    }
}

void Terminal::toggleTerminal()
{
    setHidden(isHidden() ^ 1);
}

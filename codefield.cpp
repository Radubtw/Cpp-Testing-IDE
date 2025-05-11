#include "StyleSheets.h"
#include "codefield.h"

#include <QKeyEvent>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

CodeField::CodeField(QString& path, QWidget* parent) : QWidget(parent), path(path)
{
    QGridLayout* layout = new QGridLayout(this);
    textEdit = new QTextEdit();
    textEdit->setWordWrapMode(QTextOption::NoWrap);
    isSaved = true;
    setFocusPolicy(Qt::ClickFocus);
    setMinimumWidth(100);
    closeButton = new QPushButton("X");
    closeButton->setFixedSize(20, 20);

    label = new QLabel();
    label->setMinimumWidth(40);
    setLabel();
    label->setContentsMargins(0, 0, 0, 0);
    closeButton->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(label, 0,0, 1,1);
    layout->addWidget(closeButton, 0,19,1,1);
    layout->addWidget(textEdit,1,0,20,20);
    setStyleSheets();
    layout->setContentsMargins(0, 0, 0, 0);
    connect(closeButton, &QPushButton::clicked, this, &CodeField::close);
    connect(textEdit, &QTextEdit::textChanged, this, [this](){
        isSaved = false;
        qDebug() << "Text changed, isSaved = false";
    });
}

void CodeField::close()
{
    emit closed();
}

void CodeField::keyPressEvent(QKeyEvent* event)
{
    if((event->modifiers() & Qt::ControlModifier) and (event->key() == Qt::Key_S))
    {
        emit saved();
    }
    else if((event->modifiers() & Qt::ControlModifier) and (event->key() == Qt::Key_P))
    {
        QString selectedText = this->textEdit->textCursor().selectedText();
        if(not selectedText.isEmpty())
        {
            qDebug() << "Sending selected text:" << selectedText;
            emit sendSelectedText(selectedText);
        }
        else
        {
            qDebug() << "No text selected, nothing to send.";
        }
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void CodeField::setLabel()
{
    QList<QString> pathTokens;
    if(path.contains('\\'))
    {
        pathTokens = path.split(u'\\');
    }
    else
    {
        pathTokens = path.split(u'/');
    }
    label->setText(pathTokens[pathTokens.length()-1]);
    label->setToolTip(path);
}

void CodeField::setStyleSheets()
{
    textEdit->setStyleSheet(stylesheets::codeFieldStyleSheet);
    closeButton->setStyleSheet(stylesheets::closeButtonStyleSheet);
    label->setStyleSheet(stylesheets::labelStyleSheet);
}

QTextEdit* CodeField::getTextEdit()
{
    return textEdit;
}

QString CodeField::getPath()
{
    return path;
}

void CodeField::setPath(QString path)
{
    this->path = path;
    setLabel();
}

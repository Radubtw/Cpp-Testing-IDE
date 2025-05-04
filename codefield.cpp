#include "StyleSheets.h"
#include "codefield.h"

#include <QKeyEvent>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
CodeField::CodeField(QString& path, QWidget* parent) : QWidget(parent), path(path)
{
    QHBoxLayout* headerLayout = new QHBoxLayout();
    QVBoxLayout* layout = new QVBoxLayout(this);
    textEdit = new QTextEdit();
    isSaved = true;
    setFocusPolicy(Qt::ClickFocus);
    setMinimumWidth(100);
    closeButton = new QPushButton();
    closeButton->setFixedSize(20, 20);

    label = new QLabel();
    label->setMinimumWidth(40);
    setLabel();


    headerLayout->addWidget(label);
    headerLayout->addStretch();
    headerLayout->addWidget(closeButton);

    layout->addLayout(headerLayout);
    layout->addWidget(textEdit);
    setStyleSheets();
    layout->setContentsMargins(2, 0, 2, 0);
    headerLayout->setContentsMargins(0, 0, 0, 0);
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
}

void CodeField::setStyleSheets()
{
    textEdit->setStyleSheet(stylesheets::codeFieldStyleSheet);
    closeButton->setStyleSheet(stylesheets::closeButtonStyleSheet);
    label->setStyleSheet(R"(color: white;
    background-color: #2E3440;
    font-size: 10px;
    padding: 3px;
    border-radius: 5px)");
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

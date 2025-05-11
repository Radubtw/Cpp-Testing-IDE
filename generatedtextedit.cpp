#include "generatedtextedit.h"
#include "StyleSheets.h"

#include <QTextEdit>
#include <QLabel>
#include <QGridLayout>

GeneratedTextEdit::GeneratedTextEdit(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout* layout = new QGridLayout(this);

    textEdit = new QTextEdit();
    label = new QLabel("Generated Code");
    layout->addWidget(label, 0,0,1,2);
    layout->addWidget(textEdit, 1,0,10,5);
    textEdit->setStyleSheet(stylesheets::codeFieldStyleSheet);
    label->setStyleSheet(stylesheets::labelStyleSheet);
}

QTextEdit* GeneratedTextEdit::getTextEdit()
{
    return textEdit;
}

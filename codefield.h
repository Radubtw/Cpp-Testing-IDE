#ifndef CODEFIELD_H
#define CODEFIELD_H

#include <QTextEdit>

class CodeField : public QTextEdit
{
    Q_OBJECT
public:
    CodeField(QWidget* parent = nullptr) : QTextEdit(parent){}
    void keyPressEvent(QKeyEvent* event) override;
signals:
    void saved();
};

#endif // CODEFIELD_H

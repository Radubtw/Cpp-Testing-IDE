#ifndef GENERATEDTEXTEDIT_H
#define GENERATEDTEXTEDIT_H

#include <QWidget>

class QTextEdit;
class QLabel;

class GeneratedTextEdit : public QWidget
{
    Q_OBJECT
public:
    explicit GeneratedTextEdit(QWidget *parent = nullptr);

    QTextEdit* getTextEdit();
private:
    QTextEdit* textEdit;
    QLabel* label;
signals:
};

#endif // GENERATEDTEXTEDIT_H

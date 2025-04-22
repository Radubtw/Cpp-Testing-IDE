#ifndef OUTPUTSECTION_H
#define OUTPUTSECTION_H

#include <QObject>
#include <QTextEdit>

class OutputSection : public QTextEdit
{
    Q_OBJECT
private:
public:
    explicit OutputSection(QWidget* parent = nullptr);

    void updateOutput(const QString& text);
public slots:
    void toggleOutput();
    void clearOutput();
};

#endif // OUTPUTSECTION_H

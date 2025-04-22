#ifndef CODEFIELD_H
#define CODEFIELD_H

#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
class CodeField : public QWidget
{
    Q_OBJECT
private:
    QString path;
    QTextEdit* textEdit;
    QLabel* label;
    QPushButton* closeButton;
public:
    bool isSaved;

    CodeField(QString& path, QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    QString getPath();
    QTextEdit* getTextEdit();

    void setPath(QString path);
    void setLabel();
    void setStyleSheets();

private slots:
    void close();
signals:
    void saved();
    void closed();
};

#endif // CODEFIELD_H

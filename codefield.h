#ifndef CODEFIELD_H
#define CODEFIELD_H

#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QShortcut>

class CodeField : public QWidget
{
    Q_OBJECT
public:
    bool isSaved;

    CodeField(QString& path, QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;

    QString getPath();
    QTextEdit* getTextEdit();

    void setPath(QString path);
    void setLabel();
    void setStyleSheets();
private:
    QString path;
    QTextEdit* textEdit;
    QLabel* label;
    QPushButton* closeButton;
private slots:
    void close();
signals:
    void saved();
    void closed();
    void sendSelectedText(const QString& text);
};

#endif // CODEFIELD_H

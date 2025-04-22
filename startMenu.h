#ifndef WIDGET_H
#define WIDGET_H
#include "windowmanager.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class WindowManager;


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() = default;

private:
    QGridLayout* mainLayout;
    QLabel* title;
    QPushButton* newProjectButton;
    QPushButton* existingProjectButton;
    QPushButton* helpButton;
    QSpacerItem* spacer1;

public:
    void initButtons();
    void handleExistingProjectButtonClick();
    void handleNewProjectButtonClick();
};
#endif // WIDGET_H

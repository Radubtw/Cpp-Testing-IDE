#include "startMenu.h"
#include "ui_widget.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("C++ Unit Testing");
    this->setStyleSheet("background-color: #3B4252;");
    setWindowTitle("Testing");
    resize(800,800);

    title = new QLabel(this);
    title->setText("Testing");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");

    initButtons();
    mainLayout->addWidget(title, 1, 2, Qt::AlignHCenter);

}

void Widget::initButtons()
{
    newProjectButton = new QPushButton(this);
    existingProjectButton = new QPushButton(this);
    helpButton = new QPushButton(this);

    QString buttonStyle = R"(
        QPushButton {
            background-color: #2E3440;
            color: white;
            border-radius: 10px;
            padding: 10px;
            font-size: 16px;
            border: 2px solid #4C566A;
        }
        QPushButton:hover {
            background-color: #4C566A;
        }
        QPushButton:pressed {
            background-color: #81A1C1;
        }
    )";


    //newProjectButton->resize(100,100);
    newProjectButton->setText("Create New Project");
    newProjectButton->setStyleSheet(buttonStyle);

    //existingProjectButton->resize(100,100);
    existingProjectButton->setText("Select Existing Project");
    existingProjectButton->setStyleSheet(buttonStyle);

    //helpButton->resize(100,100);
    helpButton->setText("Help");
    helpButton->setStyleSheet(buttonStyle);

    spacer1 = new QSpacerItem(100,100,QSizePolicy::Expanding);
    mainLayout = new QGridLayout(this);
    this->setLayout(mainLayout);
    mainLayout->addItem(spacer1, 0, 2, Qt::AlignHCenter);
    mainLayout->addWidget(newProjectButton, 2 ,1, Qt::AlignJustify);
    mainLayout->addWidget(existingProjectButton, 2, 3, Qt::AlignJustify);
    mainLayout->addWidget(helpButton,3,2, Qt::AlignHCenter);
    mainLayout->addItem(spacer1, 4, 2, Qt::AlignHCenter);
    mainLayout->addItem(spacer1, 2, 0, Qt::AlignHCenter);
    mainLayout->addItem(spacer1, 2, 4, Qt::AlignHCenter);
    mainLayout->setColumnMinimumWidth(100,100);
    connect(newProjectButton, &QPushButton::released, this, &Widget::handleNewProjectButtonClick);
}

void Widget::handleNewProjectButtonClick()
{
    WindowManager* windowManager = WindowManager::init();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    if(dir!= "")
    {
        windowManager->closeStartMenu();
        windowManager->openNewProjectWindow(dir);
    }

}

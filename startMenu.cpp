#include "startMenu.h"
#include "opennewprojectdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("C++ Unit Testing");
    this->setStyleSheet("background-color: #3B4252;");
    setWindowTitle("Testing");
    resize(800,800);

    title = new QLabel(this);
    title->setText("Testing");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");

    initButtons();


}

void Widget::initButtons()
{
    newProjectButton = new QPushButton("Create New Project");
    existingProjectButton = new QPushButton("Select Existing Project");
    helpButton = new QPushButton("Help");

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


    newProjectButton->setStyleSheet(buttonStyle);
    existingProjectButton->setStyleSheet(buttonStyle);
    helpButton->setStyleSheet(buttonStyle);
    newProjectButton->setMinimumWidth(200);
    existingProjectButton->setMinimumWidth(200);
    helpButton->setMinimumWidth(200);
    spacer1 = new QSpacerItem(100,100,QSizePolicy::Expanding);
    QVBoxLayout* buttonLayout = new QVBoxLayout(this);
    buttonLayout->addWidget(title, 0, Qt::AlignHCenter);
    buttonLayout->addWidget(existingProjectButton, 10, Qt::AlignLeft);
    buttonLayout->addWidget(newProjectButton, 10, Qt::AlignLeft);
    buttonLayout->addWidget(helpButton, 10, Qt::AlignLeft);
    buttonLayout->addSpacerItem(spacer1);
    buttonLayout->addSpacerItem(spacer1);
    buttonLayout->addSpacerItem(spacer1);
    //this->setLayout(buttonLayout);
    // mainLayout->addItem(spacer1, 0, 2, Qt::AlignHCenter);
    // mainLayout->addWidget(newProjectButton, 2 ,1, Qt::AlignJustify);
    // mainLayout->addWidget(existingProjectButton, 2, 3, Qt::AlignJustify);
    // mainLayout->addWidget(helpButton,3,2, Qt::AlignHCenter);
    // mainLayout->addItem(spacer1, 4, 2, Qt::AlignHCenter);
    // mainLayout->addItem(spacer1, 2, 0, Qt::AlignHCenter);
    // mainLayout->addItem(spacer1, 2, 4, Qt::AlignHCenter);
    // mainLayout->setColumnMinimumWidth(100,100);
    connect(existingProjectButton, &QPushButton::released, this, &Widget::handleExistingProjectButtonClick);
    connect(newProjectButton, &QPushButton::released, this, &Widget::handleNewProjectButtonClick);

}

void Widget::handleExistingProjectButtonClick()
{
    WindowManager* windowManager = WindowManager::init();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    if(dir!= "")
    {
        windowManager->closeStartMenu();
        windowManager->openExistingProjectWindow(dir);
    }
}
void Widget::handleNewProjectButtonClick()
{
    WindowManager* windowManager = WindowManager::init();
    OpenNewProjectDialog* newProjectDialog = new OpenNewProjectDialog();
    QString path = "";
    if(newProjectDialog->exec() == QDialog::Accepted)
    {
        QString projectPath = newProjectDialog->getProjectPath();
        QString projectName = newProjectDialog->getProjectName();
        bool emptyProject= newProjectDialog->getEmptyProject();
        QDir dir(projectPath);
        dir.mkdir(projectName);
        if(emptyProject)
        {
            windowManager->closeStartMenu();
            windowManager->openExistingProjectWindow(dir.absoluteFilePath(projectName));
        }
    }
}

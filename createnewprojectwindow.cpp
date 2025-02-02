#include "createnewprojectwindow.h"
#include "ui_createnewprojectwindow.h"
#include "GTestSetupFunctions.hpp"
#include "StyleSheets.h"
#include <QSplitter>
#include <QStandardItemModel>
CreateNewProjectWindow::CreateNewProjectWindow(QDir dirPath, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    // QString zipFilePath = "C:\\Users\\Radu\\Desktop\\googletest-1.15.2.zip";
    // QString extractPath = dirPath.absolutePath();
    //ui->setupUi(this);
    this->setWindowTitle("C++ Unit Testing");
    this->setStyleSheet("background-color: #000000;");
    fileSystemModel = new QFileSystemModel();
    fileSystemModel->setRootPath(dirPath.absolutePath());
    initLayout();
    // unzipWithTar(zipFilePath, extractPath);
    // compileGTest(extractPath + "\\googletest-1.15.2");
}

void CreateNewProjectWindow::initLayout()
{
    mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);



    QSplitter *horizontalMainSplitter = new QSplitter(Qt::Horizontal, this);
    QSplitter *verticalMainSplitter = new QSplitter(Qt::Vertical, this);

    treeView = new QTreeView();
    treeView->setModel(fileSystemModel);
    treeView->setRootIndex(fileSystemModel->index(fileSystemModel->rootPath()));
    treeView->setColumnWidth(0, 150);
    treeView->hideColumn(1);
    treeView->hideColumn(2);
    treeView->hideColumn(3);
    treeView->setHeaderHidden(1);
    treeView->setStyleSheet(treeViewStyleSheet);

    codeField= new CodeField(horizontalMainSplitter);
    codeField->setStyleSheet(codeFieldStyleSheet);

    testCodeField = new CodeField(verticalMainSplitter);
    testCodeField->setStyleSheet(codeFieldStyleSheet);

    horizontalMainSplitter->addWidget(treeView);
    horizontalMainSplitter->addWidget(codeField);
    horizontalMainSplitter->addWidget(verticalMainSplitter);

    QList<int> horizontalSizes;
    horizontalSizes << 200 << 600 << 400;
    horizontalMainSplitter->setSizes(horizontalSizes);

    QList<int> verticalSizes;
    verticalSizes << 300 << 300;
    verticalMainSplitter->setSizes(verticalSizes);

    QWidget *secondaryLayoutWrapper = new QWidget(this);

    secondaryLayout = new QHBoxLayout(secondaryLayoutWrapper);
    testAndMockButtonsLayout = new QVBoxLayout();

    selectedClassOrFunction = new QTextEdit(secondaryLayoutWrapper);
    selectedClassOrFunction->setStyleSheet(selectedClassOrFunctionStyleSheet);


    writeTestButton = new QPushButton("Write Test", this);
    generateTestButton = new QPushButton("Generate Test", this);
    writeMockButton = new QPushButton("Write Mock", this);
    generateMockButton = new QPushButton("Generate Mock", this);

    writeTestButton->setStyleSheet(buttonStyleSheet);
    generateTestButton->setStyleSheet(buttonStyleSheet);
    writeMockButton->setStyleSheet(buttonStyleSheet);
    generateMockButton->setStyleSheet(buttonStyleSheet);

    testAndMockButtonsLayout->addWidget(writeTestButton);
    testAndMockButtonsLayout->addWidget(generateTestButton);
    testAndMockButtonsLayout->addWidget(writeMockButton);
    testAndMockButtonsLayout->addWidget(generateMockButton);

    secondaryLayout->addWidget(selectedClassOrFunction);
    secondaryLayout->addLayout(testAndMockButtonsLayout);
    secondaryLayoutWrapper->setLayout(secondaryLayout);

    verticalMainSplitter->addWidget(secondaryLayoutWrapper);
    verticalMainSplitter->addWidget(testCodeField);


    connect(treeView, &QTreeView::doubleClicked, this, &CreateNewProjectWindow::showFileContent);
    connect(codeField, &CodeField::saved, this, &CreateNewProjectWindow::saveFileContent);

    mainLayout->addWidget(horizontalMainSplitter);

}

void CreateNewProjectWindow::showFileContent(const QModelIndex &index)
{
    QString filePath = fileSystemModel->filePath(index);
    if(not QFileInfo(filePath).isFile())
    {
        codeField->setPlainText("Not a file");
        return;
    }
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        currentFilePath = filePath;
        QTextStream in(&file);
        QString fileContents = in.readAll();
        file.close();
        codeField->setPlainText(fileContents);
    }
    else
    {
        codeField->setPlainText("Unable to open file");
    }
}

void CreateNewProjectWindow::saveFileContent()
{
    if(not QFileInfo(currentFilePath).isFile())
    {
        return;
    }
    QFile file(currentFilePath);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << codeField->toPlainText();
    }
}

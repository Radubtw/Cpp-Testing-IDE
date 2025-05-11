#include <QSplitter>
#include <QIcon>
#include <QStandardItemModel>
#include <QAction>
#include <QShortcut>
#include "createnewprojectwindow.h"
#include "ui_createnewprojectwindow.h"
#include "windowmanager.h"
#include "processes.hpp"
#include "generatetestdialog.h"
#include "StyleSheets.h"
#include "parser.h"
#include "testresultswindow.h"

CreateNewProjectWindow::CreateNewProjectWindow(QDir dirPath, QWidget *parent)
    : QWidget(parent)
    , projectPath(dirPath)
    , ui(new Ui::Form)
{
    // QString zipFilePath = "C:\\Users\\Radu\\Desktop\\googletest-1.15.2.zip";
    // QString extractPath = dirPath.absolutePath();
    setWindowTitle("Test.cpp");
    setMinimumSize(800, 800);
    setStyleSheet("background-color: #1E1E1E; QToolTip { color: white; background-color: #1E1E1E; border: 1px solid 252526;}");

    fileSystemModel = new QFileSystemModel();
    fileSystemModel->setRootPath(projectPath.absolutePath());
    initLayout();
    initMenuBar(projectPath);

    //const QString projectPath = dirPath.absolutePath();
    //processes::tests::compileAndRunTests(projectPath);
    connectElements();
    lastClickedPath = projectPath.absolutePath();
    // unzipWithTar(zipFilePath, extractPath);
    // compileGTest(extractPath + "\\googletest-1.15.2");
}

void CreateNewProjectWindow::initMenuBar(QDir dirPath)
{
    menuBar = new MenuBar(dirPath, this );
    mainLayout->setMenuBar(menuBar);
}

void CreateNewProjectWindow::initLayout()
{
    QString zipFilePath = "C:\\Users\\Radu\\Desktop\\googletest-1.15.2.zip";
    lastClickedPath = projectPath.path();
    mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
    horizontalMainSplitter = new QSplitter(Qt::Horizontal, this);
    horizontalMainSplitter->setContentsMargins(0, 0, 0, 0);
    QSplitter *verticalMainSplitter = new QSplitter(Qt::Vertical, this);
    QSplitter *terminalSplitter = new QSplitter(Qt::Vertical, this);
    treeView = new QTreeView();
    treeView->setModel(fileSystemModel);
    treeView->setRootIndex(fileSystemModel->index(fileSystemModel->rootPath()));
    treeView->setColumnWidth(0, 150);
    treeView->hideColumn(1);
    treeView->hideColumn(2);
    treeView->hideColumn(3);
    treeView->setHeaderHidden(1);
    treeView->setStyleSheet(stylesheets::treeViewStyleSheet);
    treeView->setFocusPolicy(Qt::NoFocus);
    treeView->setContentsMargins(0, 0, 0, 0);

    treeViewLayoutWidget = new QWidget();

    QPixmap pixmap(":/assets/newFile.png");
    QImage img = pixmap.toImage();
    img.invertPixels();
    QIcon newFileIcon(QPixmap::fromImage(img));

    newFileButton = new QPushButton();
    newFileButton->setIcon(newFileIcon);

    pixmap.load(":assets/newDirectory.png");
    img = pixmap.toImage();
    img.invertPixels();
    QIcon newDirectoryIcon(QPixmap::fromImage(img));

    newDirectoryButton = new QPushButton();
    newDirectoryButton->setIcon(newDirectoryIcon);

    newFileButton->setStyleSheet(stylesheets::iconButtonStyle); //TODO: stylesheets
    newDirectoryButton->setStyleSheet(stylesheets::iconButtonStyle); //TODO: stylesheets

    projectName = new ClickableLabel();
    projectName->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    projectName->setStyleSheet(stylesheets::labelStyleSheet);
    QList<QString> pathTokens;
    QString path = projectPath.absolutePath();
    if(path.contains('\\'))
    {
        pathTokens = path.split(u'\\');
    }
    else
    {
        pathTokens = path.split(u'/');
    }
    projectName->setText(pathTokens[pathTokens.length()-1]);
    projectName->setToolTip(projectPath.absolutePath());
    treeViewLayout = new QGridLayout(treeViewLayoutWidget);
    treeViewLayout->addWidget(projectName, 0, 0, 1, 8);
    treeViewLayout->addWidget(newFileButton, 0,8,1,1);
    treeViewLayout->addWidget(newDirectoryButton, 0,9,1,1);
    treeViewLayout->addWidget(treeView, 2,0,10,10);
    horizontalMainSplitter->addWidget(treeViewLayoutWidget);

    newFileButton->setContentsMargins(0, 0, 0, 0);
    newDirectoryButton->setContentsMargins(0, 0, 0, 0);
    treeViewLayout->setContentsMargins(0, 0, 0, 0);
    treeViewLayoutWidget->setContentsMargins(0, 0, 0, 0);
    projectName->setContentsMargins(0, 0, 0, 0);

    codeFieldsSplitter = new QSplitter(Qt::Horizontal, horizontalMainSplitter);
    codeFieldsSplitter->setHandleWidth(1); // thinner handle
    codeFieldsSplitter->setStyleSheet("QSplitter::handle { background: transparent; }");
    QString emptyString = "";
    codeFields.push_back(new CodeField(emptyString, codeFieldsSplitter));
    testCodeField = new GeneratedTextEdit(verticalMainSplitter);
    for(const auto& codeField : codeFields)
    {
        codeFieldsSplitter->addWidget(codeField);
    }

    horizontalMainSplitter->addWidget(verticalMainSplitter);
    QList<int> horizontalSizes;
    horizontalSizes << 200 << 600 << 400;
    horizontalMainSplitter->setSizes(horizontalSizes);

    QList<int> verticalSizes;
    verticalSizes << 300 << 300;
    verticalMainSplitter->setSizes(verticalSizes);

    QWidget *secondaryLayoutWrapper = new QWidget(this);
    secondaryLayout = new QGridLayout(secondaryLayoutWrapper);
    selectedClassOrFunction = new QTextEdit(secondaryLayoutWrapper);
    selectedClassOrFunction->setStyleSheet(stylesheets::selectedClassOrFunctionStyleSheet);
    selectedClassOrFunction->setReadOnly(true);

    generateTestButton = new QPushButton("Generate Test");
    generateMockButton = new QPushButton("Generate Mock");

    generateTestButton->setStyleSheet(stylesheets::generateButtonStyleSheet);
    generateMockButton->setStyleSheet(stylesheets::generateButtonStyleSheet);
    secondaryLayout->addWidget(generateTestButton,0,0,1,2);
    secondaryLayout->addWidget(generateMockButton,0,8,1,2);
    secondaryLayout->addWidget(selectedClassOrFunction,1,0,6,10);

    secondaryLayoutWrapper->setLayout(secondaryLayout);

    verticalMainSplitter->addWidget(secondaryLayoutWrapper);
    verticalMainSplitter->addWidget(testCodeField);

    outputSection = new OutputSection(terminalSplitter);
    outputSection->setStyleSheet(stylesheets::outputSection);
    terminal = new Terminal(projectPath.absolutePath(), terminalSplitter);
    terminalSplitter->addWidget(horizontalMainSplitter);
    terminalSplitter->addWidget(outputSection);
    terminalSplitter->addWidget(terminal);
    terminalSplitter->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(terminalSplitter);
    outputSection->hide();
    // mainLayout->addWidget(horizontalMainSplitter);

}

void CreateNewProjectWindow::connectElements()
{
    connect(menuBar, &MenuBar::testResultsOpened, this, &CreateNewProjectWindow::openTestResultsWindow);
    connect(treeView, &QTreeView::doubleClicked, this, &CreateNewProjectWindow::showFileContent);
    connect(treeView, &QTreeView::clicked, this, &CreateNewProjectWindow::clickTreeViewEntry);
    connect(projectName, &ClickableLabel::clicked, this, &CreateNewProjectWindow::clickLabel);
    connect(newDirectoryButton, &QPushButton::clicked, this, &CreateNewProjectWindow::showNewDirLineEdit);
    connect(newFileButton, &QPushButton::clicked, this, &CreateNewProjectWindow::showNewFileLineEdit);
    connect(generateTestButton, &QPushButton::clicked, this, &CreateNewProjectWindow::openGenerateTestDialog);
    connect(generateMockButton, &QPushButton::clicked, this, &CreateNewProjectWindow::generateMock);
    connect(menuBar, &MenuBar::outputUpdated, outputSection, &OutputSection::updateOutput);
    connect(menuBar->processes,&Processes::outputChanged,this, &CreateNewProjectWindow::readOutput); // ??????????
    connect(menuBar, &MenuBar::outputToggled, this, &CreateNewProjectWindow::toggleOutput);
    connect(menuBar, &MenuBar::terminalToggled, this, &CreateNewProjectWindow::toggleTerminal);
    connect(menuBar, &MenuBar::outputCleared, outputSection, &OutputSection::clearOutput);
    connect(menuBar, &MenuBar::explorerToggled, this, &CreateNewProjectWindow::toggleExplorer);
    connect(menuBar, &MenuBar::codeFieldSplitted, this, &CreateNewProjectWindow::splitCodeField);
    connect(menuBar, &MenuBar::startMenuOpened, this, &CreateNewProjectWindow::openStartMenu);
    for(auto& codeField : codeFields)
    {
        connect(codeField, &CodeField::saved, this, &CreateNewProjectWindow::saveFileContent);
        connect(codeField, &CodeField::sendSelectedText, selectedClassOrFunction, &QTextEdit::setPlainText);
        connect(codeField, &CodeField::closed, this, [this,codeField](){
            const auto it = std::find(codeFields.begin(), codeFields.end(), codeField);
            if(it != codeFields.end())
            {
                codeFields.erase(it);
                codeField->deleteLater();
            }
        });
    }
}

void CreateNewProjectWindow::readOutput(QString output)
{
    outputSection->updateOutput(output);
}

void CreateNewProjectWindow::showFileContent(const QModelIndex &index)
{
    QString filePath = fileSystemModel->filePath(index);
    if(not QFileInfo(filePath).isFile())
    {
        return;
    }
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(codeFields.size() > 0)
        {
            for(const auto& codeField : codeFields)
            {
                if(QApplication::focusWidget() == codeField->getTextEdit() || codeField->getPath() == "")
                {
                    codeField->setPath(filePath);
                    QTextStream in(&file);
                    QString fileContents = in.readAll();
                    file.close();
                    codeField->getTextEdit()->setText(fileContents);
                    connect(codeField, &CodeField::saved, this, &CreateNewProjectWindow::saveFileContent);
                    connect(codeField, &CodeField::sendSelectedText, selectedClassOrFunction, &QTextEdit::setPlainText);
                    return;
                }
            }
        }
        if(codeFields.size() < 5)
        {
            CodeField* codeField = new CodeField(filePath, codeFieldsSplitter);
            codeFields.push_back(codeField);
            connect(codeField, &CodeField::closed, this, [this,codeField](){
                const auto it = std::find(codeFields.begin(), codeFields.end(), codeField);
                if(it != codeFields.end())
                {
                    codeFields.erase(it);
                    codeField->deleteLater();
                }
            });
            codeField->setPath(filePath);
            QTextStream in(&file);
            QString fileContents = in.readAll();
            file.close();
            codeField->getTextEdit()->setPlainText(fileContents);
            connect(codeField, &CodeField::saved, this, &CreateNewProjectWindow::saveFileContent);
            connect(codeField, &CodeField::sendSelectedText, selectedClassOrFunction, &QTextEdit::setPlainText);
        }
    }
}

void CreateNewProjectWindow::saveFileContent()
{
    for(const auto& codeField : codeFields)
    {
        qDebug()<< "FILE PATH" << codeField->getPath();
        if(QApplication::focusWidget() == codeField->getTextEdit() && not codeField->isSaved)
        {
            auto text = codeField->getTextEdit()->toPlainText();
            auto path = codeField->getPath();
            QFile file(path);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << text;
            file.close();
            codeField->isSaved = true;
            qDebug() << "CONTENTS SAVED:" << file.fileName();
        }
    }
}

void CreateNewProjectWindow::toggleExplorer()
{
    treeViewLayoutWidget->setHidden(treeViewLayoutWidget->isHidden() ^ 1);
}

void CreateNewProjectWindow::splitCodeField()
{

    if(codeFields.size() > 4)
    {
        return;
    }
    QString path = "";
    if(codeFields.size() > 0)
    {
        for(const auto& codeField : codeFields)
        {
            if(QApplication::focusWidget() == codeField->getTextEdit())
            {
                path = codeField->getPath();
                break;
            }
        }
        path = codeFields.front()->getPath();
    }
    CodeField* codeField = new CodeField(path, codeFieldsSplitter);
    connect(codeField, &CodeField::saved, this, &CreateNewProjectWindow::saveFileContent);
    codeFields.push_back(codeField);
    connect(codeField, &CodeField::closed, this, [this,codeField](){
        auto it = std::find(codeFields.cbegin(), codeFields.cend(), codeField);
        if(it != codeFields.end())
        {
            codeFields.erase(it);
            codeField->deleteLater();
        }
    });

    QFile file(codeField->getPath());
    if(! QFileInfo(file).isFile())
    {
        return;
    }
    qDebug() << "PATH: " << codeField->getPath();

    QTextStream in(&file);
    QString fileContents = in.readAll();
    file.close();
    codeField->getTextEdit()->setText(fileContents);
}

void CreateNewProjectWindow::openGenerateTestDialog()
{
    GenerateTestDialog* dialog = new GenerateTestDialog(this);
    if(dialog->exec() == QDialog::Accepted)
    {
        QString functionBody = selectedClassOrFunction->toPlainText();
        QString testSuiteName = dialog->getTestSuiteName();
        QString testCaseName = dialog->getTestCaseName();
        QVector<QString> functionInputs = dialog->getFunctionInputs().split(u',');
        QString functionOutput = dialog->getFunctionOutput();
        QVector<ExpectCall> expectCalls = dialog->getExpectCalls();

        Parser parser{};
        parser.generateTestWithInputAndOutput(functionBody, testSuiteName, testCaseName, functionInputs, functionOutput, expectCalls);
        QString test = parser.getGeneratedTest();
        testCodeField->getTextEdit()->setText(test);
    }
}

void CreateNewProjectWindow::openTestResultsWindow()
{
    TestResultsWindow* testResultsWindow = new TestResultsWindow(projectPath);
    testResultsWindow->show();
}

void CreateNewProjectWindow::generateMock()
{
    Parser parser{};
    QString generatedMock = parser.createMock(selectedClassOrFunction->toPlainText());
    testCodeField->getTextEdit()->setText(generatedMock);
}

void CreateNewProjectWindow::toggleTerminal()
{
    if(outputSection->isVisible())
    {
        outputSection->toggleOutput();
    }
    terminal->toggleTerminal();
}

void CreateNewProjectWindow::toggleOutput()
{
    if(terminal->isVisible())
    {
        terminal->toggleTerminal();
    }
    outputSection->toggleOutput();
}

void CreateNewProjectWindow::openStartMenu()
{
    WindowManager* windowManager = WindowManager::init();
    windowManager->closeExistingProjectWindow();
    windowManager->openStartMenu();
}

void CreateNewProjectWindow::clickLabel()
{
    lastClickedPath = projectPath.absolutePath();
}

void CreateNewProjectWindow::clickTreeViewEntry(const QModelIndex index)
{
    QFileSystemModel *model = qobject_cast<QFileSystemModel *>(treeView->model());
    lastClickedPath = model->filePath(index);
}

void CreateNewProjectWindow::showNewFileLineEdit()
{
    if(newDirLineEdit)
    {
        newDirLineEdit->hide();
    }
    newFileLineEdit = new QLineEdit();
    treeViewLayout->addWidget(newFileLineEdit,1,0,1,10);
    newFileLineEdit->show();
    newFileLineEdit->setFocus();
    newFileLineEdit->setStyleSheet(stylesheets::inputLine);
    connect(newFileLineEdit, &QLineEdit::returnPressed, this, &CreateNewProjectWindow::createNewFile);
}

void CreateNewProjectWindow::showNewDirLineEdit()
{
    if(newFileLineEdit)
    {
        newFileLineEdit->hide();
    }
    newDirLineEdit = new QLineEdit();
    treeViewLayout->addWidget(newDirLineEdit,1,0,1,10);
    newDirLineEdit->show();
    newDirLineEdit->setFocus();
    newDirLineEdit->setStyleSheet(stylesheets::inputLine);
    connect(newDirLineEdit, &QLineEdit::returnPressed, this, &CreateNewProjectWindow::createNewDirectory);
}

void CreateNewProjectWindow::createNewFile()
{
    QFileInfo path(lastClickedPath);
    if(QFileInfo(path).isFile())
    {
        if (!QFile::exists(path.dir().absolutePath() + "/" + newFileLineEdit->text())) {
            QFile file(path.dir().absolutePath() + "/" + newFileLineEdit->text());
            if (file.open(QIODevice::WriteOnly)) {
                file.close();
                newFileLineEdit->hide();
            }
        }
    }
    else
    {
        if (!QFile::exists(path.absolutePath() + "/" + newFileLineEdit->text())) {
            QFile file(lastClickedPath + "/" + newFileLineEdit->text());
            if (file.open(QIODevice::WriteOnly)) {
                file.close();
                newFileLineEdit->hide();
            }
        }
    }
}

void CreateNewProjectWindow::createNewDirectory()
{
    QFileInfo path(lastClickedPath);
    if(QFileInfo(path).isFile())
    {
        qDebug() << "IS FILE";
        QDir newDir(path.dir().absolutePath());
        if(!QDir(newDir.absolutePath() + newDirLineEdit->text()).exists())
        {
            qDebug() << "DIR DOES NOT ALREADY EXIST";
            newDir.mkdir(newDirLineEdit->text());
            newDirLineEdit->hide();
        }
    }
    else
    {
        qDebug() << "IS NOT FILE";
        QDir newDir(lastClickedPath);
        if(!QDir(newDir.absolutePath() + newDirLineEdit->text()).exists())
        {
            qDebug() << "DIR DOES NOT ALREADY EXIST";
            newDir.mkdir(newDirLineEdit->text());
            newDirLineEdit->hide();
        }
    }
}

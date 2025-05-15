#include "newcmakeprojectfunctions.h"
#include "newcmakeprojectconstants.h"
#include <QFile>
#include <QDir>

void createCMakeProject(const QString path, const QString projectName)
{
    QDir currentDir(path);
    if(!currentDir.exists())
    {
        currentDir.mkpath(path);
        currentDir.setPath(path);
    }
    currentDir.mkdir(projectName);

    currentDir.cd(projectName);
    addFile(currentDir.absolutePath(), "CMakeLists", fileType::CMakeLists, newProjectConstants::rootCmakeListsContents);

    currentDir.mkdir("Component1");
    currentDir.cd("Component1");
    addFile(currentDir.absolutePath(), "CMakeLists", fileType::CMakeLists, newProjectConstants::Component1CmakeListsContents);

    currentDir.mkdir("include");
    currentDir.cd("include");
    currentDir.mkdir("Component1");
    currentDir.cd("Component1");
    addFile(currentDir.absolutePath(), "ExampleHeader", fileType::Header, newProjectConstants::headerFileContents);

    currentDir.cd("..");
    currentDir.cd("..");
    currentDir.mkdir("src");
    currentDir.cd("src");
    addFile(currentDir.absolutePath(), "ExampleSource", fileType::Source, newProjectConstants::sourceFileContents);
    addFile(currentDir.absolutePath(), "main", fileType::Source, newProjectConstants::mainFileContents);

    currentDir.cd("..");
    currentDir.mkdir("tests");
    currentDir.cd("tests");
    addFile(currentDir.absolutePath(), "Example_test", fileType::Source, newProjectConstants::testFileContents);
    addFile(currentDir.absolutePath(), "CMakeLists", fileType::CMakeLists, newProjectConstants::testsCmakeListsContents);

}

void addFile(const QString path, const QString name, fileType type, const QString content)
{
    QString fileExtension;
    switch(type)
    {
    case fileType::CMakeLists:
        fileExtension = ".txt";
        break;
    case fileType::Header:
        fileExtension = ".hpp";
        break;
    case fileType::Source:
        fileExtension = ".cpp";
        break;
    default:
        return;
    }

    QFile file(path + "/" + name + fileExtension);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << content;
    file.close();
}

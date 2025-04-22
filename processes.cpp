#include "processes.hpp"
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QFile>
namespace processes
{
void Processes::unzipWithTar(const QString &zipFilePath, const QString &extractPath) {
    QProcess tarProcess;
    tarProcess.setProgram("tar");
    tarProcess.setArguments({"-xf", zipFilePath, "-C", extractPath});

    tarProcess.start();
    tarProcess.waitForFinished(-1); // Wait for the process to finish

    if (tarProcess.exitCode() == 0) {
        qDebug() << "Unzipped successfully!";
    } else {
        qDebug() << "Failed to unzip:" << tarProcess.readAllStandardError();
    }
}
void Processes::compileGTest(const QString &gtestSourceDir) {
    QDir buildDir(gtestSourceDir + "/build");
    if (!buildDir.exists()) {
        if (!buildDir.mkpath(".")) {
            qDebug() << "Failed to create build directory!";
            return;
        }
    }

    // Run CMake
    QProcess cmakeProcess;
    cmakeProcess.setWorkingDirectory(buildDir.absolutePath());
    cmakeProcess.setProgram("cmake");
    cmakeProcess.setArguments({"..", "-G Ninja"});

    qDebug() << "Running CMake...";
    cmakeProcess.start();
    if (!cmakeProcess.waitForFinished(-1)) {
        qDebug() << "CMake process failed to start or finish!";
        return;
    }

    if (cmakeProcess.exitCode() != 0) {
        qDebug() << "CMake configuration failed:" << cmakeProcess.readAllStandardError();
        return;
    }
    qDebug() << "CMake configuration successful!";

    // Run Build
    QProcess buildProcess;
    buildProcess.setWorkingDirectory(buildDir.absolutePath());
    buildProcess.setProgram("cmake");
    buildProcess.setArguments({"--build", "."});

    qDebug() << "Building GTest...";
    buildProcess.start();
    if (!buildProcess.waitForFinished(-1)) {
        qDebug() << "Build process failed to start or finish!";
        return;
    }

    if (buildProcess.exitCode() != 0) {
        qDebug() << "Build failed:" << buildProcess.readAllStandardError();
        return;
    }
    qDebug() << "GTest compiled successfully!";
}
QString& Processes::compileTests(const QString& projectPath)
{
    output = "";
    QDir buildDir(projectPath + "/build");
    if (!buildDir.exists()) {
        if (!buildDir.mkpath(".")) {
            output+="Failed to create build directory!";
            return output;
        }
    }

    QProcess cmakeProcess;
    cmakeProcess.setWorkingDirectory(buildDir.absolutePath());
    cmakeProcess.setProgram("cmake");
    cmakeProcess.setArguments({"..", "-G Ninja"});

    output+="Running CMake...";
    cmakeProcess.start();
    if (!cmakeProcess.waitForFinished(-1)) {
        output+="CMake process failed to start or finish!";
        return output;
    }

    if (cmakeProcess.exitCode() != 0) {
        output+="CMake configuration failed:";
        output+=cmakeProcess.readAllStandardError();
        return output;
    }
    output+="CMake configuration successful!";

    QProcess buildProcess;
    buildProcess.setWorkingDirectory(buildDir.absolutePath());
    buildProcess.setProgram("cmake");
    buildProcess.setArguments({"--build", "."});

    output+="Building Project...";
    buildProcess.start();
    if (!buildProcess.waitForFinished(-1)) {
        output+="Build process failed to start or finish!";
        return output;
    }

    if (buildProcess.exitCode() != 0) {
        output+="Build failed:";
        output+=buildProcess.readAllStandardError();
        return output;
    }
    output+="Tests compiled successfully!";
    return output;
}

// QString& Processes::runTests(const QString& projectPath)
// {
//     output = "";
//     QProcess runTestsProcess;
//     runTestsProcess.setWorkingDirectory(projectPath + "/build");
//     runTestsProcess.setProgram("ctest");
//     runTestsProcess.setArguments({"-V"});
//     output+="Running Tests";
//     runTestsProcess.start();
//     if (!runTestsProcess.waitForFinished(-1)) {
//         output+="Run process failed to start or finish!";
//         return output;
//     }
//     output+=runTestsProcess.readAllStandardOutput();
//     output+="Tests ran successfully!";

//     QFile file(projectPath + "/testsOutput.log");
//     file.open(QIODevice::WriteOnly);
//     QTextStream stream(&file);
//     stream << output;
//     file.close();

//     return output;
// }

QString& Processes::runTests(const QString& projectPath)
{
    output = "";
    QProcess runTestsProcess;
    runTestsProcess.setWorkingDirectory(projectPath + "/build");
    runTestsProcess.setProgram("ctest");
    runTestsProcess.setArguments({"-V"});

    runTestsProcess.start();


    output+="Tests ran successfully!";

    QFile file(projectPath + "/testsOutput.log");
    file.open(QIODevice::Append);
    QTextStream stream(&file);
    stream << output;
    file.close();

    return output;
}

QString& Processes::compileAndRunTests(const QString& projectPath)
{
    output = "";
    output+=compileTests(projectPath);
    output+=runTests(projectPath);
    return output;
}

void Processes::readOutput(QProcess& process)
{
    output+=process.readAllStandardOutput();
    output+=process.readAllStandardError();
}

}

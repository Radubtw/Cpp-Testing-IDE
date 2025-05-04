#include "processes.hpp"
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QFile>

Processes::Processes(QString projectPath, QObject *parent)
    : QObject(parent), projectPath(projectPath)
{}

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
void Processes::compileTests(const QString& projectPath)
{
    // Disconnect any previous connections
    disconnect(process, &QProcess::finished, nullptr, nullptr);

    output.clear();
    QDir buildDir(projectPath + "/build");
    if (!buildDir.exists()) {
        buildDir.mkpath(".");
    }

    // Configure for CMake step
    process->setWorkingDirectory(buildDir.absolutePath());
    process->setProgram("cmake");
    process->setArguments({"..", "-G Ninja"});

    // Connect output handlers
    connect(process, &QProcess::readyReadStandardOutput, this, &Processes::readOutput);
    connect(process, &QProcess::readyReadStandardError, this, &Processes::readOutput);

    // Connect finished handler with state tracking
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, buildDir](int exitCode, QProcess::ExitStatus status) {
                static bool isBuildStep = false; // Track which step we're on

                if (exitCode == 0) {
                    if (!isBuildStep) {
                        // CMake step succeeded, now do build
                        output += "CMake finished successfully. Starting build...\n";
                        emit outputChanged(output);

                        process->setProgram("cmake");
                        process->setArguments({"--build", "."});
                        isBuildStep = true;
                        process->start();
                    } else {
                        // Build step completed successfully
                        output += "Build completed successfully!\n";
                        emit outputChanged(output);
                        isBuildStep = false; // Reset for next run
                    }
                } else {
                    output += isBuildStep ? "Build failed!\n" : "CMake failed!\n";
                    emit outputChanged(output);
                    isBuildStep = false; // Reset on failure
                }
            });

    process->start();
}

void Processes::runTests(const QString& projectPath)
{
    output = "";
    process = new QProcess(this);

    process->setWorkingDirectory(projectPath + "/build");
    process->setProgram("ctest");
    process->setArguments({"-V"});
    connect(process, &QProcess::readyReadStandardOutput, this, &Processes::readOutput);

    connect(process, &QProcess::readyReadStandardError, this, &Processes::readOutput);
    connect(process, &QProcess::finished, process, &QProcess::deleteLater);
    QFile file(projectPath + "/testsOutput.log");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "";
    file.close();

    process->start();
}

void Processes::compileAndRunTests(const QString& projectPath)
{
    output = "";
    compileTests(projectPath);
    if(process->state() == QProcess::NotRunning)
    {
        runTests(projectPath);
    }
}

void Processes::readOutput()
{
    output += process->readAllStandardOutput();
    output += process->readAllStandardError();
    if(process->program() == "ctest")
    {
        QFile file(projectPath + "/testsOutput.log");
        file.open(QIODevice::Append | QIODevice::Text);
        QTextStream out(&file);
        out << output;
        file.close();
    }
    emit outputChanged(output);
    output = "";
}

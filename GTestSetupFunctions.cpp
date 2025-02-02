#include <QProcess>
#include <QDebug>
#include <QDir>

void unzipWithTar(const QString &zipFilePath, const QString &extractPath) {
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
void compileGTest(const QString &gtestSourceDir) {
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

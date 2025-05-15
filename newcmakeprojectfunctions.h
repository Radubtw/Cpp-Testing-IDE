#ifndef NEWCMAKEPROJECTFUNCTIONS_H
#define NEWCMAKEPROJECTFUNCTIONS_H
#include <QString>

enum fileType {
    CMakeLists,
    Source,
    Header
};

void createCMakeProject(const QString path, const QString projectName);
void addFile(const QString path, const QString name, fileType type, const QString content);

#endif // NEWCMAKEPROJECTFUNCTIONS_H

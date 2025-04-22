#include "opennewprojectdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QDialogButtonBox>
OpenNewProjectDialog::OpenNewProjectDialog()
{
    QGridLayout* layout = new QGridLayout(this);
    QLabel* nameLabel = new QLabel("Project Name: ");
    projectName = new QLineEdit();
    QLabel* pathLabel = new QLabel("Project path: ");
    projectPath = new QLineEdit();
    emptyProject = new QCheckBox();
    emptyProject->setText("Create Empty Project");
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(projectName, 0,1);
    layout->addWidget(pathLabel, 1, 0);
    layout->addWidget(projectPath, 1,1);
    layout->addWidget(emptyProject);

    QDialogButtonBox *buttonBox = new QDialogButtonBox
        ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
         Qt::Horizontal, this );

    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &OpenNewProjectDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &OpenNewProjectDialog::reject);
}

QString OpenNewProjectDialog::getProjectName()
{
    return projectName->text();
}

QString OpenNewProjectDialog::getProjectPath()
{
    return projectPath->text();
}

bool OpenNewProjectDialog::getEmptyProject()
{
    return emptyProject->isChecked();
}

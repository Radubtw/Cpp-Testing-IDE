#include "outputsection.h"
OutputSection::OutputSection(QWidget* parent) : QTextEdit(parent)
{
    setReadOnly(true);
}

void OutputSection::updateOutput(const QString& text)
{
    append(text);
}

void OutputSection::toggleOutput()
{
    setHidden(isHidden() ^ 1);
}

void OutputSection::clearOutput()
{
    clear();
}

#include "codefield.h"
#include <QKeyEvent>
#include <QTextEdit>

void CodeField::keyPressEvent(QKeyEvent* event)
{
    if((event->modifiers() & Qt::ControlModifier) and (event->key() == Qt::Key_S))
    {
        emit saved();
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}

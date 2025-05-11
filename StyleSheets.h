#pragma once
#ifndef STYLESHEETS_H
#define STYLESHEETS_H
#include<QString>
namespace stylesheets
{
inline const static QString treeViewStyleSheet = R"(
        QTreeView {
            background-color: #1E1E1E;
            color: #D8DEE9;
            border: 1px solid #464646;
            border-radius: 1px;
            padding: 5px;
            alternate-background-color: #252526;
            font-family: "Segoe UI", sans-serif;
            font-size: 14px;
        }

        QTreeView::item {
            padding: 5px;
        }

        QTreeView::item:hover {
            background-color: #252526;
            color: #ECEFF4;
        }

        QTreeView::item:selected {
            background-color: #3C3C3C;
            color: #ECEFF4;
        }

        QTreeView::branch {
            background-color: #1E1E1E;
        }

        QTreeView::branch:closed:has-children,
        QTreeView::branch:open:has-children {
            color: #D8DEE9;
        }

        QHeaderView::section {
            background-color: #1E1E1E;
            color: #D8DEE9;
            padding: 5px;
            border: 1px solid #464646;
            font-size: 14px;
        }

        QHeaderView::section:hover {
            background-color: #464646;
        }

        QScrollBar:vertical {
            background: #252526;
            width: 12px;
            margin: 0px;
        }

        QScrollBar::handle:vertical {
            background: #3C3C3C;
            min-height: 20px;
            border-radius: 6px;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical,
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: none;
        }

        QScrollBar:horizontal {
            background: #252526;
            height: 12px;
            margin: 0px;
        }

        QScrollBar::handle:horizontal {
            background: #3C3C3C;
            min-width: 20px;
            border-radius: 6px;
        }

        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal,
        QScrollBar::add-page:horizontal,
        QScrollBar::sub-page:horizontal {
            background: none;
        })";


inline const static QString codeFieldStyleSheet = R"(
        QTextEdit {
            background-color: #1E1E1E;
            color: #D8DEE9;
            border: 1px solid #464646;
            padding: 10px;
            selection-background-color: #81A1C1;
            selection-color: #ECEFF4;
            font-family: "Segoe UI", sans-serif;
            font-size: 14px;
        }

        QTextEdit:focus {
            border: 1px solid #3C3C3C;
        }

        QScrollBar:vertical {
            background: #252526;
            width: 12px;
            margin: 0px;
        }

        QScrollBar::handle:vertical {
            background: #3C3C3C;
            min-height: 20px;
            border-radius: 6px;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical,
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: none;
        }

        QScrollBar:horizontal {
            background: #252526;
            height: 12px;
            margin: 0px;
        }

        QScrollBar::handle:horizontal {
            background: #3C3C3C;
            min-width: 20px;
            border-radius: 6px;
        }

        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal,
        QScrollBar::add-page:horizontal,
        QScrollBar::sub-page:horizontal {
            background: none;
        }
    )";

inline const static QString labelStyleSheet = R"(
        color: white;
        background-color: #252526;
        font-size: 10px;
        padding: 3px;
    )";

inline const static QString buttonStyleSheet = R"(
        QPushButton {
            background-color: #1E1E1E;
            color: white;
            border-radius: 10px;
            padding: 10px;
            font-size: 16px;
            border: 2px solid #252526;
        }
        QPushButton:hover {
            background-color: #3C3C3C;
        }
        QPushButton:pressed {
            background-color: #3C3C3C;
        }
    )";

inline const static QString generateButtonStyleSheet = R"(
        QPushButton {
            background-color: #1E1E1E;
            color: white;
            padding: 5px;
            font-size: 10px;
            border: 2px solid #252526;
        }
        QPushButton:hover {
            background-color: #3C3C3C;
        }
        QPushButton:pressed {
            background-color: #3C3C3C;
        }
    )";

inline const static QString closeButtonStyleSheet = R"(
        QPushButton {
            background-color: #1E1E1E;
            color: white;
            padding: 3px;
            font-size: 10px;
            border: 2px solid #252526;
        }
        QPushButton:hover {
            background-color: #3C3C3C;
        }
        QPushButton:pressed {
            background-color: #3C3C3C;
        }
    )";

inline const static QString selectedClassOrFunctionStyleSheet = R"(
        QTextEdit {
            background-color: #1E1E1E;
            color: #D8DEE9;
            border: 1px solid #464646;
            padding: 10px;
            selection-background-color: #81A1C1;
            selection-color: #ECEFF4;
            font-family: "Segoe UI", sans-serif;
            font-size: 14px;
        }

        QTextEdit:focus {
            border: 1px solid #3C3C3C;
        }

        QScrollBar:vertical {
            background: #252526;
            width: 12px;
            margin: 0px;
        }

        QScrollBar::handle:vertical {
            background: #3C3C3C;
            min-height: 20px;
            border-radius: 6px;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical,
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: none;
        }

        QScrollBar:horizontal {
            background: #252526;
            height: 12px;
            margin: 0px;
        }

        QScrollBar::handle:horizontal {
            background: #3C3C3C;
            min-width: 20px;
            border-radius: 6px;
        }

        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal,
        QScrollBar::add-page:horizontal,
        QScrollBar::sub-page:horizontal {
            background: none;
        }
    )";

inline const static QString outputSection = R"(
    OutputSection {
        background-color: #1E1E1E;
        color: #D8DEE9;
        border: 1px solid #464646;
        padding: 5px;
        selection-background-color: #81A1C1;
        selection-color: #ECEFF4;
        font-family: "Segoe UI", sans-serif;
        font-size: 14px;
    }

    OutputSection:focus {
        border: 1px solid #3C3C3C;
    }

    QScrollBar:vertical, QScrollBar:horizontal {
        background: #252526;
        width: 12px;
        height: 12px;
        margin: 0px;
    }

    QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
        background: #3C3C3C;
        border-radius: 6px;
        min-height: 20px;
        min-width: 20px;
    }

    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
        background: none;
    }
)";

inline const static QString terminal = R"(
    QTextEdit {
        background-color: #1E1E1E;
        color: #D8DEE9;
        border: 1px solid #464646;
        padding: 5px;
        selection-background-color: #81A1C1;
        selection-color: #ECEFF4;
        font-family: "Segoe UI", sans-serif;
        font-size: 14px;
    }

    QTextEdit:focus {
        border: 1px solid #3C3C3C;
    }

    QScrollBar:vertical, QScrollBar:horizontal {
        background: #252526;
        width: 12px;
        height: 12px;
        margin: 0px;
    }

    QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
        background: #3C3C3C;
        border-radius: 6px;
        min-height: 20px;
        min-width: 20px;
    }

    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
        background: none;
    }
)";


inline const static QString inputLine = R"(
        QLineEdit {
            background-color: #1E1E1E;
            color: white;
            border: 1px solid #464646;
            padding: 5px;
            selection-background-color: #81A1C1;
            selection-color: #ECEFF4;
            font-family: "Segoe UI", sans-serif;
            font-size: 10px;
        }
        QLineEdit:focus {
            border: 1px solid #3C3C3C;
        }
    )";

inline const static QString menuBarStyleSheet = R"(
    QMenuBar {
        background-color: #1E1E1E;
        color: #D8DEE9;
        font-family: "Segoe UI", sans-serif;
        font-size: 10px;
        border-bottom: 1px solid #464646;
    }

    QMenuBar::item {
        background-color: transparent;
        padding: 5px 10px;
        margin: 0px 5px;
    }

    QMenuBar::item:selected {
        background-color: #252526;
        color: #ECEFF4;
    }

    QMenuBar::item:pressed {
        background-color: #3C3C3C;
        color: #ECEFF4;
    }

    QMenu {
        background-color: #1E1E1E;
        color: #D8DEE9;
        border: 1px solid #464646;
        font-size: 14px;
    }

    QMenu::item {
        padding: 6px 20px;
    }

    QMenu::item:selected {
        background-color: #252526;
        color: #ECEFF4;
    }

    QMenu::item:disabled {
        color: #555555;
    }

    QMenu::separator {
        height: 1px;
        background: #464646;
        margin: 5px 10px;
    }
)";

inline const static QString menuStyleSheet = R"(
    QMenu {
        background-color: #1E1E1E;
        color: #D8DEE9;
        border: 1px solid #464646;
        font-family: "Segoe UI", sans-serif;
        font-size: 10px;
    }

    QMenu::item {
        padding: 6px 20px;
        background-color: transparent;
    }

    QMenu::item:selected {
        background-color: #252526;
        color: #ECEFF4;
    }

    QMenu::item:pressed {
        background-color: #3C3C3C;
    }

    QMenu::item:disabled {
        color: #555555;
    }

    QMenu::separator {
        height: 1px;
        background: #464646;
        margin: 5px 10px;
    }

    QMenu::indicator {
        background-color: transparent;
        width: 16px;
        height: 16px;
    }

    QMenu::indicator:checked {
        background-color: #3C3C3C;
        border: 1px solid #464646;
    }

    QMenu::indicator:unchecked {
        background-color: transparent;
    }
)";

inline const static QString iconButtonStyle = R"(
    QPushButton {
        background-color: #252526;
        border-radius: 4px;
        padding: 6px;
    }

    QPushButton:hover {
        background-color: #252526;
    }

    QPushButton:pressed {
        background-color: #3C3C3C;
    }

    QPushButton:disabled {
        background-color: #1E1E1E;
        border: 1px solid #2C2C2C;
        color: #666666;
    }
)";


}
#endif // STYLESHEETS_H

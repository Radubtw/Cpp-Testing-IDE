#ifndef STYLESHEETS_H
#define STYLESHEETS_H
#include<QString>

QString treeViewStyleSheet= R"(QTreeView {
    background-color: #2E3440; /* Dark background */
    color: #D8DEE9; /* Light text color */
    border: 1px solid #4C566A; /* Dark border */
    border-radius: 5px; /* Slightly rounded corners */
    padding: 5px; /* Padding inside the QTreeView */
    alternate-background-color: #3B4252; /* Alternate row color */
    font-family: "Segoe UI", sans-serif; /* Font family */
    font-size: 14px; /* Font size */
    }

    QTreeView::item {
        padding: 5px; /* Padding for each item */
    }

    QTreeView::item:hover {
        background-color: #4C566A; /* Background color on hover */
        color: #ECEFF4; /* Text color on hover */
    }

    QTreeView::item:selected {
        background-color: #81A1C1; /* Background color for selected items */
        color: #ECEFF4; /* Text color for selected items */
    }

    QTreeView::branch {
        background-color: #2E3440; /* Background color for branches */
    }

    QTreeView::branch:closed:has-children {
        color: #D8DEE9; /* Light color for the arrow */
    }

    QTreeView::branch:open:has-children {
        color: #D8DEE9; /* Light color for the arrow */
    }

    QHeaderView::section {
        background-color: #3B4252; /* Background color for header sections */
        color: #D8DEE9; /* Text color for header sections */
        padding: 5px; /* Padding for header sections */
        border: 1px solid #4C566A; /* Border for header sections */
        font-size: 14px; /* Font size for header sections */
    }

    QHeaderView::section:hover {
        background-color: #4C566A; /* Background color on hover */
    }

    QScrollBar:vertical {
        background: #3B4252; /* Dark background for the scrollbar */
        width: 12px; /* Width of the vertical scrollbar */
        margin: 0px 0px 0px 0px;
    }

    QScrollBar::handle:vertical {
        background: #4C566A; /* Dark handle for the scrollbar */
        min-height: 20px; /* Minimum height of the scrollbar handle */
        border-radius: 6px; /* Rounded corners for the handle */
    }

    QScrollBar::add-line:vertical,
    QScrollBar::sub-line:vertical {
        background: none; /* Remove the arrows */
    }

    QScrollBar::add-page:vertical,
    QScrollBar::sub-page:vertical {
        background: none; /* Remove the background of the scrollbar track */
    }

    QScrollBar:horizontal {
        background: #3B4252; /* Dark background for the horizontal scrollbar */
        height: 12px; /* Height of the horizontal scrollbar */
        margin: 0px 0px 0px 0px;
    }

    QScrollBar::handle:horizontal {
        background: #4C566A; /* Dark handle for the horizontal scrollbar */
        min-width: 20px; /* Minimum width of the scrollbar handle */
        border-radius: 6px; /* Rounded corners for the handle */
    }

    QScrollBar::add-line:horizontal,
    QScrollBar::sub-line:horizontal {
        background: none; /* Remove the arrows */
    }

    QScrollBar::add-page:horizontal,
    QScrollBar::sub-page:horizontal {
        background: none; /* Remove the background of the scrollbar track */
    })";

QString codeFieldStyleSheet = R"(
        CodeField {
            background-color: #2E3440;
            color: #D8DEE9;
            border: 1px solid #4C566A;
            border-radius: 5px;
            padding: 5px;
            selection-background-color: #81A1C1;
            selection-color: #ECEFF4;
            font-family: "Segoe UI", sans-serif;
            font-size: 14px;
        }
        CodeField:focus {
            border: 1px solid #81A1C1;
        }
        QScrollBar:vertical {
            background: #3B4252;
            width: 12px;
            margin: 0px 0px 0px 0px;
        }
        QScrollBar::handle:vertical {
            background: #4C566A;
            min-height: 20px;
            border-radius: 6px;
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            background: none;
        }
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: none;
        }
        QScrollBar:horizontal {
            background: #3B4252;
            height: 12px;
            margin: 0px 0px 0px 0px;
        }
        QScrollBar::handle:horizontal {
            background: #4C566A;
            min-width: 20px;
            border-radius: 6px;
        }
        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            background: none;
        }
        QScrollBar::add-page:horizontal,
        QScrollBar::sub-page:horizontal {
            background: none;
        }
    )";

QString buttonStyleSheet = R"(
        QPushButton {
            background-color: #2E3440;
            color: white;
            border-radius: 10px;
            padding: 10px;
            font-size: 16px;
            border: 2px solid #4C566A;
        }
        QPushButton:hover {
            background-color: #4C566A;
        }
        QPushButton:pressed {
            background-color: #81A1C1;
        }
    )";

QString selectedClassOrFunctionStyleSheet = R"(
        QTextEdit {
            background-color: #2E3440;
            color: #D8DEE9;
            border: 1px solid #4C566A;
            border-radius: 5px;
            padding: 5px;
            selection-background-color: #81A1C1;
            selection-color: #ECEFF4;
            font-family: "Segoe UI", sans-serif;
            font-size: 14px;
        }
        QTextEdit :focus {
            border: 1px solid #81A1C1;
        }
        QScrollBar:vertical {
            background: #3B4252;
            width: 12px;
            margin: 0px 0px 0px 0px;
        }
        QScrollBar::handle:vertical {
            background: #4C566A;
            min-height: 20px;
            border-radius: 6px;
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            background: none;
        }
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: none;
        }
        QScrollBar:horizontal {
            background: #3B4252;
            height: 12px;
            margin: 0px 0px 0px 0px;
        }
        QScrollBar::handle:horizontal {
            background: #4C566A;
            min-width: 20px;
            border-radius: 6px;
        }
        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            background: none;
        }
        QScrollBar::add-page:horizontal,
        QScrollBar::sub-page:horizontal {
            background: none;
        }
    )";

#endif // STYLESHEETS_H

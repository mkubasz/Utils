#ifndef EDITORWINDOWS_H
#define EDITORWINDOWS_H

#include <QWidget>

namespace Ui {
class EditorWindows;
}

class EditorWindows : public QWidget
{
    Q_OBJECT

public:
    explicit EditorWindows(QWidget *parent = 0);
    ~EditorWindows();

private:
    Ui::EditorWindows *ui;
};

#endif // EDITORWINDOWS_H

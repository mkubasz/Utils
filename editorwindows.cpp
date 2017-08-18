#include "editorwindows.h"
#include "ui_editorwindows.h"

EditorWindows::EditorWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWindows)
{
    ui->setupUi(this);
}

EditorWindows::~EditorWindows()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include "editorwindows.h"
#include <QMainWindow>
#include <QListWidget>
#include <QMap>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void selectConfigAndLoad();
    void invokeOne(QListWidgetItem* item);
    void doAll();
    void clearAll();
    void addToDo();
    void removeFromDo();
    void on_actionJson_Editor_triggered();

private:
    Ui::MainWindow *ui;
    EditorWindows* editor;
    QListWidget* commandList;
    QListWidget* toDoList;
    QMap<QString, Config> map;
    void invoke(QString command);
    void loadDefaultConfig();
    void loadConfigFile(QFile &file);
};

#endif // MAINWINDOW_H

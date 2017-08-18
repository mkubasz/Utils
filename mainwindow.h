#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include <QMainWindow>
#include <QListWidget>
#include <QMap>

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
    void loadFile();
    void invokeOne(QListWidgetItem* item);
    void invokeAll();

private:
    Ui::MainWindow *ui;
    QListWidget* names;
    QMap<QString, Config> map;
    void invoke(QString command);
};

#endif // MAINWINDOW_H

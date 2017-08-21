#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parserconfig.hpp"
#include <QPushButton>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    commandList = ui->lsCommands;
    toDoList = ui->lsToDo;

    // Set connects
    connect(ui->btnLoad, SIGNAL(released()), this, SLOT(selectConfigAndLoad()));
    connect(ui->btnDo, SIGNAL(released()),this, SLOT(doAll()));
    connect(ui->btnClear, SIGNAL(released()),this, SLOT(clearAll()));
    connect(ui->btnAdd, SIGNAL(released()), this, SLOT(addToDo()));
    connect(ui->btnRemove, SIGNAL(released()),this, SLOT(removeFromDo()));
    connect(commandList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(invokeOne(QListWidgetItem*)));

    loadDefaultConfig();
}

void MainWindow::selectConfigAndLoad()
{
    ui->loaded->setChecked(false);
    commandList->clear();
    QFile configFile(QFileDialog::getOpenFileName(this, tr("Open Config"),NULL, tr("Json Files (*.json)")));
    loadConfigFile(configFile);
}

void MainWindow::loadDefaultConfig()
{
    QString fn = "./config.json";

#ifdef QT_DEBUG
    fn = "../Utils/config.json";
#endif

    QFile configFile(fn);
    if(configFile.exists())
    {
        loadConfigFile(configFile);
    }
}

void MainWindow::loadConfigFile(QFile &file)
{
    if (!file.exists())
    {
        qDebug() << "Cannot find file: " + file.fileName();
        QMessageBox::critical(this, "Error", "Cannot find config file.",QMessageBox::StandardButton::Abort, 0);
        return;
    }
    file.open(QIODevice::ReadOnly);

    QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = jdoc.object();

    if(obj.empty())
    {
        qDebug() << "Parse " + file.fileName() + " file error.";
        QMessageBox::critical(this, "Error", "Error parse json file",QMessageBox::StandardButton::Abort, 0);
        return;
    }

    file.close();

    ui->loaded->setChecked(true);
    ParserConfig parser(obj);
    map = parser.getMap();

    for(auto it = map.begin(); it != map.end(); ++it)
    {
          commandList->addItem(it.key());
    }
}

void MainWindow::addToDo()
{
    QList<QListWidgetItem *> selected = commandList->selectedItems();
    for(auto item : selected)
    {
        toDoList->addItem(item->text());
    }
}

void MainWindow::removeFromDo()
{
    qDeleteAll(toDoList->selectedItems());
}

void MainWindow::invoke(QString command)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.startDetached("/bin/bash", QStringList() << "-c" << command);
    process.waitForFinished();
    qDebug() << "Pass: " << command << process.readAllStandardError();
    qDebug() << "Error: " << command << process.readAllStandardOutput();
    process.close();
}

void MainWindow::invokeOne(QListWidgetItem* item)
{
    const QString command = map[item->text()].command;
    invoke(command);
}

void MainWindow::doAll()
{
    for(int i = 0; i < toDoList->count(); ++i)
    {
        const QString command = map[toDoList->item(i)->text()].command;
        invoke(command);
    }
}

void MainWindow::clearAll()
{
    toDoList->clear();
}


MainWindow::~MainWindow()
{
    delete editor;
    delete ui;
}

void MainWindow::on_actionJson_Editor_triggered()
{
    editor = new EditorWindows(this);
    this->setHidden(true);
    editor->setWindowFlags(Qt::Window);

    // Position child window
    const QRect geometry = this->geometry();
    QPoint pos = this->pos();
    editor->move(pos.rx(), pos.ry());
    editor->resize(geometry.width(), geometry.height());

    editor->show();
}

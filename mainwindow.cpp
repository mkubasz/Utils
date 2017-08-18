#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parserconfig.hpp"
#include <QPushButton>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    names = ui->names;

    // Set connects
    connect(ui->btnLoad, SIGNAL(released()), this, SLOT(loadFile()));
    connect(ui->btnInvoke, SIGNAL(released()),this, SLOT(invokeAll()));
    connect(names, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(invokeOne(QListWidgetItem*)));
}

void MainWindow::loadFile()
{
    ui->loaded->setChecked(false);
    names->clear();
    const QString fn = QFileDialog::getOpenFileName(this, tr("Open Config"),NULL, tr("Json Files (*.json)"));

    QFile file(fn);
    file.open(QIODevice::ReadOnly);

    QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = jdoc.object();

    if(obj.empty())
    {
        qDebug() << "Parse " + fn + " file error.";
        QMessageBox::critical(this, "Error", "Error parse json file",QMessageBox::StandardButton::Abort, 0);
        return;
    }

    file.close();

    ui->loaded->setChecked(true);
    ParserConfig parser(obj);
    map = parser.getMap();

    for(auto it = map.begin(); it != map.end(); ++it)
    {
          names->addItem(it.key());
    }
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

void MainWindow::invokeAll()
{
    for(auto it = map.begin(); it != map.end(); ++it)
    {
        invoke(it.value().command);
    }
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

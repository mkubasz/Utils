#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <parserconfig.hpp>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    names = ui->names;
    connect(ui->btnLoad, SIGNAL(released()), this, SLOT(loadFile()));
    connect(ui->btnInvoke, SIGNAL(released()),this, SLOT(invokeAll()));
}

void MainWindow::loadFile()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open Config"),NULL, tr("Json Files (*.json)"));
    QFile file(fn);
    file.open(QIODevice::ReadOnly);
    QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = jdoc.object();
    file.close();
    ParserConfig parser(obj);

    map = parser.getMap();
    names->clear();
    for(auto it = map.begin(); it != map.end(); ++it)
    {
          names->addItem(it.key());
    }
    connect(names, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(invokeOne(QListWidgetItem*)));
}

void MainWindow::invokeOne(QListWidgetItem* item)
{
    QString it = map[item->text()].command;
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("/bin/bash", QStringList() << "-c" << it);
    process.waitForFinished();
    qDebug() << process.readAllStandardError();
    qDebug() << process.readAllStandardOutput();
    process.close();
}

void MainWindow::invokeAll()
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    for(auto it = map.begin(); it != map.end(); ++it)
    {
        process.start("/bin/bash", QStringList() << "-c" << it.value().command);
        process.waitForFinished();
        qDebug() << process.readAllStandardError();
        qDebug() << process.readAllStandardOutput();
        process.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

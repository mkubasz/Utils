#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <parserconfig.hpp>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
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
    connect(names, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(invokeOne(QListWidgetItem*)));
}

void MainWindow::loadFile()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open Config"),NULL, tr("Json Files (*.json)"));
    QFile file(fn);
    file.open(QIODevice::ReadOnly);
    QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = jdoc.object();
    if(obj.empty())
    {
        qDebug() << "Parse " + fn + " json file error.";
        QMessageBox::critical(this, "Error", "Error parse json file",QMessageBox::StandardButton::Abort, NULL);
    }
    file.close();
    ParserConfig parser(obj);

    map = parser.getMap();
    names->clear();
    for(auto it = map.begin(); it != map.end(); ++it)
    {
          names->addItem(it.key());
    }
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

void MainWindow::invoke(QString command)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("/bin/bash", QStringList() << "-c" << command);
    process.waitForFinished();
    qDebug() << "Pass: " << command << process.readAllStandardError();
    qDebug() << "Error: " << command << process.readAllStandardOutput();
    process.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

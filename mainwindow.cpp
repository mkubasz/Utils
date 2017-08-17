#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <config.hpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *btnLoad = ui->btnLoad;
    names = ui->names;
    connect(btnLoad, SIGNAL(released()), this, SLOT(loadFile()));
    //connect(btnCheck, SIGNAL(released()),this, SLOT(checkPassword()));
}

void MainWindow::loadFile()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open Config"),NULL, tr("Json Files (*.json)"));
    QFile file(fn);
    file.open(QIODevice::ReadOnly);
    QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = jdoc.object();
    file.close();
    Config conf(obj);
    QMap<QString, QString> map = conf.map;
    for(auto it = map.begin(); it != map.end(); ++it)
    {
          names->addItem("Test");
    }
}

//void MainWindow::checkPassword()
//{
//    QString pass = ui->boxPassword->text();
//    QProcess process;
//    process.setProcessChannelMode(QProcess::MergedChannels);
//    process.start("/bin/bash", QStringList()<< "-c" << "docker restart decisco");
//    process.waitForFinished();
//    qDebug()<< process.readAllStandardError();
//    qDebug()<< process.readAllStandardOutput();
//    process.close();
//}



MainWindow::~MainWindow()
{
    delete ui;
}

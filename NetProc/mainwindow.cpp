#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    
    qDebug() << ui->lineEdit->text();
    manager->get(QNetworkRequest(QUrl(ui->lineEdit->text())));
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    qDebug() << reply->bytesAvailable();
    if(reply->bytesAvailable() > 0) {
        ui->textEdit->setText(reply->readAll());
    }
}

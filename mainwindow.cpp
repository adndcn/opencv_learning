#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    QString fileName = QFileDialog::getOpenFileName(this,
//    tr("Open Image"), ".",
//    tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    cv::Mat ima(240, 320, CV_8U, cv::Scalar(250));
    cv::namedWindow("window");
    cv::imshow("window", ima);

}

void MainWindow::on_pushButton_2_clicked()
{
}

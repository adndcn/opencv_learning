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

void sharpen(const cv::Mat &image, cv::Mat &result)
{
    // allocate if necessary
    result.create(image.size(), image.type());
    for (int j= 1; j<image.rows-1; j++)
    { // for all rows
        // (except first and last)
        const uchar* previous=
        image.ptr<const uchar>(j-1); // previous row
        const uchar* current=
        image.ptr<const uchar>(j); // current row
        const uchar* next=
        image.ptr<const uchar>(j+1); // next row
        uchar* output= result.ptr<uchar>(j); // output row
        for (int i=1; i<image.cols-1; i++)
        {
            *output++= cv::saturate_cast<uchar>(5*current[i]-current[i-1]-current[i+1]-previous[i]-next[i]);
        }
    }
    // Set the unprocess pixels to 0
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "F:\\qt\\opencv_learning",
    tr("Image Files (*.png *.jpg *.jpeg *.bmp *.tif)"));
    image = cv::imread(fileName.toLatin1().data(), 0);
    cv::namedWindow("window");
    cv::imshow("window", image);

}

void MainWindow::on_pushButton_2_clicked()
{
    cv::Mat result;
    sharpen(image, result);
    cv::namedWindow("result");
    cv::imshow("result", result);
}

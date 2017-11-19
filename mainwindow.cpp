#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histogram1d.h"

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

void sharpen2D(const cv::Mat &image, cv::Mat &result) {
    // Construct kernel (all entries initialized to 0)
    cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
    // assigns kernel values
    kernel.at<float>(1,1)= 5.0;
    kernel.at<float>(0,1)= -1.0;
    kernel.at<float>(2,1)= -1.0;
    kernel.at<float>(1,0)= -1.0;
    kernel.at<float>(1,2)= -1.0;
    //filter the image
    cv::filter2D(image,result,image.depth(),kernel);
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
    Histogram1D h;

    cv::Mat histo = h.getHistogramImage(image);

    cv::namedWindow("result");
    cv::imshow("result", histo);
}

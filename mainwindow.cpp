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

void salt(cv::Mat &ima, int n)
{
    qsrand(90000);
    for (int k=0; k<n; k++)
    {
        // rand() is the MFC random number generator
        // try qrand() with Qt
        int i= qrand()%ima.cols;
        int j= qrand()%ima.rows;
        if (ima.channels() == 1)
        { // gray-level image
            ima.at<uchar>(j,i)= 255;
        } else if (ima.channels() == 3)
        { // color image
            ima.at<cv::Vec3b>(j,i)[0]= 255;
            ima.at<cv::Vec3b>(j,i)[1]= 255;
            ima.at<cv::Vec3b>(j,i)[2]= 255;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), ".",
    tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    image= cv::imread(fileName.toLatin1().data());
    cv::namedWindow("Original Image");
    cv::imshow("Original Image", image);
}

void MainWindow::on_pushButton_2_clicked()
{
    double duration;
    duration = static_cast<double>(cv::getTickCount());
    cv::flip(image,image,1);
    cv::cvtColor(image, image, CV_BGR2RGB);

    QImage img = QImage((const unsigned char*)(image.data),
            image.cols, image.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    ui->label->resize(ui->label->pixmap()->size());
    duration = static_cast<double>(cv::getTickCount()) - duration;
    duration /= cv::getTickFrequency();
    cout<<duration<<"s"<<endl;
}

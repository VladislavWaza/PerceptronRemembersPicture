#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "network.h"
#include <cuchar>
#include <QFileDialog>
#include <chrono>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double getDistanceBetweenColors(const QColor& color1, const QColor& color2)
{
    return sqrt(pow(color1.red()-color2.red(), 2) +
                pow(color1.blue()-color2.blue(), 2) +
                pow(color1.green()-color2.green(), 2));
}

void MainWindow::on_pushButton_clicked()
{
    QPixmap pm;
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "Выберите файл", "../", "Images (*.png *.bmp *.jpg)");
    if (!fileName.isEmpty())
    {
        ui->logs->clear();

        pm.load(fileName);
        ui->img->setPixmap(pm);
        QImage img(pm.toImage());
        ui->logs->append("Picture size: " + QString::number(img.width()) + " x " + QString::number(img.height()));

        const ActivateFunction::FunctionType af = ActivateFunction::FunctionType::ReLU;
        const std::vector<size_t> sizes = {2, 10, 10, 10, 3};
        size_t l = sizes.size();
        const int maxEpoch = 20;
        const int eps = 0;
        Network NW(l,sizes, af);

        ui->logs->append("Network config:");
        ui->logs->append(QString::number(l) + " layers");
        QString str("Sizes of layers: ");
        for (size_t i = 0; i < l; ++i)
            str += QString::number(sizes[i]) + ' ';
        ui->logs->append(str);
        if (af == ActivateFunction::FunctionType::Sigmoid)
            ui->logs->append("Activate function: sigmoid");
        else if (af == ActivateFunction::FunctionType::Linear)
            ui->logs->append("Activate function: Linear");
        else if (af == ActivateFunction::FunctionType::ReLU)
            ui->logs->append("Activate function: ReLU");
        else if (af == ActivateFunction::FunctionType::Tanh)
            ui->logs->append("Activate function: Tanh");
        ui->logs->append("Epsilon: " + QString::number(eps));
        ui->logs->append("----------------------------------------------");
        ui->logs->append("Training...");
        QImage result(img.size(), img.format());
        setUpdatesEnabled(true);
        repaint();
        setUpdatesEnabled(false);


        auto begin = std::chrono::steady_clock::now();
        int examples = img.height() * img.width();
        int score = 0, epoch = 0;
        int bestScore = 0;
        while (score / examples * 100 < 100)
        {
            score = 0;
            auto t1 = std::chrono::steady_clock::now();
            for (int x = 0; x < img.width(); ++x)
            {
                for (int y = 0; y < img.height(); ++y)
                {
                    std::vector<double> in = {static_cast<double>(x)/img.width(), static_cast<double>(y)/img.height()};
                    NW.input(in);
                    NW.forwardFeed();
                    Vector out = NW.getLastLayer();
                    QColor c;
                    c.setRedF(out(0));
                    c.setGreenF(out(1));
                    c.setBlueF(out(2));
                    result.setPixelColor(x,y,c);
                    QColor trueColor = img.pixelColor(x,y);
                    if (getDistanceBetweenColors(c, trueColor) > eps)
                    {
                        out(0) = trueColor.redF();
                        out(1) = trueColor.greenF();
                        out(2) = trueColor.blueF();
                        NW.backPropogation(out);
                        NW.updateWeights(0.15 * exp(-epoch / static_cast<double>(maxEpoch)));
                    }
                    else {
                        ++score;
                    }
                }
            }
            auto t2 = std::chrono::steady_clock::now();
            auto time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
            if (score > bestScore)
            {
                bestScore = score;
                m_best = result;
            }

            str = "epoch: " + QString::number(epoch);
            str += "  score: "+ QString::number(score / static_cast<double>(examples) * 100);
            str += "  time: " + QString::number(time.count()) + "ms";
            ui->logs->append(str);
            ui->img2->setPixmap(QPixmap::fromImage(result));
            setUpdatesEnabled(true);
            repaint();
            setUpdatesEnabled(false);
            ++epoch;
            if (epoch == maxEpoch)
                break;
        }
        auto end = std::chrono::steady_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        ui->logs->append("----------------------------------------------");
        ui->logs->append("time: " + QString::number(time.count() / 60000.0) + " min");
        ui->logs->append("best score: " + QString::number(bestScore / static_cast<double>(examples) * 100));
        setUpdatesEnabled(true);
        repaint();
        setUpdatesEnabled(false);
    }
    setUpdatesEnabled(true);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->img2->setPixmap(QPixmap::fromImage(m_best));
}


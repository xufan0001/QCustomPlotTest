#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);

    setupRealtimeDataDemo(ui->widget);
    ui->widget->replot();

//    ui->checkBox_temp->setChecked(true);
//    ui->checkBox_hui->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
//    customPlot->graph(0)->rescaleAxes(true);
    customPlot->graph(0)->setName("temp");

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));
//    customPlot->graph(1)->rescaleAxes(true);
    customPlot->graph(1)->setName("hui");


//    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
//    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
//    customPlot->xAxis->setAutoTickStep(false);
//    customPlot->xAxis->setTickStep(2);
//    customPlot->axisRect()->setupFullAxesBox();

    // include this section to fully disable antialiasing for higher performance:
    /*
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    customPlot->legend->setFont(font);
    */
//    customPlot->addGraph(); // blue line
//    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
//    customPlot->addGraph(); // red line
//    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
//    timeTicker->setTickOrigin(60);
//    timeTicker->setTickCount(10);
    //timeTicker->setFieldWidth(QCPAxisTickerTime::tuSeconds,3);
//    timeTicker->setTickStepStrategy(QCPAxisTicker::tssReadability);
    customPlot->xAxis->setTicker(timeTicker);

    customPlot->axisRect()->setupFullAxesBox();
    //customPlot->yAxis->setRange(-2, 2);



      customPlot->xAxis2->setVisible(true);
      customPlot->xAxis2->setTickLabels(false);
      customPlot->yAxis2->setVisible(true);
      customPlot->yAxis2->setTickLabels(false);
      // make left and bottom axes always transfer their ranges to right and top axes:
      connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
      connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

      customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    //customPlot->yAxis->rescale(true);


//    customPlot->xAxis->setAutoTickStep(false);
//    customPlot->xAxis->setTickStep(1); // one  in seconds
//    customPlot->xAxis->setSubTickCount(3);

    // make left and bottom axes transfer their ranges to right and top axes:
//    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
//    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
//    dataTimer.start(0); // Interval 0 means to refresh as fast as possible

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
    customPlot->legend->setVisible(true);
//    customPlot->legend->setWrap(101);
}

void MainWindow::realtimeDataSlot()
{
//    //key的单位是秒
//    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
//    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 10000);
//    //使用随机数产生两条曲线
//    double value0 = qrand() % 100;
//    double value1 = qrand() % 80;
//    if (ui->checkBox_temp->isChecked())
//       ui->widget->graph(0)->addData(key, value0);//添加数据1到曲线1
//    if (ui->checkBox_hui->isChecked())
//       ui->widget->graph(1)->addData(key, value1);//添加数据2到曲线2
//    //删除8秒之前的数据。这里的8要和下面设置横坐标宽度的8配合起来
//    //才能起到想要的效果，可以调整这两个值，观察显示的效果。
//    ui->widget->graph(0)->removeDataBefore(key-8);
//    ui->widget->graph(1)->removeDataBefore(key-8);

//    //自动设定graph(1)曲线y轴的范围，如果不设定，有可能看不到图像
//    //也可以用ui->customPlot->yAxis->setRange(up,low)手动设定y轴范围

//    ui->widget->graph(0)->rescaleValueAxis();
//    ui->widget->graph(1)->rescaleValueAxis(true);

//    //这里的8，是指横坐标时间宽度为8秒，如果想要横坐标显示更多的时间
//    //就把8调整为比较大到值，比如要显示60秒，那就改成60。
//    //这时removeDataBefore(key-8)中的8也要改成60，否则曲线显示不完整。
//    ui->widget->xAxis->setRange(key+0.25, 8, Qt::AlignRight);//设定x轴的范围
//    ui->widget->replot();

    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    //if (key-lastPointKey > 0.002) // at most add point every 2 ms
    if (key-lastPointKey > 0.2)
    {
      // add data to lines:
        ui->widget->graph(0)->addData(key, qSin(key));
        ui->widget->graph(1)->addData(key, qCos(key));
//      ui->widget->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
//      ui->widget->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      // rescale value (vertical) axis to fit the current data:
      ui->widget->graph(0)->rescaleValueAxis();
      ui->widget->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }

    // make key axis range scroll with the data (at a constant range size of 8):
    //ui->widget->xAxis->moveRange(60);
    ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->widget->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->widget->graph(0)->data()->size()+ui->widget->graph(1)->data()->size())
            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
}

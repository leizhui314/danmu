#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    i = 0;
    start = 0;
    w = QApplication::desktop()->width();
    h = QApplication::desktop()->height();

    url = "http://139.196.140.182/dm.php/s?dm=1";
    Qnam = new QNetworkAccessManager(this);
    QObject::connect(Qnam, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::la(QString s)
{
    i = (i + 1) % 1000;
    //设置随机数种子
    QTime time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    //设置字体
    QFont ft;
    ft.setPointSize(25);
    //随机数
    int r = qrand() % (h - 50);
    //设置标签
    label[i] = new QLabel(this);
    label[i]->setGeometry(w, r, 100, 30);
    label[i]->setFont(ft);
    label[i]->setText(s);
    //设置动画
    pa[i] = new QPropertyAnimation(label[i], "pos");
    pa[i]->setDuration(5000);
    pa[i]->setStartValue(QPoint(w, r));
    pa[i]->setEndValue(QPoint(-100, r));
    label[i]->show();
    pa[i]->start();
}

void Widget::finishedSlot(QNetworkReply *reply)
{
    //获取label内容
    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes);
    if(reply->error() == QNetworkReply::NoError){
        la(str);
    }
    else{
        qDebug() << reply->error();
        la("error");
    }
    reply->deleteLater();
}

void Widget::sl(unsigned int msec)
{
    QTime t;
    t.start();
    while(t.elapsed() < msec)
        QCoreApplication::processEvents();
}

void Widget::on_pushButton_clicked()
{
    start = 1 - start;
    if(start == 1)
        ui->pushButton->setText("End");
    else
        ui->pushButton->setText("Start");
    while(start){
        Qnam->get(QNetworkRequest(url));
        sl(500);
    }
}

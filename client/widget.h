#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QLabel>
#include <QPropertyAnimation>
#include <QDesktopWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QNetworkAccessManager *Qnam;
    void sl(unsigned int msec);
    int w, h;
    QUrl url;
    void la(QString s);
    QLabel *label[1000];
    QPropertyAnimation *pa[1000];
    int i;
    int start;

private slots:
    void finishedSlot(QNetworkReply *reply);
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H

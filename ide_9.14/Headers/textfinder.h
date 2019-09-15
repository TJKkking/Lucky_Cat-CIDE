#ifndef TEXTFINDER_H
#define TEXTFINDER_H
#include<QlineEdit>
#include <QDialog>
#include<QVBoxLayout>
#include <QPlainTextEdit>
#include <QObject>
class QPushButton;
class TextFinder : public QDialog
{
    Q_OBJECT

public:
    TextFinder(QWidget *parent = 0);
    QPushButton *findButton;
    QPushButton *exchangeButton;
    QLineEdit *findlineEdit;
    QLineEdit *exchangeEdit;
    QString str;
    QString str2;
    QVBoxLayout *lay;
    QHBoxLayout *toplay;
    QHBoxLayout *downlay;
signals:
    void sendData(QString);//输送查找信号
    void sendData2(QString,QString);//输送替换信号
private slots:
    void on_findButton_clicked();
    void on_exchangeButton_clicked();
};

#endif // TEXTFINDER_H

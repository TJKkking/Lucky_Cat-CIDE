#include <textfinder.h>
#include<QString>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <luckycat.h>
TextFinder::TextFinder(QWidget *parent)
    : QDialog (parent)
{
    setWindowTitle(tr("查找"));
    resize(300,100);
    findlineEdit = new QLineEdit();
    findButton = new QPushButton(tr("查找"));
    exchangeEdit = new QLineEdit();
    exchangeButton = new QPushButton(tr("替换"));
    toplay = new QHBoxLayout();
    toplay->addWidget(findlineEdit);
    toplay->addWidget(findButton);
    downlay = new QHBoxLayout();
    downlay->addWidget(exchangeEdit);
    downlay->addWidget(exchangeButton);
    lay = new QVBoxLayout();
    lay->addLayout(toplay);
    lay->addLayout(downlay);
    setLayout(lay);
    connect(findButton,SIGNAL(clicked()),this,SLOT(on_findButton_clicked()));
    connect(exchangeButton,SIGNAL(clicked()),this,SLOT(on_exchangeButton_clicked()));
}

void TextFinder::on_findButton_clicked(){
    str=findlineEdit->text();
    emit sendData(str);
}

void TextFinder::on_exchangeButton_clicked(){
    str=findlineEdit->text();
    str2=exchangeEdit->text();
    emit sendData2(str,str2);
}

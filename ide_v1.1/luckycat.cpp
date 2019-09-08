#include "luckycat.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QSplitter>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>
#include<QString>
#include <stdlib.h>

#define cout qDebug()
QTextCodec *co;

luckycat::luckycat(QWidget *parent)
        : QMainWindow(parent)
{
        setWindowTitle(tr("LuckyCat"));
        setWindowIcon(QIcon(":/image/title.jpg"));

        co = QTextCodec::codecForName("GBK");
        //菜单栏
        filemenu();
        editmenu();
        runmenu();
        //helpmenu();
        //工具栏
        tool();
        //状态栏
        status();
        //分割窗口
        splitter();

        isChanged=false;
        this->TextIndex=0;
        QListWidgetItem *qwi=new QListWidgetItem;
        CodeEditor *qpt=new CodeEditor;
        qwi->setText("未命名");
        qwi->setTextAlignment(Qt::AlignCenter);
        Texts.push_back(qpt);
        textMain->setEnabled(true);
        FileManager->addItem(qwi);
        FileManager->item(this->TextIndex)->setSelected(true);

        //第一个参数是触发事件的控件，第二个参数是对于Action来说的固定写法
        //第三个参数固定写this，第四个参数指定点击Action后执行那个函数
        connect(newAction,SIGNAL(triggered()),this,SLOT(on_new()));
        connect(openAction,SIGNAL(triggered()),this,SLOT(on_open()));
        connect(closeAction,SIGNAL(triggered()),this,SLOT(on_close()));
        connect(saveAction,SIGNAL(triggered()),this,SLOT(on_save()));
        connect(copyAction,SIGNAL(triggered()),this,SLOT(on_copy()));
        connect(cutAction,SIGNAL(triggered()),this,SLOT(on_cut()));
        connect(pasteAction,SIGNAL(triggered()),this,SLOT(on_paste()));
        connect(selectallAction,SIGNAL(triggered()),this,SLOT(on_selectall()));
        connect(compileAction,SIGNAL(triggered()),this,SLOT(on_compile()));
        connect(runAction,SIGNAL(triggered()),this,SLOT(on_run()));
        connect(textMain,SIGNAL(textChanged()),this,SLOT(on_changed()));
        connect(comprunAction,SIGNAL(triggered()),this,SLOT(on_comprun()));
        connect(textMain,SIGNAL(textChanged()),this,SLOT(SaveMainText()));
        connect(FileManager,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(ChangeMainText(QListWidgetItem*)));
}

luckycat::~luckycat()
{
         delete textMain;
}
//文件下拉菜单
void luckycat::filemenu()
{   //新建按钮
    newAction = new QAction(tr("&新建文件"), this);
    openAction = new QAction(tr("&打开文件"), this);
    closeAction = new QAction(tr("&关闭文件"), this);
    saveAction = new QAction(tr("&保存文件"), this);
    //插入到菜单栏
    file1 = menuBar()->addMenu(tr("&文件"));
    file1->addAction(newAction);
    file1->addAction(openAction);
    file1->addAction(closeAction);
    file1->addAction(saveAction);
    //状态栏显示
    newAction->setStatusTip(tr("新建文件"));
    openAction->setStatusTip(tr("打开文件"));
    closeAction->setStatusTip(tr("关闭文件"));
    saveAction->setStatusTip(tr("保存文件"));
    //快捷键绑定
    newAction->setShortcut(QKeySequence::New);
    openAction->setShortcut(QKeySequence::Open);
    closeAction->setShortcut(QKeySequence::Close);
    saveAction->setShortcut(QKeySequence::Save);
}
//编辑下拉菜单
void luckycat::editmenu()
{
    copyAction = new QAction(tr("&复制(C)"), this);
    cutAction = new QAction(tr("&剪切(T)"), this);
    pasteAction = new QAction(tr("&粘贴(P)"), this);
    selectallAction = new QAction(tr("&Select All(A)"), this);

    file2 = menuBar()->addMenu(tr("&编辑"));
    file2->addAction(copyAction);
    file2->addAction(cutAction);
    file2->addAction(pasteAction);
    file2->addSeparator();
    file2->addAction(selectallAction);

    copyAction->setShortcut(QKeySequence::Copy);
    cutAction->setShortcut(QKeySequence::Cut);
    pasteAction->setShortcut(QKeySequence::Paste);
    selectallAction->setShortcut(QKeySequence::SelectAll);
}
//运行下拉菜单
void luckycat::runmenu()
{
    compileAction = new QAction(tr("&编译"), this);
    runAction = new QAction(tr("&运行"), this);
    comprunAction = new QAction(tr("&编译运行"), this);

    file3 = menuBar()->addMenu(tr("&运行"));
    file3->addAction(compileAction);
    file3->addAction(runAction);
    file3->addAction(comprunAction);

    compileAction->setStatusTip(tr("编译"));
    runAction->setStatusTip(tr("运行"));
    comprunAction->setStatusTip(tr("编译运行"));

    compileAction->setShortcut(QKeySequence(Qt::Key_F9));
    runAction->setShortcut(QKeySequence(Qt::Key_F10));
    comprunAction->setShortcut(QKeySequence(Qt::Key_F11));
}
//工具栏
void luckycat::tool()
{   //图标更改
    newAction->setIcon(QIcon(":/image/newsrc.bmp"));
    openAction->setIcon(QIcon(":/image/opnproj.bmp"));
    closeAction->setIcon(QIcon(":/image/closefl.bmp"));
    saveAction->setIcon(QIcon(":/image/save.bmp"));
    compileAction->setIcon(QIcon(":/image/compile.bmp"));
    runAction->setIcon(QIcon(":/image/run.bmp"));
    comprunAction->setIcon(QIcon(":/image/comprun.bmp"));
    //按钮添加
    toolBar = addToolBar(tr("&文件"));
    toolBar->addAction(newAction);
    toolBar->addAction(openAction);
    toolBar->addAction(closeAction);
    toolBar->addAction(saveAction);
    toolBar->addSeparator();
    toolBar->addAction(compileAction);
    toolBar->addAction(runAction);
    toolBar->addAction(comprunAction);
}
//状态栏
void luckycat::status()
{
    msgLabel = new QLabel;
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);

    statusBar()->addWidget(msgLabel);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
}
void luckycat::splitter()
{
    QSplitter *splitterMain =new QSplitter(Qt::Horizontal);//新建一个分割类对象作为分割窗口，设置分割方式为水平
    textLeft=new QTextEdit(splitterMain);
    QSplitter *splitterRight =new QSplitter(Qt::Vertical,splitterMain);//右分割窗口，分割方式为垂直
    splitterRight->setOpaqueResize(true);//设置实时更新是否可用
    QSplitter *splitterRightUp =new QSplitter(Qt::Vertical,splitterRight);
    FileManager=new QListWidget(splitterRightUp);
    FileManager->setFlow(QListView::TopToBottom);
    FileManager->setFont(QFont("微软雅黑",12,QFont::Light));
    QSplitter *splitterRightDown=new QSplitter(Qt::Horizontal,splitterRightUp);
    textMain=new CodeEditor();
    LineNumber=new LineNumberArea(textMain);
    //splitterRightDown->addWidget(LineNumber);
    splitterRightDown->addWidget(textMain);
    textMain->setFont(QFont("微软雅黑",16,QFont::Normal));
    textBottom =new QTextEdit(splitterRight);
    this->setCentralWidget(splitterMain);

    textBottom->setReadOnly(true);

    splitterMain->setHandleWidth(5);
    splitterRight->setHandleWidth(5);
    splitterRightUp->setHandleWidth(0);
    splitterRightDown->setHandleWidth(0);

    splitterMain->setStretchFactor(0, 1);
    splitterMain->setStretchFactor(1, 9);
    splitterRight->setStretchFactor(0,7);
    splitterRight->setStretchFactor(1,3);
    splitterRightUp->setStretchFactor(0,1);
    splitterRightUp->setStretchFactor(1,9);
    splitterRightDown->setStretchFactor(0,1);
    splitterRightDown->setStretchFactor(1,9);

}
void luckycat::on_new()
{
    QListWidgetItem *qwi=new QListWidgetItem;
    CodeEditor *qpt=new CodeEditor;
    qwi->setText("未命名");
    qwi->setTextAlignment(Qt::AlignCenter);
    FileManager->addItem(qwi);
    Texts.push_back(qpt);
    FileManager->item(this->TextIndex)->setSelected(false);
    FileManager->scrollToBottom();
    this->TextIndex=FileManager->count()-1;
    FileManager->item(this->TextIndex)->setSelected(true);
    textMain->setPlainText(qpt->document()->toPlainText());
}

void luckycat::on_open()
{
    filename=QFileDialog::getOpenFileName(this,tr("打开文件"),".",tr("C source files(*.c *.h)"));
    //函数返回路径+文件名

    QListWidgetItem *qwi=new QListWidgetItem;
    CodeEditor *qpt=new CodeEditor;
    if(!filename.isEmpty())
    {
    QFile p(filename);
    if(!p.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","打开文件失败");
    }
    else
    {
        qpt->setPlainText(p.readAll());
        p.close();

    }
    }
    qwi->setText(filename);
    qwi->setTextAlignment(Qt::AlignCenter);
    FileManager->addItem(qwi);
    Texts.push_back(qpt);
    FileManager->item(this->TextIndex)->setSelected(false);
    this->TextIndex=FileManager->count()-1;
    FileManager->item(this->TextIndex)->setSelected(true);
    FileManager->scrollToBottom();
    textMain->setPlainText(qpt->document()->toPlainText());
    textMain->setEnabled(true);
}
void luckycat::on_close()
{
    if(this->TextIndex>=FileManager->count()) return;
    if(!FileManager->item(this->TextIndex)->isSelected()) return;
    Texts.removeAt(this->TextIndex);
    QListWidgetItem *item=FileManager->item(this->TextIndex);
    delete item;
    textMain->setEnabled(false);
}
void luckycat::on_save()
{
    if(this->TextIndex>=FileManager->count()) return;
    if(!(FileManager->item(this->TextIndex)->isSelected())) return;
      QString e=textMain->toPlainText();
      savefilename=QFileDialog::getSaveFileName(this,tr("保存文件"),".",tr("C source files(*.c *.h)"));
      if(!savefilename.isEmpty())
      {
      QFile p(savefilename);
      if(!p.open(QIODevice::WriteOnly  | QIODevice::Text))
      {
          QMessageBox::warning(this,"错误","保存文件失败");
          return;
      }
      else
      {
          p.write(e.toUtf8());
          p.close();

      }
      }
}
void luckycat::on_copy()
{
    textMain->copy();
}
void luckycat::on_cut()
{
    textMain->cut();
}
void luckycat::on_paste()
{
    textMain->paste();
}
void luckycat::on_selectall()
{
    textMain->selectAll();
}
void luckycat::on_compile()
{
    if (isChanged== true)//在点击编译按钮，如果文本内容发生变化，就自动保存
        {
            on_save();
        }
    if(!savefilename.isEmpty())
    {
        QString demo = savefilename;

        demo.replace(".c", ""); //将.c替换为空字符
        //cout << "demo = " << demo;

        QString cmd = QString("gcc %1 -o %2").arg(savefilename).arg(demo);

        cout << "cmd = "<<cmd;

        //如果有中文，需要转化gbk，同时将QString 转换为 char *;
        int ret = system(co->fromUnicode(cmd).data());
        //cout << "ret = " << ret;
        if(ret != 0)
        {
            cmd = QString("cmd /k gcc %1 -o %2").arg(savefilename).arg(demo);
            system(co->fromUnicode(cmd).data());
            return;
        }

        //如何删除那个临时文件呢
        cmd = filename.replace("/","\\") + ".c";
        remove(cmd.toStdString().data());

    }

}
void luckycat::on_run()
{
    QString demo = savefilename;

    demo.replace(".c", "");
    QString cmd = QString("cmd /k %1").arg(demo);
    system(co->fromUnicode(cmd).data());
}
void luckycat::on_comprun()
{
    on_compile();
    on_run();
}
void luckycat::on_changed()
{
    isChanged=true;
}

void luckycat::ChangeMainText(QListWidgetItem* item){
    this->TextIndex=FileManager->row(item);
    textMain->setPlainText(Texts.at(this->TextIndex)->document()->toPlainText());
    textMain->setEnabled(true);
}

void luckycat::SaveMainText(){
    Texts.at(this->TextIndex)->setPlainText(textMain->document()->toPlainText());
}

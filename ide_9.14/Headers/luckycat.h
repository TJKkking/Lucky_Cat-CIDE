#ifndef luckycat_H
#define luckycat_H

#include <QMainWindow>
#include<QTextEdit>
#include<QSplitter>
#include<QListWidget>
#include<QTextBrowser>
#include<QVector>
#include<QPlainTextEdit>
#include"codeeditor.h"
#include "highlighter.h"
#include"textfinder.h"
#include<QCompleter>
#include<QStringListModel>
#include<QGuiApplication>
#include <QFileSystemModel>
class QTreeView;
QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QCompleter;
class QLabel;
class QLineEdit;
class QProgressBar;
QT_END_NAMESPACE
class CodeEditor;
class QAction;
class QLabel;

class MyFileSytemModel : public QFileSystemModel
{
public:
    //第1列显示名称，其他几列都屏蔽掉
    int columnCount(const QModelIndex &parent) const
    {
        return 1;
    }
};

class luckycat : public QMainWindow
{
        Q_OBJECT

public:
        luckycat(QWidget *parent = 0);
        ~luckycat();

private:
        bool isChanged;
        int TextIndex;
        QString filename;
        QString savefilename;

        CodeEditor *textMain;

        QAction *openAction;
        QAction *newAction;
        QAction *closeAction;
        QAction *saveAction;

        QAction *compileAction;
        QAction *runAction;
        QAction *comprunAction;

        QAction *copyAction;
        QAction *cutAction;
        QAction *pasteAction;
        QAction *selectallAction;
        QAction *findAction;

        QAction *helpAction;

        QLabel *msgLabel;

        QMenu *file1;
        QMenu *file2;
        QMenu *file3;
        QMenu *file4;
        QToolBar *toolBar;
        QTextEdit *textLeft;
        QTextEdit *textBottom;
        QListWidget *FileManager;
        LineNumberArea *LineNumber;
        QVector<CodeEditor*> Texts;
        CodeEditor *qpt;
        QListWidgetItem *qwi;
        Highlighter *highlighter;
        TextFinder *textfinder;

        QAbstractItemModel *modelFromFile(const QString& fileName);
        QCompleter *completer;

        QTreeView *tree;
        MyFileSytemModel *model;

        void filemenu();
        void editmenu();
        void runmenu();
        void helpmenu();
        void tool();
        void status();
        void splitter();
        void treeset();
private slots:
    void on_open();
    void on_new();
    void on_close();
    void on_save();

    void on_copy();
    void on_cut();
    void on_paste();
    void on_selectall();
    void on_find();//点击查找的槽

    void on_compile();
    void on_run();
    void on_comprun();

    void on_help();

    void on_changed();

    void ChangeMainText(QListWidgetItem* item);
    void SaveMainText();
    void doubleclickedtree(const QModelIndex &idx);

    void receiveData(QString);//接收textfinder传过来数据的槽
    void receiveData2(QString,QString);//接收textfinder传过来数据的槽
};

#endif // luckycat_H


#ifndef luckycat_H
#define luckycat_H

#include <QMainWindow>
#include<QTextEdit>
#include<QSplitter>
#include<QListWidget>
#include<QTextBrowser>
#include<QVector>
#include<QPlainTextEdit>
#include<codeeditor.h>

class QAction;
class QLabel;
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

        QLabel *msgLabel;

        QMenu *file1;
        QMenu *file2;
        QMenu *file3;
        QToolBar *toolBar;
        QTextEdit *textLeft;
        QTextEdit *textBottom;
        QListWidget *FileManager;
        LineNumberArea *LineNumber;
        QVector<CodeEditor*> Texts;

        void filemenu();
        void editmenu();
        void runmenu();
        //void helpmenu();
        void tool();
        void status();
        void splitter();
private slots:
    void on_open();
    void on_new();
    void on_close();
    void on_save();

    void on_copy();
    void on_cut();
    void on_paste();
    void on_selectall();

    void on_compile();
    void on_run();
    void on_comprun();

    void on_changed();

    void ChangeMainText(QListWidgetItem* item);
    void SaveMainText();

};

#endif // luckycat_H


#ifndef MYDICT_H
#define MYDICT_H

#include <QWidget>
#include <QTabBar>
#include <QTabWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QKeyEvent>
#include <QComboBox>
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QLabel>
#include <QDialog>


class span_engl : public QWidget {
    Q_OBJECT
public:
    span_engl(QString which="From english to spanish", QWidget *parent=0);

    QDir myDir;
    QString line;
    QTextStream in;
    QFile file;
    QStringList span_to_engl_list;

    QComboBox *win_box;

    QTextEdit *screen;

protected:
    void keyPressEvent (QKeyEvent *e);

};

class aboutWord : public QDialog {
    Q_OBJECT
public:
    aboutWord(QWidget *parent=0);

    QString surprizYumurta;
    QLabel *ab;};


class MyDict : public QMainWindow {//public class for window
    Q_OBJECT
public:
    MyDict( QWidget *parent=0);//no parent

    QMenuBar *menubar;

    QMenu *InfoMenu;
    QAction *DictInfo;
    QAction *QTInfo;
    QAction *exitMenu;

    QTabWidget *tabs;

    span_engl *engl_to_span;
    span_engl *span_to_engl;

    aboutWord *sh;
public slots:
    void slotQtInfo();
    void slotDict();
    void slotExit();

};

#endif

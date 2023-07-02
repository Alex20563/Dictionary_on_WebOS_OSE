#include <QApplication>

#include "MyDict.h"

MyDict::MyDict(QWidget *parent)
        : QMainWindow(parent)
{
    //create menu
    menubar = new QMenuBar(this);
    InfoMenu = new QMenu(trUtf8("Information"));
    DictInfo = new QAction(trUtf8("About dictionary"), menubar);
    QTInfo = new QAction(trUtf8("About QT"), menubar);
    exitMenu = new QAction(trUtf8("Exit"), menubar);

    menubar->addMenu(InfoMenu);
    InfoMenu->addAction(DictInfo);
    InfoMenu->addAction(QTInfo);
    menubar->addAction(exitMenu);

    //tabs
    tabs = new QTabWidget(this);
    tabs->setGeometry(0,50,400,300);

    engl_to_span = new span_engl("From english to spanish");
    span_to_engl = new span_engl("From spanish to english");
    tabs->addTab(engl_to_span, trUtf8("English->Spanish"));
    tabs->addTab(span_to_engl, trUtf8("Spanish->English"));

    //menubar ve sekmeleri ana pencereye ata
    setCentralWidget(tabs);
    setMenuBar(menubar);
    setWindowTitle(tr(".: sozluQ :."));

    // connect with buttons
    QObject::connect(QTInfo, SIGNAL(triggered()), this, SLOT(slotQtInfo()));

    QObject::connect(exitMenu, SIGNAL(triggered()), this, SLOT(slotExit()));

    QObject::connect(DictInfo, SIGNAL(triggered()), this, SLOT(slotDict()));
}

void MyDict::slotQtInfo(){
    qApp->aboutQt();
}

void MyDict::slotDict(){
    sh = new aboutWord(this);
    sh->show();
}

void MyDict::slotExit(){
    qApp->quit();
}

 //tab for translate
span_engl::span_engl(QString which, QWidget *parent) : QWidget(parent) {

    //window for search
    win_box = new QComboBox(this);
    win_box->setGeometry(50,20,200,25);
    win_box->setEditable(true);
    win_box->setAutoCompletion(false);
    win_box->setFocus();

    //place results screen
    screen = new QTextEdit(this);
    screen->setGeometry(10,50,275,400);
    screen->setReadOnly(true);

    //arama kutusunun icini doldur
    myDir.setPath(qApp->applicationDirPath());
    myDir.cd("word");

    span_to_engl_list.append("");
    file.setFileName(myDir.absoluteFilePath(which + "_liste"));
    if (file.open(QIODevice::ReadOnly)) {
        in.setDevice(&file);
    }
    while (!in.atEnd()) {
        line = in.readLine();
        span_to_engl_list.append(line.toLower());
    }
    file.close();
    span_to_engl_list.sort();
    win_box->addItems(span_to_engl_list);

    myDir.cd(which);
}

void span_engl::keyPressEvent(QKeyEvent *e){

    if(e->key()==Qt::Key_Return) {
//go to screen if ENTER, open file with first letter
//output if match or error

        if(win_box->currentText().length()>0){

            screen->clear();

            //file's name with first letter
            QString curr = win_box->currentText().at(0);
            file.setFileName(myDir.absoluteFilePath(curr));

            QString find;
            find = win_box->currentText();
            find.append(":|:");
            int count=0;

            //open file
             if (!file.open(QIODevice::ReadOnly)) {
                screen->insertHtml(trUtf8("There's the result :: There's no result"));
            }
            else {
                in.setDevice(&file);

                //is there a word
                while (!in.atEnd()) {
                    line = in.readLine().toLower();

                    if (line.startsWith(find.toLower())) {
                        count++;
                        line.replace(find,"");
                        line.toUtf8();
                        screen->insertHtml(line+"<hr/> <br />");
                    }
                }
                //if no result
                if(count<1)
                    screen->insertPlainText(trUtf8("No result"));
                file.close();
            }
        }
    }
}

aboutWord::aboutWord(QWidget *parent) : QDialog(parent) {

    ab = new QLabel(this);
    ab->setText(trUtf8("<h3 align=\"center\"> Dictionary</h3> <center>English Spanish Dictionary <br />Qt version is 5.12.2.<br /></center> "));
    ab->setGeometry(0,0,400,250);
    ab->setAlignment(Qt::AlignTop);
    resize(400,250);

    setWindowTitle(trUtf8(".: About Dictionary :."));
    ab->show();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QScrollBar>
#include <QFileDialog>
#include "remoteselector.h"
#include "chatclient.h"
#include <qbluetoothuuid.h>
#include <qbluetoothserver.h>
#include <qbluetoothservicediscoveryagent.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <y.tab.c>

//eliminar prueba
#include "QJsonObject"
#include "QJsonDocument"
//

static const QLatin1String serviceUuid("00001101-0000-1000-8000-00805F9B34FB");//este es el uuid definitivo para c++ del hc-06

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),currentAdapterIndex(0),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    ui->textEdit->installEventFilter(this);

    this->setFixedSize(size());

    ui->textEdit_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar* scrollBar = ui->textEdit->verticalScrollBar();
    QScrollBar* scrollBar2 = ui->textEdit_2->verticalScrollBar();
    QObject::connect(scrollBar, SIGNAL(valueChanged(int)),
                     scrollBar2, SLOT(setValue(int)));

    ui->textEdit_3->setPlainText("Tablet LED Console");
    ui->textEdit_2->setReadOnly(true);
    ui->textEdit_3->setReadOnly(true);
    }


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBright_triggered()
{
    mode = "light";
    int i = 0;
    QTextCursor tmpCursor = ui->textEdit->textCursor();
    tmpCursor.setPosition(0);
    this->setStyleSheet("");
    ui->textEdit->setStyleSheet("");
    ui->textEdit_2->setStyleSheet("");
    ui->textEdit_3->setStyleSheet("");
    ui->mainToolBar->setStyleSheet("");
    ui->menuBar->setStyleSheet("");
    while(i!=5000){
        tmpCursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);
        ui->textEdit->setTextCursor(tmpCursor);
        dinamically_bg();
        i++;

    }



}



void MainWindow::dinamically_bg(){


    QTextCursor cursor = ui->textEdit->textCursor(); // editor is QTextEdit
    cursor.select(QTextCursor::WordUnderCursor);
    QString c = cursor.selectedText();

    if (c == ELSE1){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Purple\">" + ELSE1 + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Green\">" + ELSE1 + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }

        }
    else if (c == IF){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Purple\">" + IF + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Green\">" + IF + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }
    }
    else if (c == ELSEIF){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Purple\">" + ELSEIF + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Green\">" + ELSEIF + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }

    }
    else if (c == DOW){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Purple\">" + DOW + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Green\">" + DOW + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }

    }
    else if (c == ENDDO){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Purple\">" + ENDDO + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Green\">" + ENDDO + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }

    }
    else if (c == FEND){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Purple\">" + FEND + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Green\">" + FEND + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }

    }
    else if (c == ENDIF){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Purple\">" + ENDIF + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Green\">" + ENDIF + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }
    }
    else if (c == FOR){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Purple\">" + FOR + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Green\">" + FOR + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }

    }
    else if (c == EXIT1){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Red\">" + EXIT1 + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"magenta\">" + EXIT1 + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }
    }
    else if (c == D){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Orange\">" + D + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"cyan\">" + D + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }



    }
    else if (c == INZ1){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"Green\">" + INZ1 + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"Yellow\">" + INZ1 + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }
    }
        else if (c == P1){
            cursor.removeSelectedText();
            if(mode == "light"){
                cursor.insertHtml("<font color=\"Blue\">" + P1 + "</font>");
                ui->textEdit->setTextColor("#000000");
            }
            else if(mode == "dark"){
                cursor.insertHtml("<font color=\"magenta\">" + P1 + "</font>");
                ui->textEdit->setTextColor("#FEFEFE");

            }
        }
            else if (c == TEMPO){
                cursor.removeSelectedText();
                if(mode == "light"){
                    cursor.insertHtml("<font color=\"darkRed\">" + TEMPO + "</font>");
                    ui->textEdit->setTextColor("#000000");
                }
                else if(mode == "dark"){
                    cursor.insertHtml("<font color=\"Orange\">" + TEMPO + "</font>");
                    ui->textEdit->setTextColor("#FEFEFE");

                }



            }
    else if (c == S_ON){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"RED\">" + S_ON + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"cyan\">" + S_ON + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }



    }
    else if (c == S_On){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"RED\">" + S_On + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"cyan\">" + S_On + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }



    }
    else if (c == T_ON){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"RED\">" + T_ON + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"cyan\">" + T_ON + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }



    }
    else if (c == T_On){
        cursor.removeSelectedText();
        if(mode == "light"){
            cursor.insertHtml("<font color=\"RED\">" + T_On + "</font>");
            ui->textEdit->setTextColor("#000000");
        }
        else if(mode == "dark"){
            cursor.insertHtml("<font color=\"cyan\">" + T_On + "</font>");
            ui->textEdit->setTextColor("#FEFEFE");

        }



    }





        }






void MainWindow::on_actionDark_triggered()
{
    mode = "dark";
    int i = 0;
    QTextCursor tmpCursor = ui->textEdit->textCursor();
    tmpCursor.setPosition(0);
    this->setStyleSheet("color: black;"
                        "background-color: gray;"
                        "selection-color: gray;"
                        "selection-background-color: gray;");
    ui->textEdit->setStyleSheet("color: white;"
                                "background-color: black;"
                                "selection-color: white;"
                                "selection-background-color: white;");
    ui->textEdit_2->setStyleSheet("color: orange;"
                                "background-color: gray;"
                                "selection-color: white;"
                                "selection-background-color: black;");
    ui->textEdit_3->setStyleSheet("color: purple;"
                                "background-color: gray;"
                                "selection-color: white;"
                                "selection-background-color: gray;");
    ui->mainToolBar->setStyleSheet("background-color: darkGray;");
    ui->menuBar->setStyleSheet("color: white;"
                               "background-color: darkGray;"
                               "selection-color: darkGray;"
                               "selection-background-color: gray;");
    while(i!=5000){
        tmpCursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);
        ui->textEdit->setTextCursor(tmpCursor);
        dinamically_bg();
        i++;

    }

}

void MainWindow::on_actionRun_triggered()
{
    ui->textEdit_3->clear();
    ui->textEdit_3->setPlainText("Tablet LED Console");
//    interprete(this);

//    QJsonObject object;
//    object.insert("Juego",3);
//    object.insert("Text","hala madrid! :)");
//    object.insert("R",7);
//    object.insert("G",245);
//    object.insert("B",7);
//    QJsonDocument doc(object);
//    qDebug(doc.toJson());
//    sendMessage(doc.toJson());



    QJsonObject object2;
    object2.insert("Juego",1);
    object2.insert("Type","SoundOn");
    object2.insert("Boton",3);
    QJsonDocument doc2(object2);
    qDebug(doc2.toJson());
    sendMessage(doc2.toJson());

    QJsonObject object3;
    object3.insert("Juego",1);
    object3.insert("Type","SoundOn");
    object3.insert("Boton",2);
    QJsonDocument doc3(object3);
    qDebug(doc3.toJson());
    sendMessage(doc3.toJson());

    QJsonObject object4;
    object4.insert("Juego",1);
    object4.insert("Type","SoundOn");
    object4.insert("Boton",4);
    QJsonDocument doc4(object4);
    qDebug(doc4.toJson());
    sendMessage(doc4.toJson());



//    QJsonObject object4;
//    object4.insert("Juego",1);
//    object4.insert("Type","TurnOn");
//    object4.insert("Boton",18);
//    object4.insert("Fil",3);
//    object4.insert("Col",1);
//    object4.insert("R",7);lpl
//    object4.insert("G",224);
//    object4.insert("B",245);
//    QJsonDocument doc4(object4);
//    qDebug(doc4.toJson());
//    sendMessage(doc4.toJson());


//    QJsonObject object5;
//    object5.insert("Juego",1);
//    object5.insert("Type","TurnOn");
//    object5.insert("Boton",24);
//    object5.insert("Fil",4);
//    object5.insert("Col",1);
//    object5.insert("R",242);
//    object5.insert("G",245);
//    object5.insert("B",7);
//    QJsonDocument doc5(object5);
//    qDebug(doc5.toJson());
//    sendMessage(doc5.toJson());

//    QJsonObject object6;
//    object6.insert("Juego",1);
//    object6.insert("Type","TurnOn");
//    object6.insert("Boton",30);
//    object6.insert("Fil",5);
//    object6.insert("Col",5);
//    object6.insert("R",7);
//    object6.insert("G",224);
//    object6.insert("B",245);
//    QJsonDocument doc6(object6);
//    qDebug(doc6.toJson());
//    sendMessage(doc6.toJson());

//    QJsonObject object7;
//    object6.insert("Juego",1);
//    object6.insert("Type","TurnOn");
//    object6.insert("Boton",36);
//    object6.insert("Fil",3);
//    object6.insert("Col",4);
//    object6.insert("R",7);
//    object6.insert("G",124);
//    object6.insert("B",100);
//    QJsonDocument doc7(object6);
//    qDebug(doc7.toJson());
//    sendMessage(doc7.toJson());


//    QJsonObject object7;
//    object7.insert("Juego",1);
//    object7.insert("Type","TurnON");
//    object7.insert("Boton",36);
//    object7.insert("Fil",3);
//    object7.insert("Col",2);
//    QJsonDocument doc7(object7);
//    qDebug(doc7.toJson());
//    sendMessage(doc7.toJson());

//    QJsonObject object8;
//    object8.insert("Juego",1);
//    object8.insert("Type","TurnON");
//    object8.insert("Boton",13);
//    object8.insert("Fil",5);
//    object8.insert("Col",5);
//    QJsonDocument doc8(object8);
//    qDebug(doc8.toJson());
//    sendMessage(doc8.toJson());


//    QJsonObject object56;
//    object56.insert("Juego",1);
//    object56.insert("Type","TurnOFF");
//    object56.insert("Boton",25);
//    object56.insert("Fil",5);
//    object56.insert("Col",5);
//    QJsonDocument doc56(object56);
//    qDebug(doc56.toJson());
//    sendMessage(doc56.toJson());
//    QJsonObject object8;
//    object8.insert("Juego",1);
//    object8.insert("Type","TurnOFF");
//    object8.insert("Boton",7);
//    object8.insert("Fil",3);
//    object8.insert("Col",2);
//    QJsonDocument doc8(object8);
//    qDebug(doc8.toJson());
//    sendMessage(doc8.toJson());




//    QJsonObject object11;
//    object11.insert("Juego",1);
//    object11.insert("Type","TurnON");
//    object11.insert("Boton",8);
//    object11.insert("Fil",0);
//    object11.insert("Col",0);
//    QJsonDocument doc11(object11);
//    qDebug(doc11.toJson());
//    sendMessage(doc11.toJson());

//    QJsonObject object12;
//    object12.insert("Juego",1);
//    object12.insert("Type","TurnOn");
//    object12.insert("Boton",14);
//    object12.insert("Fil",5);
//    object12.insert("Col",0);
//    QJsonDocument doc12(object12);
//    qDebug(doc12.toJson());
//    sendMessage(doc12.toJson());

//    QJsonObject object13;
//    object13.insert("Juego",1);
//    object13.insert("Type","TurnOn");
//    object13.insert("Boton",20);
//    object13.insert("Fil",3);
//    object13.insert("Col",5);
//    QJsonDocument doc13(object13);
//    qDebug(doc13.toJson());
//    sendMessage(doc13.toJson());

//    QJsonObject object14;
//    object14.insert("Juego",1);
//    object14.insert("Type","TurnOn");
//    object14.insert("Boton",26);
//    object14.insert("Fil",2);
//    object14.insert("Col",2);
//    QJsonDocument doc14(object14);
//    qDebug(doc14.toJson());
//    sendMessage(doc14.toJson());

//    QJsonObject object15;
//    object15.insert("Juego",1);
//    object15.insert("Type","TurnOn");
//    object15.insert("Boton",32);
//    object15.insert("Fil",4);
//    object15.insert("Col",2);
//    QJsonDocument doc15(object15);
//    qDebug(doc15.toJson());
//    sendMessage(doc15.toJson());

//    QJsonObject object16;
//    object16.insert("Juego",1);
//    object16.insert("Type","TurnOn");
//    object16.insert("Boton",7);
//    object16.insert("Fil",4);
//    object16.insert("Col",4);
//    QJsonDocument doc16(object16);
//    qDebug(doc16.toJson());
//    sendMessage(doc16.toJson());

//    QJsonObject object17;
//    object17.insert("Juego",1);
//    object17.insert("Type","TurnOn");
//    object17.insert("Boton",7);
//    object17.insert("Fil",5);
//    object17.insert("Col",5);
//    QJsonDocument doc17(object17);
//    qDebug(doc17.toJson());
//    sendMessage(doc17.toJson());

//    //---------------------------------------------------------PRUEBA 1-----------------------------------------------------------
//        QJsonObject object1;
//        object1.insert("Juego",2);
//        object1.insert("Type","Maze");
//        object1.insert("Fil",0);
//        object1.insert("Col",0);
//        QJsonDocument doc1(object1);
//        qDebug(doc1.toJson());
//        sendMessage(doc1.toJson());

//        QJsonObject object2;
//        object2.insert("Juego",2);
//        object2.insert("Type","Maze");
//        object2.insert("Fil",1);
//        object2.insert("Col",1);
//        QJsonDocument doc2(object2);
//        qDebug(doc2.toJson());
//        sendMessage(doc2.toJson());


//        QJsonObject object11;
//        object11.insert("Juego",2);
//        object11.insert("Type","Maze");
//        object11.insert("Fil",2);
//        object11.insert("Col",2);
//        QJsonDocument doc11(object11);
//        qDebug(doc11.toJson());
//        sendMessage(doc11.toJson());


//        QJsonObject object3;
//        object3.insert("Juego",2);
//        object3.insert("Type","Maze");
//        object3.insert("Fil",3);
//        object3.insert("Col",3);
//        QJsonDocument doc3(object3);
//        qDebug(doc3.toJson());
//        sendMessage(doc3.toJson());

//        QJsonObject object4;
//        object4.insert("Juego",2);
//        object4.insert("Type","Maze");
//        object4.insert("Fil",4);
//        object4.insert("Col",4);
//        QJsonDocument doc4(object4);
//        qDebug(doc4.toJson());
//        sendMessage(doc4.toJson());

//        QJsonObject object5;
//        object5.insert("Juego",2);
//        object5.insert("Type","Maze");
//        object5.insert("Fil",5);
//        object5.insert("Col",5);
//        QJsonDocument doc5(object5);
//        qDebug(doc5.toJson());
//        sendMessage(doc5.toJson());

//        QJsonObject object12;
//        object12.insert("Juego",2);
//        object12.insert("Type","Maze");
//        object12.insert("Fil",5);
//        object12.insert("Col",1);
//        QJsonDocument doc12(object12);
//        qDebug(doc12.toJson());
//        sendMessage(doc12.toJson());

//        QJsonObject object6;
//        object6.insert("Juego",2);
//        object6.insert("Type","Maze");
//        object6.insert("Fil",5);
//        object6.insert("Col",2);
//        QJsonDocument doc6(object6);
//        qDebug(doc6.toJson());
//        sendMessage(doc6.toJson());

//        QJsonObject object8;
//        object8.insert("Juego",2);
//        object8.insert("Type","Maze");
//        object8.insert("Fil",5);
//        object8.insert("Col",3);
//        QJsonDocument doc8(object8);
//        qDebug(doc8.toJson());
//        sendMessage(doc8.toJson());

//        QJsonObject object9;
//        object9.insert("Juego",2);
//        object9.insert("Type","Maze");
//        object9.insert("Fil",5);
//        object9.insert("Col",4);
//        QJsonDocument doc9(object9);
//        qDebug(doc9.toJson());
//        sendMessage(doc9.toJson());

//        QJsonObject object10;
//        object10.insert("Juego",2);
//        object10.insert("Type","Maze");
//        object10.insert("Fil",5);
//        object10.insert("Col",5);
//        QJsonDocument doc10(object10);
//        qDebug(doc10.toJson());
//        sendMessage(doc10.toJson());



            //asdasdmmaslkdnaskldnaskldn


//            QJsonObject object1;
//            object1.insert("Juego",2);
//            object1.insert("Type","Maze");
//            object1.insert("Fil",0);
//            object1.insert("Col",0);
//            QJsonDocument doc1(object1);
//            qDebug(doc1.toJson());
//            sendMessage(doc1.toJson());

//            QJsonObject object2;
//            object2.insert("Juego",2);
//            object2.insert("Type","Maze");
//            object2.insert("Fil",1);
//            object2.insert("Col",0);
//            QJsonDocument doc2(object2);
//            qDebug(doc2.toJson());
//            sendMessage(doc2.toJson());


//            QJsonObject object3;
//            object3.insert("Juego",2);
//            object3.insert("Type","Maze");
//            object3.insert("Fil",2);
//            object3.insert("Col",0);
//            QJsonDocument doc3(object3);
//            qDebug(doc3.toJson());
//            sendMessage(doc3.toJson());


//            QJsonObject object4;
//            object4.insert("Juego",2);
//            object4.insert("Type","Maze");
//            object4.insert("Fil",3);
//            object4.insert("Col",0);
//            QJsonDocument doc4(object4);
//            qDebug(doc4.toJson());
//            sendMessage(doc4.toJson());

//            QJsonObject object5;
//            object5.insert("Juego",2);
//            object5.insert("Type","Maze");
//            object5.insert("Fil",4);
//            object5.insert("Col",0);
//            QJsonDocument doc5(object5);
//            qDebug(doc5.toJson());
//            sendMessage(doc5.toJson());

//            QJsonObject object6;
//            object6.insert("Juego",2);
//            object6.insert("Type","Maze");
//            object6.insert("Fil",5);
//            object6.insert("Col",0);
//            QJsonDocument doc6(object6);
//            qDebug(doc6.toJson());
//            sendMessage(doc6.toJson());



//                QJsonObject object1;
//                object1.insert("Juego",2);
//                object1.insert("Type","Maze");
//                object1.insert("Fil",0);
//                object1.insert("Col",0);
//                QJsonDocument doc1(object1);
//                qDebug(doc1.toJson());
//                sendMessage(doc1.toJson());

//                QJsonObject object2;
//                object2.insert("Juego",2);
//                object2.insert("Type","Maze");
//                object2.insert("Fil",0);
//                object2.insert("Col",1);
//                QJsonDocument doc2(object2);
//                qDebug(doc2.toJson());
//                sendMessage(doc2.toJson());


//                QJsonObject object3;
//                object3.insert("Juego",2);
//                object3.insert("Type","Maze");
//                object3.insert("Fil",1);
//                object3.insert("Col",1);
//                QJsonDocument doc3(object3);
//                qDebug(doc3.toJson());
//                sendMessage(doc3.toJson());


//                QJsonObject object4;
//                object4.insert("Juego",2);
//                object4.insert("Type","Maze");
//                object4.insert("Fil",2);
//                object4.insert("Col",1);
//                QJsonDocument doc4(object4);
//                qDebug(doc4.toJson());
//                sendMessage(doc4.toJson());

//                QJsonObject object5;
//                object5.insert("Juego",2);
//                object5.insert("Type","Maze");
//                object5.insert("Fil",2);
//                object5.insert("Col",2);
//                QJsonDocument doc5(object5);
//                qDebug(doc5.toJson());
//                sendMessage(doc5.toJson());

//                QJsonObject object6;
//                object6.insert("Juego",2);
//                object6.insert("Type","Maze");
//                object6.insert("Fil",2);
//                object6.insert("Col",3);
//                QJsonDocument doc6(object6);
//                qDebug(doc6.toJson());
//                sendMessage(doc6.toJson());

//                QJsonObject object7;
//                object7.insert("Juego",2);
//                object7.insert("Type","Maze");
//                object7.insert("Fil",3);
//                object7.insert("Col",3);
//                QJsonDocument doc7(object7);
//                qDebug(doc7.toJson());
//                sendMessage(doc7.toJson());

//                QJsonObject object8;
//                object8.insert("Juego",2);
//                object8.insert("Type","Maze");
//                object8.insert("Fil",3);
//                object8.insert("Col",4);
//                QJsonDocument doc8(object8);
//                qDebug(doc8.toJson());
//                sendMessage(doc8.toJson());

//                QJsonObject object9;
//                object9.insert("Juego",2);
//                object9.insert("Type","Maze");
//                object9.insert("Fil",4);
//                object9.insert("Col",4);
//                QJsonDocument doc9(object9);
//                qDebug(doc9.toJson());
//                sendMessage(doc9.toJson());


//                QJsonObject object10;
//                object10.insert("Juego",2);
//                object10.insert("Type","Maze");
//                object10.insert("Fil",5);
//                object10.insert("Col",5);
//                QJsonDocument doc10(object10);
//                qDebug(doc10.toJson());
//                sendMessage(doc10.toJson());



}

void MainWindow::on_actionNew_triggered()
{

    bn = "";
    indice = 1;
    ui->textEdit->setPlainText("");
    ui->textEdit_2->setPlainText(QString::number(indice));



}

void MainWindow::on_actionOpen_triggered()
{
    QString pbloc = QFileDialog::getOpenFileName(this,"Open New Archive");

    if(!pbloc.isEmpty()){
        QFile archT(pbloc);
        if (archT.open(QFile::ReadOnly | QFile::Text)){
            bn = pbloc;
            QTextStream n(&archT);
            QString tex= n.readAll();
            archT.close();
            ui->textEdit->setPlainText(tex);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFile archJ(bn);
    if(archJ.open(QFile::WriteOnly | QFile::Text)){
        QTextStream stream(&archJ);

        stream << ui->textEdit->toPlainText();

        archJ.flush();
        archJ.close();

    }
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString pbloc = QFileDialog::getSaveFileName(this, "Save As");

    if(!pbloc.isEmpty()){
        bn = pbloc;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"Ayuda","<hl> Para dudas y sugerencias favor contactar con el provedor al correo: ce.jose7rivera@gmail.com</hl");




}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->textEdit) {
        if (event->type()==QEvent::KeyPress) {
            QKeyEvent *keyE = static_cast<QKeyEvent *>(event);
            if ( keyE->key() == Qt::Key_Enter || keyE->key() == Qt::Key_Return ) {
                //Enter or return was pressed
                //qDebug("Nigga pls");
                indice = indice + 1;
                QString txt = ui->textEdit_2->toPlainText() + "\n" + QString::number(indice);
                ui->textEdit_2->setPlainText(txt);
                dinamically_bg();
                return QObject::eventFilter(obj, event);
            }
            else if( keyE->key() == Qt::Key_Space || keyE->key() == Qt::Key_Return ) {
                dinamically_bg();
                return QObject::eventFilter(obj, event);
            }

        }
        else {
            return false;
        }
    }
    else {
        return QObject::eventFilter(obj, event);
    }
}

//    this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
//    this->socket->connectToService(QBluetoothAddress("98:D3:31:FD:6A:49"), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
    //    // scan for services


void MainWindow::on_actionBluetooth_triggered()
{
    // scan for services
    const QBluetoothAddress adapter = localAdapters.isEmpty() ?
                                           QBluetoothAddress() :
                                           localAdapters.at(currentAdapterIndex).address();

    RemoteSelector remoteSelector(adapter);
    remoteSelector.startDiscovery(QBluetoothUuid(serviceUuid));
    if (remoteSelector.exec() == QDialog::Accepted) {
        QBluetoothServiceInfo service = remoteSelector.service();

        qDebug() << "Connecting to service 2" << service.serviceName()
                 << "on" << service.device().name();

        // Create client
        qDebug() << "Going to create client";
        ChatClient *client = new ChatClient(this);
qDebug() << "Connecting...";

        connect(client, SIGNAL(messageReceived(QString,QString)),this, SLOT(showMessage(QString,QString)));
        connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        connect(client, SIGNAL(connected(QString)), this, SLOT(connected(QString)));
        connect(this, SIGNAL(sendMessage(QString)), client, SLOT(sendMessage(QString)));
qDebug() << "Start client";
        client->startClient(service);

        clients.append(client);
    }
}




    void MainWindow::on_actionBuild_triggered()
    {
        int i = 0;
        QTextCursor tmpCursor = ui->textEdit->textCursor();
        tmpCursor.setPosition(0);

        while(i!=5000){

            tmpCursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);
            ui->textEdit->setTextCursor(tmpCursor);
            dinamically_bg();
            i++;

        }

        int lines = ui->textEdit->document()->documentLayout()->documentSize().height();
        indice = 1;
        ui->textEdit_2->setPlainText(QString::number(indice));

        for(int i=0; i<lines; i++)
        {
            indice = indice + 1;
            QString txt = ui->textEdit_2->toPlainText() + "\n" + QString::number(indice);
            ui->textEdit_2->setPlainText(txt);

        }
}

    void MainWindow::sendJson(const QString &json){
    emit sendMessage(json);
    //qDebug("si entra aqui");

 }
    void MainWindow::console(QString error){
        ui->textEdit_3->append(error);
        QTextCursor cursor = ui->textEdit_3->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignLeft);
        cursor.mergeBlockFormat(textBlockFormat);
        ui->textEdit_3->setTextCursor(cursor);



    }

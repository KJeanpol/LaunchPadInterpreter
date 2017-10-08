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
    interprete(this);






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

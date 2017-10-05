#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <iostream>
#include <QKeyEvent>
#include <QDebug>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothsocket.h>
#include <qbluetoothhostinfo.h>





QT_USE_NAMESPACE

class ChatServer;
class ChatClient;

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject* obj, QEvent* event);

signals:
    void sendMessage(const QString &message);

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionAbout_triggered();

    void on_actionBright_triggered();

    void on_actionDark_triggered();

    void on_actionRun_triggered();

    void on_actionBluetooth_triggered();

    void dinamically_bg();

    void on_actionBuild_triggered();

private:
    Ui::MainWindow *ui;
    QString bn;
    QString bn2;
    int indice;
    int adapterFromUserSelection() const;
    int currentAdapterIndex;

    ChatServer *server;
    QList<ChatClient *> clients;
    QList<QBluetoothHostInfo> localAdapters;

    QString localName;
    ChatClient *send;

    QString mode = "light";

    QString IF = "If";
    QString ELSE1 = "else";
    QString ELSEIF = "elseIf";
    QString  DOW = "Dow";
    QString ENDDO = "Enddo";
    QString FEND = "FEnd";
    QString ENDIF = "Endif";
    QString FOR = "For";

    QString EXIT1 = "Exit";

    QString D = "D";

public:
    bool flag = true;


};

#endif // MAINWINDOW_H

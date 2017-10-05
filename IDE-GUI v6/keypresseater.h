#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H
#include <QObject>
#include <QKeyEvent>


class KeyPressEater : public QObject
{
    Q_OBJECT
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};
bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("key pressed", keyEvent->key());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
//KeyPressEater *keyPressEater = new KeyPressEater(this);


#endif // KEYPRESSEATER_H

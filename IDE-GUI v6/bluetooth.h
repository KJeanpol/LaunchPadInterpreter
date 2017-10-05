#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QWidget>

namespace Ui {
class bluetooth;
}

class bluetooth : public QWidget
{
    Q_OBJECT

public:
    explicit bluetooth(QWidget *parent = 0);
    ~bluetooth();

private:
    Ui::bluetooth *ui;
};

#endif // BLUETOOTH_H

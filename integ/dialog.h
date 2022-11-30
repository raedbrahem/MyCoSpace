#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"
#include <QDialog>
class MainWindow;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pb_connect_clicked();

private:
    Ui::Dialog *ui;
    MainWindow* mainwindow;
};

#endif // DIALOG_H

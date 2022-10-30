#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <employe.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();

    void on_pb_delete_clicked();

    void on_list_employes_currentRowChanged(int currentRow);

    void on_pb_update_clicked();

private:
    Ui::MainWindow *ui;
    Employe E;
    int mnSelected=-1;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialog.h"
#include <QMainWindow>
#include <employe.h>
#include <QFileDialog>
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
    void on_pb_chercher_clicked();
    void on_pb_trier_clicked();

    void on_pb_pdf_clicked();

    void on_tabWidget_2_tabBarClicked(int index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pb_trier_nom_clicked();

    void on_pb_trier_cin_clicked();

    void on_tab_etudiants_activated(const QModelIndex &index);

    void clearLayout(QLayout *layout);


    void on_pb_image_clicked();

    void on_pb_imagemaj_clicked();

private:
    Ui::MainWindow *ui;
    Employe E;
};


#endif // MAINWINDOW_H

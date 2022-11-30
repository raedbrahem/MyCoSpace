#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialog.h"
#include <QMainWindow>
#include <employe.h>
#include <QFileDialog>

#include "login.h"
#include "arduino.h"


#include"reservation.h"
#include"smtp.h"
#include <QMainWindow>
//#include "reservation.h"
#include"QSqlQuery"
#include"QtDebug"
#include"qmessagebox.h"
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QDataStream>
#include "secformdialog.h"
#include <QUrl>

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

    void on_comboBox_currentTextChanged(const QString );

    void on_pb_trier_nom_clicked();

    void on_pb_trier_cin_clicked();

    void on_tab_etudiants_activated(const QModelIndex &index);

    void clearLayout(QLayout *layout);


    void on_pb_image_clicked();

    void on_pb_imagemaj_clicked();

    void on_pb_ajouteruser_clicked();

    void on_pb_supprimeruser_clicked();

    void on_tab_etudiants2_activated(const QModelIndex &index);

    void on_pb_modifiereruser_clicked();

    void on_pb_cherchernom_clicked();

    void on_pbchercherprenom_clicked();

    void update_label();


    void on_pushButton_clicked();

    void on_effacer_clicked();


    //reservation
    void on_pb_ajouterres_clicked();

    void on_supprmierres_clicked();

    void on_pushButton_2_clicked();

    void on_trires_clicked();

    void on_pb_chercherres_clicked();

    void on_pushButton_4_clicked();

    void on_tab_res_activated(const QModelIndex &index);

    void on_triernum_clicked();

    void on_triertype_clicked();

    void on_recherche_textChanged(const QString &arg1);

    void  browse();

    void   mailSent(QString status);

    void  sendMail() ;


    void on_Calendrier_clicked();

    void on_pushButtonchercheridres_clicked();

    void on_pushButton_cherchertyperes_clicked();

    void on_pushButton_cherchernumres_clicked();






    void on_pushButton_gestion_remploye_badel_clicked();

    void on_pushButton_gestionres_badel_clicked();

private:
    Ui::MainWindow *ui;
    Employe E;
    login user;
     Arduino A;
     QByteArray data;
     QByteArray str;
     QString  DataAsString ="";
     QString s;
      reservation R ;
     QStringList files;
      QSortFilterProxyModel *proxy;

       SECFORMDialog *secDialog;
};


#endif // MAINWINDOW_H

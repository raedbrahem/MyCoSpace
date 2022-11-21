#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"reservation.h"
#include"smtp.h"
#include <QMainWindow>
#include "reservation.h"
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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void on_pushButton_ajouterres_clicked();

private slots:
    void on_pb_ajouterres_clicked();

    void on_supprmierres_clicked();

    void on_pushButton_2_clicked();

    void on_trires_clicked();


    void on_pushButton_4_clicked();

    void on_tab_res_activated(const QModelIndex &index);

    void on_triernum_clicked();

    void on_triertype_clicked();

    void on_recherche_textChanged(const QString &arg1);

    void  browse();

    void   mailSent(QString status);

    void  sendMail() ;


    void on_Calendrier_clicked();

    void on_chercherrestype_clicked();

    void on_chercherresnom_clicked();

    void on_chercherres_clicked();

    void on_sendBtn_clicked();

private:
    Ui::MainWindow *ui;
    reservation R ;
    QStringList files;
     QSortFilterProxyModel *proxy;
     SECFORMDialog *secDialog;
};


#endif // MAINWINDOW_H

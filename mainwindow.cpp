#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QObject>
#include <QIntValidator>
#include <QString>
#include "employe.h"
#include <QtDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(0,9999999,this));
    ui->le_numtel->setValidator(new QIntValidator(0,99999999,this));
    ui->le_salaire->setValidator(new QIntValidator(0,9999999,this));
    QRegExp rx("(|\"|/|\\.|[0-9]){30}");
    ui->le_date->setValidator(new QRegExpValidator(rx,this));
    ui->le_nom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z_]{0,255}"), this ));
    ui->le_prenom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z_]{0,255}"), this ));
    ui->le_etat->setValidator(new QRegExpValidator( QRegExp("[A-Za-z_]{0,255}"), this ));




    ui->le_nummaj->setValidator(new QIntValidator(0,99999999,this));
    ui->le_salairemaj->setValidator(new QIntValidator(0,9999999,this));
    ui->le_datemaj->setValidator(new QRegExpValidator(rx,this));
    ui->le_nommaj->setValidator(new QRegExpValidator( QRegExp("[A-Za-z_]{0,255}"), this ));
    ui->le_prenommaj->setValidator(new QRegExpValidator( QRegExp("[A-Za-z_]{0,255}"), this ));
    ui->le_etatmaj->setValidator(new QRegExpValidator( QRegExp("[A-Za-z_]{0,255}"), this ));

    ui->tab_etudiants->setModel(E.afficher());
    ui->comboBox->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
      int cin=ui->le_cin->text().toInt();
      QString nom=ui->le_nom->text();
      QString prenom=ui->le_prenom->text();
      QString date=ui->le_date->text();
      QString adresse=ui->le_adresse->text();
      float salaire=ui->le_salaire->text().toFloat();
      int numtel=ui->le_numtel->text().toInt();
      QString etat=ui->le_etat->text();
      QString email=ui->le_email->text();

      Employe E(cin,nom,prenom,email,date,salaire,numtel,etat,adresse);

      bool test=E.ajouter();

    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectué\nclick cancel to exit"),QMessageBox::Cancel);
        ui->tab_etudiants->setModel(E.afficher());
        ui->comboBox->addItem(QString::number(cin));
        ui->comboBox->setModel(E.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("ajout non effectué\nclick cancel to exit"),QMessageBox::Cancel);

}

void MainWindow::on_pb_supprimer_clicked()
{
Employe E1;
E1.setcin(ui->comboBox->currentText().toInt());
bool test=E1.supprimer(E1.getcin());
QMessageBox msgBox;
if(ui->comboBox->currentText().toInt()==NULL)
    test=0;
if(test)
{
     msgBox.setText("suppression avec succes");
     ui->tab_etudiants->setModel(E1.afficher());
     ui->comboBox->removeItem(ui->comboBox->currentText().toInt());
     ui->comboBox->setModel(E.afficher());
}

else
     msgBox.setText("echec");
msgBox.exec();
}

void MainWindow::on_pb_delete_clicked(){}
void MainWindow::on_list_employes_currentRowChanged(int currentRow){}

void MainWindow::on_pb_update_clicked()
{
    int cin=ui->comboBox->currentText().toInt();

    QString nom=ui->le_nommaj->text();
    QString prenom=ui->le_prenommaj->text();
    QString date=ui->le_datemaj->text();
    QString adresse=ui->le_adressemaj->text();
    float salaire=ui->le_salairemaj->text().toFloat();
    int numtel=ui->le_nummaj->text().toInt();
    QString etat=ui->le_etatmaj->text();
    QString email=ui->le_emailmaj->text();
    Employe E(cin,nom,prenom,email,date,salaire,numtel,etat,adresse);

    bool test=E.modifier(cin);
    if (cin==NULL)
        test=0;
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("modification effectué\nclick cancel to exit"),QMessageBox::Cancel);
        ui->tab_etudiants->setModel(E.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("modification non effectué\nclick cancel to exit"),QMessageBox::Cancel);

}

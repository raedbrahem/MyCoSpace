#ifndef ETUDIANT_H
#define ETUDIANT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QtDebug>
#include <QObject>

#include<istream>
#include<fstream>
#include<vector>
#include<QFileDialog>
#include<QPixmap>
#include<QPainter>
#include<QtSvg/QSvgRenderer>
#include<QMainWindow>
#include "qtablewidget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts/QChart>
QT_CHARTS_USE_NAMESPACE


class Employe
{
    QString nom,prenom,email,datedenaissance,adresse,etatcivil,imageurl;
    int cin,numtel;
    float salaire;
public:
    Employe(){};
    Employe(int,QString,QString,QString,QString,float,int,QString,QString,QString);
    QString getnom(){return  nom;}
    QString getprenom(){return  prenom;}
    QString getemail(){return  email;}
    QString getdate(){return  datedenaissance;}
    QString getadresse(){return  adresse;}
    QString getetat(){return  etatcivil;}
    int getnum(){return  numtel;}
    int getcin(){return  cin;}
    float getsalaire(){return  salaire;}

    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setcin(int cinn){this->cin=cinn;}

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher1();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trier();
    QSqlQueryModel * triercin();
    QSqlQueryModel * triernom();
    void CREATION_PDF();
    QChartView *stat();
};
#endif // ETUDIANT_H

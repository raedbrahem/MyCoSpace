#include "employe.h"
#include <QString>
#include <QtDebug>
#include <QMessageBox>

Employe::Employe(int cin,QString nom,QString prenom,QString email,QString date,float salaire,int numtel,QString etat,QString adresse)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->datedenaissance=date;
    this->salaire=salaire;
    this->numtel=numtel;
    this->etatcivil=etat;
    this->adresse=adresse;
}



bool Employe::ajouter()
{
QSqlQuery query;
QString cin_string = QString::number(cin);
//QString num_string = QString::number(numtel);
QString salary_string = QString::number(salaire);

query.prepare("insert into employe(cin, nom, prenom, email,datedenaissance,salaire,numtel,etatcivil,adresse)"
              "VALUES(:cin,:surname,:forename,:email,:datedenaissance,:salaire,:numtel,:etatcivil,:adresse)");
query.bindValue(":cin",cin_string);
query.bindValue(":surname",nom);
query.bindValue(":forename",prenom);
query.bindValue(":email",email);
query.bindValue(":datedenaissance",datedenaissance);
query.bindValue(":salaire",salary_string);
query.bindValue(":numtel",numtel);
query.bindValue(":etatcivil",etatcivil);
query.bindValue(":adresse",adresse);
return query.exec();
}



QSqlQueryModel * Employe::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT* from employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datedenaissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("numtel"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("etatcivil"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("adresse"));
return model;
}




bool Employe::modifier(int cin)
{
    QSqlQuery query;
    QString cin_string = QString::number(cin);
    QString num_string = QString::number(numtel);
    QString salary_string = QString::number(salaire);
    query.prepare("UPDATE EMPLOYE SET nom='"+nom+"' , prenom='"+prenom+"', email='"+email+"',datedenaissance='"+datedenaissance+"', salaire='"+salary_string+"', numtel='"+num_string+"', etatcivil='"+etatcivil+"', adresse='"+adresse+"'where cin='"+cin_string+"' ");
    query.bindValue(0,cin_string);
    query.bindValue(1,nom);
    query.bindValue(2,prenom);
    query.bindValue(3,email);
    query.bindValue(4,datedenaissance);
    query.bindValue(5,salary_string);
    query.bindValue(6,num_string);
    query.bindValue(7,etatcivil);
    query.bindValue(8,adresse);
    return query.exec();
}


bool Employe::supprimer(int cin)
{
 QSqlQuery query;
 QString cin_string=QString::number(cin);
 query.prepare("delete from employe where cin= :cin");
 query.bindValue(0,cin_string);
 return query.exec();
}

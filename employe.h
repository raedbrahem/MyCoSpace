#ifndef ETUDIANT_H
#define ETUDIANT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{
    QString nom,prenom,email,datedenaissance,adresse,etatcivil;
    int cin,numtel;
    float salaire;
public:
    Employe(){};
    Employe(int,QString,QString,QString,QString,float,int,QString,QString);
    //     (cin, nom, prenom, email,datedenaissance,salaire,numtel,etatcivil,adresse)
    QString getnom(){return  nom;}
    QString getprenom(){return  prenom;}
    int getcin(){return  cin;}

    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setcin(int cinn){this->cin=cinn;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
};
#endif // ETUDIANT_H

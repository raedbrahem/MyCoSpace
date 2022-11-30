#ifndef RESERVATION_H
#define RESERVATION_H
#include<QString>
#include <QDateTime>
#include <QDate>
#include"QSqlQueryModel"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QUrl>
class reservation

{
public:
    reservation();
   reservation(QString nomres,QString prenomres,QString numtlres,QString idres,QString typeres ,QString prixres,QDate dateres );
  // reservation(QString nomres,QString prenomres,QString numtlres,QString idres,QString typeres ,QString prixres,QString dateres );

   QString getnomres();
QString getprenomres();
QString getnumtlres();
QString getidres();
QString gettyperes();
QString getprixres();
QDate  getdateres();
void setnomres(QString nomres);
void setprenomres(QString prenomres);
void setnumtlres(QString numtlres);
void setidres(QString idres);
void settyperes(QString typeres);
void setprixres(QString prixres);
void setdateres(QDate dateres);
bool ajouterres();
bool supprimer(QString idres);
bool modifier();
QSqlQueryModel *afficher();
QSqlQueryModel *tri();
QSqlQueryModel *trinum();
QSqlQueryModel *tritype();
QSqlQueryModel* rechercher(QString id);
void CREATION_PDF();

QSqlQueryModel* recherchernum(QString id);
QSqlQueryModel* recherchertype(QString id);

private:
    QString nomres,prenomres,numtlres,idres,typeres ;
    QString prixres;
       QDate dateres;



};

#endif // RESERVATION_H

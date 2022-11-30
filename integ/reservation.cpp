#include "reservation.h"
#include"QSqlQuery"
#include"QtDebug"
#include"QObject"
    #include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
reservation::reservation()
{
nomres=" ";
prenomres=" ";
numtlres=" ";
typeres=" ";
prixres=" ";
idres="";



}
reservation::reservation(QString nomres,QString prenomres,QString numtlres,QString idres,QString typeres ,QString   prixres,QDate  dateres )
{
        this->nomres=nomres;
        this->prenomres=prenomres;
        this->numtlres=numtlres;
        this->idres=idres ;
        this->typeres=typeres ;
        this->prixres=prixres;
        this->dateres =dateres ;

}
QString reservation ::  getnomres(){return nomres;}
 QString reservation ::getprenomres(){return prenomres;}
QString reservation ::getnumtlres(){  return numtlres;}
QString reservation ::getidres(){  return idres;}
QString reservation ::gettyperes(){return typeres;}
QString  reservation ::getprixres(){return prixres;}
QDate reservation ::getdateres(){return dateres;}

void reservation ::setnomres(QString nomres){  this->nomres=nomres ;}
void reservation ::setprenomres(QString prenomres){   this->prenomres=prenomres; }
void reservation ::setnumtlres(QString numtlres){  this->numtlres=numtlres;}
void reservation ::setidres(QString idres){   this->idres=idres ; }
void reservation ::settyperes(QString typeres){      this->typeres=typeres ;}
void  reservation ::setprixres(QString  prixres){   this->prixres=prixres;}
void reservation ::setdateres(QDate dateres){ this->dateres =dateres ;}
bool reservation ::ajouterres()
{  QSqlQuery query;
   // QString ress=QString::number(prixres);
         query.prepare("INSERT INTO RESERVATION (nomres, prenomres, numtlres,idres,prixres,typeres,dateres) "
                       "VALUES (        :NOMRES,      :PRENOMRES,     :NUMTLRES,    :IDRES,   :PRIXRES,   :TYPERES,      :DATERES )");
         query.bindValue(":NOMRES", nomres);
         query.bindValue(":PRENOMRES", prenomres);
         query.bindValue(":NUMTLRES", numtlres);
         query.bindValue(":IDRES", idres);
         query.bindValue(":PRIXRES", prixres);
         query.bindValue(":TYPERES", typeres);

         query.bindValue(":DATERES", dateres);

    return   query.exec();
}
QSqlQueryModel* reservation::afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    //QSqlQueryModel *model = new QSqlQueryModel;
       model->setQuery("SELECT* FROM reservation");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID résérvation"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de résérvation"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));

return model ;
}
bool reservation :: supprimer(QString idres)
{
    QSqlQuery query;
 //     QString ress=QString::text(idres);
            query.prepare("Delete from reservation where idres= :idres");
            query.bindValue(":idres", idres);
            return   query.exec();


}
bool reservation::modifier()
{
    QSqlQuery query;
  //  QString res= QString(cin);
        //query.prepare("UPDATE livraisons SET DATE_LIVRAISON=:DATE_LIVRAISON,NOM_LIVREUR=:NOM_LIVREUR,REF_CMD=:REF_CMD  WHERE ID_LIVR=:ID_LIVR");
    query.prepare(" NOMRES=:NOMRES,      PRENOMRES=:PRENOMRES,     NUMTLRES=:NUMTLRES,    IDRES=:IDRES,   PRIXRES=:PRIXRES,   TYPERES=:TYPERES,      DATERES=:DATERES");
    //QString str = model1->record(0).value(0).toString();
    //label->setText(str);
    query.bindValue(":NOMRES", nomres);
    query.bindValue(":PRENOMRES", prenomres);
    query.bindValue(":NUMTLRES", numtlres);
    query.bindValue(":IDRES", idres);
    query.bindValue(":PRIXRES", prixres);
    query.bindValue(":TYPERES", typeres);
    query.bindValue(":DATERES", dateres);


return   query.exec();
}
QSqlQueryModel* reservation::tri()
{
    QSqlQueryModel * model = new QSqlQueryModel();
            model->setQuery("Select * FROM RESERVATION ORDER BY IDRES ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID résérvation"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de résérvation"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
return model ;
}

QSqlQueryModel *reservation::trinum()
{
    QSqlQueryModel * model = new QSqlQueryModel();
            model->setQuery("Select * FROM RESERVATION ORDER BY NUMTLRES ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID résérvation"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de résérvation"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
return model ;
}
QSqlQueryModel *reservation::tritype()
{
    QSqlQueryModel * model = new QSqlQueryModel();
            model->setQuery("Select * FROM RESERVATION ORDER BY TYPERES");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID résérvation"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de résérvation"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
return model ;
}
QSqlQueryModel* reservation::rechercher(QString id)
{          QSqlQuery query ;
           query.prepare("SELECT * FROM RESERVATION WHERE IDRES=:IDRES");
                  query.bindValue(":IDRES",id);
                         query.exec();
    QSqlQueryModel * model = new QSqlQueryModel();
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID résérvation"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de résérvation"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
         model->setQuery(query);
                   return model ;
}


QSqlQueryModel* reservation::recherchertype(QString id)
{          QSqlQuery query ;
           query.prepare("SELECT * FROM RESERVATION WHERE  TYPERES=:TYPERES");
                  query.bindValue(":IDRES",id);
                         query.exec();
    QSqlQueryModel * model = new QSqlQueryModel();
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID résérvation"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de résérvation"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
         model->setQuery(query);
                   return model ;
}
QSqlQueryModel* reservation::recherchernum(QString id)
{          QSqlQuery query ;
           query.prepare("SELECT * FROM RESERVATION WHERE NUMTLRES=:NUMTLRES");
                  query.bindValue(":IDRES",id);
                         query.exec();
    QSqlQueryModel * model = new QSqlQueryModel();
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID résérvation"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type de résérvation"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
         model->setQuery(query);
                   return model ;
}


void reservation::CREATION_PDF()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
        { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;
    q.prepare("SELECT * FROM RESERVATION ");
    q.exec();
    QString pdf="<br> <h1  style='color:blue'>LISTE DES RESERVATIONS   <br></h1>\n <br> <table>  <tr>  <th>CIN </th> <th>NOM </th> <th>PRENOM  </th> <th>NUMTLRES </th><th>IDRES </th><th>PRIXRES  </th> <th>TYPERES   </th> <th>DATERES  </tr>" ;

    while ( q.next())
        {

        pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);


}

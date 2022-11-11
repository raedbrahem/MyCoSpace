#include "employe.h"
#include <QString>
#include <QtDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>

Employe::Employe(int cin,QString nom,QString prenom,QString email,QString date,float salaire,int numtel,QString etat,QString adresse,QString imageurl)
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
    this->imageurl=imageurl;
}



bool Employe::ajouter()
{
QSqlQuery query;
QString cin_string = QString::number(cin);
//QString num_string = QString::number(numtel);
QString salary_string = QString::number(salaire);

query.prepare("insert into employe(cin, nom, prenom, email,datedenaissance,salaire,numtel,etatcivil,adresse,image)"
              "VALUES(:cin,:surname,:forename,:email,:datedenaissance,:salaire,:numtel,:etatcivil,:adresse,:image)");
query.bindValue(":cin",cin_string);
query.bindValue(":surname",nom);
query.bindValue(":forename",prenom);
query.bindValue(":email",email);
query.bindValue(":datedenaissance",datedenaissance);
query.bindValue(":salaire",salary_string);
query.bindValue(":numtel",numtel);
query.bindValue(":etatcivil",etatcivil);
query.bindValue(":adresse",adresse);
query.bindValue(":image",imageurl);
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

QSqlQueryModel * Employe::afficher1()
{
    QSqlQuery query;
    query.prepare("SELECT* from employe where cin= :cin");
    query.bindValue(":cin",cin);
    query.exec();

    QSqlQueryModel * model= new QSqlQueryModel;
    model->setQuery(query);
    return model;
}


bool Employe::modifier()
{
    QSqlQuery query;
    QString cin_string = QString::number(cin);
    QString num_string = QString::number(numtel);
    QString salary_string = QString::number(salaire);
    query.prepare("UPDATE EMPLOYE SET cin='"+cin_string+"' , nom='"+nom+"' , prenom='"+prenom+"', email='"+email+"',datedenaissance='"+datedenaissance+"', salaire='"+salary_string+"', numtel='"+num_string+"', etatcivil='"+etatcivil+"', adresse='"+adresse+"', image='"+imageurl+"' where cin='"+cin_string+"' ");
    query.bindValue(0,cin_string);
    query.bindValue(1,nom);
    query.bindValue(2,prenom);
    query.bindValue(3,email);
    query.bindValue(4,datedenaissance);
    query.bindValue(5,salary_string);
    query.bindValue(6,num_string);
    query.bindValue(7,etatcivil);
    query.bindValue(8,adresse);
    query.bindValue(9,imageurl);
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


QSqlQueryModel * Employe::trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT* from employe order by prenom");
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

QSqlQueryModel * Employe::triernom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT* from employe order by nom");
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


QSqlQueryModel * Employe::triercin()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT* from employe order by cin");
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



void Employe::CREATION_PDF()
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
    q.prepare("SELECT * FROM CITOYEN ");
    q.exec();
    QString pdf="<br> <h1  style='color:blue'>LISTE DES EMPLOYESS  <br></h1>\n <br> <table>  <tr>  <th>CIN </th> <th>NOM </th> <th>PRENOM  </th> <th>AGE  </th><th>TEL  </th><th>ADRESS   </th> </tr>" ;
    while ( q.next())
        {
            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
        }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}


QChartView * Employe::stat()
{
    int row_count = 0;
    int row_count1 = 0;
    int row_count2 = 0;
            QSqlQuery query,query2,query3;
            query.prepare("SELECT * FROM employe where salaire < 1000 ");
            query.exec();
            query2.prepare("SELECT * FROM employe where (salaire >= 1000) AND (salaire < 5000) ");
            query2.exec();
            query3.prepare("SELECT * FROM employe where salaire >= 5000");
            query3.exec();

            while(query3.next())
                row_count2++;

            while(query2.next())
                row_count1++;

            while(query.next())
                row_count++;

            qDebug()<<row_count<<row_count1<<row_count2;

    QPieSeries *series = new QPieSeries();
    series->append("employee ont un salaire >5000 DT", row_count2);
    series->append("employee ont un salaire entre 5000 et 1000 DT", row_count1);
    series->append("employee ont un salaire <1000 DT", row_count);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("statistic Des salaires");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setBackgroundVisible(true);
    chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
    chart->legend()->setPen(QPen(QColor(248, 246, 0)));
    series->setLabelsVisible();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}


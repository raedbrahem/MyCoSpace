#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QString>
#include "employe.h"
#include <QtDebug>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include "login.h"
#include "arduino.h"
#include <QtQml>
#include <QQuickView>
#include "qtquickcontrolsapplication.h"
   #include "sqleventmodel.h"
#include <QtGui>
#include <QtOpenGL>
#include <QVariant>
#include <QAbstractEventDispatcher>
#include <QDir>
        #include <QtQml>
           #include <QQuickView>
#include <QSurfaceFormat>
              #include "qrcode.h"
const QString RESULTS_PATH = " C:\\";

#include <QSystemTrayIcon>
#include <sys/types.h>
#include <QUrl>

#include <QSqlRecord>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
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

    ui->tab_etudiants2->setModel(user.afficher());
    ui->comboBox2->setModel(E.afficher());
    ui->comboBox22->setModel(E.cherchernom());
    ui->comboBox222->setModel(E.chercherprenom());
    ui->verticalLayout->addWidget(E.stat());


    ui->tab_res->setModel(R.afficher());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    QOpenGLContext::currentContext();

    qmlRegisterType<SqlEventModel>("org.qtproject.examples.calendar", 1, 0, "SqlEventModel");
    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
    ui->quickWidget->show();




}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearLayout(QLayout *layout)
{
     QLayoutItem *item;
     while ((item = layout->takeAt(0)))
         delete item;
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
      QString image=ui->le_imageurl->text();
      Employe E(cin,nom,prenom,email,date,salaire,numtel,etat,adresse,image);
      bool test=E.ajouter();

    if(test)
    {
        QMessageBox::information(this,"ok","ajout effectué");
        ui->tab_etudiants->setModel(E.afficher());
        ui->comboBox2->setModel(E.afficher());
        ui->comboBox22->setModel(E.chercherprenom());
        ui->comboBox222->setModel(E.cherchernom());
        clearLayout(ui->verticalLayout);
        ui->verticalLayout->addWidget(E.stat());
    }
    else
    QMessageBox::warning(this,"not ok","ajout non effectué");
}

void MainWindow::on_pb_supprimer_clicked()
{
Employe E1;
E1.setcin(ui->le_cinmaj->text().toInt());

bool test=E1.supprimer(E1.getcin());

if(ui->le_cinmaj->text()==NULL)
    test=0;
if(test)
{
     QMessageBox::information(this," ok","suppression effectué");
     ui->tab_etudiants->setModel(E1.afficher());
     ui->comboBox22->setModel(E.chercherprenom());
     ui->comboBox222->setModel(E.cherchernom());
     ui->comboBox2->setModel(E.afficher());

     ui->le_cinmaj->setText(NULL);
     ui->le_nommaj->setText(NULL);
     ui->le_prenommaj->setText(NULL);
     ui->le_emailmaj->setText(NULL);
     ui->le_datemaj->setText(NULL);
     ui->le_salairemaj->setText(NULL);
     ui->le_nummaj->setText(NULL);
     ui->le_etatmaj->setText(NULL);
     ui->le_adressemaj->setText(NULL);
     ui->le_imageurlmaj->setText(NULL);


     clearLayout(ui->verticalLayout);
     ui->verticalLayout->addWidget(E.stat());
}

else
     QMessageBox::warning(this,"not ok","suppression non effectué");
}

void MainWindow::on_pb_update_clicked()
{
    int cin=ui->le_cinmaj->text().toInt();
    QString nom=ui->le_nommaj->text();
    QString prenom=ui->le_prenommaj->text();
    QString date=ui->le_datemaj->text();
    QString adresse=ui->le_adressemaj->text();
    float salaire=ui->le_salairemaj->text().toFloat();
    int numtel=ui->le_nummaj->text().toInt();
    QString etat=ui->le_etatmaj->text();
    QString email=ui->le_emailmaj->text();
    QString imageurl=ui->le_imageurlmaj->text();
    Employe E(cin,nom,prenom,email,date,salaire,numtel,etat,adresse,imageurl);
    bool test=E.modifier();

    if (ui->le_cinmaj->text()==NULL)
        test=0;
    if(test)
    {
        QMessageBox::information(this,"ok","modification effectué");
        ui->tab_emp->setModel(NULL);
        ui->tab_etudiants->setModel(E.afficher());
        ui->comboBox222->setModel(E.chercherprenom());
        ui->comboBox22->setModel(E.cherchernom());
        clearLayout(ui->verticalLayout);
        ui->verticalLayout->addWidget(E.stat());
    }
    else
        QMessageBox::warning(this,"not ok","modification non effectué");
}






void MainWindow::on_tab_etudiants_activated(const QModelIndex &index)
{
    QString cin=ui->tab_etudiants->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT* from employe where cin='"+cin+"'");
    if(qry.exec())
        {
            while (qry.next())
                {
                  ui->le_cinmaj->setText(qry.value(0).toString());
                  ui->le_nommaj->setText(qry.value(1).toString());
                  ui->le_prenommaj->setText(qry.value(2).toString());
                  ui->le_emailmaj->setText(qry.value(3).toString());
                  ui->le_datemaj->setText(qry.value(4).toString());
                  ui->le_salairemaj->setText(qry.value(5).toString());
                  ui->le_nummaj->setText(qry.value(6).toString());
                  ui->le_etatmaj->setText(qry.value(7).toString());
                  ui->le_adressemaj->setText(qry.value(8).toString());
                  ui->le_imageurlmaj->setText(qry.value(9).toString());
                  QImage image;
                  image.load(qry.value(9).toString());
                  image=image.scaledToWidth(ui->le_imagemaj->width(),Qt::SmoothTransformation);
                  ui->le_imagemaj->setPixmap(QPixmap::fromImage(image));
            }
        }
}


void MainWindow::on_pb_pdf_clicked()
{
    QString strStream;
            strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(strStream).suffix().isEmpty())
                    { strStream.append(".pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(strStream);

                      QTextStream out(&strStream);

                      const int rowCount = ui->tab_etudiants->model()->rowCount();
                      const int columnCount = ui->tab_etudiants->model()->columnCount();
                      QString TT = QDateTime::currentDateTime().toString();
                      out <<"<html>\n"
                            "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE LIST<title>\n "
                          << "</head>\n"
                          "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                          "<h1 style=\"text-align: center;\"><strong> ****LISTE DES EMPLOYES **** </strong></h1>"

                          "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                            "</br> </br>";
                      // headers
                      out << "<thead><tr bgcolor=#d6e5ff>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->tab_etudiants->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->tab_etudiants->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";

                      // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++)
                        {
                              if (!ui->tab_etudiants->isColumnHidden(column)) {
                                  QString data =ui->tab_etudiants->model()->data(ui->tab_etudiants->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //pas compriis
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";
                      QTextDocument document;
                      document.setHtml(strStream);
                      document.print(&printer);
                      QMessageBox::information(this,"ok","fichier crée");
}

void MainWindow::on_pb_trier_clicked()
{
    Employe E1;
    ui->tab_etudiants->setModel(E1.trier());
}
void MainWindow::on_pb_trier_nom_clicked()
{
    Employe E1;
    ui->tab_etudiants->setModel(E1.triernom());
}

void MainWindow::on_pb_trier_cin_clicked()
{
    Employe E1;
    ui->tab_etudiants->setModel(E1.triercin());
}


void MainWindow::on_pb_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images(*.png *""jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid=image.load((filename));
        if(valid)
        {
            image=image.scaledToWidth(ui->le_image->width(),Qt::SmoothTransformation);
            ui->le_image->setPixmap(QPixmap::fromImage(image));
            ui->le_imageurl->setText(filename);
        }
    }

}

void MainWindow::on_pb_imagemaj_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images(*.png *""jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid=image.load((filename));
        if(valid)
        {
            image=image.scaledToWidth(ui->le_image->width(),Qt::SmoothTransformation);
            ui->le_imagemaj->setPixmap(QPixmap::fromImage(image));
            ui->le_imageurlmaj->setText(filename);
        }
    }
}

void MainWindow::on_pb_ajouteruser_clicked()
{

    QString un=ui->le_unajout->text();
    QString pw=ui->le_pwajout->text();
    QString pw1=ui->le_pwajout2->text();

    login user(un,pw);
    bool test=user.createuser();
    if(pw!=pw1)
        test=0;
    if(test)
    {
        ui->tab_etudiants2->setModel(user.afficher());

        //ui->comboBox3->setModel(user.afficher());
        QMessageBox::information(this,"ok","ajout effectué");
    }
    else
        QMessageBox::warning(this,"not ok","ajout non effectué");
}

void MainWindow::on_pb_supprimeruser_clicked()
{
    login l;
    l.setusername(ui->le_unmaj->text());
    bool test=l.supprimer(l.getusername());

    if(ui->le_unmaj->text()==NULL)
        test=0;
    if(test)
    {
         QMessageBox::information(this," ok","suppression effectué");
         ui->tab_etudiants2->setModel(l.afficher());
    }
    else
    QMessageBox::warning(this,"not ok","suppression non effectué");
}

void MainWindow::on_tab_etudiants2_activated(const QModelIndex &index)
{
    QString username=ui->tab_etudiants2->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT* from users where username='"+username+"'");
    if(qry.exec())
        {
            while (qry.next())
                {
                  ui->le_unmaj->setText(qry.value(0).toString());
                  ui->le_pwmaj->setText(qry.value(1).toString());
                }
        }
}

void MainWindow::on_pb_modifiereruser_clicked()
{
    QString un=ui->le_unmaj->text();
    QString pw=ui->le_pwmaj->text();
    QString pw1=ui->le_pwmaj2->text();
    login user(un,pw);
    bool test=user.modifier();
    if(pw!=pw1)
        test=0;
    if(test)
    {
        QMessageBox::information(this,"ok","modification effectué");
        ui->tab_etudiants2->setModel(user.afficher());
    }
    else
        QMessageBox::warning(this,"no ok","modification non effectué");

}

void MainWindow::on_pb_cherchernom_clicked()
{
    bool test;
    Employe E1;
    E1.setnom(ui->comboBox22->currentText());
    test=E1.afficher2();
    if(ui->comboBox22->currentText()==NULL || test==0)
        QMessageBox::information(this,"not ok","error");
    else
    ui->tab_emp->setModel(E1.afficher2());
}

void MainWindow::on_pbchercherprenom_clicked()
{
    bool test;
    Employe E1;
    E1.setprenom(ui->comboBox222->currentText());
    test=E1.afficher3();
    if(ui->comboBox222->currentText()==NULL || test==0)
        QMessageBox::information(this,"not ok","error");
    else
    ui->tab_emp->setModel(E1.afficher3());
}
void MainWindow::on_pb_chercher_clicked()
{
    bool test;
    Employe E1;
    E1.setcin(ui->comboBox2->currentText().toInt());
    test=E1.afficher1();
    if(ui->comboBox2->currentText()==NULL || test==0)
        QMessageBox::information(this,"not ok","error");
    else
    ui->tab_emp->setModel(E1.afficher1());
}

void MainWindow::update_label()
{
        data = A.read_from_arduino();
        if(str.size()<5)
        {
         str=str+data;
         DataAsString = QString::fromStdString(str.toStdString());
         s="";
         for(int i=0;i<5;i++)
             s[i]=DataAsString[i];
         ui->idres->setText(s);
        }
        qDebug()<<"data : "<<s;
        qDebug()<<"length : "<<s.size();
}

void MainWindow::on_effacer_clicked()
{
A.write_to_arduino("0");
ui->idres->setText("");
str="";
}



void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    QString cin=ui->idres->text();
    query.prepare("SELECT * from reservation where idres='"+cin+"'");
    if(query.exec())
      {
        while (query.next())
        {
         if(query.value(0)==cin)
            {QMessageBox::information(this,"login","correct");
             A.write_to_arduino("1");
             qDebug()<<"oui";
             A.write_to_arduino("2");
             QString nom=query.value(2).toString();
             A.write_to_arduinonom(nom.toUtf8());}
         else
            {QMessageBox::warning(this,"error","error");
             A.write_to_arduino("0");
             qDebug()<<"non";}
        }
      }
    else {QMessageBox::warning(this,"login","error");}
}

void MainWindow::on_pb_delete_clicked(){}
void MainWindow::on_list_employes_currentRowChanged(int){}
void MainWindow::on_tabWidget_2_tabBarClicked(int){}
void MainWindow::on_comboBox_currentTextChanged(const QString){}

void MainWindow::on_pb_ajouterres_clicked()
{
    QString nomres=ui->le_nomres->text(),prenomres=ui->le_prenomres->text(),numres=ui->le_numres->text(),idres=ui->le_idres->text();
        QString typeres=ui->cb_typeres->text();

       QString prixres=ui->le_prixres->text()  ;
        QDate dateres=ui->le_dateres->date();
        reservation r(nomres,prenomres,numres,idres,typeres,prixres,dateres);

    bool test=r.ajouterres();
    if(test)
    { QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("Ajout effectué\n" "Click Cancel to exit. "),QMessageBox::Cancel);
         ui->tab_res->setModel(R.afficher());
    }
    else QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Ajout non effectué\n" "Click Cancel to exit. "),QMessageBox::Cancel);



    QDir().rmpath(RESULTS_PATH);
        QDir().mkpath(RESULTS_PATH);





                const QString RESULTS_PATH = "C:\\Users\\ismai\\Dropbox\\My PC (LAPTOP-3HHJB834)\\Desktop\\formation_QT\\cof\\cof\\Qrcode\\";
                 QString cc;
                        cc=nomres+ " " +typeres+ " " +prixres+ " " +dateres.toString();


                        using namespace ::qrcodegen;
                 QrCode qr = QrCode::encodeText(cc.toUtf8().constData(), QrCode::Ecc::HIGH);

                 // Read the black & white pixels
                 QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                 for (int y = 0; y < qr.getSize(); y++) {
                     for (int x = 0; x < qr.getSize(); x++) {
                         int color = qr.getModule(x, y);  // 0 for white, 1 for black

                         // You need to modify this part
                         if(color==0)
                             im.setPixel(x, y,qRgb(254, 254, 254));
                         else
                             im.setPixel(x, y,qRgb(0, 0, 0));
                     }
                 }
                 im=im.scaled(100,100);
                 QString nomimg=nomres+".PNG";
                 im.save(RESULTS_PATH + nomimg,"PNG");
                ui->qr_code->setPixmap(QPixmap::fromImage(im));


}

void MainWindow::on_supprmierres_clicked()
{
    reservation r1; r1.setidres(ui->le_suppres->text());
bool test=r1.supprimer(r1.getidres());
QMessageBox msgBox;
if(test && r1.getidres()!="\0")
{
    msgBox.setText("suppression avec succes");
    ui->tab_res->setModel(r1.afficher());
}
else msgBox.setText("echec de suppression");
msgBox.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
        QString nomres=ui->le_nommres->text() ;
        QString prenomres=ui->le_prenommres->text() ;
        QString numtlres=ui->le_nummres->text() ;
        QString idres=ui->le_idmres->text() ;
        QString prixres=ui->le_prixmres->text() ;
        QString typeres=ui->le_typemres->text() ;
        QDate dateres=ui->le_datemres->date() ;


reservation res(nomres,prenomres,numtlres,idres,typeres ,prixres,dateres );

      bool test=res.modifier() ;

        QMessageBox msgBox;

        if(test)
           {
            msgBox.setText("Modification avec succes.");
          ui->tab_res->setModel(res.afficher()) ;
           }
        else
            msgBox.setText("Echec de Modification.!!!");
            msgBox.exec();
}

void MainWindow::on_trires_clicked()
{
    reservation r ;
    ui->tab_res->setModel(r.tri());
bool test= r.tri();
if(test)
{
    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("tri effectué.\n""click cancel to exit."),QMessageBox::Cancel);

}
else
{
    QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectué.\n""click cancel to exit."),QMessageBox::Cancel);


}
}


void MainWindow::on_pb_chercherres_clicked()
{   reservation r;
    QString id ;
    id= ui->le_cherherres->text();
    ui->tab_res->setModel(r.rechercher(id));}







void MainWindow::on_pushButton_4_clicked()
{
    QString strStream;
            strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(strStream).suffix().isEmpty())
                    { strStream.append(".pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(strStream);

                      QTextStream out(&strStream);

                      const int rowCount = ui->tab_res->model()->rowCount();
                      const int columnCount = ui->tab_res->model()->columnCount();
                      QString TT = QDateTime::currentDateTime().toString();
                      out <<"<html>\n"
                            "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE LIST<title>\n "
                          << "</head>\n"
                          "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                          "<h1 style=\"text-align: center;\"><strong> ****LISTE DES RESERVATIONS **** </strong></h1>"

                          "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                            "</br> </br>";
                      // headers
                      out << "<thead><tr bgcolor=#d6e5ff>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->tab_res->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->tab_res->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";

                      // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++)
                        {
                              if (!ui->tab_res->isColumnHidden(column)) {
                                  QString data =ui->tab_res->model()->data(ui->tab_res->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //pas compriis
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";

                      QTextDocument document;
                      document.setHtml(strStream);
                      document.print(&printer);
}

void MainWindow::on_tab_res_activated(const QModelIndex &index)
{
    QString id=ui->tab_res->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * FROM RESERVATION WHERE NOMRES='"+id+"' or PRENOMRES='"+id+"' or NUMTLRES='"+id+"' or IDRES='"+id+"' or PRIXRES='"+id+"' or TYPERES='"+id+"'"  );
        if (qry.exec())
            {   while (qry.next())
                    {
                      ui->le_suppres->setText(qry.value(3).toString());
                      ui->le_idmres->setText(qry.value(3).toString());
                      ui->le_nommres->setText(qry.value(0).toString());
                      ui->le_prenommres->setText(qry.value(1).toString());
                      ui->le_nummres->setText(qry.value(2).toString());
                      ui->le_prixmres->setText(qry.value(4).toString());
                      ui->le_typemres->setText(qry.value(5).toString());


            }
        }

}

void MainWindow::on_triernum_clicked()
{
    reservation r ;
    ui->tab_res->setModel(r.trinum());
bool test= r.tri();
if(test)
{
    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("tri effectué.\n""click cancel to exit."),QMessageBox::Cancel);

}
else
{
    QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectué.\n""click cancel to exit."),QMessageBox::Cancel);


}
}

void MainWindow::on_triertype_clicked()
{
    reservation r ;
    ui->tab_res->setModel(r.tritype());
bool test= r.tri();
if(test)
{
    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("tri effectué.\n""click cancel to exit."),QMessageBox::Cancel);

}
else
{
    QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectué.\n""click cancel to exit."),QMessageBox::Cancel);


}
}

void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    proxy = new QSortFilterProxyModel();
proxy->setFilterFixedString(arg1);
//definir la source (tableau original)
   //proxy->setSourceModel(tab_res.afficher());

//pour la recherche
   //proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
   //proxy->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
  //remplissage tableau avec le masque
   //ui->tableau->setModel(proxy);

}



void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );


}
void   MainWindow::sendMail()
{

    Smtp* smtp = new Smtp("waterproof.application@gmail.com" , "waterproofwaterproof", "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("waterproof.application@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)

{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple    client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->msg->clear();
}



void MainWindow::on_Calendrier_clicked()
{
    secDialog= new SECFORMDialog(this);
    secDialog->show();


}


void MainWindow::on_pushButtonchercheridres_clicked()
{
    reservation r;
        QString id ;
        id= ui->le_cherherres->text();
        ui->tab_res->setModel(r.rechercher(id));
}

void MainWindow::on_pushButton_cherchertyperes_clicked()
{
    reservation r;
        QString id ;
        id= ui->le_cherherrestype->text();
        ui->tab_res->setModel(r.recherchertype(id));
}

void MainWindow::on_pushButton_cherchernumres_clicked()
{
    reservation r;
        QString id ;
        id= ui->le_cherherresnum->text();
        ui->tab_res->setModel(r.recherchernum(id));

}


void MainWindow::on_pushButton_gestion_remploye_badel_clicked()
{
      ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_gestionres_badel_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
}
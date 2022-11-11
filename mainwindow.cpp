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
    ui->comboBox2->setModel(E.afficher());
    ui->verticalLayout->addWidget(E.stat());
    QPieSeries *series = new QPieSeries();
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
        ui->comboBox->addItem(QString::number(cin));
        ui->comboBox->setModel(E.afficher());
        ui->comboBox2->addItem(QString::number(cin));
        ui->comboBox2->setModel(E.afficher());
        clearLayout(ui->verticalLayout);
        ui->verticalLayout->addWidget(E.stat());
    }
    else
    QMessageBox::warning(this,"not ok","ajout non effectué");
}

void MainWindow::on_pb_supprimer_clicked()
{
Employe E1;
E1.setcin(ui->comboBox->currentText().toInt());
bool test=E1.supprimer(E1.getcin());

if(ui->comboBox->currentText()==NULL)
    test=0;
if(test)
{
     QMessageBox::information(this," ok","suppression effectué");
     ui->tab_etudiants->setModel(E1.afficher());
     ui->comboBox->removeItem(ui->comboBox->currentText().toInt());
     ui->comboBox->setModel(E.afficher());

     ui->comboBox2->removeItem(ui->comboBox->currentText().toInt());
     ui->comboBox2->setModel(E.afficher());
     clearLayout(ui->verticalLayout);
     ui->verticalLayout->addWidget(E.stat());
}

else
     QMessageBox::warning(this,"not ok","ajout non effectué");
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

    if (ui->comboBox->currentText()==NULL)
        test=0;
    if(test)
    {
        QMessageBox::information(this,"ok","modification effectué");
        ui->tab_etudiants->setModel(E.afficher());
        clearLayout(ui->verticalLayout);
        ui->verticalLayout->addWidget(E.stat());
    }
    else
        QMessageBox::information(this,"no tok","modification non effectué");
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



void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    Employe E1;
    E1.setcin(ui->comboBox->currentText().toInt());
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
void MainWindow::on_pb_delete_clicked(){}
void MainWindow::on_list_employes_currentRowChanged(int){}
void MainWindow::on_tabWidget_2_tabBarClicked(int){}

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

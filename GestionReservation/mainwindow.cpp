#include "mainwindow.h"
#include "ui_mainwindow.h"
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
const QString RESULTS_PATH = "C:\\Users\\ismai\\Dropbox\\My PC (LAPTOP-3HHJB834)\\Desktop\\formation_QT\\cof\\cof\\Qrcode\\";
#include <QSystemTrayIcon>
#include <sys/types.h>
#include <QUrl>

#include <QSqlRecord>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_res->setModel(R.afficher());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    //connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    QOpenGLContext::currentContext();

    qmlRegisterType<SqlEventModel>("org.qtproject.examples.calendar", 1, 0, "SqlEventModel");
    //ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
    //ui->quickWidget->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouterres_clicked()
{
}

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

    Smtp* smtp = new Smtp("ghaith.elbenna@esprit.tn" , "211JMT8242", "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("cospace123@yahoo.fr", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
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
{   secDialog= new SECFORMDialog(this);
    secDialog->show();
}


void MainWindow::on_chercherrestype_clicked()
{
        reservation r;
        QString id ;
        id= ui->le_cherherrest->text();
        ui->tab_res->setModel(r.rechercherty(id));

}

void MainWindow::on_chercherresnom_clicked()
{
       reservation r;
        QString id ;
        id= ui->le_cherherresn->text();
        ui->tab_res->setModel(r.rechercherno(id));

}

void MainWindow::on_chercherres_clicked()
{
    reservation r;
        QString id ;
        id= ui->le_cherherres->text();
        ui->tab_res->setModel(r.rechercher(id));
}

void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("ismail.triki@esprit.tn", "211JMT8186", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QString a=ui->rcpt->text();
    QString b=ui->subject->text();
    QString c=ui->msg->toPlainText();

    smtp->sendMail("ismail.triki@esprit.tn", a , b,c);
}

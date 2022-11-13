#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include"mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pb_connect_clicked()
{   int a=0;
    QString username=ui->le_un->text();
    QString password=ui->le_pw->text();
    QSqlQuery qry;
    qry.prepare("SELECT* from users where username='"+username+"'and password='"+password+"'");
    if(qry.exec())
      {
        while (qry.next())
        {
         if(username==qry.value(0) && password==qry.value(1))
         {
            QMessageBox::information(this,"login","Username and Password are correct");
            hide();
            mainwindow=new MainWindow(this);
            mainwindow->show();
            a=1;
         }
        }
         if(a==0)
            QMessageBox::warning(this,"login","Username and Password are incorrect");


      }

}

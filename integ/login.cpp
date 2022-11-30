#include "login.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QtDebug>
#include<QString>

login::login()
{

}
bool login::createuser()
{
    QSqlQuery query;
    query.prepare("insert into users(username,password)"
                  "VALUES(:username,:password)");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    return query.exec();
}

QSqlQueryModel * login::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT* from users");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("username"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("password"));
return model;
}

bool login::modifier()
{
    QSqlQuery query;
    query.prepare("update users set password='"+password+"' where username='"+username+"' ");
    query.bindValue(1,password);
    return query.exec();
}

bool login::supprimer(QString username)
{
 QSqlQuery query;
 query.prepare("delete from users where username= :username");
 query.bindValue(0,username);
 return query.exec();
}

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
    query.bindValue(":pw",password);
    return query.exec();
}

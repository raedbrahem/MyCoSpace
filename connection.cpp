#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("raed");
db.setPassword("esprit18");

if (db.open()) test=true;
test=true;
return test;}

void Connection::closeconnection(){db.close();}

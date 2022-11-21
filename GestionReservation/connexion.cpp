#include "connexion.h"

connexion::connexion()
{

}
bool connexion::createconnection()
{
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("isssmail");
    db.setPassword("esprit18");
    if(db.open())
        return true ;
    return  false ;
}
void connexion::closeconnection(){db.close();}

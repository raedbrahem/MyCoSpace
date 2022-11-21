#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlQuery>
class connexion
{QSqlDatabase db ;
public:


    connexion();
    bool createconnection();
    void closeConnection();
    void closeconnection();
};

#endif // CONNEXION_H

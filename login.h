#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QSqlQueryModel>
class login
{
public:
    login();
    login(QString un,QString pw){this->username=un;
                                this->password=pw;}
    bool createuser();
    void connect();
    QSqlQueryModel *afficher();
    bool modifier();
    bool supprimer(QString);
    void setusername(QString un){this->username =un;}
    QString getusername(){return this->username;}
private:
    QString username;
    QString password;
};

#endif // LOGIN_H

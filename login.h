#ifndef LOGIN_H
#define LOGIN_H
#include <QString>

class login
{
public:
    login();
    bool createuser();
    void connect();
private:
    QString username;
    QString password;
};

#endif // LOGIN_H

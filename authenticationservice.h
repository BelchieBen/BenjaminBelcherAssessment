#define AUTHENTICATIONSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>

using namespace std;

class authenticationservice{
private:
    string email;
    string password;

public:
    authenticationservice(){};
//    authenticationservice(string eml, string pssword){
//        this->email = eml;
//        this->password = pssword;
//    }

    //int hashPassword(string const &Combine);
    int login(QString username, QString password);
    //int registerUsr();
    //int forgotPassword(string email);


};

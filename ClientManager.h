#include <iostream>
#include <pqxx/pqxx>
using namespace std;

struct ClientData{
    string first_name;
    string last_name;
    string email;
    friend ostream & operator << ( ostream& print, ClientData& obj ){
        print << "first_name: "<< obj.first_name << endl;
        print << "last_name: "<< obj.last_name << endl;
        print << "email: "<< obj.email << endl;
        return print;
    }
};

class ClientManager{

     string ConStr;

     pqxx::connection * con;

public:

    ClientManager();

     ~ClientManager();

     void InitDbStructure();

     void AddClient(const string &first_name, const string& last_name, const string & email);

     void AddPhone(const int & id, const string& number);

     void UpdateDataClient(const int & id, const string& first_name, const string& last_name, const string& email);

     void DeletePhone(const string& number);

     void RemoveClient(const int & id);

     ClientData FindClient(const string& SearchValue);
};


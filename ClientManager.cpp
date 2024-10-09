#include "ClientManager.h"
#include <tuple>
ClientManager::ClientManager(): ConStr("host=localhost "
                           "port=5432 "
                           "dbname=postgres "
                           "user=myuser1 "
                           "password=123"),
                           con(new pqxx::connection(ConStr))

{}
void ClientManager::InitDbStructure(){
    pqxx::transaction tran(*con);
    string CreateClients = "CREATE TABLE IF NOT EXISTS CLIENTS ("
                           "client_id SERIAL PRIMARY KEY, "
                           "first_name VARCHAR(100) NOT NULL, "
                           "last_name VARCHAR(100) NOT NULL, "
                           "email VARCHAR(100) NOT NULL UNIQUE);";
    tran.exec(CreateClients);
    tran.commit();
    pqxx::transaction tran1(*con);
    string CreatePhones = "CREATE TABLE IF NOT EXISTS PHONES  ("
                          "phone_id SERIAL PRIMARY KEY,"
                          "client_id INTEGER NOT NULL,"
                          "phone_number VARCHAR(20),"
                          "FOREIGN KEY (client_id) REFERENCES clients (client_id) ON DELETE CASCADE); ";


    tran1.exec(CreatePhones);
    tran1.commit();
}
void ClientManager::AddClient(const string &first_name, const string& last_name, const string & email){
    pqxx::transaction tran(*con);

    string query ="INSERT INTO CLIENTS(first_name, last_name, email)"
                  "VALUES('" +tran.esc(first_name)+ "', ' "+tran.esc(last_name)+"', '" +tran.esc(email)+ "')";
    tran.exec(query);
    tran.commit();
}

void ClientManager::UpdateDataClient(const int & id, const string& first_name, const string& last_name, const string& email) {
    pqxx::transaction tran_name(*con);

    string string_id = to_string(id);
    std::string select = "UPDATE CLIENTS SET "
                         "first_name='" + tran_name.esc(first_name) + "', "
                          "last_name='"+tran_name.esc(last_name)+ "', "
                          "email='"+tran_name.esc(email)+"'"
                          " WHERE client_id='" + tran_name.esc(string_id) + "' ";

     tran_name.exec(select);
     tran_name.commit();

}

void ClientManager::AddPhone(const int & id, const string& number){
    pqxx::transaction tran(*con);

    string id_str = to_string(id);
    string select1 = "SELECT first_name FROM CLIENTS"
                     " WHERE client_id = "  + id_str +";";
    auto result = tran.exec(select1);
    tran.commit();

    if(result.size() > 0){
     pqxx::transaction tran1(*con);
     string select2 ="INSERT INTO PHONES(client_id, phone_number)"
                     "VALUES('" +id_str+"', '" +number+"')";
    cout << "Phone was added\n";
    tran1.exec(select2);
    tran1.commit();
    }else{
        cout << "That guy not exists\n";
    }

}

void ClientManager::DeletePhone(const string& number) {
    pqxx::transaction tran(*con);
    string select = "UPDATE PHONES SET "
                    "phone_number=NULL "
                    "WHERE phone_number='" + tran.esc(number)+ "';";
    cout << "NUmber removed\n";
    tran.exec(select);
    tran.commit();
}

void ClientManager::RemoveClient(const int & id) {
    pqxx::transaction tran(*con);
    string id_string = to_string(id);
    string select = "DELETE FROM CLIENTS WHERE client_id='"+id_string+"';";

    tran.exec(select);
    tran.commit();
}

ClientData ClientManager::FindClient(const string& SearchValue) {
    pqxx::work txn(*con);

    std::string select = "SELECT first_name, last_name, email FROM CLIENTS "
                         "WHERE first_name ILIKE " + txn.quote(SearchValue) + " "
                         "OR email ILIKE " + txn.quote(SearchValue) + " "
                         "OR TRIM(last_name) ILIKE " + txn.quote(SearchValue) + ";";

    pqxx::result result = txn.exec(select);

    ClientData obj;

    if (!result.empty()) {
        const pqxx::row& row = result[0];

        obj.first_name = row["first_name"].c_str();
        obj.last_name = row["last_name"].c_str();
        obj.email = row["email"].c_str();
    } else {
        std::cerr << "The client was not found." << std::endl;
    }

    txn.commit();

    return obj;
}
ClientManager::~ClientManager(){

    delete con;
    con = nullptr;
}
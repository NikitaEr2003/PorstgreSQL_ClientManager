#include "ClientManager.h"


int main()
{
    try {
        ClientManager obj;
        obj.InitDbStructure();
        obj.AddClient("Nikita", "Ivanov", "@gmail.ru");
        obj.AddClient("Dima", "Petrov", "@yandex.ru");
        obj.AddClient("Artem", "White", "@email.ru");
        obj.AddPhone(1, "11111");
        obj.AddPhone(2, "22222");
        obj.AddPhone(3, "33333");
        obj.UpdateDataClient(1, "Anton", "Soldatov", "12@gmail.ru");
        obj.DeletePhone("22222");
        obj.RemoveClient(2);

    auto value = obj.FindClient("12@gmail.ru");
    cout << value;
    } catch(exception &e){
        cerr << e.what() << endl;
    }
    return 0;
}

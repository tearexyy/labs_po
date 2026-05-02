#include "notification.hpp"
#include <cstring>
#include <ctime>

Notification::Notification() : timestamp(time(nullptr)), type(system1){}

Notification sys_notify(const char* message, bool is_seriuos){ // создание системного уведомления
    Notification notification;
    notification.type = system1;
    notification.timestamp = time(nullptr);

    strncpy(notification.systemn.message, message, 255);
    notification.systemn.message[255] = '\0';

    notification.systemn.is_seriuos = is_seriuos;
    
    return notification;
}

Notification instant_notify(const char* contact, const char* text){ // создание мгновенного уведомления
    Notification notification;
    notification.type = instant;
    notification.timestamp = time(nullptr);

    strncpy(notification.instantn.contact, contact, 99);
    notification.instantn.contact[99] = '\0';

    strncpy(notification.instantn.text, text, 255);
    notification.instantn.text[255] = '\0';
    
    return notification;
}

Notification app_notify(const char* app_name, const char* title, const char* text){ // создание уведомления от приложения
    Notification notification;
    notification.type = app;
    notification.timestamp = time(nullptr);
    
    strncpy(notification.appn.app_name, app_name, 99);
    notification.appn.app_name[99] = '\0';

    strncpy(notification.appn.title, title, 199);
    notification.appn.title[199] = '\0';

    strncpy(notification.appn.text, text, 255);
    notification.appn.text[255] = '\0';
    
    return notification;
}

void print_notify(const Notification& notification) {
    char* time_str = ctime(&notification.timestamp); // ctime преобразует кол-во секунд в читаемую строку
    std::cout << "время: " << time_str << "\n";
    
    switch (notification.type) {
        case system1:
            std::cout << "системное уведомление\n";
            std::cout << "сообщение: " << notification.systemn.message << "\n";
            if (notification.systemn.is_seriuos){
                std::cout << "срочное\n";
            }
            else{
                std::cout << "обычное\n";
            }
            break;
            
        case instant:
            std::cout << "мгновенное уведомление\n";
            std::cout << "отправитель: " << notification.instantn.contact << "\n";
            std::cout << "''" << notification.instantn.text << "''\n";
            break;
            
        case app:
            std::cout << "уведомление от приложения\n";
            std::cout << "приложение: " << notification.appn.app_name << "\n";
            std::cout << "заголовок: " << notification.appn.title << "\n";
            std::cout << "''" << notification.appn.text << "''\n";
            break;
    }
}

int count_notifications_by_type(const Notification* array, int size, NotificationType type) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i].type == type) {
            count++;
        }
    }
    return count;
}
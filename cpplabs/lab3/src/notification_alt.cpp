#include "notification_alt.hpp"

BaseNotification::BaseNotification() : timestamp(time(nullptr)) {}
BaseNotification::~BaseNotification() {}
time_t BaseNotification::get_timestamp() const {
    return timestamp;
}
SystemNotification::SystemNotification(const char* msg, bool is_serious) 
    : BaseNotification(), is_serious(is_serious) {
    strncpy(message, msg, 255);
    message[255] = '\0';
}

void SystemNotification::print() const {
    char* time_str = ctime(&timestamp);
    time_str[strlen(time_str) - 1] = '\0';
    
    std::cout << "время: " << time_str << "\n";
    std::cout << "системное уведомление\n";
    std::cout << "сообщение: " << message << "\n";
    if (is_serious) {
        std::cout << "срочное\n";
    } else {
        std::cout << "обычное\n";
    }
}

InstantNotification::InstantNotification(const char* cnt, const char* txt) 
    : BaseNotification() {
    strncpy(contact, cnt, 99);
    contact[99] = '\0';
    strncpy(text, txt, 255);
    text[255] = '\0';
}

void InstantNotification::print() const {
    char* time_str = ctime(&timestamp);
    time_str[strlen(time_str) - 1] = '\0';
    
    std::cout << "время: " << time_str << "\n";
    std::cout << "мгновенное уведомление\n";
    std::cout << "отправитель: " << contact << "\n";
    std::cout << "''" << text << "''\n";
}

AppNotification::AppNotification(const char* app, const char* ttl, const char* txt) 
    : BaseNotification() {
    strncpy(app_name, app, 99);
    app_name[99] = '\0';
    strncpy(title, ttl, 199);
    title[199] = '\0';
    strncpy(text, txt, 255);
    text[255] = '\0';
}

void AppNotification::print() const {
    char* time_str = ctime(&timestamp);
    time_str[strlen(time_str) - 1] = '\0';
    
    std::cout << "время: " << time_str << "\n";
    std::cout << "уведомление от приложения\n";
    std::cout << "приложение: " << app_name << "\n";
    std::cout << "заголовок: " << title << "\n";
    std::cout << "''" << text << "''\n";
}

SystemNotification create_sys_notify(const char* message, bool is_serious) {
    return SystemNotification(message, is_serious);
}

InstantNotification create_instant_notify(const char* contact, const char* text) {
    return InstantNotification(contact, text);
}

AppNotification create_app_notify(const char* app_name, const char* title, const char* text) {
    return AppNotification(app_name, title, text);
}

void print_notify(const BaseNotification* notif) {
    notif->print();
    std::cout << "\n";
}

int count_notifications_by_type(BaseNotification** array, int size, int type) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (type == 0 && dynamic_cast<SystemNotification*>(array[i]) != nullptr) {
            count++;
        } else if (type == 1 && dynamic_cast<InstantNotification*>(array[i]) != nullptr) {
            count++;
        } else if (type == 2 && dynamic_cast<AppNotification*>(array[i]) != nullptr) {
            count++;
        }
    }
    return count;
}
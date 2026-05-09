#include <iostream>
#include <ctime>
#include <cstring>

class BaseNotification {
protected:
    time_t timestamp;
public:
    BaseNotification();
    virtual ~BaseNotification();
    
    virtual void print() const = 0;
    time_t get_timestamp() const;
};

class SystemNotification : public BaseNotification {
    char message[256];
    bool is_serious;
public:
    SystemNotification(const char* msg, bool is_serious);
    virtual void print() const;
};

class InstantNotification : public BaseNotification {
    char contact[100];
    char text[256];
public:
    InstantNotification(const char* contact, const char* text);
    virtual void print() const;
};

class AppNotification : public BaseNotification {
    char app_name[100];
    char title[200];
    char text[256];
public:
    AppNotification(const char* app_name, const char* title, const char* text);
    virtual void print() const;
};

SystemNotification create_sys_notify(const char* message, bool is_serious);
InstantNotification create_instant_notify(const char* contact, const char* text);
AppNotification create_app_notify(const char* app_name, const char* title, const char* text);
void print_notify(const BaseNotification* notif);
int count_notifications_by_type(BaseNotification** array, int size, int type); // type: 0-системные, 1-мгновенные, 2-приложения
#include <iostream>
#include <ctime>

enum NotificationType {
    system1,
    instant,
    app
};

struct Notification {
    time_t timestamp;
    NotificationType type;
    union {
        struct {
            char message[256];
            bool is_seriuos;
        } systemn;
        
        struct {
            char contact[100];
            char text[256];
        } instantn;

        struct {
            char app_name[100];
            char title[200];
            char text[256];
        } appn;
    };
    Notification();
};

Notification sys_notify(const char* message, bool is_seriuos);
Notification instant_notify(const char* contact, const char* text);
Notification app_notify(const char* app_name, const char* title, const char* text);

void print_notify(const Notification& notif);
int count_notifications_by_type(const Notification* array, int size, NotificationType type);
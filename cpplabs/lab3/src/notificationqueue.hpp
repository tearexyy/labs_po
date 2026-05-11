#include "notification.hpp" 

struct QueueNode {
    Notification data;
    QueueNode* next; // след элемент
};

class NotificationQueue {
private:
    QueueNode* start; // первый элемент
    QueueNode* final; //последний элемент
    int count;
    
public:
    NotificationQueue();
    ~NotificationQueue();
    void push(const Notification& notification);
    Notification pop();
    int size() const;
    bool empty() const;
    class Iterator {
    private:
        QueueNode* current;
    public:
        Iterator(QueueNode* node = nullptr); // значение по умолчанию - nullptr
        bool operator!=(const Iterator& other) const;
        Iterator& operator++();
        Notification& operator*();
        Notification* operator->();
    };
    
    Iterator begin();
    Iterator end();
};

class NotificationPriorityQueue {
private:
    QueueNode* start; // первый элемент
    QueueNode* final; // последний элемент
    int count;
    
    bool is_more_serious(const Notification& a, const Notification& b) const; // сравнение актуальности двух уведомлений
    
public:
    NotificationPriorityQueue();
    ~NotificationPriorityQueue();
    int get_priority(NotificationType type, bool is_serious) const;
    void push(const Notification& notification);
    Notification pop();
    int size() const;
    bool empty() const;

    class Iterator {
    private:
        QueueNode* current;
    public:
        Iterator(QueueNode* node = nullptr);
        bool operator!=(const Iterator& other) const;
        Iterator& operator++();
        Notification& operator*();
        Notification* operator->();
    };
    
    Iterator begin();
    Iterator end();
};
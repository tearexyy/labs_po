#include "notificationqueue.hpp"

NotificationQueue::NotificationQueue() : start(nullptr), final(nullptr), count(0) {}

NotificationQueue::~NotificationQueue() {
    while (!empty()) {
        pop(); // удаляет вск элементы в очереди
    }
}

void NotificationQueue::push(const Notification& notification) {
    QueueNode* new_node = new QueueNode;
    new_node->data = notification; // копирование данных
    new_node->next = nullptr;
    
    if (final == nullptr) {
        start = final = new_node; // если очередь пуста, start и final указывают на новый узел
    } else {
        final->next = new_node;
        final = new_node; // если не пуста, добавление нового узла в конец очереди
    }
    count++;
}

Notification NotificationQueue::pop() {
    if (start == nullptr) {
        throw "очередь пуста";
    }
    
    QueueNode* temp = start;
    Notification result = start->data; // сохранение данных для возврата
    
    start = start->next; // теперь start указывает на след. элемент
    if (start == nullptr) {
        final = nullptr;
    }
    
    delete temp;
    count--;
    return result;
}
int NotificationQueue::size() const { // кол-во элементов
    return count;
}

bool NotificationQueue::empty() const { // если пусто
    return count == 0;
}

NotificationQueue::Iterator::Iterator(QueueNode* node) : current(node) {} // констурктор

bool NotificationQueue::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

NotificationQueue::Iterator& NotificationQueue::Iterator::operator++() {
    if (current != nullptr) {
        current = current->next; // переход к следующему элементу
    }
    return *this; // ссылка на след. (уже текущий) элемент
}

Notification& NotificationQueue::Iterator::operator*() {
    return current->data;
}

Notification* NotificationQueue::Iterator::operator->() {
    return &current->data;
}
NotificationQueue::Iterator NotificationQueue::begin() {
    return Iterator(start);
}
NotificationQueue::Iterator NotificationQueue::end() {
    return Iterator(nullptr);
}




NotificationPriorityQueue::NotificationPriorityQueue(): start(nullptr), final(nullptr), count(0) {}

NotificationPriorityQueue::~NotificationPriorityQueue() {
    while (!empty()) {
        pop();
    }
}

bool NotificationPriorityQueue::is_more_serious(const Notification& a, const Notification& b) const { // сравнение актуальности
    bool a_is_serious_system = (a.type == system1 && a.systemn.is_seriuos); // оба уведомления системные
    bool b_is_serious_system = (b.type == system1 && b.systemn.is_seriuos); // сначала проверяются срочные системные уведомления,
                                                                            // тк они важнее
    
    if (a_is_serious_system && !b_is_serious_system) return true;
    if (!a_is_serious_system && b_is_serious_system) return false;
    // если они одинакового приоритета, необходимо сравнивать по времени и типу

    int a_priority = get_priority(a.type, a.systemn.is_seriuos);
    int b_priority = get_priority(b.type, b.systemn.is_seriuos);
    
    if (a_priority != b_priority) {
        return a_priority > b_priority;
    }
    // если одинаковые по приоритету, сравниваем по времени
    return a.timestamp < b.timestamp;  // актуальнее то, что раньше пришло
}


int NotificationPriorityQueue::get_priority(NotificationType type, bool is_serious) const{
    if (type == instant) {
        return 3;
    }
    if (type == system1 && is_serious) {
        return 4;
    }
    if (type == system1) {
        return 2;
    }
    return 1;
}

void NotificationPriorityQueue::push(const Notification& notification) {
    QueueNode* new_node = new QueueNode;
    new_node->data = notification; // копирование данных
    new_node->next = nullptr; // ставим в конец
    
    if (start == nullptr) {
        start = final = new_node;
    } else {
        final->next = new_node;
        final = new_node;
    }
    count++;
}

Notification NotificationPriorityQueue::pop() {
    if (start == nullptr) {
        throw "очередь пуста";
    }
    
    QueueNode* prev_most_urgent = nullptr; // предыдущий перед самым актуальным
    QueueNode* most_serious = start; // считаем первый самым актуальным
    QueueNode* prev = nullptr; // предыдущий узел 
    QueueNode* current = start; // текущий узел 
    
    while (current != nullptr) {
        if (is_more_serious(current->data, most_serious->data)) {
            most_serious = current; // если нашли более актуальный
            prev_most_urgent = prev; // необходимо запомнить предыдущий
        }
        prev = current;
        current = current->next;
    }
    
    Notification result = most_serious->data; // сохранение данных
    
    if (prev_most_urgent != nullptr) { // удаляем самое актуальное
        prev_most_urgent->next = most_serious->next;
    } else {
        start = most_serious->next;
    }
    
    if (most_serious == final) {
        final = prev_most_urgent; // если был удален последний элемент, надо обновить final
    }
    
    delete most_serious;
    count--;
    
    return result;
}

int NotificationPriorityQueue::size() const {
    return count;
}

bool NotificationPriorityQueue::empty() const {
    return count == 0;
}

NotificationPriorityQueue::Iterator::Iterator(QueueNode* node) : current(node) {}

bool NotificationPriorityQueue::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

NotificationPriorityQueue::Iterator& NotificationPriorityQueue::Iterator::operator++() {
    if (current != nullptr) {
        current = current->next;
    }
    return *this;
}

Notification& NotificationPriorityQueue::Iterator::operator*() {
    return current->data;
}

Notification* NotificationPriorityQueue::Iterator::operator->() {
    return &current->data;
}

NotificationPriorityQueue::Iterator NotificationPriorityQueue::begin() {
    return Iterator(start);
}

NotificationPriorityQueue::Iterator NotificationPriorityQueue::end() {
    return Iterator(nullptr);
}
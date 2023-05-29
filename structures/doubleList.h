// codigo de la tarea anterior hecha por nosotros

#include <iostream>
#include "list.h"

template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
        Node() {}
        Node(T value): data(value) {}
        ~Node() {}
    };

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int nodes;

public:
    DoubleList() : List<T>(), nodes(0) {}

    ~DoubleList() {  delete head, tail; };

    T front() {
       if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T back() {
      if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    void push_front(T data) {
        Node *new_node = new Node(data);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        ++nodes;
    }

    void push_back(T data) {
        Node *new_node = new Node(data);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        ++nodes;
    }

    T pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        T data = head->data;
        if (head->next == nullptr)
            head == tail == nullptr;

        else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            --nodes;
        }
        return data;
    }

    T pop_back() {
        if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        T data = tail->data;
        if (tail->prev == nullptr)
            head == tail == nullptr;

        else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            --nodes;
        }
        return data;
    }

    void insert(T value, int index=0) {
        if (index < 0 || index >= nodes) {
            throw std::out_of_range("Index out of range");
        }
        else if (index == 0) {
            push_front(value);       return;
        }

        Node* new_node = new Node(value);
        if (head == nullptr)         head = new_node;

        else {
            Node* temp;
            if (index+1 > nodes/2) {
                temp = tail;
                while (index-- > nodes/2)
                    temp = temp->prev;
            }
            else {
                temp = head;
                while (index-- > 0)
                    temp = temp->next;
            }
            new_node->next = temp;
            new_node->prev = temp->prev;
            temp->prev->next = new_node;
            temp->prev = new_node;
            ++nodes;
        }
    }

    void remove(int pos) {
        if (is_empty() || pos<0 || pos>=nodes) {
            throw std::out_of_range("Index out of range");
        }
        if (pos == 0) {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        else if (pos == nodes-1) {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        else {
            Node* temp = head;
            while (pos-- > 0)
                temp = temp->next;

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
        --nodes;
    }

    T &operator[](int pos) {
        Node *current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->data;
    }

    bool is_empty() {
        return (head == nullptr && tail == nullptr);
    }

    int size() {
        return nodes;
    }

    void clear() {
        while (head != nullptr) {
            pop_front();
        }
    }

    void sort() {
        for (int i = 0; i < nodes - 1; i++) {
            Node *current = head;
            for (int j = 0; j < nodes - 1 - i; j++) {
                if (current->data > current->next->data) {
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                }
                current = current->next;
            }
        }
    }

    bool is_sorted() {
        Node *current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->data > current->next->data) {
                return false;
            }
            current = current->next;
        }
        return true;
    }


    std::string name() {
        return "DoubleList";
    }

    Node *begin() {
        return head;
    }

    Node *end() {
        return tail;
    }
};
//! Copyright [2022] <PABLO LOPES TEIXEIRA>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class LinkedList {
 public:
    LinkedList(); 
    
    ~LinkedList();  
    
    void clear(); 
    
    void push_back(const T& data); 
    
    void push_front(const T& data); 
    
    void insert(const T& data, std::size_t index); 
   
    void insert_sorted(const T& data); 
   
    
    T pop(std::size_t index);  
    
    T pop_back(); 
   
    T pop_front();  
    //! ...
    void remove(const T& data); 
    
    bool empty() const; 
    
    bool contains(const T& data) const;  
    
    std::size_t find(const T& data) const; 
    
    std::size_t size() const;  
    
 private:
    class Node { 
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() { 
            return data_;
        }

        const T& data() const { 
            return data_;
        }

        Node* next() {  
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
    std::size_t initial{0u};
};

}

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() {
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while (size()) {
        pop_front();
    }
    head = nullptr;
    size_ = 0u;
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    if (size() == 0) {
        push_front(data);
    } else {
        Node* ptr_back = new Node(data, nullptr);
        Node* ptr = head;
        while (ptr->next() != nullptr) {
            ptr = ptr->next();
        }
        ptr->next(ptr_back);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* ptr_front = new Node(data, head);
    head = ptr_front;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size() || index < 0) {
        throw std::out_of_range("Index maior que o tamanho!");
    } else if (index == size()) {
        push_back(data);
    } else if (index == 0) {
        push_front(data);
    } else {
        Node* ptr_insert = new Node(data);
        Node* ptr = head;
        for (auto i = initial; i < index - 1; i++) {
            ptr = ptr->next();
        }
        ptr_insert->next(ptr->next());
        ptr->next(ptr_insert);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (size() == 0) {
        push_front(data);
    } else {
        Node* ptr = head;
        for (auto i = initial; i < size(); i++) {
            if (data < ptr->data()) {
                if (i == 0) {
                    push_front(data);
                } else {
                    insert(data, i);
                }
                break;
            } else if (ptr->next() == nullptr) {
                push_back(data);
                break;
            } else {
                ptr = ptr->next();
            }
        }
    }
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index >= size()) {
        throw std::out_of_range("Index fora de escopo");
    } else {
        Node* ptr = head;
        for (auto i = initial; i < index; i++) {
            ptr = ptr->next();
        }
        return ptr->data();
    }
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (size() == 0) {
        throw std::out_of_range("Index fora de escopo");
    } else {
        if (size() == 1) {
            Node* ptr = head;
            T data_removed = ptr->data();
            head = nullptr;
            delete ptr;
            size_--;
            return data_removed;
        } else {
            Node* ptr = head;
            for (auto i = 1u; i < size() - 1; i++) {
                ptr = ptr->next();
            }
            Node* ptr_removed = ptr->next();
            T data_removed = ptr_removed->data();
            ptr->next(nullptr);
            delete ptr_removed;
            size_--;
            return data_removed;
        }
    }
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (size() == 0) {
        throw std::out_of_range("Index fora de escopo");
    } else {
        Node* ptr = head;
        head = ptr->next();
        T data_removed = ptr->data();
        delete ptr;
        size_--;
        return data_removed;
    }
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (index < 0 || index > size() - 1) {
        throw std::out_of_range("Index fora de escopo");
    } else if (index == 0) {
        pop_front();
    } else if (index == size() - 1) {
        pop_back();
    } else {
        Node* ptr = head;
        for (auto i = 1u; i < index; i++) {
            ptr = ptr->next();
        }
        Node* ptr_removed = ptr->next();
        ptr->next(ptr_removed->next());
        T data_removed = ptr_removed->data();
        delete ptr_removed;
        size_--;
        return data_removed;
    }
    return 1;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    Node* ptr = head;
    Node* ptr_h = nullptr;
    for (auto i = 1u; i < size() - 1; i++) {
        if (ptr->data() == data) {
            if (ptr_h != nullptr) {
                ptr_h->next(ptr->next());
            } else {
                head = nullptr;
            }
            delete ptr;
            size_--;
        } else {
            ptr_h = ptr;
            ptr = ptr->next();
        }
    }
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    Node* ptr = head;
    for (auto i = initial; i < size(); i++) {
        if (ptr->data() == data) {
            return true;
        }
        ptr = ptr->next();
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* ptr = head;
    for (auto i = initial; i < size(); i++) {
        if (ptr->data() == data) {
            return i;
        }
        ptr = ptr->next();
    }
    return size();
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

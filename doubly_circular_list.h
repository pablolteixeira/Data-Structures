// "Copyright [2022] <PABLO LOPES TEIXEIRA>"
namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_ = data;
        }
        Node(Node* prev, Node* next) {
            prev_ = prev;
            next_ = next;
        }
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }
        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
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
        Node* prev_;
        Node* next_;
    };

    Node* head;
    Node* sentinela;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    sentinela = new Node(nullptr, nullptr);
    sentinela->next(sentinela);
    sentinela->prev(sentinela);
    head = sentinela;
    size_ = 0;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
    delete sentinela;
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    Node* ptr = head->next();
    Node* aux = nullptr;

    while (ptr != head) {
        aux = ptr;
        ptr = ptr->next();
        size_--;
        delete aux;
    }

    head->next(head);
    head->prev(head);
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* last = head->prev();
    Node* ptr_push = new Node(data, last, head);
    last->next(ptr_push);
    head->prev(ptr_push);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* first = head->next();
    Node* ptr_push = new Node(data, head, head->next());
    first->prev(ptr_push);
    head->next(ptr_push);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::
insert(const T& data, std::size_t index) {
    if (index < 0 || index > size()) {
        throw std::out_of_range("Index out of range!");
    } else if (index == 0) {
        push_front(data);
    } else if (index == size()) {
        push_back(data);
    } else {
        Node* ptr = head;

        for (auto i = 0u; i < index; ++i) {
            ptr = ptr->next();
        }
        Node* ptr_inserted = new Node(data, ptr, ptr->next());
        ptr->next()->prev(ptr_inserted);
        ptr->next(ptr_inserted);
        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    Node* ptr = head->next();
    auto i = 0u;
    while (ptr != head) {
        if (ptr->data() > data) {
            break;
        }
        ptr = ptr->next();
        i++;
    }
    insert(data, i);
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    } else {
        Node* ptr_pop = head->prev();
        T data = ptr_pop->data();

        ptr_pop->prev()->next(head);
        head->prev(ptr_pop->prev());

        size_--;

        delete ptr_pop;
        return data;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    } else {
        Node* ptr_pop = head->next();
        T data = ptr_pop->data();

        ptr_pop->next()->prev(head);
        head->next(ptr_pop->next());

        size_--;

        delete ptr_pop;
        return data;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (index < 0 || index >= size()) {
        throw std::out_of_range("Index out of range!");
    } else if (index == 0) {
        pop_front();
    } else if (index == size() - 1) {
        pop_back();
    } else {
        Node* ptr_pop = head;

        for (auto i = 0u; i <= index; ++i) {
            ptr_pop = ptr_pop->next();
        }
        ptr_pop->prev()->next(ptr_pop->next());
        ptr_pop->next()->prev(ptr_pop->prev());

        T data = ptr_pop->data();
        size_--;

        delete ptr_pop;
        return data;
    }
    return 0;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    Node* ptr = head->next();

    while (ptr != head) {
        if (ptr->data() == data) {
            break;
        }
        ptr = ptr->next();
    }

    if (ptr != head) {
        ptr->prev()->next(ptr->next());
        ptr->next()->prev(ptr->prev());

        delete ptr;
        size_--;
    }
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    bool contain = false;
    Node* ptr = head->next();

    while (ptr != head) {
        if (ptr->data() == data) {
            contain = true;
            break;
        }
        ptr = ptr->next();
    }

    return contain;
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (index < 0 || index > size()) {
        throw std::out_of_range("Index out of range!");
    } else {
        Node* ptr = head->next();

        for (auto i = 0u; i < index; ++i) {
            ptr = ptr->next();
        }
        return ptr->data();
    }
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (index < 0 || index > size()) {
        throw std::out_of_range("Index out of range!");
    } else {
        Node* ptr = head->next();

        for (auto i = 0u; i <= index; ++i) {
            ptr = ptr->next();
        }

        return ptr->data();
    }
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node* ptr = head->next();

    auto i = 0u;

    while (ptr != head) {
        if (ptr->data() == data) {
            break;
        }
        ptr = ptr->next();
        i++;
    }

    return i;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}

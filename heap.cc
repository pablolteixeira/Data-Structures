// Copyright [2018] <PABLO LOPES TEIXEIRA>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class ArrayQueue {
 public:
    ArrayQueue();
    explicit ArrayQueue(std::size_t max);
    ~ArrayQueue();
    void enqueue(const T& data);
    T dequeue();
    T& back();
    void clear();
    std::size_t size();
    std::size_t max_size();
    bool empty();
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  
    int end_;  
    int quant_;
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    size_ = 0;
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    size_ = 0;
    max_size_ = max;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    } else {
        end_ = (end_ + 1) % max_size_;
        size_++;
        contents[end_] = data;
    }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
         size_--;
         int v = begin_;
         begin_ = (begin_ + 1) % max_size_;
         return contents[v];
    }
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return contents[end_];
    }
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return size_ == 0;
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    return size_ == max_size_;
}

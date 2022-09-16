// Copyright [2022] <PABLO LOPES TEIXEIRA>
#include <string>
#include "./array_queue.h"

structures::ArrayQueue<char> editaTexto(std::string texto) {
    structures::ArrayQueue<char> fila(500);
    for (int i = 0; i < static_cast<int>(texto.length()); i++) {
        if (texto[i] == '<') {
            fila.dequeue();
        } else if (texto[i] == '>') {
            fila.enqueue(fila.back());
        } else {
            fila.enqueue(texto[i]);
        }
    }

    return fila;
}

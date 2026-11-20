
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

template <class T>
class Stack {
private:
    // Node cua Stack
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& giaTri) {
            data = giaTri;
            next = nullptr;
        }
    };

    Node* topNode;
    int soLuong;

public:
    // ================= CONSTRUCTOR =================

    Stack() {
        topNode = nullptr;
        soLuong = 0;
    }

    // Copy constructor
    Stack(const Stack& other) {
        topNode = nullptr;
        soLuong = 0;

        // Tao Stack tam de giu nguyen thu tu
        Stack<T> tam;

        Node* p = other.topNode;

        while (p != nullptr) {
            tam.push(p->data);
            p = p->next;
        }

        // Chuyen tu Stack tam sang Stack moi
        while (!tam.rong()) {
            push(tam.pop());
        }
    }

    // ================= DESTRUCTOR =================

    ~Stack() {
        xoaTatCa();
    }

    // ================= TOAN TU GAN =================

    Stack& operator=(const Stack& other) {
        if (this == &other) {
            return *this;
        }

        xoaTatCa();

        Stack<T> tam;

        Node* p = other.topNode;

        while (p != nullptr) {
            tam.push(p->data);
            p = p->next;
        }

        while (!tam.rong()) {
            push(tam.pop());
        }

        return *this;
    }

    // ================= KIEM TRA =================

    bool rong() const {
        return topNode == nullptr;
    }

    int getSoLuong() const {
        return soLuong;
    }

    // ================= THEM PHAN TU =================

    // Them phan tu vao Stack
    void push(const T& giaTri) {
        Node* nodeMoi = new Node(giaTri);

        nodeMoi->next = topNode;
        topNode = nodeMoi;

        soLuong++;
    }

    // ================= LAY PHAN TU =================

    // Lay va xoa phan tu tren cung
    T pop() {
        if (rong()) {
            throw std::runtime_error("Stack rong!");
        }

        Node* nodeXoa = topNode;
        T giaTri = nodeXoa->data;

        topNode = topNode->next;

        delete nodeXoa;
        soLuong--;

        return giaTri;
    }

    // Lay phan tu tren cung nhung khong xoa
    T& top() {
        if (rong()) {
            throw std::runtime_error("Stack rong!");
        }

        return topNode->data;
    }

    // Lay phan tu tren cung (const)
    const T& top() const {
        if (rong()) {
            throw std::runtime_error("Stack rong!");
        }

        return topNode->data;
    }

    // ================= HIEN THI =================

    void hienThi() const {
        if (rong()) {
            std::cout << "Stack rong!\n";
            return;
        }

        Node* p = topNode;
        int stt = 1;

        std::cout << "Cac phan tu trong Stack:\n";

        while (p != nullptr) {
            std::cout << stt << ". " << p->data << '\n';

            p = p->next;
            stt++;
        }
    }

    // ================= XOA TOAN BO =================

    void xoaTatCa() {
        Node* p = topNode;

        while (p != nullptr) {
            Node* nodeXoa = p;
            p = p->next;

            delete nodeXoa;
        }

        topNode = nullptr;
        soLuong = 0;
    }
};

#endif

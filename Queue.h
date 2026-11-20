
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

template <class T>
class Queue {
private:
    // Node cua Queue
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& giaTri) {
            data = giaTri;
            next = nullptr;
        }
    };

    Node* frontNode;
    Node* rearNode;
    int soLuong;

public:
    // ================= CONSTRUCTOR =================

    Queue() {
        frontNode = nullptr;
        rearNode = nullptr;
        soLuong = 0;
    }

    // Copy constructor
    Queue(const Queue& other) {
        frontNode = nullptr;
        rearNode = nullptr;
        soLuong = 0;

        Node* p = other.frontNode;

        while (p != nullptr) {
            enqueue(p->data);
            p = p->next;
        }
    }

    // ================= DESTRUCTOR =================

    ~Queue() {
        xoaTatCa();
    }

    // ================= TOAN TU GAN =================

    Queue& operator=(const Queue& other) {
        if (this == &other) {
            return *this;
        }

        xoaTatCa();

        Node* p = other.frontNode;

        while (p != nullptr) {
            enqueue(p->data);
            p = p->next;
        }

        return *this;
    }

    // ================= KIEM TRA =================

    bool rong() const {
        return frontNode == nullptr;
    }

    int getSoLuong() const {
        return soLuong;
    }

    // ================= THEM PHAN TU =================

    // Them phan tu vao cuoi Queue
    void enqueue(const T& giaTri) {
        Node* nodeMoi = new Node(giaTri);

        if (rong()) {
            frontNode = rearNode = nodeMoi;
        }
        else {
            rearNode->next = nodeMoi;
            rearNode = nodeMoi;
        }

        soLuong++;
    }

    // ================= LAY PHAN TU =================

    // Lay va xoa phan tu dau Queue
    T dequeue() {
        if (rong()) {
            throw std::runtime_error("Queue rong!");
        }

        Node* nodeXoa = frontNode;
        T giaTri = nodeXoa->data;

        frontNode = frontNode->next;

        if (frontNode == nullptr) {
            rearNode = nullptr;
        }

        delete nodeXoa;
        soLuong--;

        return giaTri;
    }

    // Xem phan tu dau Queue
    T& front() {
        if (rong()) {
            throw std::runtime_error("Queue rong!");
        }

        return frontNode->data;
    }

    // Xem phan tu dau Queue (const)
    const T& front() const {
        if (rong()) {
            throw std::runtime_error("Queue rong!");
        }

        return frontNode->data;
    }

    // Xem phan tu cuoi Queue
    T& rear() {
        if (rong()) {
            throw std::runtime_error("Queue rong!");
        }

        return rearNode->data;
    }

    // Xem phan tu cuoi Queue (const)
    const T& rear() const {
        if (rong()) {
            throw std::runtime_error("Queue rong!");
        }

        return rearNode->data;
    }

    // ================= HIEN THI =================

    void hienThi() const {
        if (rong()) {
            std::cout << "Queue rong!\n";
            return;
        }

        Node* p = frontNode;
        int stt = 1;

        std::cout << "Cac phan tu trong Queue:\n";

        while (p != nullptr) {
            std::cout << stt << ". " << p->data << '\n';

            p = p->next;
            stt++;
        }
    }

    // ================= XOA TOAN BO =================

    void xoaTatCa() {
        Node* p = frontNode;

        while (p != nullptr) {
            Node* nodeXoa = p;
            p = p->next;

            delete nodeXoa;
        }

        frontNode = nullptr;
        rearNode = nullptr;
        soLuong = 0;
    }
};

#endif

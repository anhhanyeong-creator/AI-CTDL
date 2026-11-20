
#ifndef DANH_SACH_LIEN_KET_H
#define DANH_SACH_LIEN_KET_H

#include <iostream>
#include <stdexcept>
#include <functional>

template <class T>
class DanhSachLienKet {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& giaTri) {
            data = giaTri;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int soLuong;

public:
    DanhSachLienKet() {
        head = nullptr;
        tail = nullptr;
        soLuong = 0;
    }

    DanhSachLienKet(const DanhSachLienKet& other) {
        head = nullptr;
        tail = nullptr;
        soLuong = 0;

        Node* p = other.head;

        while (p != nullptr) {
            themCuoi(p->data);
            p = p->next;
        }
    }

    ~DanhSachLienKet() {
        xoaTatCa();
    }

    DanhSachLienKet& operator=(const DanhSachLienKet& other) {
        if (this == &other) {
            return *this;
        }

        xoaTatCa();

        Node* p = other.head;

        while (p != nullptr) {
            themCuoi(p->data);
            p = p->next;
        }

        return *this;
    }

    bool rong() const {
        return head == nullptr;
    }

    int getSoLuong() const {
        return soLuong;
    }

    // Them vao dau danh sach
    void themDau(const T& giaTri) {
        Node* nodeMoi = new Node(giaTri);

        nodeMoi->next = head;
        head = nodeMoi;

        if (tail == nullptr) {
            tail = nodeMoi;
        }

        soLuong++;
    }

    // Them vao cuoi danh sach
    void themCuoi(const T& giaTri) {
        Node* nodeMoi = new Node(giaTri);

        if (rong()) {
            head = tail = nodeMoi;
        }
        else {
            tail->next = nodeMoi;
            tail = nodeMoi;
        }

        soLuong++;
    }

    // Lay phan tu tai vi tri index
    T* getTai(int index) {
        if (index < 0 || index >= soLuong) {
            return nullptr;
        }

        Node* p = head;

        for (int i = 0; i < index; i++) {
            p = p->next;
        }

        return &(p->data);
    }

    // Lay phan tu tai vi tri index (const)
    const T* getTai(int index) const {
        if (index < 0 || index >= soLuong) {
            return nullptr;
        }

        Node* p = head;

        for (int i = 0; i < index; i++) {
            p = p->next;
        }

        return &(p->data);
    }

    // Tim phan tu theo dieu kien
    T* timKiem(const std::function<bool(const T&)>& dieuKien) {
        Node* p = head;

        while (p != nullptr) {
            if (dieuKien(p->data)) {
                return &(p->data);
            }

            p = p->next;
        }

        return nullptr;
    }

    // Tim phan tu theo dieu kien (const)
    const T* timKiem(
        const std::function<bool(const T&)>& dieuKien
    ) const {
        Node* p = head;

        while (p != nullptr) {
            if (dieuKien(p->data)) {
                return &(p->data);
            }

            p = p->next;
        }

        return nullptr;
    }

    // Xoa phan tu tai vi tri
    bool xoaTai(int index) {
        if (index < 0 || index >= soLuong) {
            return false;
        }

        Node* nodeXoa = nullptr;

        // Xoa node dau
        if (index == 0) {
            nodeXoa = head;
            head = head->next;

            if (head == nullptr) {
                tail = nullptr;
            }
        }
        else {
            Node* truoc = head;

            for (int i = 0; i < index - 1; i++) {
                truoc = truoc->next;
            }

            nodeXoa = truoc->next;
            truoc->next = nodeXoa->next;

            // Neu xoa node cuoi
            if (nodeXoa == tail) {
                tail = truoc;
            }
        }

        delete nodeXoa;
        soLuong--;

        return true;
    }

    // Xoa phan tu dau
    bool xoaDau() {
        if (rong()) {
            return false;
        }

        return xoaTai(0);
    }

    // Xoa phan tu cuoi
    bool xoaCuoi() {
        if (rong()) {
            return false;
        }

        return xoaTai(soLuong - 1);
    }


    void duyet(
        const std::function<void(const T&)>& hamXuLy
    ) const {
        Node* p = head;

        while (p != nullptr) {
            hamXuLy(p->data);
            p = p->next;
        }
    }

    // Hien thi danh sach
    void hienThi() const {
        if (rong()) {
            std::cout << "Danh sach rong!\n";
            return;
        }

        Node* p = head;
        int stt = 1;

        while (p != nullptr) {
            std::cout << stt << ". " << p->data << '\n';

            p = p->next;
            stt++;
        }
    }


    void xoaTatCa() {
        Node* p = head;

        while (p != nullptr) {
            Node* nodeXoa = p;
            p = p->next;

            delete nodeXoa;
        }

        head = nullptr;
        tail = nullptr;
        soLuong = 0;
    }
};

#endif

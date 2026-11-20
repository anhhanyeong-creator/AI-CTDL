
#ifndef CAY_TIM_KIEM_NHAN_VIEN_H
#define CAY_TIM_KIEM_NHAN_VIEN_H

#include "NhanVien.h"
#include <iostream>
#include <string>

class CayTimKiemNhanVien {
private:
    // Node cua cay BST
    class Node {
    public:
        std::string username;
        NhanVien data;

        Node* left;
        Node* right;

        Node(const std::string& username, const NhanVien& nv) {
            this->username = username;
            data = nv;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;
    int soLuong;

    // ================= THEM NODE =================

    Node* themNode(
        Node* node,
        const std::string& username,
        const NhanVien& nv
    ) {
        if (node == nullptr) {
            soLuong++;
            return new Node(username, nv);
        }

        if (username < node->username) {
            node->left = themNode(node->left, username, nv);
        }
        else if (username > node->username) {
            node->right = themNode(node->right, username, nv);
        }

        return node;
    }

    // ================= TIM NODE =================

    Node* timNode(
        Node* node,
        const std::string& username
    ) const {
        if (node == nullptr || node->username == username) {
            return node;
        }

        if (username < node->username) {
            return timNode(node->left, username);
        }

        return timNode(node->right, username);
    }

    // ================= TIM NODE NHO NHAT =================

    Node* timNodeNhoNhat(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        while (node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    // ================= XOA NODE =================

    Node* xoaNode(
        Node* node,
        const std::string& username
    ) {
        if (node == nullptr) {
            return nullptr;
        }

        if (username < node->username) {
            node->left = xoaNode(node->left, username);
        }
        else if (username > node->username) {
            node->right = xoaNode(node->right, username);
        }
        else {
            // Node khong co con
            if (node->left == nullptr &&
                node->right == nullptr) {

                delete node;
                soLuong--;

                return nullptr;
            }

            // Node chi co con phai
            if (node->left == nullptr) {
                Node* temp = node->right;

                delete node;
                soLuong--;

                return temp;
            }

            // Node chi co con trai
            if (node->right == nullptr) {
                Node* temp = node->left;

                delete node;
                soLuong--;

                return temp;
            }

            // Node co hai con
            Node* temp = timNodeNhoNhat(node->right);

            node->username = temp->username;
            node->data = temp->data;

            node->right = xoaNode(
                node->right,
                temp->username
            );
        }

        return node;
    }

    // ================= DUYET LNR =================

    void duyetLNR(Node* node) const {
        if (node == nullptr) {
            return;
        }

        duyetLNR(node->left);

        std::cout << node->data << '\n';

        duyetLNR(node->right);
    }

    // ================= XOA TOAN BO CAY =================

    void xoaCay(Node* node) {
        if (node == nullptr) {
            return;
        }

        xoaCay(node->left);
        xoaCay(node->right);

        delete node;
    }

public:
    // ================= CONSTRUCTOR =================

    CayTimKiemNhanVien() {
        root = nullptr;
        soLuong = 0;
    }

    // ================= DESTRUCTOR =================

    ~CayTimKiemNhanVien() {
        xoaTatCa();
    }

    // ================= KIEM TRA =================

    bool rong() const {
        return root == nullptr;
    }

    int getSoLuong() const {
        return soLuong;
    }

    // ================= THEM NHAN VIEN =================

    bool themNhanVien(
        const std::string& username,
        const NhanVien& nv
    ) {
        if (timNode(root, username) != nullptr) {
            return false;
        }

        root = themNode(root, username, nv);

        return true;
    }

    // ================= TIM NHAN VIEN =================

    NhanVien* timNhanVien(
        const std::string& username
    ) {
        Node* node = timNode(root, username);

        if (node == nullptr) {
            return nullptr;
        }

        return &(node->data);
    }

    const NhanVien* timNhanVien(
        const std::string& username
    ) const {
        Node* node = timNode(root, username);

        if (node == nullptr) {
            return nullptr;
        }

        return &(node->data);
    }

    // ================= XOA NHAN VIEN =================

    bool xoaNhanVien(
        const std::string& username
    ) {
        if (timNode(root, username) == nullptr) {
            return false;
        }

        root = xoaNode(root, username);

        return true;
    }

    // ================= DUYET CAY =================

    void hienThiLNR() const {
        if (rong()) {
            std::cout << "Cay rong!\n";
            return;
        }

        std::cout << "Danh sach nhan vien theo username:\n";

        duyetLNR(root);
    }

    // ================= XOA TOAN BO =================
    void xoaTatCa() {
        xoaCay(root);

        root = nullptr;
        soLuong = 0;
    }
};

#endif


#ifndef NHAN_VIEN_H
#define NHAN_VIEN_H

#include "NguoiDung.h"
#include <iostream>
#include <string>

class NhanVien : public NguoiDung {
private:
    std::string hoTen;
    std::string diaChi;
    std::string soDienThoai;
    std::string email;

public:
    // Constructor
    NhanVien();
    explicit NhanVien(const TaiKhoan& tk);

    NhanVien(
        const TaiKhoan& tk,
        const std::string& hoTen,
        const std::string& diaChi,
        const std::string& soDienThoai,
        const std::string& email
    );

    // Copy constructor
    NhanVien(const NhanVien& other);

    // Destructor
    ~NhanVien() override;

    // Getter
    std::string getHoTen() const;
    std::string getDiaChi() const;
    std::string getSoDienThoai() const;
    std::string getEmail() const;

    // Setter
    void setHoTen(const std::string& hoTen);
    void setDiaChi(const std::string& diaChi);
    void setSoDienThoai(const std::string& soDienThoai);
    void setEmail(const std::string& email);

    // Hien thi thong tin
    void hienThiThongTin() const;

    // Phuong thuc ao
    void hienThiMenu() const override;
    std::string getVaiTro() const override;

    // Doc va ghi file
    bool docThongTin(const std::string& path);
    bool ghiThongTin(const std::string& path) const;

    // Toan tu nhap/xuat
    friend std::ostream& operator<<(
        std::ostream& out,
        const NhanVien& nv
    );

    friend std::istream& operator>>(
        std::istream& in,
        NhanVien& nv
    );
};

#endif

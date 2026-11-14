#ifndef NHAN_VIEN_H
#define NHAN_VIEN_H
#include "NguoiDung.h"
#include <iostream>
class NhanVien:public NguoiDung{
private: std::string hoTen,diaChi,soDienThoai,email;
public:
    NhanVien(); explicit NhanVien(const TaiKhoan& tk);
    NhanVien(const TaiKhoan& tk,const std::string& hoTen,const std::string& diaChi,const std::string& sdt,const std::string& email);
    NhanVien(const NhanVien& other); ~NhanVien() override;
    std::string getHoTen()const; std::string getDiaChi()const; std::string getSoDienThoai()const; std::string getEmail()const;
    void setHoTen(const std::string& x); void setDiaChi(const std::string& x); void setSoDienThoai(const std::string& x); void setEmail(const std::string& x);
    void hienThiThongTin()const; void hienThiMenu()const override; std::string getVaiTro()const override;
    bool docThongTin(const std::string& path); bool ghiThongTin(const std::string& path)const;
    friend std::ostream& operator<<(std::ostream& out,const NhanVien& nv);
    friend std::istream& operator>>(std::istream& in,NhanVien& nv);
};
#endif

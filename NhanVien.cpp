#include "NhanVien.h"
#include "GiaoDien.h"
#include <fstream>
#include <iostream>
#include <string>
NhanVien::NhanVien()
    :NguoiDung(),
     hoTen(""),
     diaChi(""),
     soDienThoai(""),
     email(""){
}
NhanVien::NhanVien(const TaiKhoan& tk)
    :NguoiDung(tk),
     hoTen(""),
     diaChi(""),
     soDienThoai(""),
     email(""){
}
NhanVien::NhanVien(
    const TaiKhoan& tk,
    const std::string& ht,
    const std::string& dc,
    const std::string& sdt,
    const std::string& em
)
    :NguoiDung(tk),
     hoTen(ht),
     diaChi(dc),
     soDienThoai(sdt),
     email(em){
}
NhanVien::NhanVien(const NhanVien& other)
    :NguoiDung(other),
     hoTen(other.hoTen),
     diaChi(other.diaChi),
     soDienThoai(other.soDienThoai),
     email(other.email){
}
NhanVien::~NhanVien(){
}
std::string NhanVien::getHoTen()const{return hoTen;}
std::string NhanVien::getDiaChi()const{return diaChi;}
std::string NhanVien::getSoDienThoai()const{return soDienThoai;}
std::string NhanVien::getEmail()const{return email;}
void NhanVien::setHoTen(const std::string& x){hoTen=x;}
void NhanVien::setDiaChi(const std::string& x){diaChi=x;}
void NhanVien::setSoDienThoai(const std::string& x){soDienThoai=x;}
void NhanVien::setEmail(const std::string& x){email=x;}
void NhanVien::hienThiThongTin()const{
    GiaoDien::inTieuDe("THONG TIN NHAN VIEN");
    std::cout<<*this;
}
void NhanVien::hienThiMenu()const{
    GiaoDien::hienThiMenuNhanVien();
}
std::string NhanVien::getVaiTro()const{
    return "Employee";
}
bool NhanVien::docThongTin(const std::string& path){
    std::ifstream file(path);
    if(!file.is_open()){
        return false;
    }
    file>>*this;
    return !file.fail();
}
bool NhanVien::ghiThongTin(const std::string& path)const{
    std::ofstream file(path);
    if(!file.is_open()){
        return false;
    }
    file<<hoTen<<'\n';
    file<<diaChi<<'\n';
    file<<soDienThoai<<'\n';
    file<<email<<'\n';
    return file.good();
}
std::ostream& operator<<(std::ostream& out,const NhanVien& nv){
    out<<"Username       : "<<nv.taiKhoan.getUsername()<<'\n';
    out<<"Ho ten         : "<<nv.hoTen<<'\n';
    out<<"Dia chi        : "<<nv.diaChi<<'\n';
    out<<"So dien thoai  : "<<nv.soDienThoai<<'\n';
    out<<"Email          : "<<nv.email<<'\n';
    return out;
}
std::istream& operator>>(std::istream& in,NhanVien& nv){
    if(!std::getline(in,nv.hoTen)||
       !std::getline(in,nv.diaChi)||
       !std::getline(in,nv.soDienThoai)||
       !std::getline(in,nv.email)){
            in.setstate(std::ios::failbit);
       }
    return in;
}

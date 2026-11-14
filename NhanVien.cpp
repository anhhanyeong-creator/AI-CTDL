#include "NhanVien.h"
#include "GiaoDien.h"
#include <fstream>
#include <iostream>
NhanVien::NhanVien():NguoiDung(),hoTen(""),diaChi(""),soDienThoai(""),email(""){}
NhanVien::NhanVien(const TaiKhoan& tk):NguoiDung(tk),hoTen(""),diaChi(""),soDienThoai(""),email(""){}
NhanVien::NhanVien(const TaiKhoan& tk,const std::string& ht,const std::string& dc,const std::string& sdt,const std::string& em):NguoiDung(tk),hoTen(ht),diaChi(dc),soDienThoai(sdt),email(em){}
NhanVien::NhanVien(const NhanVien& x):NguoiDung(x),hoTen(x.hoTen),diaChi(x.diaChi),soDienThoai(x.soDienThoai),email(x.email){}
NhanVien::~NhanVien(){}
std::string NhanVien::getHoTen()const{return hoTen;} std::string NhanVien::getDiaChi()const{return diaChi;} std::string NhanVien::getSoDienThoai()const{return soDienThoai;} std::string NhanVien::getEmail()const{return email;}
void NhanVien::setHoTen(const std::string& x){hoTen=x;} void NhanVien::setDiaChi(const std::string& x){diaChi=x;} void NhanVien::setSoDienThoai(const std::string& x){soDienThoai=x;} void NhanVien::setEmail(const std::string& x){email=x;}
void NhanVien::hienThiThongTin()const{GiaoDien::inTieuDe("THONG TIN NHAN VIEN");std::cout<<*this;}
void NhanVien::hienThiMenu()const{GiaoDien::hienThiMenuNhanVien();}
std::string NhanVien::getVaiTro()const{return "Employee";}
bool NhanVien::docThongTin(const std::string& path){std::ifstream f(path);if(!f)return false;return static_cast<bool>(f>>*this);}
bool NhanVien::ghiThongTin(const std::string& path)const{std::ofstream f(path);if(!f)return false;f<<hoTen<<'\n'<<diaChi<<'\n'<<soDienThoai<<'\n'<<email<<'\n';return f.good();}
std::ostream& operator<<(std::ostream& out,const NhanVien& nv){out<<"Username       : "<<nv.taiKhoan.getUsername()<<'\n'<<"Ho ten         : "<<nv.hoTen<<'\n'<<"Dia chi        : "<<nv.diaChi<<'\n'<<"So dien thoai  : "<<nv.soDienThoai<<'\n'<<"Email          : "<<nv.email<<'\n';return out;}
std::istream& operator>>(std::istream& in,NhanVien& nv){if(!std::getline(in,nv.hoTen)||!std::getline(in,nv.diaChi)||!std::getline(in,nv.soDienThoai)||!std::getline(in,nv.email))in.setstate(std::ios::failbit);return in;}

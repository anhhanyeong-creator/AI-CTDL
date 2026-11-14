#include "Admin.h"
#include "GiaoDien.h"
Admin::Admin():NguoiDung(){}
Admin::Admin(const TaiKhoan& tk):NguoiDung(tk){}
Admin::Admin(const Admin& x):NguoiDung(x){}
Admin::~Admin(){}
void Admin::hienThiMenu()const{GiaoDien::hienThiMenuAdmin();}
std::string Admin::getVaiTro()const{return "Administrator";}
std::ostream& operator<<(std::ostream& out,const Admin& a){return out<<a.taiKhoan;}
std::istream& operator>>(std::istream& in,Admin& a){return in>>a.taiKhoan;}

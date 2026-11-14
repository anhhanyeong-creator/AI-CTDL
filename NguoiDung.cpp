#include "NguoiDung.h"
NguoiDung::NguoiDung():taiKhoan(){}
NguoiDung::NguoiDung(const TaiKhoan& tk):taiKhoan(tk){}
NguoiDung::NguoiDung(const NguoiDung& x):taiKhoan(x.taiKhoan){}
NguoiDung::~NguoiDung(){}
TaiKhoan NguoiDung::getTaiKhoan()const{return taiKhoan;}
void NguoiDung::setTaiKhoan(const TaiKhoan& x){taiKhoan=x;}

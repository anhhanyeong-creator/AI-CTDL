#ifndef ADMIN_H
#define ADMIN_H
#include "NguoiDung.h"
#include <iostream>
class Admin:public NguoiDung{
public:
    Admin(); explicit Admin(const TaiKhoan& tk); Admin(const Admin& other); ~Admin() override;
    void hienThiMenu() const override; std::string getVaiTro() const override;
    friend std::ostream& operator<<(std::ostream& out,const Admin& admin);
    friend std::istream& operator>>(std::istream& in,Admin& admin);
};
#endif

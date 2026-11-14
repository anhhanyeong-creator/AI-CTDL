#ifndef NGUOI_DUNG_H
#define NGUOI_DUNG_H
#include "TaiKhoan.h"
#include <string>
class NguoiDung {
protected: TaiKhoan taiKhoan;
public:
    NguoiDung();
    explicit NguoiDung(const TaiKhoan& taiKhoan);
    NguoiDung(const NguoiDung& other);
    virtual ~NguoiDung();
    TaiKhoan getTaiKhoan() const;
    void setTaiKhoan(const TaiKhoan& value);
    virtual void hienThiMenu() const=0;
    virtual std::string getVaiTro() const=0;
};
#endif

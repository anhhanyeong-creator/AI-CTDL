#ifndef GIAO_DIEN_H
#define GIAO_DIEN_H

#include <iostream>
#include <string>

namespace MauSac {
    extern const std::string RESET;
    extern const std::string CYAN;
    extern const std::string XANH_LA;
    extern const std::string DO;
    extern const std::string VANG;
    extern const std::string TIM;
    extern const std::string DAM;
}

class GiaoDien {
public:
    GiaoDien();
    GiaoDien(const GiaoDien& other);
    ~GiaoDien();
    static void xoaManHinh();
    static void inVienNgang(int chieuRong = 60);
    static void inDongKhung(
        const std::string& noiDung,
        int rong
    );

    static void inDongKhung(
        const std::string& noiDung,
        bool canGiua,
        int rong
    );
    static void hienThiLoGo(); 
    static void inTieuDe(const std::string& tieuDe);
    static void hienThiMenuChinh();
    static void hienThiMenuAdmin();
    static void hienThiMenuNhanVien();

    static void hienThiKhungDangNhap();
    static void hienThiKhungThemNhanVien();

    static void batDauKhungNhap(
        const std::string& tieuDe,
        int chieuRong=40
    );
    static std::string nhapChuoiTrongKhung(
        const std::string& nhan,
        int chieuRong=40
    );
    static std::string nhapMatKhauTrongKhung(
        const std::string& nhan,
        int chieuRong=40
    );
    static void inThongBaoTrongKhung(
        const std::string& noiDung,
        int chieuRong=40
    );
    static void ketThucKhungNhap(int chieuRong=40);
    

   
    static void inThongBao(
        const std::string& noiDung, 
        const std::string& mau
    );
    static void dungManHinh();
    static std::string nhapMatKhau(const std::string& loiNhac);
};

#endif

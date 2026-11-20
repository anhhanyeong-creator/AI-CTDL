#ifndef QUAN_LY_NHAN_SU_H
#define QUAN_LY_NHAN_SU_H

#include "TaiKhoan.h"
#include "NhanVien.h"
#include "FileRepository.h"

#include "DanhSachLienKet.h"
#include "Stack.h"
#include "Queue.h"
#include "CayTimKiemNhanVien.h"

#include <string>
#include <vector>

class QuanLyNhanSu {
private:
    // Kho lưu tài khoản
    FileRepository<TaiKhoan> khoAdmin;
    FileRepository<TaiKhoan> khoNhanVien;

    // Các cấu trúc dữ liệu của chương trình
    DanhSachLienKet<NhanVien> dsNhanVien;
    Stack<std::string> lichSuThaoTac;
    Queue<std::string> hangDoiYeuCau;
    CayTimKiemNhanVien cayNhanVien;

    // Các phương thức hỗ trợ
    void khoiTaoDuLieu();
    void capNhatCauTrucDuLieu();

    bool tenDangNhapHopLe(const std::string& username) const;
    bool emailHopLe(const std::string& email) const;
    bool soDienThoaiHopLe(const std::string& sdt) const;

    int timViTriNhanVien(
        const std::vector<TaiKhoan>& ds,
        const std::string& username
    ) const;

    std::string tenFileThongTin(
        const std::string& username
    ) const;

    // Đăng nhập
    bool dangNhap(
        FileRepository<TaiKhoan>& kho,
        TaiKhoan& taiKhoan,
        const std::string& vaiTro,
        bool gioiHanBaLan
    );

    // Menu
    void menuAdmin(const TaiKhoan& taiKhoan);
    void menuNhanVien(TaiKhoan taiKhoan);

    // Chức năng quản lý nhân viên
    void themNhanVien();
    void xoaNhanVien();
    void timNhanVien() const;
    void capNhatNhanVien();
    void hienThiTatCaNhanVien() const;

    // Chức năng tài khoản
    void doiMatKhau(TaiKhoan& taiKhoan);
    void xemThongTinCaNhan(const TaiKhoan& taiKhoan) const;

public:
    QuanLyNhanSu();

    QuanLyNhanSu(const QuanLyNhanSu& other);

    ~QuanLyNhanSu();

    // Quản lý đường dẫn file
    std::string getFileAdmin() const;
    std::string getFileNhanVien() const;

    void setFileAdmin(const std::string& tenFile);
    void setFileNhanVien(const std::string& tenFile);

    // Khởi chạy chương trình
    void chay();
};

#endif

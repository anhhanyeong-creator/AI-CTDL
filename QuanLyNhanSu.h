#ifndef QUAN_LY_NHAN_SU_H
#define QUAN_LY_NHAN_SU_H

#include "TaiKhoan.h"
#include "NhanVien.h"
#include "FileRepository.h"
#include <string>
#include <vector>

class QuanLyNhanSu {
private:
    FileRepository<TaiKhoan> khoAdmin;
    FileRepository<TaiKhoan> khoNhanVien;

    void khoiTaoDuLieu();
    bool tenDangNhapHopLe(const std::string& username) const;
    bool emailHopLe(const std::string& email) const;
    bool soDienThoaiHopLe(const std::string& sdt) const;
    int timViTriNhanVien(const std::vector<TaiKhoan>& ds,
                         const std::string& username) const;
    std::string tenFileThongTin(const std::string& username) const;

    bool dangNhap(FileRepository<TaiKhoan>& kho, TaiKhoan& taiKhoan,
                  const std::string& vaiTro, bool gioiHanBaLan);
    void menuAdmin(const TaiKhoan& taiKhoan);
    void menuNhanVien(TaiKhoan taiKhoan);

    void themNhanVien();
    void xoaNhanVien();
    void timNhanVien() const;
    void capNhatNhanVien();
    void hienThiTatCaNhanVien() const;
    void doiMatKhau(TaiKhoan& taiKhoan);
    void xemThongTinCaNhan(const TaiKhoan& taiKhoan) const;

public:
    QuanLyNhanSu();
    QuanLyNhanSu(const QuanLyNhanSu& other);
    ~QuanLyNhanSu();
    std::string getFileAdmin() const;
    std::string getFileNhanVien() const;
    void setFileAdmin(const std::string& tenFile);
    void setFileNhanVien(const std::string& tenFile);
    void chay();
};

#endif

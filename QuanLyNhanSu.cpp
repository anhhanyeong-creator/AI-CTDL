#include "QuanLyNhanSu.h"
#include "GiaoDien.h"
#include "Admin.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <string>
template <typename T>
int timViTri(const std::vector<T>& ds, const std::string& username){
    for(int i=0;i<ds.size();i++){
        if(ds[i].getUsername()==username){
            return i;
        }
    }
    return -1;
}
bool usernameHopLe(const std::string& username){
    if(username.empty()){
        return false;
    }
    for(char c:username){
        if(!std::isalnum(static_cast<unsigned char>(c))&&
            c!='_'&&c!='-'){
                return false;
            }
    }
    return true;
}
std::string tenFileThongTin(const std::string& username){
    return "Data/"+username+".txt";
}
QuanLyNhanSu::QuanLyNhanSu()
    : khoAdmin("Data/Administrator.txt"),
      khoNhanVien("Data/Employee.txt") {
    khoiTaoDuLieu();
}

QuanLyNhanSu::QuanLyNhanSu(const QuanLyNhanSu& other)
    : khoAdmin(other.khoAdmin), khoNhanVien(other.khoNhanVien) {}

QuanLyNhanSu::~QuanLyNhanSu() {}
std::string QuanLyNhanSu::getFileAdmin() const { return khoAdmin.getTenFile(); }
std::string QuanLyNhanSu::getFileNhanVien() const { return khoNhanVien.getTenFile(); }
void QuanLyNhanSu::setFileAdmin(const std::string& tenFile) { khoAdmin.setTenFile(tenFile); }
void QuanLyNhanSu::setFileNhanVien(const std::string& tenFile) { khoNhanVien.setTenFile(tenFile); }

void QuanLyNhanSu::khoiTaoDuLieu() {
    std::ifstream adminFile(khoAdmin.getTenFile());
    if (!adminFile.good()) {
        std::vector<TaiKhoan> admins = {
            TaiKhoan("admin01", "admin123"),
            TaiKhoan("admin02", "admin123"),
            TaiKhoan("admin03", "admin123")
        };
        khoAdmin.ghiTatCa(admins);
    }
    std::ifstream employeeFile(khoNhanVien.getTenFile());
    if (!employeeFile.good()) khoNhanVien.ghiTatCa({});
}

bool QuanLyNhanSu::tenDangNhapHopLe(const std::string& username) const {
    if (username.empty() || username.size() > 30) return false;
    for (unsigned char c : username) {
        if (!std::isalnum(c) && c != '_' && c != '-') return false;
    }
    return username != "." && username != "..";
}

bool QuanLyNhanSu::emailHopLe(const std::string& email) const {
    std::size_t at = email.find('@');
    std::size_t dot = email.find('.', at == std::string::npos ? 0 : at);
    return at != std::string::npos && dot != std::string::npos &&
           at > 0 && dot > at + 1 && dot + 1 < email.size();
}

bool QuanLyNhanSu::soDienThoaiHopLe(const std::string& sdt) const {
    if (sdt.size() < 9 || sdt.size() > 11) return false;
    return std::all_of(sdt.begin(), sdt.end(),
                       [](unsigned char c) { return std::isdigit(c); });
}

int QuanLyNhanSu::timViTriNhanVien(const std::vector<TaiKhoan>& ds,
                                   const std::string& username) const {
    for (std::size_t i = 0; i < ds.size(); ++i)
        if (ds[i].getUsername() == username) return static_cast<int>(i);
    return -1;
}

std::string QuanLyNhanSu::tenFileThongTin(const std::string& username) const {
    return "Data/" + username + ".txt";
}


bool QuanLyNhanSu::dangNhap(
    FileRepository<TaiKhoan>& kho,
    TaiKhoan& taiKhoan,
    const std::string& vaiTro,
    bool gioiHanBaLan
) {
    std::vector<TaiKhoan> ds = kho.docTatCa();
    int soLanSai = 0;
    int gioiHan = gioiHanBaLan ? 3 : 1000;
    while (soLanSai < gioiHan) {
        GiaoDien::batDauKhungNhap("Nhap thong tin", 40);
        std::string username =
            GiaoDien::nhapChuoiTrongKhung("Username: ", 40);
        std::string password =
            GiaoDien::nhapMatKhauTrongKhung("Password: ", 40);
        GiaoDien::ketThucKhungNhap(40);
        int viTri = timViTriNhanVien(ds, username);
        if (viTri != -1 &&
            ds[viTri].getPassword() == password) {
            taiKhoan = ds[viTri];
            GiaoDien::inThongBaoTrongKhung(
                ">> Dang nhap thanh cong", 40
            );
            GiaoDien::inThongBao(
                "Chao mung " + vaiTro + "!",
                MauSac::XANH_LA
            );
            return true;
        }
        soLanSai++;
        GiaoDien::inThongBao(
            "Username hoac password khong dung!",
            MauSac::DO
        );
        if (!gioiHanBaLan)
            return false;
        std::cout << "So lan con lai: "
                  << 3 - soLanSai << '\n';
    }
    GiaoDien::inThongBao(
        "Ban da dang nhap sai 3 lan. Chuong trinh ket thuc.",
        MauSac::DO
    );
    return false;
}


void QuanLyNhanSu::chay() {
    while (true) {
        GiaoDien::hienThiMenuChinh();
        std::string luaChon;
        std::getline(std::cin, luaChon);
        if (luaChon == "3") {
            GiaoDien::inThongBao("Cam on ban da su dung chuong trinh.", MauSac::XANH_LA);
            break;
        } else if (luaChon == "1") {
            TaiKhoan tk;
            if (dangNhap(khoAdmin, tk, "Administrator", false)) menuAdmin(tk);
        } else if (luaChon == "2") {
            TaiKhoan tk;
            if (!dangNhap(khoNhanVien, tk, "Employee", true)) break;
            if (tk.getCanDoiMatKhau()) {
                GiaoDien::inThongBao("Lan dang nhap dau tien: bat buoc doi mat khau.", MauSac::VANG);
                do {
                    doiMatKhau(tk);
                } while (tk.getCanDoiMatKhau());
            }
            menuNhanVien(tk);
        } else {
            GiaoDien::inThongBao("Lua chon khong hop le!", MauSac::DO);
        }
        GiaoDien::dungManHinh();
        GiaoDien::xoaManHinh();
    }
}

void QuanLyNhanSu::menuAdmin(const TaiKhoan& taiKhoan) {
    Admin admin(taiKhoan);
    while (true) {
        admin.hienThiMenu();
        std::string chon;
        std::getline(std::cin, chon);
        if (chon == "1") themNhanVien();
        else if (chon == "2") xoaNhanVien();
        else if (chon == "3") timNhanVien();
        else if (chon == "4") capNhatNhanVien();
        else if (chon == "5") hienThiTatCaNhanVien();
        else if (chon == "6") break;
        else GiaoDien::inThongBao("Lua chon khong hop le!", MauSac::DO);
        if (chon != "6") GiaoDien::dungManHinh();
        GiaoDien::xoaManHinh();
    }
}

void QuanLyNhanSu::themNhanVien() {
    std::vector<TaiKhoan> ds = khoNhanVien.docTatCa();

    GiaoDien::batDauKhungNhap("Them nhan vien", 40);

    std::string username =
        GiaoDien::nhapChuoiTrongKhung("Username: ", 40);

    std::string hoTen =
        GiaoDien::nhapChuoiTrongKhung("Ho ten: ", 40);

    std::string diaChi =
        GiaoDien::nhapChuoiTrongKhung("Dia chi: ", 40);

    std::string sdt =
        GiaoDien::nhapChuoiTrongKhung("So dien thoai: ", 40);

    std::string email =
        GiaoDien::nhapChuoiTrongKhung("Email: ", 40);

    GiaoDien::ketThucKhungNhap(40);

    if (!usernameHopLe(username) ||
        timViTriNhanVien(ds, username) != -1) {

        GiaoDien::inThongBao(
            "Username khong hop le hoac da ton tai!",
            MauSac::DO
        );
        return;
    }

    // Kiem tra thong tin
    if (hoTen.empty() || diaChi.empty() ||
        !soDienThoaiHopLe(sdt) ||
        !emailHopLe(email)) {

        GiaoDien::inThongBao(
            "Thong tin nhan vien khong hop le!",
            MauSac::DO
        );
        return;
    }

    // Tao tai khoan
    TaiKhoan tk(username, "111111", true);

    // Tao doi tuong nhan vien
    NhanVien nv(tk, hoTen, diaChi, sdt, email);

    // Ghi file thong tin ca nhan
    if (!nv.ghiThongTin(tenFileThongTin(username))) {
        GiaoDien::inThongBao(
            "Khong tao duoc file nhan vien!",
            MauSac::DO
        );
        return;
    }

    ds.push_back(tk);

    if (!khoNhanVien.ghiTatCa(ds)) {
        std::remove(
            tenFileThongTin(username).c_str()
        );

        GiaoDien::inThongBao(
            "Loi cap nhat Employee.txt!",
            MauSac::DO
        );
        return;
    }

    GiaoDien::inThongBao(
        "Them nhan vien thanh cong!",
        MauSac::XANH_LA
    );

    std::cout << "Mat khau mac dinh: 111111\n";
}



void QuanLyNhanSu::xoaNhanVien() {
    GiaoDien::inTieuDe("XOA NHAN VIEN");
    std::string username;
    std::cout << "Nhap username can xoa: ";
    std::getline(std::cin, username);
    std::vector<TaiKhoan> ds = khoNhanVien.docTatCa();
    int viTri = timViTriNhanVien(ds, username);
    if (viTri == -1) {
        GiaoDien::inThongBao("Khong tim thay nhan vien.", MauSac::DO);
        return;
    }
    ds.erase(ds.begin() + viTri);
    if (!khoNhanVien.ghiTatCa(ds)) {
        GiaoDien::inThongBao("Khong cap nhat duoc Employee.txt.", MauSac::DO);
        return;
    }
    std::remove(tenFileThongTin(username).c_str());
    GiaoDien::inThongBao("Da xoa nhan vien " + username, MauSac::XANH_LA);
}

void QuanLyNhanSu::timNhanVien() const {
    GiaoDien::inTieuDe("TIM NHAN VIEN");
    std::string username;
    std::cout << "Nhap username: ";
    std::getline(std::cin, username);
    std::vector<TaiKhoan> ds = khoNhanVien.docTatCa();
    int viTri = timViTriNhanVien(ds, username);
    if (viTri == -1) {
        GiaoDien::inThongBao("Khong tim thay nhan vien.", MauSac::DO);
        return;
    }
    NhanVien nv(ds[viTri]);
    if (!nv.docThongTin(tenFileThongTin(username))) {
        GiaoDien::inThongBao("Khong doc duoc file thong tin nhan vien.", MauSac::DO);
        return;
    }
    nv.hienThiThongTin();
}

void QuanLyNhanSu::capNhatNhanVien() {
    GiaoDien::inTieuDe("CAP NHAT NHAN VIEN");
    std::string username;
    std::cout << "Nhap username can cap nhat: ";
    std::getline(std::cin, username);
    std::vector<TaiKhoan> ds = khoNhanVien.docTatCa();
    if (timViTriNhanVien(ds, username) == -1) {
        GiaoDien::inThongBao("Khong tim thay nhan vien.", MauSac::DO);
        return;
    }
    NhanVien nv(ds[timViTriNhanVien(ds, username)]);
    if (!nv.docThongTin(tenFileThongTin(username))) {
        GiaoDien::inThongBao("Khong doc duoc thong tin nhan vien.", MauSac::DO);
        return;
    }

    while (true) {
        std::cout << "\n1. Ho ten\n2. Dia chi\n3. So dien thoai\n4. Email\n0. Hoan tat\nChon thuoc tinh: ";
        std::string chon, value;
        std::getline(std::cin, chon);
        if (chon == "0") break;
        std::cout << "Nhap gia tri moi: ";
        std::getline(std::cin, value);
        if (chon == "1" && !value.empty()) nv.setHoTen(value);
        else if (chon == "2" && !value.empty()) nv.setDiaChi(value);
        else if (chon == "3" && soDienThoaiHopLe(value)) nv.setSoDienThoai(value);
        else if (chon == "4" && emailHopLe(value)) nv.setEmail(value);
        else GiaoDien::inThongBao("Lua chon hoac du lieu khong hop le.", MauSac::DO);
    }
    if (nv.ghiThongTin(tenFileThongTin(username)))
        GiaoDien::inThongBao("Cap nhat thanh cong.", MauSac::XANH_LA);
    else GiaoDien::inThongBao("Loi ghi file thong tin.", MauSac::DO);
}


void QuanLyNhanSu::hienThiTatCaNhanVien() const {
    GiaoDien::inTieuDe("DANH SACH NHAN VIEN");

    std::vector<TaiKhoan> ds = khoNhanVien.docTatCa();

    if (ds.empty()) {
        GiaoDien::inThongBao(
            "Danh sach nhan vien dang trong!",
            MauSac::VANG
        );
        return;
    }

    const int rong[] = {17, 22, 21, 18, 22};

    auto catChuoi = [](std::string s, int maxRong) {
        if (static_cast<int>(s.size()) > maxRong) {
            s = s.substr(0, maxRong - 3) + "...";
        }
        return s;
    };

    auto veVienBang = [&]() {
        std::cout << "++";

        for (int i = 0; i < 5; i++) {
            std::cout << std::string(rong[i] + 2, '=')
                      << "++";
        }

        std::cout << '\n';
    };

    auto inDong = [&](const std::string cot[]) {
        std::cout << "||";

        for (int i = 0; i < 5; i++) {
            std::cout << " "
                      << std::left
                      << std::setw(rong[i])
                      << catChuoi(cot[i], rong[i])
                      << " ||";
        }

        std::cout << '\n';
    };

    // Tieu de bang
    const std::string tieuDe[] = {
        "Username",
        "Ho ten",
        "Dia chi",
        "So dien thoai",
        "Email"
    };

    veVienBang();
    inDong(tieuDe);
    veVienBang();

    // Duyet danh sach nhan vien
    for (const TaiKhoan& tk : ds) {

        NhanVien nv(tk);

        if (!nv.docThongTin(
            tenFileThongTin(tk.getUsername())
        )) {
            continue;
        }

        std::string thongTin[] = {
            tk.getUsername(),
            nv.getHoTen(),
            nv.getDiaChi(),
            nv.getSoDienThoai(),
            nv.getEmail()
        };

        inDong(thongTin);
    }

    veVienBang();
}


void QuanLyNhanSu::xemThongTinCaNhan(const TaiKhoan& taiKhoan) const {
    NhanVien nv(taiKhoan);
    if (nv.docThongTin(tenFileThongTin(taiKhoan.getUsername())))
        nv.hienThiThongTin();
    else GiaoDien::inThongBao("Khong doc duoc thong tin tai khoan.", MauSac::DO);
}

void QuanLyNhanSu::doiMatKhau(TaiKhoan& taiKhoan) {
    std::vector<TaiKhoan> ds = khoNhanVien.docTatCa();
    int viTri = timViTriNhanVien(ds, taiKhoan.getUsername());
    if (viTri == -1) {
        GiaoDien::inThongBao("Tai khoan khong ton tai.", MauSac::DO);
        return;
    }
    if (!taiKhoan.getCanDoiMatKhau()) {
        std::string hienTai = GiaoDien::nhapMatKhau("Nhap mat khau hien tai: ");
        if (hienTai != ds[viTri].getPassword()) {
            GiaoDien::inThongBao("Mat khau hien tai khong dung.", MauSac::DO);
            return;
        }
    }
    std::string moi = GiaoDien::nhapMatKhau("Nhap mat khau moi (it nhat 6 ky tu): ");
    std::string xacNhan = GiaoDien::nhapMatKhau("Nhap lai mat khau moi: ");
    if (moi.size() < 6 || moi != xacNhan) {
        GiaoDien::inThongBao("Mat khau moi khong hop le hoac khong trung khop.", MauSac::DO);
        return;
    }
    ds[viTri].setPassword(moi);
    ds[viTri].setCanDoiMatKhau(false);
    if (khoNhanVien.ghiTatCa(ds)) {
        taiKhoan.setPassword(moi);
        taiKhoan.setCanDoiMatKhau(false);
        GiaoDien::inThongBao("Doi mat khau thanh cong.", MauSac::XANH_LA);
    } else GiaoDien::inThongBao("Khong the cap nhat Employee.txt.", MauSac::DO);
}

void QuanLyNhanSu::menuNhanVien(TaiKhoan taiKhoan) {
    NhanVien nhanVien(taiKhoan);
    while (true) {
        nhanVien.hienThiMenu();
        std::string chon;
        std::getline(std::cin, chon);
        if (chon == "1") xemThongTinCaNhan(taiKhoan);
        else if (chon == "2") doiMatKhau(taiKhoan);
        else if (chon == "0") break;
        else GiaoDien::inThongBao("Lua chon khong hop le.", MauSac::DO);
        if (chon != "0") GiaoDien::dungManHinh();
        GiaoDien::xoaManHinh();
    }
}

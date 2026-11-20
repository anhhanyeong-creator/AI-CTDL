#include "GiaoDien.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace MauSac {
    const std::string RESET = "\033[0m";
    const std::string CYAN = "\033[36m";
    const std::string XANH_LA = "\033[32m";
    const std::string DO = "\033[31m";
    const std::string VANG = "\033[33m";
    const std::string TIM = "\033[35m";
    const std::string DAM = "\033[1m";
    const std::string XANH_DUONG="\033[94m";
}
const int RONG_KHUNG = 88;
const int LE_TRAI = 4;

namespace {
// Dem so ky tu UTF-8 thay vi so byte (phu hop voi chu tieng Viet).
int doRongHienThi(const std::string& s) {
    int doRong = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) ++doRong;
    }
    return doRong;
}

// Lay phan dau chuoi, khong cat ngang mot ky tu UTF-8.
std::string catTheoCot(const std::string& s, int soCot) {
    if (soCot <= 0) return "";
    std::size_t i = 0;
    int cot = 0;
    while (i < s.size() && cot < soCot) {
        const unsigned char c = static_cast<unsigned char>(s[i]);
        std::size_t buoc = (c < 0x80) ? 1 : (c < 0xE0 ? 2 : (c < 0xF0 ? 3 : 4));
        i = std::min(s.size(), i + buoc);
        ++cot;
    }
    return s.substr(0, i);
}

// Dong khung co tong do rong chieuRong + 2 cot (ke ca hai vien '|').
void inDongNhapDaHoanThanh(const std::string& nhan,
                          const std::string& giaTriHienThi,
                          int chieuRong) {
    const int rong = std::max(2, chieuRong);
    const int choNoiDung = rong - 1; // sau ky tu dau dong va dau cach
    const std::string text = catTheoCot(nhan + giaTriHienThi, choNoiDung);
    const int conLai = std::max(0, choNoiDung - doRongHienThi(text));
    std::cout << MauSac::CYAN << '|' << MauSac::RESET
              << ' ' << text << std::string(conLai, ' ')
              << MauSac::CYAN << '|' << MauSac::RESET << '\n';
}

// Chi ap dung cho khi nhap vao console that.
bool laConsole() {
#ifdef _WIN32
    DWORD mode = 0;
    return GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) != 0;
#else
    return isatty(STDOUT_FILENO) != 0;
#endif
}

#ifdef _WIN32
// Luu vi tri con tro truoc khi in nhan, de ghi de dong nhap sau Enter.
COORD viTriConTro() {
    CONSOLE_SCREEN_BUFFER_INFO info{};
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
        return info.dwCursorPosition;
    return COORD{0, 0};
}
#endif
}

GiaoDien::GiaoDien() {}
GiaoDien::GiaoDien(const GiaoDien& other) {
    (void)other;
}
GiaoDien::~GiaoDien() {}

void GiaoDien::xoaManHinh() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void GiaoDien::inVienNgang(int rong) {
    if (rong < 4) return;
    std::cout << std::string(LE_TRAI, ' ')
              << MauSac::XANH_DUONG
              << "++" << std::string(rong - 4, '=') << "++"
              << MauSac::RESET << '\n';
}

void GiaoDien::inDongKhung(const std::string& noiDung, int rong) {
    inDongKhung(noiDung, true, rong);
}

void GiaoDien::inDongKhung(
    const std::string& noiDung, bool canGiua, int rong
) {
    if (rong < 4) return;
    const int benTrong = rong - 4;
    const std::string text = catTheoCot(noiDung, benTrong);
    const int conLai = benTrong - doRongHienThi(text);
    const int trai = canGiua ? conLai / 2 : std::min(1, conLai);
    const int phai = conLai - trai;
    std::cout << std::string(LE_TRAI, ' ')
              << MauSac::XANH_DUONG << "||" << MauSac::RESET
              << std::string(trai, ' ') << text << std::string(phai, ' ')
              << MauSac::XANH_DUONG << "||" << MauSac::RESET << '\n';
}

void GiaoDien::hienThiLoGo() {
    // Chu y: khong de khoang trang sau dong cuoi cua logo.
    // Moi dong co 4 dau cach va khung rong 88 cot.
    std::cout << MauSac::CYAN << R"(    ++====================================================================================++
    ||  ▄█████▄ ▄▄ ▄▄  ▄▄▄  ▄▄  ▄▄   ▄▄  ▄▄ ▄▄   ▄▄  ▄▄ ▄▄ ▄▄  ▄▄▄  ▄▄  ▄▄    ▄▄▄▄ ▄▄ ▄▄  ||
    ||  ██ ▄ ██ ██ ██ ██▀██ ███▄██   ██  ▀███▀   ███▄██ ██▄██ ██▀██ ███▄██   ███▄▄ ██ ██  ||
    ||  ▀█████▀ ▀███▀ ██▀██ ██ ▀██   ██▄▄▄ █     ██ ▀██ ██ ██ ██▀██ ██ ▀██   ▄▄██▀ ▀███▀  ||
    ||     ▀▀                                                                             ||
    ++====================================================================================++
)" << MauSac::RESET;
}

void GiaoDien::inTieuDe(const std::string& tieuDe) {
    inVienNgang(50);
    // Dung chung ham inDongKhung de hai vien can thang.
    inDongKhung(tieuDe, true, 50);
    inVienNgang(50);
}
void GiaoDien::hienThiMenuChinh() {
    xoaManHinh();

    hienThiLoGo();

    inDongKhung("", true, RONG_KHUNG);
    inDongKhung("[1] Dang nhap Admin", true, RONG_KHUNG);
    inDongKhung("[2] Dang nhap Employee", true, RONG_KHUNG);
    inDongKhung("[3] Thoat", true, RONG_KHUNG);

    inVienNgang(RONG_KHUNG);

    std::cout << "\n"
              << MauSac::VANG
              << "Lua chon: "
              << MauSac::RESET;
}
void GiaoDien::hienThiMenuAdmin() {
    inTieuDe("ADMINISTRATOR");
    inDongKhung("[1] Them nhan vien", true,50);
    inDongKhung("[2] Xoa nhan vien",true,50);
    inDongKhung("[3] Tim nhan vien",true,50);
    inDongKhung("[4] Cap nhat nhan vien", true,50);
    inDongKhung("[5] Hien thi tat ca nhan vien", true,50);
    inDongKhung("[6] Dang xuat", true,50);
    inVienNgang(50);
    std::cout << MauSac::VANG 
              << "Lua chon: " 
              << MauSac::RESET;
}
void GiaoDien::hienThiMenuNhanVien() {
    inTieuDe("EMPLOYEE");
    inDongKhung("[1] Xem thong tin tai khoan", true,50);
    inDongKhung("[2] Doi password", true,50);
    inDongKhung("[0] Dang xuat", true,50);
    inVienNgang(50);
    std::cout << MauSac::VANG 
              << "Lua chon: "
              << MauSac::RESET;
}
void GiaoDien::batDauKhungNhap(const std::string& tieuDe,
                                int chieuRong) {
    const int rong = std::max(2, chieuRong);
    const std::string text = catTheoCot(tieuDe, std::max(0, rong - 2));
    const int dauBang = rong - 2 - doRongHienThi(text);
    const int trai = dauBang / 2;
    const int phai = dauBang - trai;
    std::cout << "\n" << MauSac::CYAN
              << "+" << std::string(trai, '=') << " " << text << " "
              << std::string(phai, '=') << "+"
              << MauSac::RESET << '\n';
}

std::string GiaoDien::nhapChuoiTrongKhung(
    const std::string& nhan, int chieuRong
) {
    std::string giaTri;
    const bool console = laConsole();
#ifdef _WIN32
    const COORD batDau = viTriConTro();
#endif
    if (console) {
        std::cout << MauSac::CYAN << '|' << MauSac::RESET
                  << ' ' << nhan << std::flush;
    }
    std::getline(std::cin, giaTri);

    // getline da xuong dong khi Enter duoc nhan. Quay lai dong cu
    // va ve lai dong day du, KHONG in khoang trang vao dong ke tiep.
    if (console) {
#ifdef _WIN32
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), batDau);
#else
        std::cout << "\033[1A\r";
#endif
    }
    inDongNhapDaHoanThanh(nhan, giaTri, chieuRong);
    return giaTri;
}

std::string GiaoDien::nhapMatKhauTrongKhung(
    const std::string& nhan, int chieuRong
) {
    std::string password;
    const int soKyTuToiDa = std::max(0, chieuRong - 1 - doRongHienThi(nhan));
    std::cout << MauSac::CYAN << '|' << MauSac::RESET
              << ' ' << nhan << std::flush;
#ifdef _WIN32
    while (true) {
        const int ch = _getch();
        if (ch == 13) break;
        if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        } else if (ch >= 32 && ch <= 126 &&
                   static_cast<int>(password.size()) < soKyTuToiDa) {
            password.push_back(static_cast<char>(ch));
            std::cout << '*' << std::flush;
        }
    }
#else
    termios oldSettings{}, newSettings{};
    const bool coTermios = tcgetattr(STDIN_FILENO, &oldSettings) == 0;
    if (coTermios) {
        newSettings = oldSettings;
        newSettings.c_lflag &= static_cast<tcflag_t>(~(ECHO | ICANON));
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    }
    while (true) {
        char ch = 0;
        if (read(STDIN_FILENO, &ch, 1) != 1) break;
        if (ch == '\n' || ch == '\r') break;
        if (ch == 127 || ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        } else if (ch >= 32 && ch <= 126 &&
                   static_cast<int>(password.size()) < soKyTuToiDa) {
            password.push_back(ch);
            std::cout << '*' << std::flush;
        }
    }
    if (coTermios) tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
#endif
    const int conLai = std::max(0, chieuRong - 1 -
        doRongHienThi(nhan) - static_cast<int>(password.size()));
    std::cout << std::string(conLai, ' ')
              << MauSac::CYAN << '|' << MauSac::RESET << '\n';
    return password;
}

void GiaoDien::inThongBaoTrongKhung(
    const std::string& noiDung, int chieuRong
) {
    const int rong = std::max(2, chieuRong);
    const std::string text = catTheoCot(noiDung, rong - 1);
    const int conLai = rong - 1 - doRongHienThi(text);
    std::cout << MauSac::CYAN << '|' << MauSac::RESET
              << ' ' << MauSac::XANH_LA << text << MauSac::RESET
              << std::string(conLai, ' ')
              << MauSac::CYAN << '|' << MauSac::RESET << '\n';
}

void GiaoDien::ketThucKhungNhap(int chieuRong) {
    std::cout << MauSac::CYAN << '+'
              << std::string(std::max(2, chieuRong), '=') << '+'
              << MauSac::RESET << '\n';
}

void GiaoDien::inThongBao(
    const std::string& noiDung, 
    const std::string& mau
) {
    std::cout << mau 
              << "\n>> " << noiDung 
              << MauSac::RESET << "\n";
}

void GiaoDien::dungManHinh() {
    std::cout << "\nNhan Enter de tiep tuc...";
    std::string temp;
    std::getline(std::cin, temp);
}

void GiaoDien::hienThiKhungDangNhap() {
    batDauKhungNhap("Nhap thong tin", 40);
    inThongBaoTrongKhung("Username:", 40);
    inThongBaoTrongKhung("Password:", 40);
    ketThucKhungNhap(40);
}

void GiaoDien::hienThiKhungThemNhanVien() {
    batDauKhungNhap("Them nhan vien", 40);
    inThongBaoTrongKhung("Username:", 40);
    inThongBaoTrongKhung("Ho ten:", 40);
    inThongBaoTrongKhung("Dia chi:", 40);
    inThongBaoTrongKhung("So dien thoai:", 40);
    inThongBaoTrongKhung("Email:", 40);
    ketThucKhungNhap(40);
}

std::string GiaoDien::nhapMatKhau(const std::string& loiNhac) {
    std::cout << loiNhac;
    std::string password;
#ifdef _WIN32
    while (true) {
        int ch = _getch();
        if (ch == 13) break;
        if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else if (ch >= 32 && ch <= 126) {
            password.push_back(static_cast<char>(ch));
            std::cout << '*';
        }
    }
#else
    termios oldSettings{}, newSettings{};
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= static_cast<tcflag_t>(~(ECHO | ICANON));
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    while (true) {
        char ch = 0;
        if (read(STDIN_FILENO, &ch, 1) != 1) break;
        if (ch == '\n' || ch == '\r') break;
        if (ch == 127 || ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        } else if (ch >= 32 && ch <= 126) {
            password.push_back(ch);
            std::cout << '*' << std::flush;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
#endif
    std::cout << '\n';
    return password;
}

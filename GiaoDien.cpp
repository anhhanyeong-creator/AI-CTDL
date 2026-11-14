#include "GiaoDien.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

#ifdef _WIN32
#include <conio.h>
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
}

GiaoDien::GiaoDien() {}
GiaoDien::GiaoDien(const GiaoDien&) {}
GiaoDien::~GiaoDien() {}

void GiaoDien::xoaManHinh() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void GiaoDien::inVienNgang(int chieuRong) {
    std::cout << MauSac::CYAN << "++" << std::string(chieuRong, '=')
              << "++" << MauSac::RESET << '\n';
}

void GiaoDien::inDongKhung(const std::string& noiDung, bool canGiua, int chieuRong) {
    int rongTrong = chieuRong - static_cast<int>(noiDung.size());
    if (rongTrong < 1) rongTrong = 1;
    int leTrai = canGiua ? rongTrong / 2 : 1;
    int lePhai = rongTrong - leTrai;
    std::cout << MauSac::CYAN << "||" << MauSac::RESET
              << std::string(leTrai, ' ') << noiDung
              << std::string(lePhai, ' ')
              << MauSac::CYAN << "||" << MauSac::RESET << '\n';
}

void GiaoDien::inTieuDe(const std::string& tieuDe) {
    inVienNgang(60);
    inDongKhung(MauSac::DAM + MauSac::CYAN + tieuDe + MauSac::RESET, true, 60);
    inVienNgang(60);
}

void GiaoDien::inThongBao(const std::string& noiDung, const std::string& mau) {
    std::cout << mau << "\n>> " << noiDung << MauSac::RESET << "\n";
}

void GiaoDien::dungManHinh() {
    std::cout << "\nNhan Enter de tiep tuc...";
    std::string temp;
    std::getline(std::cin, temp);
}

void GiaoDien::hienThiMenuChinh() {
    inTieuDe("HE THONG QUAN LY NHAN SU");
    inDongKhung("", false, 60);
    inDongKhung("[1] Dang nhap Admin", false, 60);
    inDongKhung("[2] Dang nhap Employee", false, 60);
    inDongKhung("[3] Thoat", false, 60);
    inDongKhung("", false, 60);
    inVienNgang(60);
    std::cout << MauSac::VANG << MauSac::DAM << "Lua chon: " << MauSac::RESET;
}

void GiaoDien::hienThiMenuAdmin() {
    inTieuDe("MENU ADMINISTRATOR");
    inDongKhung("[1] Them Employee", false, 60);
    inDongKhung("[2] Xoa Employee", false, 60);
    inDongKhung("[3] Tim Employee", false, 60);
    inDongKhung("[4] Cap nhat Employee", false, 60);
    inDongKhung("[5] Hien thi tat ca Employee", false, 60);
    inDongKhung("[6] Dang xuat", false, 60);
    inVienNgang(60);
    std::cout << MauSac::VANG << "Lua chon: " << MauSac::RESET;
}

void GiaoDien::hienThiMenuNhanVien() {
    inTieuDe("MENU EMPLOYEE");
    inDongKhung("[1] Xem thong tin tai khoan", false, 60);
    inDongKhung("[2] Doi password", false, 60);
    inDongKhung("[0] Dang xuat", false, 60);
    inVienNgang(60);
    std::cout << MauSac::VANG << "Lua chon: " << MauSac::RESET;
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

#include "GiaoDien.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <algorithm>

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
    const std::string XANH_DUONG="\033[94m";
}
const int RONG_KHUNG = 88;
const int LE_TRAI = 4;
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
    std::cout << std::string(LE_TRAI, ' ')
              << MauSac::XANH_DUONG
              << "++"
              << std::string(rong - 4, '=')
              << "++\n"
              << MauSac::RESET;
}
void GiaoDien::inDongKhung(
    const std::string& noiDung,
    int rong
) {
    inDongKhung(noiDung, true, rong);
}
void GiaoDien::inDongKhung(
    const std::string& noiDung,
    bool canGiua,
    int rong
) {
    int khoangTrong = rong - 4;
    int trai = 1;

    if (canGiua) {
        trai = (khoangTrong - noiDung.length()) / 2;
    }

    int phai = khoangTrong - noiDung.length() - trai;

    std::cout << std::string(LE_TRAI, ' ')
              << MauSac::XANH_DUONG << "||"
              << MauSac::RESET
              << std::string(trai, ' ')
              << noiDung
              << std::string(phai, ' ')
              << MauSac::XANH_DUONG << "||\n"
              << MauSac::RESET;
}
void GiaoDien::hienThiLoGo(){
    std::cout<<MauSac::CYAN;
    std::cout<<R"(
    ++====================================================================================++
    ||  ▄█████▄ ▄▄ ▄▄  ▄▄▄  ▄▄  ▄▄   ▄▄  ▄▄ ▄▄   ▄▄  ▄▄ ▄▄ ▄▄  ▄▄▄  ▄▄  ▄▄    ▄▄▄▄ ▄▄ ▄▄  ||
    ||  ██ ▄ ██ ██ ██ ██▀██ ███▄██   ██  ▀███▀   ███▄██ ██▄██ ██▀██ ███▄██   ███▄▄ ██ ██  ||
    ||  ▀█████▀ ▀███▀ ██▀██ ██ ▀██   ██▄▄▄ █     ██ ▀██ ██ ██ ██▀██ ██ ▀██   ▄▄██▀ ▀███▀  ||
    ||     ▀▀                                                                             ||                                           
    ++====================================================================================++
    )";
    std::cout<<MauSac::RESET;
}
void GiaoDien::inTieuDe(const std::string& tieuDe) {
    inVienNgang(50);
    std::cout<<MauSac::CYAN<<"||"<<MauSac::RESET;
    int rong=50-static_cast<int>(tieuDe.size());
    int trai=rong/2;
    int phai=rong-trai;

    std::cout<<std::string(trai,' ')
             <<MauSac::DAM<<MauSac::CYAN
             <<tieuDe
             <<MauSac::RESET
             <<std::string(phai,' ')
             <<MauSac::CYAN<<"||"
             <<MauSac::RESET<<'\n';
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
void GiaoDien::batDauKhungNhap(
    const std::string& tieuDe,
    int chieuRong
){
    int trai=(chieuRong-static_cast<int>(tieuDe.size()))/2;
    int phai=chieuRong-static_cast<int>(tieuDe.size())-trai;
    std::cout<<"\n"
             <<MauSac::CYAN
             <<"+"<<std::string(trai,'=')
             <<" "<<tieuDe<<" "
             <<std::string(phai,'=')<<"+"
             <<MauSac::RESET<<'\n';
}
std::string GiaoDien::nhapChuoiTrongKhung(
    const std::string& nhan,
    int chieuRong
){
    std::string giaTri;
    std::cout<<MauSac::CYAN<<"|"<<MauSac::RESET
             <<" "<<nhan;
    std::getline(std::cin,giaTri);
    int daDung=1+static_cast<int>(nhan.size())
                +static_cast<int>(giaTri.size());
    int conLai=std::max(0,chieuRong-daDung);
    std::cout<<std::string(conLai,' ')
             <<MauSac::CYAN<<"|"<<MauSac::RESET
             <<'\n';
    return giaTri;
}
std::string GiaoDien::nhapMatKhauTrongKhung(
    const std::string& nhan,
    int chieuRong
){
    std::string password;
    std::cout<<MauSac::CYAN<<"|"<<MauSac::RESET
             <<" "<<nhan;
#ifdef _WIN32
    while(true){
        int ch=_getch();
        if(ch==13)
            break;
        if(ch==8){
            if(!password.empty()){
                password.pop_back();
                std::cout<<"\b \b";
            }
        }
        else if(ch>=32 && ch<=126){
            password.push_back(static_cast<char>(ch));
            std::cout<<'*';
        }
    }
#else
    termios oldSettings{}, newSettings{};
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings=oldSettings;
    newSettings.s_lflag &= stactic_cast<tcflag_t>(~(ECHO|ICANON));
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    while(true){
        char ch=0;
        if(read(STDIN_FILENO,&ch, 1)!=1)
            break;
        if(ch=='\n'||ch=='\r')
            break;
        if(ch==127||ch==8){
            if(!password.empty()){
                password.pop_back();
                std::cout<<"\b \b"<<std::flush;
            }
        }
        else if(ch>=32 && ch<=126){
            password.push_back(ch);
            std::cout<<'*'<<sdt::flush;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
#endif  
    int daDung=1+static_cast<int>(nhan.size())
                +static_cast<int>(password.size());
    int conLai=std::max(0,chieuRong-daDung);
    std::cout<<std::string(conLai,' ')
             <<MauSac::CYAN<<"|"<<MauSac::RESET
             <<'\n';
    return password;
}
void GiaoDien::inThongBaoTrongKhung(
    const std::string& noiDung,
    int chieuRong
){
    int daDung=static_cast<int>(noiDung.size())+1;
    int conLai=std::max(0, chieuRong-daDung);
    std::cout<<MauSac::CYAN<<"|"<<MauSac::RESET
             <<" "<<MauSac::XANH_LA
             <<noiDung<<MauSac::RESET
             <<std::string(conLai,' ')
             <<MauSac::CYAN<<"|"<<MauSac::RESET
             <<'\n';
}
void GiaoDien::ketThucKhungNhap(int chieuRong){
    std::cout<<MauSac::CYAN
             <<"+"<<std::string(chieuRong,'=')<<"+"
             <<MauSac::RESET<<"\n";
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

void GiaoDien::hienThiKhungDangNhap(){
    std::cout<<"\n";
    std::cout<<"+============ Nhap thong tin ============+\n";
    std::cout<<"| Username:                               |\n";
    std::cout<<"| Password:                               |\n";
    std::cout<<"+========================================+\n";
}
void GiaoDien::hienThiKhungThemNhanVien(){
    std::cout << "\n";
    std::cout << "+============ Them nhan vien ============+\n";
    std::cout << "| Username:                               |\n";
    std::cout << "| Ho ten:                                 |\n";
    std::cout << "| Dia chi:                                |\n";
    std::cout << "| So dien thoai:                          |\n";
    std::cout << "| Email:                                  |\n";
    std::cout << "+========================================+\n";
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

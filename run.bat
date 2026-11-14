@echo off
chcp 65001 > nul
title PROJECT 2 - QUAN LY NHAN SU

cd /d "%~dp0"

echo ================================================
echo       PROJECT 2 - HE THONG QUAN LY NHAN SU
echo ================================================
echo.

where g++ >nul 2>nul
if errorlevel 1 (
    echo [LOI] Khong tim thay G++.
    echo Hay cai MinGW-w64 hoac MSYS2 va them g++ vao PATH.
    echo.
    pause
    exit /b 1
)

if not exist "Data" mkdir "Data"

echo [1/2] Dang bien dich chuong trinh...
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp TaiKhoan.cpp NguoiDung.cpp Admin.cpp NhanVien.cpp GiaoDien.cpp QuanLyNhanSu.cpp -o QuanLyNhanSu.exe

if errorlevel 1 (
    echo.
    echo [LOI] Bien dich that bai. Hay kiem tra loi phia tren.
    pause
    exit /b 1
)

echo.
echo [2/2] Bien dich thanh cong. Dang khoi chay...
echo.
QuanLyNhanSu.exe

echo.
echo Chuong trinh da ket thuc.
pause

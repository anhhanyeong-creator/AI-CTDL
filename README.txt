PROJECT 2 - HE THONG QUAN LY NHAN SU (BAN CLASS)
================================================

Tat ca doi tuong duoc khai bao bang class, khong dung struct.

Cac lop: TaiKhoan, NguoiDung (truu tuong), Admin, NhanVien,
FileRepository<T> (template), QuanLyNhanSu, GiaoDien.

Cac lop du lieu co constructor mac dinh, constructor co tham so (neu phu hop),
copy constructor, destructor, getter/setter. TaiKhoan va NhanVien co nap chong
toanh tu >> va <<; Admin cung co nap chong >> va << thong qua TaiKhoan.

Build thu cong:
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp TaiKhoan.cpp NguoiDung.cpp Admin.cpp NhanVien.cpp GiaoDien.cpp QuanLyNhanSu.cpp -o QuanLyNhanSu.exe

Chay: nhan dup run.bat hoac chay QuanLyNhanSu.exe.

Tai khoan Admin mac dinh (tu tao neu chua co file):
admin01 / admin123
admin02 / admin123
admin03 / admin123

Nhan vien moi co mat khau mac dinh 111111 va bat buoc doi mat khau lan dau.
Dang nhap Employee sai 3 lan thi chuong trinh ket thuc.

Luu tru:
Data/Administrator.txt: username|password|0
Data/Employee.txt: username|password|canDoiMatKhau
Data/<username>.txt: ho ten, dia chi, so dien thoai, email (moi thong tin mot dong).

Luu y: Mat khau hien duoc che bang dau * khi nhap, nhung van luu dang van ban
trong file theo yeu cau project; day chua phai ma hoa mat khau an toan.

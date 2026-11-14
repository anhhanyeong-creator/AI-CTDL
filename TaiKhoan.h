#ifndef TAI_KHOAN_H
#define TAI_KHOAN_H
#include <iostream>
#include <string>
class TaiKhoan {
private:
    std::string username, password;
    bool canDoiMatKhau;
public:
    TaiKhoan();
    TaiKhoan(const std::string& username, const std::string& password, bool canDoiMatKhau=false);
    TaiKhoan(const TaiKhoan& other);
    TaiKhoan& operator=(const TaiKhoan& other);
    ~TaiKhoan();
    std::string getUsername() const;
    std::string getPassword() const;
    bool getCanDoiMatKhau() const;
    void setUsername(const std::string& value);
    void setPassword(const std::string& value);
    void setCanDoiMatKhau(bool value);
    std::string toLine() const;
    static bool fromLine(const std::string& line, TaiKhoan& taiKhoan);
    friend std::ostream& operator<<(std::ostream& out, const TaiKhoan& tk);
    friend std::istream& operator>>(std::istream& in, TaiKhoan& tk);
};
#endif

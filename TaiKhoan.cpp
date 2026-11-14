#include "TaiKhoan.h"
#include <sstream>
TaiKhoan::TaiKhoan() : username(""), password(""), canDoiMatKhau(false) {}
TaiKhoan::TaiKhoan(const std::string& u,const std::string& p,bool doi) : username(u),password(p),canDoiMatKhau(doi) {}
TaiKhoan::TaiKhoan(const TaiKhoan& x) : username(x.username),password(x.password),canDoiMatKhau(x.canDoiMatKhau) {}
TaiKhoan& TaiKhoan::operator=(const TaiKhoan& x) {
    if (this != &x) { username=x.username; password=x.password; canDoiMatKhau=x.canDoiMatKhau; }
    return *this;
}
TaiKhoan::~TaiKhoan() {}
std::string TaiKhoan::getUsername() const{return username;}
std::string TaiKhoan::getPassword() const{return password;}
bool TaiKhoan::getCanDoiMatKhau() const{return canDoiMatKhau;}
void TaiKhoan::setUsername(const std::string& x){username=x;}
void TaiKhoan::setPassword(const std::string& x){password=x;}
void TaiKhoan::setCanDoiMatKhau(bool x){canDoiMatKhau=x;}
std::string TaiKhoan::toLine() const{return username+"|"+password+"|"+(canDoiMatKhau?"1":"0");}
bool TaiKhoan::fromLine(const std::string& line,TaiKhoan& tk){std::stringstream ss(line);std::string u,p,f;if(!std::getline(ss,u,'|')||!std::getline(ss,p,'|')||!std::getline(ss,f)||u.empty()||p.empty())return false;tk=TaiKhoan(u,p,f=="1");return true;}
std::ostream& operator<<(std::ostream& out,const TaiKhoan& tk){return out<<tk.toLine();}
std::istream& operator>>(std::istream& in,TaiKhoan& tk){std::string line;if(std::getline(in,line)&&!TaiKhoan::fromLine(line,tk))in.setstate(std::ios::failbit);return in;}

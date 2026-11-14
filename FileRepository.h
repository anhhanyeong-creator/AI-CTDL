#ifndef FILE_REPOSITORY_H
#define FILE_REPOSITORY_H
#include <fstream>
#include <string>
#include <vector>

template<class T>
class FileRepository {
private:
    std::string tenFile;
public:
    FileRepository() : tenFile("") {}
    explicit FileRepository(const std::string& tenFile) : tenFile(tenFile) {}
    FileRepository(const FileRepository<T>& other) : tenFile(other.tenFile) {}
    ~FileRepository() {}
    std::string getTenFile() const { return tenFile; }
    void setTenFile(const std::string& value) { tenFile = value; }
    std::vector<T> docTatCa() const {
        std::vector<T> ds;
        std::ifstream file(tenFile);
        if (!file.is_open()) return ds;
        std::string line;
        while (std::getline(file, line)) {
            T item;
            if (T::fromLine(line, item)) ds.push_back(item);
        }
        return ds;
    }
    bool ghiTatCa(const std::vector<T>& ds) const {
        std::ofstream file(tenFile);
        if (!file.is_open()) return false;
        for (const T& item : ds) file << item << '\n';
        return file.good();
    }
};
#endif

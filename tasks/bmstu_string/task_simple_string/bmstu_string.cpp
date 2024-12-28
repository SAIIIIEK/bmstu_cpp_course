#include <iostream>
#include <cstring>
#include <utility>

namespace bmstu {
    class string {
public:
    /// Конструктор по умолчанию
    string() : size_(0) {
        ptr_ = new char[size_ + 1];
        ptr_[0] = '\0'; 
    }
    /// Конструктор с параметром "cи строкой" 
    string(const char* str) {
        size_ = strlen(str);
        ptr_ = new char[size_ + 1];
        strcpy(ptr_, str);
    }
    /// Копирующий конструктор
    string(const string& other) : size_(other.size_) {
        ptr_ = new char[size_ + 1];
        strcpy(ptr_, other.ptr_);
    }
    /// Конструктор перемещения
    string(string&& dying) : size_(dying.size_), ptr_(dying.ptr_) {
        dying.size_ = 0;
        dying.ptr_ = nullptr;
    }
    /// Деструктор
    ~string() {
        delete[] ptr_;
    }
    /// Геттер на си-строку
    const char *c_str() const {
        return ptr_;
    }
    /// Геттер на размер
    size_t size() const {
        return size_;
    }
    /// Оператор копирующего присваивания 
    string &operator=(const string &other) {
        // Защита от самоприсваивания
        if (this != &other) {
            delete[] ptr_;
            size_ = other.size_;
            ptr_ = new char[size_ + 1];
            strcpy(ptr_, other.ptr_);
        }
        return *this;
    } 
    /// Оператор перемещающего присваивания 
    string &operator=(string &&other) {
        if (this != &other) {
            delete[] ptr_;
            size_ = other.size_;
            ptr_ = other.ptr_;
            other.size_ = 0;
            other.ptr_ = nullptr;
        } 
        return *this;
    }
    /// Оператор присваивания си строки 
    string &operator=(const char * c_str) {
        if (c_str != ptr_) { 
            delete[] ptr_; 
            if (c_str) {
                size_ = std::strlen(c_str);
                ptr_ = new char[size_ + 1];
                std::strcpy(ptr_, c_str);
            } else {
                ptr_ = nullptr;
                size_ = 0;
            }
        }
        return *this;
    }
    
    /*Все все понимают*/
    friend bmstu::string operator+(const string &left, const string &right) {
        string result;
        result.size_ = left.size_ + right.size_;
        result.ptr_ = new char[result.size_ + 1];
        strcpy(result.ptr_, left.ptr_);
        strcat(result.ptr_, right.ptr_);
        return result;
    }
    friend std::ostream &operator<<(std::ostream &os, const string &obj) {
        os << obj.ptr_;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, string &obj) {
        // ограничение на максимальную длину строки 1023 символа
        char buffer[1024]; 
        is >> buffer;
        obj = buffer;
        return is;
    }
    string &operator+=(const string &other) {
        *this = *this + other;
        return *this;
    }
    string &operator+=(char symbol) {
        char temp[2] = {symbol, '\0'};
        *this += temp;
        return *this;

    }
    char &operator[](size_t index) {
        return ptr_[index];
    }

private:
    /// Поля класса
    char *ptr_ = nullptr;
    int size_;
};
}

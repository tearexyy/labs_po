#ifndef mystring_hpp
#define mystring_hpp

#include <ostream>
#include <istream>

class MyString{
    char* string;
public:
    MyString();
    MyString(const char *);
    ~MyString();
    MyString(const MyString& other);
    const char* get_string() const { return string; }
    int get_length() const;
    char get(int i) const;
    void print() const;
    void set(int i, char c);
    void set_new_string(const char *str);
    void read_line();

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other);
    MyString(MyString&& other);
    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* other);
    MyString operator+(const MyString& other) const;
    MyString operator+(const char* other) const;
    
    bool operator==(const MyString& other) const;
    bool operator==(const char* other) const;
    bool operator!=(const MyString& other) const;
    bool operator!=(const char* other) const;
    bool operator<(const MyString& other) const;
    bool operator<(const char* other) const;
    bool operator<=(const MyString& other) const;
    bool operator<=(const char* other) const;
    
    char& operator[](int index);
};

MyString operator+(const char* string, const MyString& other);
bool operator==(const char* left, const MyString& right);
bool operator!=(const char* left, const MyString& right);
bool operator<(const char* left, const MyString& right);
bool operator<=(const char* left, const MyString& right);
std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);

#endif
#ifndef mystring_hpp
#define mystring_hpp
class MyString{
    char* string;
public:
    MyString();
    MyString(const char *);
    char get(int i);
    void set(int i, char c);
    void set_new_string(const char *str);
    void print();
    void read_line();
    ~MyString();
    MyString(const MyString& other);
    int get_length();
};
#endif
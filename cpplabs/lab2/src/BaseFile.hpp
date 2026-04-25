#include <cstdio>
class IFile
{
/*
В IFile есть только объявления функций, наследники обязаны их реализовать.
Он определяет, что должен уметь класс-наследник
*/
public:
    virtual bool can_read()=0; // возвращает true, если из файла можно считать данные;
    virtual bool can_write()=0; // возвращает true, если в файл можно записать данные;
    virtual size_t write(const void* buf, size_t n_bytes)=0;
    virtual size_t read(void* buf, size_t max_bytes)=0;
    virtual ~IFile(){}; // без virtual ~IFile() вызовется деструктор IFile, а с ним правильный деструктор, который будет
                        // переопределен классом-наследником
};

class BaseFile : public IFile { // оборачивает стандартные функции С
private:
    FILE* file;
    char* filename;
    char* mode;
public:
    BaseFile(); // конструктор по умолчанию
    BaseFile(const char* path, const char* mode); // конструктор с путем файла и парметром открытия
    BaseFile(FILE* file); // готовый указатель
    virtual ~BaseFile();
    bool is_open(); // возвращает true, если файл успешно открыт;
    bool can_read(); // возвращает true, если из файла можно считать данные;
    bool can_write(); // возвращает true, если в файл можно записать данные;
    size_t write_raw(const void* buf, size_t n_bytes); /** записывает
     *   указанное количество байт в файл и возвращает количество байт, которое
     *   удалось записать;*/
    size_t read_raw(void* buf, size_t max_bytes); /** читает доступные данные
     *   в буфер, но не более указанного количества и возвращает количество
     *   байт, которое удалось считать; */
    virtual size_t write(const void* buf, size_t n_bytes);
    virtual size_t read(void* buf, size_t max_bytes);
    long tell(); // возвращает текущий сдвиг файла ftell
    bool seek(long offset); // устанавливает сдвиг файла fseek
};

class Base32File : public BaseFile {
private:
    char* encode_buffer; // буфер для кодированных данных
    char* decode_buffer; // буфер для декодированных данных
    int buffer_size; // текущий размер буферов для данных
    const char* encoding_table; // таблица кодировки
    bool own_table; // есть ли пользовательский алфавит кодирования
    char m_leftover[5]; // массив для хранения декодированных байт, которые не попали в буфер при вызове read.
    int m_leftover_size; // кол-во символов в char m_leftover
    int m_leftover_pos; // сколько символов передано
public:
    Base32File();
    ~Base32File();
    Base32File(const char* path, const char* mode);
    Base32File(FILE* file);
    Base32File(const char* path, const char* mode, const char* table); // конструкторы с таблицей
    Base32File(FILE* file, const char* table);
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
    int encoded32_size(int raw_size);
    int decoded32_size(int encode_size);
    int encode32(const char* raw_data, int raw_size, char* dst);
    int decode32(const char* encoded_data, int encoded_size, char* dst);
};

class RleFile : public BaseFile {
    private:
    char m_leftover[5];
    int m_leftover_size;
    int m_leftover_pos;
public:
    RleFile();
    ~RleFile();
    RleFile(FILE* file);
    RleFile(const char* path, const char* mode);
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

class Base32File2 : public IFile { // работает с файлом через IFile
private:
    IFile* file;
    char* encode_buffer;
    char* decode_buffer;
    int buffer_size;
    const char* encoding_table; // таблица кодировки
    bool own_table;
    char leftover_decoded[5];
    int leftover_size;
    int leftover_pos;
public:
    Base32File2();
    Base32File2(IFile* file1);
    ~Base32File2();
    Base32File2(IFile* file, const char* table);
    bool can_read();
    bool can_write();
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes); 
    int encoded32_size(int raw_size);
    int decoded32_size(int encode_size);
    int encode32(const char* raw_data, int raw_size, char* dst);
    int decode32(const char* encoded_data, int encoded_size, char* dst);
};

class RleFile2 : public IFile {
    IFile* file;
    char m_leftover[5];
    int m_leftover_size;
    int m_leftover_pos;
public:
    RleFile2();
    ~RleFile2();
    RleFile2(IFile* file);
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
    bool can_read();
    bool can_write();
};
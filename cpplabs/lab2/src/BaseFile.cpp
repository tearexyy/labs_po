#include "BaseFile.hpp"
#include <iostream>
#include <cstring>
BaseFile::BaseFile(){
    std::cout << "вызов конструктора без параметров\n";
    file = nullptr;
    filename = nullptr;
    mode = nullptr;
}

BaseFile::BaseFile(const char* path, const char* user_mode){
    std::cout << "вызов конструктора с параметром пути к файлу и режимом\n";
    if (strcmp(user_mode, "r") != 0 && strcmp(user_mode, "w") != 0 && strcmp(user_mode, "rb") != 0 && strcmp(user_mode, "wb") != 0) {
        std::cout << "неверный режим\n";
        filename = nullptr;
        mode = nullptr;
        file = nullptr;
        return;
    }
    
    filename = new char[strlen(path) + 1];
    strcpy(filename, path); // сохранение (копирование) пути к файлу
    mode = new char[strlen(user_mode) + 1];
    strcpy(mode, user_mode); // сохранение режима открытия
    
    file = fopen(path, user_mode);
    if (file == nullptr) { //фукнкция fopen возвращает null при ошибке, поэтому при открытии делаем проверку
        std::cout << "не удалось открыть файл\n";
    } 
}

BaseFile::BaseFile(FILE* existing_file){
std::cout << "вызов конструктора с параметром указателя на файл\n";
file=existing_file;
filename = nullptr; //путь к файлу неизвестен
mode=nullptr; // режим неизвестен
}

BaseFile::~BaseFile() {
    if (file != nullptr) {
        fclose(file); // закрытие файла
    }
    delete[] filename;
    delete[] mode;
}

bool BaseFile::is_open() {
    return file != nullptr; // если есть указатель на file.
}

bool BaseFile::can_read() {
    if (file == nullptr) return false; // тк при вызове конструктора с параметрами режима и пути открываем файл, делаем проверку на указатель.
    if (mode == nullptr) return false; //предполагаем, что file записан, но не знаем режим, значит ф-ция дает false
    return (strcmp(mode, "r") == 0 || strcmp(mode, "rb") == 0); // при равенстве строк strcmp дает 0
}

bool BaseFile::can_write() { //аналогично
    if (mode == nullptr) return false;
    return (strcmp(mode, "w") == 0 || strcmp(mode, "wb") == 0);
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) { // берем n байт из буфера
    if (file == nullptr || buf == nullptr || can_write()==0) return 0;
    return fwrite(buf, 1, n_bytes, file); // указатель на данные, размер элемента, количество элементов и указатель на файл
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) { // побайтовое копирование из файла в буффер
    if (file == nullptr || buf == nullptr || can_read() == 0) return 0;
    return fread(buf, 1, max_bytes, file); // указатель на буфер, размер элемента, количество элементов и указатель на файл
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}

long BaseFile::tell() {
    if (file == nullptr){
        std::cout << "позиция не определена\n";
        return -1;
    };
    return ftell(file); // возвращает текущую позицию указателя чтения/записи в файловом потоке, измеряемую в байтах от начала файла
}

bool BaseFile::seek(long offset) {
    if (file == nullptr) return false;
    return fseek(file, offset, SEEK_SET) == 0; // file - указатель, offset - кол-во байтов на сдвиг (позиция), 
    // SEEK_SET - параметр, который определяет, что сдвиг происходит относительно начала файла
}

Base32File::Base32File() : BaseFile() { // явный вызов конструктора базового класса
    std::cout << "вызов конструктора Base32File без параметров\n";
    encode_buffer = nullptr;
    decode_buffer = nullptr;
    buffer_size = 0;
    encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    own_table = false;     
    m_leftover_size = 0;
    m_leftover_pos = 0;
}
// явный вызов конструктора базового класса
Base32File::Base32File(const char* path, const char* mode) : BaseFile(path, mode){ // у BaseFile убрали типы тк BaseFile(path, mode)
                                                                                   // рабоатет как вызов
    std::cout << "вызов конструктора Base32File с параметром пути к файлу и режимом\n";
    encode_buffer = nullptr;
    decode_buffer = nullptr;
    buffer_size = 0;
    encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    own_table = false;  
     m_leftover_size = 0;
    m_leftover_pos = 0;
};

Base32File::Base32File(FILE* file) : BaseFile(file){ // явный вызов конструктора базового класса
std::cout << "вызов конструктора Base32File с параметром указателя на файл\n";
    encode_buffer = nullptr;
    decode_buffer = nullptr;
    buffer_size = 0;
    encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    own_table = false;  
     m_leftover_size = 0;
    m_leftover_pos = 0;
}

Base32File::Base32File(const char* path, const char* mode, const char* table) : BaseFile(path, mode){ // явный вызов конструктора базового класса
    std::cout << "вызов конструктора Base32File с параметрами и таблицей\n";
    encode_buffer = nullptr;
    decode_buffer = nullptr;
    buffer_size = 0;
    if (table != nullptr && strlen(table) == 32) { // проверка на 32 символа
        encoding_table = new char[33]; // new, чтобы не сохранять указатель на несуществующую строку
        strcpy((char*)encoding_table, table); // копирование в динамичсекую память
        own_table = true;  // нужно будет удалить в деструкторе
    } else {
        encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456"; // если таблица не соотвествует размерам, надо использовать по умолчанию
        own_table = false;
    }
     m_leftover_size = 0;
    m_leftover_pos = 0;
}

Base32File::Base32File(FILE* file, const char* table) : BaseFile(file) {// явный вызов конструктора базового класса
    std::cout << "Вызов конструктора Base32File с FILE* и таблицей\n";
    encode_buffer = nullptr;
    decode_buffer = nullptr;
    buffer_size = 0;
    
    if (table != nullptr && strlen(table) == 32) {
        encoding_table = new char[33];
        strcpy((char*)encoding_table, table);
        own_table = true;
    } else {
        encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
        own_table = false;
    }
     m_leftover_size = 0;
    m_leftover_pos = 0;
}

Base32File::~Base32File() {
    std::cout << "вызов деструктора Base32File\n";
    delete[] encode_buffer;
    delete[] decode_buffer;
    
    if (own_table) { // если была пользовательская таблица, освобождаем память
        delete[] encoding_table;
    }
}

int Base32File::encode32(const char *raw_data, int raw_size, char *dst) {
    if (raw_size < 0 || raw_data == nullptr || dst == nullptr) { //проверка на подходящий ввод
        return 1;
    }
    
    if (raw_size == 0) {
        return 0;
    }
    const char* table = encoding_table;
    
    int index_in_dst = 0;//индекс в dst буффере
    int bit_buffer = 0; //буффер
    int counting = 0; //счетчик битов для 1 пятерки
    
    for (int i = 0; i < raw_size; i++) {
        unsigned char byte = raw_data[i];
        
        for (int j = 7; j >= 0; j--) {//добавление в буффер
            int bit = (byte >> j) & 1; // текущий бит
            bit_buffer = (bit_buffer << 1) | bit;//освобождаем одну позицию слева и добавляем текущий бит 
            counting++; //добавили один бит = увеличили счетчик битов в буффере
            
            //накопили 5 битов = кодируем, тк символ кодирует 5 бит информации
            if (counting == 5) {
                dst[index_in_dst] = table[bit_buffer]; //закодировали и положили в буффер
                index_in_dst++; //предыдущая ячейка заполнена  = нужна следующая
                bit_buffer = 0;
                counting = 0;
            }
        }
    }
    
    if (counting > 0) { //не полностью поделилось на пятерки
        bit_buffer = bit_buffer << (5 - counting); //сдвигаем на оставшееся количество бит влево
        dst[index_in_dst] = table[bit_buffer]; // кодируем в символ
        index_in_dst++; //предыдущая ячейка заполнена  = нужна следующая
    }
    
    dst[index_in_dst] = '\0';
    return 0;
}

int Base32File::decode32(const char *encoded_data, int encoded_size, char *dst) {
    if (encoded_data == nullptr || encoded_size < 0 || dst == nullptr) {
        return 1;
    }
    
    if (encoded_size == 0) {
        return 0;
    }
    const char* table = encoding_table;
    for (int i = 0; i < encoded_size; i++) { //проходим по таблице
        bool is_it_there = false; // проверка есть ли символ в таблице
        for (int j = 0; j < 32; j++) {
            if (encoded_data[i] == table[j]) {
                is_it_there = true;
                break;
            }
        }
        if (!is_it_there) {
            return 2; 
        }
    }
    int index_in_dst = 0;//индекс в dst буффере
    int bit_buffer = 0; //буффер
    int counting = 0; //счетчик битов для 1 пятерки в bit_buffer

    for (int i = 0; i < encoded_size; i++) {
        int symbol_value = -1; //номер символа в таблице
        for (int j = 0; j < 32; j++) {
            if (encoded_data[i] == table[j]) { // если сошлось, 
                symbol_value = j; // запоминаем номер символа
                break;
            }
        }
        
        for (int k = 4; k >= 0; k--) { //добавление 5 символов в буффер
            int bit = (symbol_value >> k) & 1;
            bit_buffer = (bit_buffer << 1) | bit;
            counting++;
            
            if (counting == 8) { // изначальный символ - 8 бит
                dst[index_in_dst] = (unsigned char)bit_buffer; //декодировали и положили в буффер
                index_in_dst++;
                bit_buffer = 0;
                counting = 0;
            }
        }
    }
    
    return 0;

}

int Base32File::encoded32_size(int raw_size){
    int new_len = raw_size*8;
    if (new_len%5 == 0){
        return new_len / 5;
    }
    new_len += (5 - new_len%5);
    return new_len / 5;
}
int Base32File::decoded32_size(int encode_size){
    return encode_size*5/8;
}

size_t Base32File::write(const void* buf, size_t n_bytes) { // buf - указатель на данные, n - кол-во байт, записывает закодированные данные в файл
    if (buf == nullptr || n_bytes == 0) return 0;
    if (!can_write()) return 0;

    int encoded_size = encoded32_size(n_bytes); // размер закодированных данных

    if (encoded_size > buffer_size) { // при необходимости увеличиваем буффер, buffer_size - текущий размер буфера encode_buffer
        delete[] encode_buffer;
        encode_buffer = new char[encoded_size + 1];
        buffer_size = encoded_size;
    }
    int result = encode32((const char*)buf, n_bytes, encode_buffer); // кодирование и запись
    if (result != 0) return 0; // encode32 возвращает 0 после выполнения, значит, если она не 0, то данные не записаны

    size_t written = BaseFile::write(encode_buffer, encoded_size); // вызываем метод write класса BaseFile и записываем закодированные данные
    return (written == encoded_size) ? n_bytes : 0; // проверяем на совпадение кол-ва записанных байт
}

size_t Base32File::read(void* buf, size_t max_bytes) { // чтение с декодированием
/*
    * копируем остатки строки в пользовательский буфер из m_leftover, читаем закодированные символы, декодирование, копирование в 
    * пользовательский буфер, остаток сохраняем в m_leftover
    * в последующих вызовах сначала отдаем leftover и только потом читаем файл. 
*/
    if (buf == nullptr || max_bytes == 0) return 0;
    if (!can_read()) return 0;
    
    char* outdata = (char*)buf; // создание длкального указателя
    size_t total_decoded = 0; // сколько байт уже передали в пользовательский буфер
    

    while (m_leftover_pos < m_leftover_size && total_decoded < max_bytes) { // если в leftover есть еще нескопированные байты и в буфере есть место
        outdata[total_decoded] = m_leftover[m_leftover_pos];
        total_decoded++;
        m_leftover_pos++;
    }
    
    if (m_leftover_pos >= m_leftover_size) { // все ли остатки скопированны в пользовательский буфер
        m_leftover_size = 0;
        m_leftover_pos = 0;
    }
    
    if (total_decoded == max_bytes) { // проверяем совпадает ли количество байт в буфере
        return total_decoded;
    }
    
    int encoded_needed = encoded32_size(max_bytes - total_decoded); // нужно больше байт, проверяем сколько именно
    if (encoded_needed < 8) encoded_needed = 8;  // минимум 8 символов, минимальное кол-во символов, которое даст целое число байт
    
    if (encoded_needed > buffer_size) { // проверяем хватает ли буфера для закодированных данных из файла
        delete[] decode_buffer;
        decode_buffer = new char[encoded_needed + 1];
        buffer_size = encoded_needed;
    }
    
    size_t bytes_read = 0; // cчетчик прочитанных закодированных байт
    while (bytes_read < (size_t)encoded_needed) { // прочтение до нужного количества
        size_t got = BaseFile::read(decode_buffer + bytes_read, encoded_needed - bytes_read); // decode_buffer + bytes_read - место в буфере
                                                                                              // encoded_needed - bytes_read - сколько осталось прочитать
        if (got == 0) break; // got - сколько прочитали за одну итерацию
        bytes_read += got; // всего прочитано
    }
    if (bytes_read == 0) { // ничего не прочитано - проверка на когннец файла
        return total_decoded; 
    }
    
    int decoded_size = decoded32_size(bytes_read);
    char* decoded = new char[decoded_size]; // массив для декодированных данных
    int result = decode32(decode_buffer, bytes_read, decoded); // декодировка
    
    if (result != 0) { // успешность декодирования
        delete[] decoded;
        return total_decoded;
    }
    
    size_t to_copy; // сколько нужно копировать в пользовательский буффер
    if (total_decoded + decoded_size > max_bytes) { // если получилось больше
    to_copy = max_bytes - total_decoded;} // копируем столько, сколько еще осталось копировать
    else{
    to_copy = decoded_size; // столько, сколько декодировали
    }
    for (size_t i = 0; i < to_copy; i++) { // копируем
        outdata[total_decoded] = decoded[i];
        total_decoded++;
    }
    if (to_copy < (size_t)decoded_size) {
        m_leftover_size = decoded_size - to_copy; // проверяем, осталось ли что-то, остатки копируем в leftover
        for (int i = 0; i < m_leftover_size; i++) {
            m_leftover[i] = decoded[to_copy + i];
        }
        m_leftover_pos = 0;
    }
    
    delete[] decoded;
    return total_decoded;
}

RleFile::RleFile() : BaseFile() {
    std::cout << "вызов конструктора RleFile без параметров\n"; 
    m_leftover_size = 0;
    m_leftover_pos = 0;
}

RleFile::RleFile(const char* path, const char* mode) : BaseFile(path, mode){ // у BaseFile убрали типы тк BaseFile(path, mode)
                                                                                   // рабоатет как вызов
    std::cout << "вызов конструктора RleFile с параметром пути к файлу и режимом\n";
    m_leftover_size = 0;
    m_leftover_pos = 0;
};

RleFile::RleFile(FILE* file) : BaseFile(file){
    std::cout << "вызов конструктора RleFile с параметром указателя на файл\n";
    m_leftover_size = 0;
    m_leftover_pos = 0;
}

size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (buf == nullptr || n_bytes == 0) return 0;
    if (!can_write()) return 0;

    const char* data = (const char*)buf; // исходные данные
    char* compressed = new char[n_bytes * 2]; // буфер для сжатых данных, если все символы различны
    int position = 0; // текущая позиция в буфере
    
    int i = 0;
    while (i < n_bytes) {
        char current = data[i]; // текущий символ
        int count = 1; // счётчик повторений

        while (i + count < n_bytes && data[i + count] == current) {// смотрим повторения символов и записываем в compressed символ и количество
            count++;
        }
        compressed[position] = current;
        position++;
        compressed[position] = (char)count;
        position++;
        i += count;
    }
    
    size_t write_res = BaseFile::write(compressed, position); // position = размер сжатых данных
    delete[] compressed;
    if (write_res == position){ // кол-во байт, записанных в файл
        return n_bytes;
    }
    else{
        return 0;
    }
}

size_t RleFile::read(void* buf, size_t max_bytes) {
/*
    * копируем остатки строки в пользовательский буфер из m_leftover, читаем из файла по 2 байта (символ и кол-во повторений), 
    * генерируем символ count раз. Делаем проверку: если есть место в буфере, копируем туда, 
    * если буфер заполнился, сохраняем в m_leftover
 */
    if (buf == nullptr || max_bytes == 0) return 0;
    if (!can_read()) return 0;

    char* outdata = (char*)buf;
    size_t total_decoded = 0;

    while (m_leftover_pos < m_leftover_size && total_decoded < max_bytes){ // если в leftover есть еще нескопированные байты и в буфере есть место
        outdata[total_decoded] = m_leftover[m_leftover_pos]; // копируем байт
        total_decoded++;
        m_leftover_pos++;
    }
    if (m_leftover_pos >= m_leftover_size) { m_leftover_size = 0; m_leftover_pos = 0; } // если leftover закончился
    if (total_decoded == max_bytes) return total_decoded; // если буфер заполнился

    while (total_decoded < max_bytes) {
        unsigned char byte[2];
        size_t n = 0;
        while (n < 2) { // читаем по 2 байта, тк так записывается RLE
            size_t got = BaseFile::read(byte + n, 2 - n); // got - сколько прочитали за итерацию
            if (got == 0) break; // файл закончился
            n += got; // все прочитанные байты
        }
        if (n < 2) break;

        char current = (char)byte[0];
        unsigned char count = byte[1];

        for (unsigned char j = 0; j < count; j++) {
            if (total_decoded < max_bytes){ //если есть место в буфере
                outdata[total_decoded] = current; // копируем символ
                total_decoded++;
            }
            else {
                m_leftover[m_leftover_size] = current;
                m_leftover_size++;
            }
        }
        m_leftover_pos = 0; // позиция leftover на начло
    }

    return total_decoded; // возвращаем кол-во скопированных байт в пользовательский буфер
}
RleFile::~RleFile() {
    std::cout << "вызов деструктора RleFile\n";
}

Base32File2::Base32File2(IFile* file1){
    file =  file1;
    std::cout << "вызов конструктора Base32File2 с IFile*\n";
    encode_buffer = nullptr;
    decode_buffer = nullptr;
    buffer_size = 0;
    encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    own_table = false;
    leftover_size = 0;
    leftover_pos = 0;
}

bool Base32File2::can_read() { 
    return file->can_read(); 
}

bool Base32File2::can_write() { 
    return file->can_write(); 
}

Base32File2::Base32File2(IFile* file, const char* table){
    std::cout << "вызов конструктора Base32File2 с IFile* и таблицей\n";
    encode_buffer = nullptr;
    decode_buffer = nullptr;
    buffer_size = 0;
    
    if (table != nullptr && strlen(table) == 32) {
        encoding_table = new char[33];
        strcpy((char*)encoding_table, table);
        own_table = true;
    } else {
        encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
        own_table = false;
    }
}

Base32File2::~Base32File2() {
    std::cout << "вызов деструктора Base32File2\n";
    delete[] encode_buffer;
    delete[] decode_buffer;
    if (own_table) {
        delete[] encoding_table;
    }
    if(file!= nullptr){delete file;}
}

size_t Base32File2::write(const void* buf, size_t n_bytes) { // buf - указатель на данные, n - кол-во байт
    if (buf == nullptr || n_bytes == 0) return 0;
    if (!can_write()) return 0;

    int encoded_size = encoded32_size(n_bytes); // размер закодированных данных

    if (encoded_size > buffer_size) { // при необходимости увеличиваем буффер, buffer_size - текущий размер буфера encode_buffer
        delete[] encode_buffer;
        encode_buffer = new char[encoded_size + 1];
        buffer_size = encoded_size;
    }
    int result = encode32((const char*)buf, n_bytes, encode_buffer); // кодирование и запись
    if (result != 0) return 0; // encode32 возвращает 0 после выполнения, значит, если она не 0, то данные не записаны

    size_t written = file->write(encode_buffer, encoded_size); // записываем закодированные данные используя абстрактный класс
    return (written == encoded_size) ? n_bytes : 0; // проверяем на совпадение кол-ва записанных байт
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
    if (buf == nullptr || max_bytes == 0) return 0;
    if (!can_read()) return 0;
    
    char* outdata = (char*)buf; // создание длкального указателя
    size_t total_decoded = 0; // сколько байт уже передали в пользовательский буфер
    

    while (leftover_pos < leftover_size && total_decoded < max_bytes) { // если в leftover есть еще нескопированные байты и в буфере есть место
        outdata[total_decoded] = leftover_decoded[leftover_pos];
        total_decoded++;
        leftover_pos++;
    }
    
    if (leftover_pos >= leftover_size) { // все ли остатки скопированны в пользовательский буфер
        leftover_size = 0;
        leftover_pos = 0;
    }
    
    if (total_decoded == max_bytes) { // проверяем совпадает ли количество байт в буфере
        return total_decoded;
    }
    
    int encoded_needed = encoded32_size(max_bytes - total_decoded); // нужно больше байт, проверяем сколько именно
    if (encoded_needed < 8) encoded_needed = 8;  // минимум 8 символов, минимальное кол-во символов, которое даст целое число байт
    
    if (encoded_needed > buffer_size) { // проверяем хватает ли буфера для закодированных данных из файла
        delete[] decode_buffer;
        decode_buffer = new char[encoded_needed + 1];
        buffer_size = encoded_needed;
    }
    
    size_t bytes_read = 0; // cчетчик прочитанных закодированных байт
    while (bytes_read < (size_t)encoded_needed) { // прочтение до нужного количества
        size_t got = file->read(decode_buffer + bytes_read, encoded_needed - bytes_read); // decode_buffer + bytes_read - место в буфере
                                                                                              // encoded_needed - bytes_read - сколько осталось прочитать
        if (got == 0) break; // got - сколько прочитали за одну итерацию
        bytes_read += got; // всего прочитано
    }
    if (bytes_read == 0) { // ничего не прочитано - проверка на когннец файла
        return total_decoded; 
    }
    
    int decoded_size = decoded32_size(bytes_read);
    char* decoded = new char[decoded_size]; // массив для декодированных данных
    int result = decode32(decode_buffer, bytes_read, decoded); // декодировка
    
    if (result != 0) { // успешность декодирования
        delete[] decoded;
        return total_decoded;
    }
    
    size_t to_copy; // сколько нужно копировать в пользовательский буффер
    if (total_decoded + decoded_size > max_bytes) { // если получилось больше
    to_copy = max_bytes - total_decoded;} // копируем столько, сколько еще осталось копировать
    else{
    to_copy = decoded_size; // столько, сколько декодировали
    }
    for (size_t i = 0; i < to_copy; i++) { // копируем
        outdata[total_decoded] = decoded[i];
        total_decoded++;
    }
    if (to_copy < (size_t)decoded_size) {
        leftover_size = decoded_size - to_copy; // проверяем, осталось ли что-то, остатки копируем в leftover
        for (int i = 0; i < leftover_size; i++) {
            leftover_decoded[i] = decoded[to_copy + i];
        }
        leftover_pos = 0;
    }
    
    delete[] decoded;
    return total_decoded;
}

int Base32File2::encoded32_size(int raw_size) {
    int new_len = raw_size * 8;
    if (new_len % 5 == 0) {
        return new_len / 5;
    }
    new_len += (5 - new_len % 5);
    return new_len / 5;
}

int Base32File2::decoded32_size(int encode_size) {
    return encode_size * 5 / 8;
}

int Base32File2::encode32(const char *raw_data, int raw_size, char *dst) {
    if (raw_size < 0 || raw_data == nullptr || dst == nullptr) {//проверка на неподходящий ввод
        return 1;
    }
    
    if (raw_size == 0) {
        return 0;
    }
    const char* table = encoding_table;
    
    int index_in_dst = 0;//индекс в dst буффере
    int bit_buffer = 0; //буффер
    int counting = 0; //счетчик битов для 1 пятерки
    
    for (int i = 0; i < raw_size; i++) {
        unsigned char byte = raw_data[i];
        
        for (int j = 7; j >= 0; j--) {//добавление в буффер
            int bit = (byte >> j) & 1; // текущий бит
            bit_buffer = (bit_buffer << 1) | bit;//освобождаем одну позицию слева и добавляем текущий бит 
            counting++; //добавили один бит = увеличили счетчик битов в буффере
            
            //накопили 5 битов = кодируем
            if (counting == 5) {
                dst[index_in_dst] = table[bit_buffer]; //закодировали и положили в буффер
                index_in_dst++; //предыдущая ячейка заполнена  = нужна следующая
                bit_buffer = 0;
                counting = 0;
            }
        }
    }
    
    if (counting > 0) { //не полностью поделилось на пятерки
        bit_buffer = bit_buffer << (5 - counting); //сдвигаем на оставшееся количсетво бит влево
        dst[index_in_dst] = table[bit_buffer];
        index_in_dst++;
    }
    
    dst[index_in_dst] = '\0';
    return 0;
}


int Base32File2::decode32(const char *encoded_data, int encoded_size, char *dst) {
    if (encoded_data == nullptr || encoded_size < 0 || dst == nullptr) {
        return 1;
    }
    
    if (encoded_size == 0) {
        return 0;
    }
    const char* table = encoding_table;
    for (int i = 0; i < encoded_size; i++) { //проходим по таблице
        bool is_it_there = false;
        for (int j = 0; j < 32; j++) {
            if (encoded_data[i] == table[j]) {
                is_it_there = true;
                break;
            }
        }
        if (!is_it_there) {
            return 2; 
        }
    }
    int index_in_dst = 0;//индекс в dst буффере
    int bit_buffer = 0; //буффер
    int counting = 0; //счетчик битов для 1 пятерки

    for (int i = 0; i < encoded_size; i++) {
        int symbol_value = -1; //номер символа в таблице
        for (int j = 0; j < 32; j++) {
            if (encoded_data[i] == table[j]) {
                symbol_value = j;
                break;
            }
        }
        
        for (int k = 4; k >= 0; k--) { //добавление 5 символов в буффер
            int bit = (symbol_value >> k) & 1;
            bit_buffer = (bit_buffer << 1) | bit;
            counting++;
            
            if (counting == 8) {
                dst[index_in_dst] = (unsigned char)bit_buffer; //декодировали и положили в буффер
                index_in_dst++;
                bit_buffer = 0;
                counting = 0;
            }
        }
    }
    return 0;
}

Base32File2::Base32File2(){
    file = nullptr;
    encode_buffer = nullptr;
    decode_buffer = nullptr;
    buffer_size = 0;
    encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    own_table = false;
}

RleFile2::RleFile2() {
    file = nullptr;
    m_leftover_pos = 0;
    m_leftover_size = 0;
    std::cout << "вызов конструктора RleFile2 без параметров\n"; 
}

RleFile2::RleFile2(IFile* file1){
    file = file1;
    m_leftover_size = 0;
    m_leftover_pos = 0;
}

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    if (buf == nullptr || n_bytes == 0) return 0;
    if (!can_write()) return 0;

    const char* data = (const char*)buf; // исходные данные
    char* compressed = new char[n_bytes * 2]; // буфер для сжатых данных, если все символы различны
    int position = 0; // текущая позиция в буфере
    
    int i = 0;
    while (i < n_bytes) {
        char current = data[i]; // текущий символ
        int count = 1; // счётчик повторений

        while (i + count < n_bytes && data[i + count] == current) {// смотрим повторения символов и записываем в compressed символ и количество
            count++;
        }
        compressed[position] = current;
        position++;
        compressed[position] = (char)count;
        position++;
        i += count;
    }
    
    size_t write_res = file->write(compressed, position); // position = размер сжатых данных
    delete[] compressed;
    if (write_res == position){ // кол-во байт, записанных в файл
        return n_bytes;
    }
    else{
        return 0;
    }
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    /*
    * копируем остатки строки в пользовательский буфер из m_leftover, читаем из файла по 2 байта (символ и кол-во повторений), 
    * генерируем символ count раз. Делаем проверку: если есть место в буфере, копируем туда, 
    * если буфер заполнился, сохраняем в m_leftover
 */
    if (buf == nullptr || max_bytes == 0) return 0;
    if (!can_read()) return 0;

    char* outdata = (char*)buf;
    size_t total_decoded = 0;

    while (m_leftover_pos < m_leftover_size && total_decoded < max_bytes){ // если в leftover есть еще нескопированные байты и в буфере есть место
        outdata[total_decoded] = m_leftover[m_leftover_pos]; // копируем байт
        total_decoded++;
        m_leftover_pos++;
    }
    if (m_leftover_pos >= m_leftover_size) { m_leftover_size = 0; m_leftover_pos = 0; } // если leftover закончился
    if (total_decoded == max_bytes) return total_decoded; // если буфер заполнился

    while (total_decoded < max_bytes) {
        unsigned char byte[2];
        size_t n = 0;
        while (n < 2) { // читаем по 2 байта, тк так записывается RLE
            size_t got = file->read(byte + n, 2 - n); // got - сколько прочитали за итерацию
            if (got == 0) break; // файл закончился
            n += got; // все прочитанные байты
        }
        if (n < 2) break;

        char current = (char)byte[0];
        unsigned char count = byte[1];

        for (unsigned char j = 0; j < count; j++) {
            if (total_decoded < max_bytes){ //если есть место в буфере
                outdata[total_decoded] = current; // копируем символ
                total_decoded++;
            }
            else {
                m_leftover[m_leftover_size] = current;
                    m_leftover_size++;
            }
        }
        m_leftover_pos = 0; // позиция leftover на начло
    }

    return total_decoded; // возвращаем кол-во скопированных байт в пользовательский буфер
}

RleFile2::~RleFile2() {
    std::cout << "вызов деструктора RleFile2\n";
    delete file;
}

bool RleFile2::can_read() { 
    return file->can_read(); 
}

bool RleFile2::can_write() { 
    return file->can_write(); 
}
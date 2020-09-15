/*
Пермяков Никита
github nikit34
Создать класс BitString для работы с 96-битовыми строками.
Битовая строка должна быть представлена двумя полями:
    1) старшая часть unsigned long long,
    2) младшая часть unsigned int.
Должны быть реализованы все традиционные операции для работы с битами: and, or, xor, not.
Реализовать сдвиг влево shiftLeft и сдвиг вправо shiftRight на заданное количество битов.
Реализовать операцию вычисления количества единичных битов, операции сравнения по количеству единичных битов.
Реализовать операцию проверки включения.
*/

#include<iostream>
#include<string>
#include<assert.h>

const unsigned int UNIT_N = 28;
const unsigned int LENGTH_A = 20;
const unsigned int LENGTH_B = 10;
const unsigned int SIZE_A = 64;
const unsigned int SIZE_B = 32;


class TestCase {
    public:
        template <typename Ta, typename Tb>
        void test_field_length(Ta a, Tb b) {
            int length_a = std::to_string(a).length();
            int length_b = std::to_string(b).length();
            if (length_a < length_b)
                std::swap(length_a, length_b);
            assert(("\nTest Error: overflow for [a b] by [length]\n", length_a < LENGTH_A && length_b < LENGTH_B));
            std::cout << "\nResult test at length - OK" << std::endl;
        };

        template <typename Ta, typename Tb>
        void test_field_size(Ta a, Tb b) {
            int size_a = std::to_string(a).size();
            int size_b = std::to_string(b).size();
            if (size_a < size_b)
                std::swap(size_a, size_b);
            assert(("\nTest Error: overflow for [a b] by [size]\n", size_a < SIZE_A && size_b < SIZE_B));
            std::cout << "\nResult test at size   - OK" << std::endl;
        };
};


class BitString {
public:
    BitString() {
        this->unit = nullptr;
        this->count = 0;
        this->bits = { 1, 1 };
    };

    struct fields {
        unsigned long long part_large;
        unsigned int part_small;
    } bits;

    void recard_fields() {
        std::string str;
        for(unsigned int i = 0; i < this->count; ++i)
            str.push_back(this->unit[i]);

        if(this->count > LENGTH_B - 1) {
            const std::string str_large = '1' + str.substr(0, this->count - LENGTH_B + 1);
            this->bits.part_large = std::stoull(str_large, nullptr, 10);
            const std::string str_small = '1' + str.substr(this->count - LENGTH_B + 1, LENGTH_B - 1);
            this->bits.part_small = std::stoul(str_small, nullptr, 10);
        }
        else {
            this->bits.part_small = std::stoul('1' + str.substr(0, this->count), nullptr, 10);
        }
    };

    class Error {
        public:
            Error() {
                std::cout << std::endl << "Error: ";
            };
            Error(const std::string &msg) : Error() {
                std::cout << msg << std::endl;
            };
    };

    int sizeBitString() {
        return this->count;
    };

    template <typename T>
    void valid_input_length(T a) {
        int length_a = a.length();
        assert(("\nTest Error: overflow for [a] by [length]\n", length_a <= UNIT_N));
    }

    void enter() {
        std::string str;
        std::cout << "Введите битовую строку: " << std::endl;
        std::cin >> str;
        this->count = str.size();
        this->valid_input_length(str);

        for(unsigned int i = 0; i < this->count; i++)
            if (str[i] != '0' && str[i] != '1')
                throw BitString::Error();

        this->unit = new unsigned char[this->count];

        for(unsigned int i = 0; i < this->count; i++)
            this->unit[i] = str[i];
        this->recard_fields();
    };

    void show() {
        for (unsigned int i = 0; i < this->count; i++)
            std::cout << this->unit[i];
    };

    std::string notBit() {
        std::string str;

        for(unsigned int i = 0; i < this->count; i++) {
            if(this->unit[i] == '0')
                this->unit[i] = '1';
            else
                if(this->unit[i] == '1')
                    this->unit[i] = '0';
            str += this->unit[i];
        }
        return str;
    };

    std::string andBit(BitString b) {
        std::string str;

        for (unsigned int i = 0; i < this->count; i++) {
            if(this->unit[i] == '0' && b.unit[i] == '1')
                str += '0';
            else
                if(this->unit[i] == '1' && b.unit[i] == '0')
                    str += '0';
                else
                    str += this->unit[i];
        }
        return str;
    };

    std::string orBit(BitString b) {
         std::string str;

         for(unsigned int i = 0; i < this->count; i++) {
             if(this->unit[i]== '0' && b.unit[i] == '1')
                 str += '1';
             else
                 if(this->unit[i] == '1' && b.unit[i] == '0')
                     str += '1';
                 else
                     str += this->unit[i];
         }
         return str;
    };

    std::string xorBit(BitString b) {
        std::string str;

        for(unsigned int i = 0; i < this->count; i++) {
            if(this->unit[i] == '0' && b.unit[i] == '1')
                str += '1';
            else
                if(this->unit[i] == '1' && b.unit[i] == '0')
                    str += '1';
                else
                    if(this->unit[i] == '0' && b.unit[i] == '0')
                        str += '0';
                    else
                        if(this->unit[i] == '1' && b.unit[i] == '1')
                            str += '0';
        }
        return str;
    }

    std::string rightShift(unsigned int n) {
        std::string str;

        for(unsigned int i = 0; i < this->count; i++)
            str += this->unit[i];

        str.erase(0, n);

        for(unsigned int i = 0; i < n; i++)
             str.append("0");
        return str;
    }

    std::string leftShift(unsigned int n) {
        std::string str;

        for(unsigned int i = 0; i < this->count; i++)
            str += this->unit[i];

        str.erase(this->count-n, n);
        str.insert(0, n, '0');

        return str;
    }

    std::string rightCycleShift(unsigned int n) {
        std::string str;

        for(unsigned int i = n; i < this->count; i++)
            str += this->unit[i];

        for(unsigned int i = 0; i < n; i++)
            str += this->unit[i];

         return str;
    }

    std::string leftCycleShift(unsigned int n) {
        std::string str;

        for(unsigned int i = count - n; i < this->count; i++)
            str += this->unit[i];

        for(unsigned int i = 0; i < this->count - n; i++)
            str += this->unit[i];

        return str;
    }

private:
    unsigned char* unit;
    unsigned int count;
};


int main() {
    setlocale(LC_ALL, "RUS");

    TestCase tests;
    BitString a, b;

    try {
        a.enter();
        b.enter();

        if (a.sizeBitString() != b.sizeBitString())
            throw BitString::Error();

        int key = 0;
        bool flag_loop = true;
        while(flag_loop) {
            std::cout << std::endl
                << " 1  - сложить битовые строки" << std::endl
                << " 2  - перемножить битовые строки" << std::endl
                << " 3  - сложить по модулю битовые строки " << std::endl
                << " 4  - выполнить побитовое отрицание  строк" << std::endl
                << " 5  - выполнить побитовый сдвиг вправо строк" << std::endl
                << " 6  - выполнить побитовый сдвиг влево  строк " << std::endl
                << " 7  - выполнить циклический сдвиг строк вправо   " << std::endl
                << " 8  - выполнить циклический сдвиг строк влево  " << std::endl
                << " 9  - узнать состояние строк" << std::endl
                << " 10 - запустить тесты внутреннего представления" << std::endl
                << " 11 - очистить экран" << std::endl
                << " 12 - выйти"<<std::endl;
            std::cin >> key;

            switch(key) {
                case 1: {
                    std::cout << std::endl << "Сумма равна: " << a.orBit(b) << std::endl << std::endl;
                    a.recard_fields();
                    break;
                }
                case 2: {
                    std::cout << std::endl << "Произведение равно: " << a.andBit(b) << std::endl << std::endl;
                    a.recard_fields();
                    break;
                }
                case 3: {
                    std::cout << std::endl << "Сумма по модулю равна: " << a.xorBit(b) << std::endl << std::endl;
                    a.recard_fields();
                    break;
                }
                case 4: {
                    std::cout << std::endl << "Побитовое отрицание первой строки равно: " << a.notBit() << std::endl
                                           << "Побитовое отрицание второй строки равно: " << b.notBit() << std::endl << std::endl;
                    a.recard_fields();
                    break;
                }
                case 5: {
                    std::cout << " На сколько двигать строки?" << std::endl;
                    unsigned int n;
                    std::cin >> n;

                    if (n < 0)
                        throw BitString::Error("Invalid shift value");

                    std::cout << "Результаты побитового сдвига:" << std::endl
                         << "   первая строка - " << a.rightShift(n) << std::endl
                         << "   вторая строка - " << b.rightShift(n) << std::endl << std::endl;

                    a.recard_fields();
                    b.recard_fields();
                    break;
                }
                case 6: {
                    std::cout << " На сколько будем двигать строки?" <<std::endl;
                    unsigned int n;
                    std::cin >> n;

                    if (n < 0)
                        throw BitString::Error();

                    std::cout << "Результаты побитового сдвига:" << std::endl
                        << "   первая строка - " << a.leftShift(n) << std::endl
                        << "   вторая строка - " << b.leftShift(n) << std::endl << std::endl;

                    a.recard_fields();
                    b.recard_fields();
                    break;
                }
                case 7: {
                    std::cout << " На сколько будем двигать строки?" <<std::endl;
                    unsigned int n;
                    std::cin >> n;

                    if (n < 0)
                        throw BitString::Error();

                    std::cout << "Результаты побитового сдвига:" << std::endl
                              << "    первая строка - " << a.rightCycleShift(n) << std::endl
                              << "    вторая строка - " << b.rightCycleShift(n) << std::endl << std::endl;

                    a.recard_fields();
                    b.recard_fields();
                    break;
                }
                case 8: {
                    std::cout << " На сколько будем двигать строки?" <<std::endl;
                    unsigned int n;
                    std::cin >> n;

                    if (n < 0)
                        throw BitString::Error();

                    std::cout << "Результаты побитового сдвига:" << std::endl
                              << "    первая строка - " << a.leftCycleShift(n) << std::endl
                              << "    вторая строка - " << b.leftCycleShift(n) << std::endl << std::endl;

                    a.recard_fields();
                    b.recard_fields();
                    break;
                }
                case 9: {
                    std::cout << "Первая строка "; a.show(); std::cout << std::endl;
                    std::cout << "Вторая строка "; b.show(); std::cout << std::endl <<std::endl;
                    break;
                }
                case 10: {
                    tests.test_field_length(a.bits.part_large, a.bits.part_small);
                    tests.test_field_size(a.bits.part_large, a.bits.part_small);
                    break;
                }
                case 11: system("cls"); break;
                case 12: flag_loop = false; break;
            }
        }

    }
    catch(...){
        BitString::Error e("Cout value invalid");
    }

    return 0;
}

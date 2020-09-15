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


template <typename T>
void test_field_length(T a, T b) {
    int length_a = std::to_string(a).length();
    int length_b = std::to_string(b).length();
    if (length_a < length_b)
        std::swap(length_a, length_b);
    assert(("\nTest Error: overflow for [a b] by [length]\n", length_a < LENGTH_A && length_b < LENGTH_B));
}

template <typename T>
void test_field_size(T a, T b) {
    int size_a = a.size();
    int size_b = b.size();
    if (size_a < size_b)
        std::swap(size_a, size_b);
    assert(("\nTest Error: overflow for [a b] by [size]\n", size_a < SIZE_A && size_b < SIZE_B));
}

template <typename T>
void test_field_length(T a) {
    int length_a = a.length();
    assert(("\nTest Error: overflow for [a] by [length]\n", length_a <= UNIT_N));
}

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
        for (unsigned int i = 0; i < this->count; ++i)
            str.push_back(this->unit[i]);

        if (this->count > LENGTH_B - 1) {
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
                std::cout << "Error: ";
            };
            Error(const std::string &msg) : Error() {
                std::cout << msg << std::endl;
            };
    };

    int sizeBitString() {
        return this->count;
    };

    void enter() {
        std::string str;
        std::cout << "Введите битовую строку: " << std::endl;
        std::cin >> str;
        this->count = str.size();
        test_field_length(str);

        for (unsigned int i = 0; i < this->count; i++)
            if (str[i] != '0' && str[i] != '1')
                throw BitString::Error();

        this->unit = new unsigned char[this->count];

        for (unsigned int i = 0; i < this->count; i++)
            this->unit[i] = str[i];
        this->recard_fields();
    };

    void show() {
        for (unsigned int i = 0; i < this->count; i++)
            std::cout << this->unit[i];
    };

private:
    unsigned char* unit;
    unsigned int count;
};


int main() {
    setlocale(LC_ALL, "RUS");

    BitString a, b;
    try {
        a.enter();
        b.enter();

        if (a.sizeBitString() != b.sizeBitString())
            throw BitString::Error();

        //     int key = 0;
        //     while(key != 11)
        //     {
        //          cout << "Нажмите (1) если хотите сложить битовые строки" <<endl
        //               << "Нажмите (2) если хотите перемножить битовые строки" << endl
        //               << "Нажмите (3) если хотите сложить по модулю битовые строки " << endl
        //               << "Нажмите (4) если хотите выполнить побитовое отрицание  строк" <<endl
        //               << "Нажмите (5) если хотите выполнить побитовый сдвиг вправо строк" << endl
        //               << "Нажмите (6) если хотите выполнить побитовый сдвиг влево  строк " <<endl
        //               << "Нажмите (7) если хотите выполнить циклический сдвиг строк вправо   " <<endl
        //               << "Нажмите (8) если хотите выполнить циклический сдвиг строк влево  " <<endl
        //               << "Нажмите (9) если хотите узнать состояние строк" <<endl
        //               << "Нажмите (10) если хотите очистить экран" <<endl
        //               << "Нажмите (11) если хотите выйти"<<endl;
        //          cin >> key;

        //          switch(key)
        //          {
        //              case 1 :{ cout << endl << "Сумма равна :" << B.or(B1) <<endl << endl; break;}
        //              case 2 :{ cout << endl << "Произведение равно :" << B.and(B1) <<endl << endl; break;}
        //              case 3 :{ cout << endl << "Сумма по модулю равна : " <<  B.xor(B1) <<endl << endl; break;}
        //              case 4 :{ cout << endl << "Побитовое отрицание первой строки равно " << B.not() << endl
        //                                     << "Побитовое отрицание второй строки равно " << B1.not() << endl << endl; break;}
        //              case 5  :{
        //                         cout << " На сколько будем двигать строки?" <<endl;
        //                         unsigned int n;
        //                         cin >> n;
        //                         if (n < 0)
        //                             throw Bitstring::Error();
        //                         cout << "Результаты побитового сдвига:" << endl
        //                              << "   первая строка - " << B.rShift(n) << endl
        //                              << "   вторая строка - " << B1.rShift(n) << endl << endl ;
        //                         break;
        //                        }
        //              case 6:  {
        //                         cout << " На сколько будем двигать строки?" <<endl;
        //                         unsigned int n;
        //                         cin >> n;
        //                         if (n < 0)
        //                             throw Bitstring::Error();
        //                         cout << "Результаты побитового сдвига:" << endl
        //                              << "   первая строка - " << B.lShift(n) << endl
        //                              << "   вторая строка - " << B1.lShift(n) << endl << endl;
        //                         break;
        //                         }
        //              case 7:   {
        //                         cout << " На сколько будем двигать строки?" <<endl;
        //                         unsigned int n;
        //                         cin >> n;
        //                         if (n < 0)
        //                             throw Bitstring::Error();
        //                         cout << "Результаты побитового сдвига:" << endl
        //                             << "    первая строка - " << B.rightCycleShift(n) << endl
        //                             << "    вторая строка - " << B1.rightCycleShift(n) << endl << endl;
        //                         break;
        //                         }
        //              case 8:   {
        //                         cout << " На сколько будем двигать строки?" <<endl;
        //                          unsigned int n;
        //                         cin >> n;
        //                         if (n < 0)
        //                             throw Bitstring::Error();
        //                         cout << "Результаты побитового сдвига:" << endl
        //                             << "    первая строка - " << B.leftCycleShift(n) << endl
        //                             << "    вторая строка - " << B1.leftCycleShift(n) << endl << endl;
        //                         break;
        //                         }
        //              case 9 :{
        //                          cout << "Первая строка " ;  B.Show() ; cout << endl;
        //                          cout << "Вторая строка "  ; B1.Show() ; cout << endl <<endl;
        //                          break;
        //                      }


        //              case 10:  system("cls"); break;
        //          }
        //     }

    }
    catch(...){
        BitString::Error e("Cout value invalid");
    }

    std::cout << a.bits.part_large << std::endl;
    std::cout << a.bits.part_small << std::endl;

    return 0;
}





// using namespace std;


// class Bitstring
// {
// public:
//     string not();
//     string and(Bitstring);
//     string or(Bitstring);
//     string xor(Bitstring);

//     string rShift(unsigned int);
//     string lShift(unsigned int);
//     string rightCycleShift(unsigned int);
//     string leftCycleShift(unsigned int);

// private:

//     unsigned char* unit;
//     unsigned int count;
// };

// #include"Bitstring.h"

// int main()
// {
//     setlocale(.1251,"");

//     Bitstring B,B1;
//     try
//     {

//         B.Enter();
//         B1.Enter();
//         if(B.SizeOfBitstring() !=  B1.SizeOfBitstring() )
//             throw Bitstring::Error();

//         int key = 0;
//         while(key != 11)
//         {
//              cout << "Нажмите (1) если хотите сложить битовые строки" <<endl
//                   << "Нажмите (2) если хотите перемножить битовые строки" << endl
//                   << "Нажмите (3) если хотите сложить по модулю битовые строки " << endl
//                   << "Нажмите (4) если хотите выполнить побитовое отрицание  строк" <<endl
//                   << "Нажмите (5) если хотите выполнить побитовый сдвиг вправо строк" << endl
//                   << "Нажмите (6) если хотите выполнить побитовый сдвиг влево  строк " <<endl
//                   << "Нажмите (7) если хотите выполнить циклический сдвиг строк вправо   " <<endl
//                   << "Нажмите (8) если хотите выполнить циклический сдвиг строк влево  " <<endl
//                   << "Нажмите (9) если хотите узнать состояние строк" <<endl
//                   << "Нажмите (10) если хотите очистить экран" <<endl
//                   << "Нажмите (11) если хотите выйти"<<endl;
//              cin >> key;

//              switch(key)
//              {
//                  case 1 :{ cout << endl << "Сумма равна :" << B.or(B1) <<endl << endl; break;}
//                  case 2 :{ cout << endl << "Произведение равно :" << B.and(B1) <<endl << endl; break;}
//                  case 3 :{ cout << endl << "Сумма по модулю равна : " <<  B.xor(B1) <<endl << endl; break;}
//                  case 4 :{ cout << endl << "Побитовое отрицание первой строки равно " << B.not() << endl
//                                         << "Побитовое отрицание второй строки равно " << B1.not() << endl << endl; break;}
//                  case 5  :{
//                             cout << " На сколько будем двигать строки?" <<endl;
//                             unsigned int n;
//                             cin >> n;
//                             if (n < 0)
//                                 throw Bitstring::Error();
//                             cout << "Результаты побитового сдвига:" << endl
//                                  << "   первая строка - " << B.rShift(n) << endl
//                                  << "   вторая строка - " << B1.rShift(n) << endl << endl ;
//                             break;
//                            }
//                  case 6:  {
//                             cout << " На сколько будем двигать строки?" <<endl;
//                             unsigned int n;
//                             cin >> n;
//                             if (n < 0)
//                                 throw Bitstring::Error();
//                             cout << "Результаты побитового сдвига:" << endl
//                                  << "   первая строка - " << B.lShift(n) << endl
//                                  << "   вторая строка - " << B1.lShift(n) << endl << endl;
//                             break;
//                             }
//                  case 7:   {
//                             cout << " На сколько будем двигать строки?" <<endl;
//                             unsigned int n;
//                             cin >> n;
//                             if (n < 0)
//                                 throw Bitstring::Error();
//                             cout << "Результаты побитового сдвига:" << endl
//                                 << "    первая строка - " << B.rightCycleShift(n) << endl
//                                 << "    вторая строка - " << B1.rightCycleShift(n) << endl << endl;
//                             break;
//                             }
//                  case 8:   {
//                             cout << " На сколько будем двигать строки?" <<endl;
//                              unsigned int n;
//                             cin >> n;
//                             if (n < 0)
//                                 throw Bitstring::Error();
//                             cout << "Результаты побитового сдвига:" << endl
//                                 << "    первая строка - " << B.leftCycleShift(n) << endl
//                                 << "    вторая строка - " << B1.leftCycleShift(n) << endl << endl;
//                             break;
//                             }
//                  case 9 :{
//                              cout << "Первая строка " ;  B.Show() ; cout << endl;
//                              cout << "Вторая строка "  ; B1.Show() ; cout << endl <<endl;
//                              break;
//                          }


//                  case 10:  system("cls"); break;
//              }
//         }


//     }
//     catch(Bitstring::Error)
//     {
//         cout << "Ошибка! Введенное значение некорректно!"<<endl;
//     }
//     return 0;

// }


// string Bitstring::not()
// {
//     string str;

//     for(unsigned int i = 0; i < count; i++)
//     {
//         if (unit[i] == *"0")
//             unit[i] = *"1";
//         else
//             if (unit[i] == *"1")
//                 unit[i] = *"0";

//         str += unit[i];
//     }


//     return str;

// }

// string Bitstring::and(Bitstring B)
// {
//     string str;

//     for(unsigned int i = 0; i < count; i++)
//     {
//         if((unit[i]== *"0")&&(B.unit[i] == *"1"))
//             str += *"0";
//         else
//             if((unit[i] == *"1")&&(B.unit[i] == *"0"))
//                 str += *"0";
//             else
//                 str+=unit[i];
//     }


//     return str;
// }

// string Bitstring::or(Bitstring B)
// {
//     string str;

//     for(unsigned int i = 0; i < count; i++)
//     {
//         if((unit[i]== *"0")&&(B.unit[i] == *"1"))
//             str += *"1";
//         else
//             if((unit[i] == *"1")&&(B.unit[i] == *"0"))
//                 str += *"1";
//             else
//                 str+=unit[i];
//     }


//     return str;
// }

// string Bitstring::xor(Bitstring B)
// {
//     string str;

//     for(unsigned int i = 0; i < count; i++)
//     {
//         if((unit[i]== *"0")&&(B.unit[i] == *"1"))
//             str += *"1";
//         else
//             if((unit[i] == *"1")&&(B.unit[i] == *"0"))
//                 str += *"1";
//             else
//                 if((unit[i] == *"0")&&(B.unit[i] == *"0"))
//                     str += *"0";
//                 else
//                     if((unit[i] == *"1")&&(B.unit[i] == *"1"))
//                         str += *"0";

//     }


//     return str;
// }

// string Bitstring::rShift (unsigned int n)
// {
//     string str;

//     for(unsigned int i = 0; i < count; i++)
//         str += unit[i];

//     str.erase(0,n);  // удаляем n символов начитая с первого

//     for(int i = 0; i < n; i++)                    // добавляем n нулей в конец
//          str.append("0");


//     return str;
// }

// string Bitstring::lShift (unsigned int n)
// {
//     string str;

//     for(unsigned int i = 0; i < count; i++)
//         str += unit[i];

//     str.erase(count-n,n);  // удаляем n символов начитая с первого

//     str.insert(0,n,*"0");           // добавляем n нулей в  начало

//     return str;
// }

// string Bitstring::rightCycleShift(unsigned int n)
// {
//     string str;



//     for(unsigned int i = n; i < count; i++)
//         str += unit[i];

//     for(unsigned int i = 0; i < n; i++)
//         str+=unit[i];

//     return str;

// }

// string Bitstring::leftCycleShift(unsigned int n)
// {
//     string str;

//     for(unsigned int i = count-n; i < count; i++)
//         str += unit[i];

//     for(unsigned int i = 0; i < count-n; i++)
//         str+=unit[i];

//     return str;

// }
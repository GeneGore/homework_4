/*!
    \brief Это 4-е задание Отуса
    \details Очень подробно! 4-е задание Отуса
    \author Имярек
    \version 1.0
    \date Год 2025 от Р.Х.
    \warning Опасносте!
*/

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>

/*!
  \brief Шаблонная функция для интов

*/
template<typename T>
void print_ip(T T_INT){

    std::size_t N_bytes = sizeof(T_INT);
//    std::cout<<"N_bytes "<<N_bytes<<std::endl;

    for(int i=0; i<N_bytes; ++i){

        if(i!=0) std::cout<<".";

        int shift = (N_bytes-1-i)*8;
        T resINT = T_INT & ((uint64_t)255<<shift);
//        std::cout<<" i "<< i << " shift "<< shift<<std::endl;

        std::cout<<static_cast<int>(resINT>>shift);
    }
    std::cout<<"\n";
}

template<>
void print_ip(std::string str){
    std::cout<<str<<"\n";
}

template<>
void print_ip(std::vector<int> vec){

    auto it = vec.begin();
    for(; it != vec.end(); ++it){
        if(it != vec.begin()) std::cout<<".";
        std::cout<<*it;
    }

//    auto it = vec.cbegin();
//    for(; it != vec.cend(); ++it){
//        std::cout<<*it;
//        if(it+1 != vec.cend()) std::cout<<"."; //есть итераторы произвольного доступа, O(1)
//    }

    std::cout<<"\n";
}

template<>
void print_ip(std::list<short> list){

    auto it = list.begin();

    for(; it != list.end(); ++it){
        if(it != list.begin()) std::cout<<".";
        std::cout<<*it;
    }

    std::cout<<"\n";
}

//template<typename T> //пу-пу-пу
//void print_ip(T container){

//    auto it = container.begin();

//    for(; it != container.end(); ++it){
//        if(it != container.begin()) std::cout<<".";
//        std::cout<<*it;
//    }

//    std::cout<<"\n";
//}


template<typename first, typename... rest>
constexpr bool checkParams(){

    if(sizeof... (rest) == 0)
        return true;
    else
        return (std::is_same_v<first, rest> && ...);
}

template<typename... T>
constexpr bool checkTuple(const std::tuple<T...>& ){
    return checkParams<T...>();
}


/*!
\brief Шаблонная функция для кортежей
\param [in] t кортеж
\return ничего
*/
template<std::size_t i = 0, typename... T>
void print_ip(const std::tuple<T...>& t){

//    static_assert(!checkTuple(t),"compile failure");

    if(!checkTuple(t)) {
//        std::cout<<"WTF!"<<std::endl;

        throw std::invalid_argument("Not same types!");
    }

    if constexpr (i < sizeof...(T)){

        if(i != 0) std::cout<<".";

        std::cout<<std::get<i>(t);

        print_ip<i+1>(t);
    }

    std::cout<<"\n";
}

int main()
{

//    Адрес может быть представлен в виде произвольного целочисленного типа.
//    Выводить побайтово в беззнаковом виде, начиная со старшего байта, с символом . (символ точки) в качестве разделителя.
//    Выводятся все байты числа.
//    вариант для целочисленного представления должен представлять собой одну функцию
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41

//    Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от содержимого.
    print_ip( std::string{"Hello, World!"} );                                            // Hello, World!

//    Адрес может быть представлен в виде контейнеров std::list, std::vector.
//    Выводится полное содержимое контейнера поэлементно и разделяется . (символом точка).
//    Элементы выводятся как есть.
//    вариант для контейнеров std::list и std::vector должен представлять собой одну функцию
    print_ip( std::vector<int>{100, 200, 300, 400} );                                    // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} );                                    // 400.300.200.100


//    Опционально адрес может быть представлен в виде std::tuple при условии, что все типы одинаковы.
//    Выводится полное содержимое поэлементно и разделяется . (одним символом точка).
//    Элементы выводятся как есть. В случае, если типы кортежа не одинаковы,должна быть выдана ошибка при компиляции кода.
//    опциональная реализация для std::tuple должна приводить к ошибке в случае отличающихся типов
//    не должно быть ограничений на размер целочисленных типов (в байтах), на размер контейнеров и кортежа (количество элементов)

    try{
//        print_ip( std::make_tuple(123, "sdfsdfsdf", 789, 0) );
        print_ip( std::make_tuple(123, 456, 789, 0) );                                      // 123.456.789.0
    }
    catch(std::invalid_argument err){
        std::cout<<"Gotcha: "<<err.what()<<std::endl;
    }

    return 0;
}

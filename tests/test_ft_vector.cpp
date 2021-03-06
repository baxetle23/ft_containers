#include "ft_vector.hpp"

#include <cassert>
#include <stdexcept>
#include <iostream>

using namespace std;

template<typename Vec, typename... Args>
Vec& construct_ft_vector(Vec& vector, Args&&... args) {
    (vector.push_back(std::forward<Args>(args)), ...);
    return vector;
}

inline void TestConstructVec() {
    // Инициализация конструктором по умолчанию
    {
        ft::vector<int> v;
        assert(v.size() == 0u);
        assert(v.empty());
        assert(v.capacity() == 0u);
    }

    // Инициализация вектора указанного размера
    {
        ft::vector<int> v(5);
        assert(v.size() == 5u);
        assert(v.capacity() == 5u);
        assert(!v.empty());
        for (size_t i = 0; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
    }

    // Инициализация вектора, заполненного заданным значением
    {
        ft::vector<int> v(3, 42);
        assert(v.size() == 3);
        assert(v.capacity() == 3);
        for (size_t i = 0; i < v.size(); ++i) {
            assert(v[i] == 42);
        }
    }

    // Доступ к элементам при помощи at
    {
        ft::vector<int> v(3);
        assert(&v.at(2) == &v[2]);
        try {
            v.at(3);
            assert(false);  // Ожидается выбрасывание исключения
        } catch (const std::out_of_range&) {
        } catch (...) {
            assert(false);  // Не ожидается исключение, отличное от out_of_range
        }
    }

    // Очистка вектора
    {
        ft::vector<int> v(10);
        const size_t old_capacity = v.capacity();
        v.clear();
        assert(v.size() == 0);
        assert(v.capacity() == old_capacity);
    }

    // Изменение размера
    {
        ft::vector<int> v(3);
        v[2] = 17;
        v.resize(7);
        assert(v.size() == 7);
        assert(v.capacity() >= v.size());
        assert(v[2] == 17);
        assert(v[3] == 0);
    }
    {
        ft::vector<int> v(3);
        v[0] = 42;
        v[1] = 55;
        const size_t old_capacity = v.capacity();
        v.resize(2);
        assert(v.size() == 2);
        assert(v.capacity() == old_capacity);
        assert(v[0] == 42);
        assert(v[1] == 55);
    }
    {
        const size_t old_size = 3;
        ft::vector<int> v(3);
        v.resize(old_size + 5);
        v[3] = 42;
        v.resize(old_size);
        v.resize(old_size + 2);
        assert(v[3] == 0);
    }

    // Итерирование по ft::vector
    {
        // Пустой вектор
        {
            ft::vector<int> v;
            assert(v.begin().base() == NULL);
            assert(v.end().base() == NULL);
        }

        // Непустой вектор
        {
            ft::vector<int> v(10, 42);
            //assert(v.begin());
            assert(*v.begin() == 42);
            assert(v.end() == v.begin() + v.size());
        }
    }
}

inline void TestInsertVec() {
    // push_back
    {
        ft::vector<int> v(1);
        v.push_back(42);
        assert(v.size() == 2);
        assert(v.capacity() >= v.size());
        assert(v[0] == 0);
        assert(v[1] == 42);
    }

    // Если хватает места, push_back не увеличивает Capacity
    {
        ft::vector<int> v(2);
        v.resize(1);
        const size_t old_capacity = v.capacity();
        v.push_back(123);
        assert(v.size() == 2);
        assert(v.capacity() == old_capacity);
    }

    // pop_back
    {
        ft::vector<int> v;
        construct_ft_vector(v, 0, 1, 2, 3);
        const size_t old_capacity = v.capacity();
        const auto old_begin = v.begin();
        v.pop_back();
        assert(v.capacity() == old_capacity);
        assert(v.begin() == old_begin);
        ft::vector<int> x;
        construct_ft_vector(x, 0, 1, 2);
        assert(v == x);
    }

    // Конструктор копирования
    {
        ft::vector<int> numbers;
        construct_ft_vector(numbers, 1, 2);
        auto numbers_copy(numbers);
        assert(&numbers_copy[0] != &numbers[0]);
        assert(numbers_copy.size() == numbers.size());
        for (size_t i = 0; i < numbers.size(); ++i) {
            assert(numbers_copy[i] == numbers[i]);
            assert(&numbers_copy[i] != &numbers[i]);
        }
    }

    // Сравнение
    {
        {
            ft::vector<int> first;
            construct_ft_vector(first, 1, 2, 3);
            ft::vector<int> second;
            construct_ft_vector(second, 1, 2, 3);
            assert(first == second);
        }

        {
            ft::vector<int> first;
            construct_ft_vector(first, 1, 2, 3);
            ft::vector<int> second;
            construct_ft_vector(second, 1, 2, 2);
            assert(first != second);
        }

        {
            ft::vector<int> first;
            construct_ft_vector(first, 1, 2, 3);
            ft::vector<int> second;
            construct_ft_vector(second, 1, 2, 3, 1);
            assert(first < second);
        }

        {
            ft::vector<int> first;
            construct_ft_vector(first, 1, 2, 3);
            ft::vector<int> second;
            construct_ft_vector(second, 1, 2, 2, 1);
            assert(first > second);
        }

        {
            ft::vector<int> first;
            construct_ft_vector(first, 1, 2, 3);
            ft::vector<int> second;
            construct_ft_vector(second, 1, 2, 3);
            assert(first >= second);
        }

        {
            ft::vector<int> first;
            construct_ft_vector(first, 1, 2, 3);
            ft::vector<int> second;
            construct_ft_vector(second, 1, 2, 3);
            assert(first <= second);
        }
    }

    // Обмен значений векторов
    {
        ft::vector<int> v1{42, 666};
        ft::vector<int> v2;
        v2.push_back(0);
        v2.push_back(1);
        v2.push_back(2);
        const int* const begin1 = &v1[0];
        const int* const begin2 = &v2[0];

        const size_t capacity1 = v1.capacity();
        const size_t capacity2 = v2.capacity();

        const size_t size1 = v1.size();
        const size_t size2 = v2.size();

        v1.swap(v2);
        
        assert(&v2[0] == begin1);
        assert(&v1[0] == begin2);
        assert(v1.size() == size2);
        assert(v2.size() == size1);
        assert(v1.capacity() == capacity2);
        assert(v2.capacity() == capacity1);
    }

    // Присваивание
    {
        ft::vector<int> src_vector;
        construct_ft_vector(src_vector, 1, 2, 3, 4);
        ft::vector<int> dst_vector;
        construct_ft_vector(dst_vector, 1, 2, 3, 4, 5, 6);
        dst_vector = src_vector;
        assert(dst_vector == src_vector);
    }

    // Вставка элементов
    {
        ft::vector<int> v;
        construct_ft_vector(v, 1, 2, 3, 4);
        v.insert(v.begin() + 2, 42);

        ft::vector<int> x;
        construct_ft_vector(x, 1, 2, 42, 3, 4);
        assert((v == x));
    }

    // Удаление элементов
    {
        ft::vector<int> v;
        construct_ft_vector(v, 1, 2, 3, 4);
        v.erase(v.begin() + 2);

        ft::vector<int> x;
        construct_ft_vector(x, 1, 2, 4);
        assert((v == x));
    }
}

void TestReserveConstructorVec() {
    ft::vector<int> v(5);
    assert(v.capacity() == 5);
    assert(v.size() == 5);
}

void TestReserveMethodVec() {
    ft::vector<int> v;
    // зарезервируем 5 мест в векторе
    v.reserve(5);
    assert(v.capacity() == 5);
    assert(v.empty());

    // попытаемся уменьшить capacity до 1
    v.reserve(1);
    // capacity должно остаться прежним
    assert(v.capacity() == 5);
    // поместим 10 элементов в вектор
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    assert(v.size() == 10);
    // увеличим capacity до 100
    v.reserve(100);
    // проверим, что размер не поменялся
    assert(v.size() == 10);
    assert(v.capacity() == 100);
    // проверим, что элементы на месте
    for (int i = 0; i < 10; ++i) {
        assert(v[i] == i);
    }
}


void test_ft_vector() {
    TestConstructVec();
    TestInsertVec();
    TestReserveConstructorVec();
    TestReserveMethodVec();
}

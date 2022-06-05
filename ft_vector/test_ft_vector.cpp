// #include "ft_vector.hpp"

// #include <cassert>
// #include <stdexcept>

// inline void Test1() {
//     // Инициализация конструктором по умолчанию
//     {
//         ft::vector<int> v;
//         assert(v.GetSize() == 0u);
//         assert(v.IsEmpty());
//         assert(v.GetCapacity() == 0u);
//     }

//     // Инициализация вектора указанного размера
//     {
//         ft::vector<int> v(5);
//         assert(v.GetSize() == 5u);
//         assert(v.GetCapacity() == 5u);
//         assert(!v.IsEmpty());
//         for (size_t i = 0; i < v.GetSize(); ++i) {
//             assert(v[i] == 0);
//         }
//     }

//     // Инициализация вектора, заполненного заданным значением
//     {
//         ft::vector<int> v(3, 42);
//         assert(v.GetSize() == 3);
//         assert(v.GetCapacity() == 3);
//         for (size_t i = 0; i < v.GetSize(); ++i) {
//             assert(v[i] == 42);
//         }
//     }

//     // Инициализация вектора при помощи initializer_list
//     {
//         ft::vector<int> v{1, 2, 3};
//         assert(v.GetSize() == 3);
//         assert(v.GetCapacity() == 3);
//         assert(v[2] == 3);
//     }

//     // Доступ к элементам при помощи At
//     {
//         ft::vector<int> v(3);
//         assert(&v.At(2) == &v[2]);
//         try {
//             v.At(3);
//             assert(false);  // Ожидается выбрасывание исключения
//         } catch (const std::out_of_range&) {
//         } catch (...) {
//             assert(false);  // Не ожидается исключение, отличное от out_of_range
//         }
//     }

//     // Очистка вектора
//     {
//         ft::vector<int> v(10);
//         const size_t old_capacity = v.GetCapacity();
//         v.Clear();
//         assert(v.GetSize() == 0);
//         assert(v.GetCapacity() == old_capacity);
//     }

//     // Изменение размера
//     {
//         ft::vector<int> v(3);
//         v[2] = 17;
//         v.Resize(7);
//         assert(v.GetSize() == 7);
//         assert(v.GetCapacity() >= v.GetSize());
//         assert(v[2] == 17);
//         assert(v[3] == 0);
//     }
//     {
//         ft::vector<int> v(3);
//         v[0] = 42;
//         v[1] = 55;
//         const size_t old_capacity = v.GetCapacity();
//         v.Resize(2);
//         assert(v.GetSize() == 2);
//         assert(v.GetCapacity() == old_capacity);
//         assert(v[0] == 42);
//         assert(v[1] == 55);
//     }
//     {
//         const size_t old_size = 3;
//         ft::vector<int> v(3);
//         v.Resize(old_size + 5);
//         v[3] = 42;
//         v.Resize(old_size);
//         v.Resize(old_size + 2);
//         assert(v[3] == 0);
//     }

//     // Итерирование по ft::vector
//     {
//         // Пустой вектор
//         {
//             ft::vector<int> v;
//             assert(v.begin() == nullptr);
//             assert(v.end() == nullptr);
//         }

//         // Непустой вектор
//         {
//             ft::vector<int> v(10, 42);
//             assert(v.begin());
//             assert(*v.begin() == 42);
//             assert(v.end() == v.begin() + v.GetSize());
//         }
//     }
// }

// inline void Test2() {
//     // PushBack
//     {
//         ft::vector<int> v(1);
//         v.PushBack(42);
//         assert(v.GetSize() == 2);
//         assert(v.GetCapacity() >= v.GetSize());
//         assert(v[0] == 0);
//         assert(v[1] == 42);
//     }

//     // Если хватает места, PushBack не увеличивает Capacity
//     {
//         ft::vector<int> v(2);
//         v.Resize(1);
//         const size_t old_capacity = v.GetCapacity();
//         v.PushBack(123);
//         assert(v.GetSize() == 2);
//         assert(v.GetCapacity() == old_capacity);
//     }

//     // PopBack
//     {
//         ft::vector<int> v{0, 1, 2, 3};
//         const size_t old_capacity = v.GetCapacity();
//         const auto old_begin = v.begin();
//         v.PopBack();
//         assert(v.GetCapacity() == old_capacity);
//         assert(v.begin() == old_begin);
//         assert((v == ft::vector<int>{0, 1, 2}));
//     }

//     // Конструктор копирования
//     {
//         ft::vector<int> numbers{1, 2};
//         auto numbers_copy(numbers);
//         assert(&numbers_copy[0] != &numbers[0]);
//         assert(numbers_copy.GetSize() == numbers.GetSize());
//         for (size_t i = 0; i < numbers.GetSize(); ++i) {
//             assert(numbers_copy[i] == numbers[i]);
//             assert(&numbers_copy[i] != &numbers[i]);
//         }
//     }

//     // Сравнение
//     {
//         assert((ft::vector{1, 2, 3} == ft::vector{1, 2, 3}));
//         assert((ft::vector{1, 2, 3} != ft::vector{1, 2, 2}));

//         assert((ft::vector{1, 2, 3} < ft::vector{1, 2, 3, 1}));
//         assert((ft::vector{1, 2, 3} > ft::vector{1, 2, 2, 1}));

//         assert((ft::vector{1, 2, 3} >= ft::vector{1, 2, 3}));
//         assert((ft::vector{1, 2, 4} >= ft::vector{1, 2, 3}));
//         assert((ft::vector{1, 2, 3} <= ft::vector{1, 2, 3}));
//         assert((ft::vector{1, 2, 3} <= ft::vector{1, 2, 4}));
//     }

//     // Обмен значений векторов
//     {
//         ft::vector<int> v1{42, 666};
//         ft::vector<int> v2;
//         v2.PushBack(0);
//         v2.PushBack(1);
//         v2.PushBack(2);
//         const int* const begin1 = &v1[0];
//         const int* const begin2 = &v2[0];

//         const size_t capacity1 = v1.GetCapacity();
//         const size_t capacity2 = v2.GetCapacity();

//         const size_t size1 = v1.GetSize();
//         const size_t size2 = v2.GetSize();

//         static_assert(noexcept(v1.swap(v2)));
//         v1.swap(v2);
//         assert(&v2[0] == begin1);
//         assert(&v1[0] == begin2);
//         assert(v1.GetSize() == size2);
//         assert(v2.GetSize() == size1);
//         assert(v1.GetCapacity() == capacity2);
//         assert(v2.GetCapacity() == capacity1);
//     }

//     // Присваивание
//     {
//         ft::vector<int> src_vector{1, 2, 3, 4};
//         ft::vector<int> dst_vector{1, 2, 3, 4, 5, 6};
//         dst_vector = src_vector;
//         assert(dst_vector == src_vector);
//     }

//     // Вставка элементов
//     {
//         ft::vector<int> v{1, 2, 3, 4};
//         v.Insert(v.begin() + 2, 42);
//         assert((v == ft::vector<int>{1, 2, 42, 3, 4}));
//     }

//     // Удаление элементов
//     {
//         ft::vector<int> v{1, 2, 3, 4};
//         v.Erase(v.cbegin() + 2);
//         assert((v == ft::vector<int>{1, 2, 4}));
//     }
// }

// void TestReserveConstructor() {
//     cout << "TestReserveConstructor"s << endl;
//     ft::vector<int> v(5);
//     assert(v.GetCapacity() == 5);
//     assert(v.IsEmpty());
//     cout << "Done!"s << endl;
// }

// void TestReserveMethod() {
//     cout << "TestReserveMethod"s << endl;
//     ft::vector<int> v;
//     // зарезервируем 5 мест в векторе
//     v.Reserve(5);
//     assert(v.GetCapacity() == 5);
//     assert(v.IsEmpty());

//     // попытаемся уменьшить capacity до 1
//     v.Reserve(1);
//     // capacity должно остаться прежним
//     assert(v.GetCapacity() == 5);
//     // поместим 10 элементов в вектор
//     for (int i = 0; i < 10; ++i) {
//         v.PushBack(i);
//     }
//     assert(v.GetSize() == 10);
//     // увеличим capacity до 100
//     v.Reserve(100);
//     // проверим, что размер не поменялся
//     assert(v.GetSize() == 10);
//     assert(v.GetCapacity() == 100);
//     // проверим, что элементы на месте
//     for (int i = 0; i < 10; ++i) {
//         assert(v[i] == i);
//     }
//     cout << "Done!"s << endl;
// }


// int main() {
//     TestReserveConstructor();
//     TestReserveMethod();
// }
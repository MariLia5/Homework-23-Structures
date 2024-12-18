#include <iostream>
#include <string>
#include <windows.h>


// Задача 1
struct Student {
    std::string Surname;
    std::string Group;
    int* Marks;
};

// Функция для вывода студентов по оценкам
void Marks(Student* students, int n) {
    std::cout << "Список отличников (>75% отличных оценок):\n";
    for (int i = 0; i < n; i++) {
        int excellentCount = 0;

        for (int j = 0; j < 5; j++) {
            if (students[i].Marks[j] == 5) {
                excellentCount++;
            }
        }
        if (excellentCount >= 4) {  // 4 из 5 - это более 75%
            std::cout << students[i].Surname << " (Группа: " << students[i].Group << ")\n";
        }
    }
    std::cout << "\nСписок двоечников (>50% оценок 2 и 3):\n";
    for (int i = 0; i < n; i++) {
        int badCount = 0;

        for (int j = 0; j < 5; j++) {
            if (students[i].Marks[j] == 3 || students[i].Marks[j] == 2) {
                badCount ++;
            }
        }
        if (badCount >= 3) {  // >50% оценок 2 и 3
            std::cout << students[i].Surname << " (Группа: " << students[i].Group << ")\n";
        }
    }
}

// Задача 2
struct Date {
    int day;
    int month;
    int year;

    // Перегрузка оператора вывода для структуры Date
    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.day << '/' << date.month << '/' << date.year;
        return os;
    }
};

struct Man {
    std::string Surname;
    std::string Name;
    int Age;
    Date dateOfBirth;
};

void Print(Man* arr, int length) {
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i].Name << ' ' << arr[i].Surname << ' ' << arr[i].Age << ' ' << arr[i].dateOfBirth << '\n';
    }
}

// Сортировка по фамилии
void SortSurname(Man* arr, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (arr[j].Surname > arr[j + 1].Surname) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Сортировка по имени
void SortName(Man* arr, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (arr[j].Name > arr[j + 1].Name) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Вывод списка именинников месяца
void PrintBirthdayInMonth(Man* arr, int length, int month) {
    std::cout << "Именинники в месяце " << month << ":\n";
    for (int i = 0; i < length; i++) {
        if (arr[i].dateOfBirth.month == month) {
            std::cout << arr[i].Name << ' ' << arr[i].Surname << " -> " << arr[i].dateOfBirth << '\n';
        }
    }
}

// Удаление записи
void DeleteMan(Man& man) {
    man.Surname.clear();
    man.Name.clear();
    man.Age = 0;
    man.dateOfBirth = { 0, 0, 0 };
}

// Добавление записи
void AddMan(Man*& arr, int& length, const Man& newMan) {
    Man* newArr = new Man[length + 1];
    for (int i = 0; i < length; i++) {
        newArr[i] = arr[i];
    }
    newArr[length] = newMan;
    delete[] arr;
    arr = newArr;
    length++;
}

// Функция для поиска по фамилии и имени
void SearchByNameAndSurname(Man* persons, int length, const std::string& surname, const std::string& name) {
    bool found = false;
    for (int i = 0; i < length; i++) {
        std::cout << "Сравниваем с: " << persons[i].Surname << " " << persons[i].Name << std::endl;
        if (persons[i].Surname == surname && persons[i].Name == name) {
            std::cout << "Найдено: " << persons[i].Surname << " " << persons[i].Name
                << ", Возраст: " << persons[i].Age
                << ", Дата рождения: " << persons[i].dateOfBirth.day << "."
                << persons[i].dateOfBirth.month << "."
                << persons[i].dateOfBirth.year << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Запись не найдена." << std::endl;
    }
}

// Функция редактирования записи
void EditCurrentRecord(Man* persons, int length, int index) {
    if (index < 0 || index >= length) {
        std::cout << "Вне диапазона." << std::endl;
        return;
    }

    std::string newSurname, newName;
    int newAge;
    Date newDateOfBirth;

    std::cout << "Введите новую фамилию: ";
    std::cin >> newSurname;
    std::cout << "Введите новое имя: ";
    std::cin >> newName;
    std::cout << "Введите новый возраст: ";
    std::cin >> newAge;
    std::cout << "Введите новую дату рождения (день месяц год): ";
    std::cin >> newDateOfBirth.day >> newDateOfBirth.month >> newDateOfBirth.year;

    persons[index].Surname = newSurname;
    persons[index].Name = newName;
    persons[index].Age = newAge;
    persons[index].dateOfBirth = newDateOfBirth;

    std::cout << "Запись успешно обновлена." << std::endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
 
    // Задача 1
    // Создание массива студентов
    const int n = 4; // Количество студентов
    Student* students = new Student[n];

    // Инициализация данных студентов
    students[0] = { "Иванов Алексей", "A1", new int[5] {3, 3, 4, 5, 2} };
    students[1] = { "Петрова Елена", "A2", new int[5] {4, 5, 5, 5, 5} };
    students[2] = { "Сидоров Петр", "A3", new int[5] {4, 5, 3, 2, 5} };
    students[3] = { "Крышковец Даниил", "A1", new int[5] {5, 5, 5, 5, 5} };

    // Вызов функции отображения отличников
    Marks(students, n);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] students[i].Marks; // Освобождаем память для оценок каждого студента
    }
    delete[] students; // Освобождаем память для массива студентов

    // Задача 2
    int n = 3; // Количество людей
    Man* person = new Man[n]; // Создаем массив структур Man

    // Инициализация стурктуры
    person[0] = { "Вишняков", "Леонид", 27, {4, 2, 1997} };
    person[1] = { "Булкин", "Александр", 25, {5, 2, 1999} };
    person[2] = { "Сулим", "Александра", 37, {11, 5, 1987} };

    std::cout << "Изначальный массив людей:\n";
    Print(person, n);
    std::cout << '\n';

    std::cout << "Сортировка по фамилии:\n"; 
    SortSurname(person, n);
    Print(person, n);
    std::cout << '\n';

    std::cout << "Сортировка по имени:\n";
    SortName(person, n);
    Print(person, n);
    std::cout << '\n';

    std::cout << "Вывод списка именинников месяца:\n";
    PrintBirthdayInMonth(person, n, 5);
    std::cout << '\n';
        
    std::cout << "Изменение размеров массива при добавлении и удалении записей\n";
    std::cout << "Массив людей:\n";
    Print(person, n);

    int act;
    std::cout << "Что вы хотите сделать?\n1. Удалить элемент (нажмите 1)\n2. Добавить элемент (нажмите 2)\n";
    std::cin >> act;

    int index;
    if (act == 1) {
        int Delete;
        std::cout << "Введите строку для очистки (0 - 2)\n*список начинается с нуля \n";
        std::cin >> Delete;
        if (Delete >= 0 && Delete < n) {
            DeleteMan(person[Delete]);
            std::cout << "Элемент очищен.\n";
        }
        else {
            std::cout << "Ошибка: индекс вне диапазона.\n";
        }
    }
    Print(person, n);

    if (act == 2) {
        Man newMan;
        std::cout << "Введите фамилию: ";
        std::cin >> newMan.Surname;
        std::cout << "Введите имя: ";
        std::cin >> newMan.Name;
        std::cout << "Введите возраст: ";
        std::cin >> newMan.Age;
        std::cout << "Введите дату рождения (день месяц год): ";
        std::cin >> newMan.dateOfBirth.day >> newMan.dateOfBirth.month >> newMan.dateOfBirth.year;
        AddMan(person, n, newMan);
        std::cout << "Массив людей после добавления:\n";
        Print(person, n);
    }
    std::cout << "\n";

    std::cout << "Поиск по фамилии и имени:\n";
    std::string surname, name;
    std::cout << "Введите фамилию для поиска:\n";
    std::getline(std::cin, surname);
    std::cout << "Введите имя для поиска:\n";
    std::getline(std::cin, name);
    SearchByNameAndSurname(person, n, surname, name);
    std::cout << "\n";

    std::cout << "Введите номер записи, которую нужно редактировать (начинается с нуля): ";
    int indexToEdit;
    std::cin >> indexToEdit;
    EditCurrentRecord(person, n, indexToEdit);

    std::cout << "Обновленная запись: " << person[indexToEdit].Surname << " " << person[indexToEdit].Name
        << ", Возраст: " << person[indexToEdit].Age
        << ", Дата рождения: " << person[indexToEdit].dateOfBirth.day << "."
        << person[indexToEdit].dateOfBirth.month << "."
        << person[indexToEdit].dateOfBirth.year << std::endl;

    delete[] person;

    return 0;
}
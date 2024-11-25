#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
class MyVector 
{
    T* array;          
    size_t capacity;   
    size_t Size;       

public:
    MyVector() : array(nullptr), capacity(0), Size(0) {}

    ~MyVector()
    {
        delete[] array;
    }

    void push_back(const T& element)
    {
        if (Size >= capacity) 
        {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newArray = new T[capacity];
            for (size_t i = 0; i < Size; ++i) 
            {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
        }
        array[Size++] = element;
    }

    T& operator[](size_t index)
    {
        if (index >= Size) 
        {
            throw out_of_range("Індекс вийшов за межі видимості");
        }
        return array[index];
    }

    size_t size() const
    {
        return Size;
    }

    bool empty() const 
    {
        return Size == 0;
    }

    T* begin() 
    {
        return array;
    }

    T* end()
    {
        return array + Size;
    }
};

class DigitalCounter 
{
    int value;
    int max_value;
    int min_value;
public:
    DigitalCounter()
    {
        value = 0;
        max_value = 59;
        min_value = 0;
    }

    DigitalCounter(int value, int max_value, int min_value)
    {
        this->value = value;
        this->max_value = max_value;
        this->min_value = min_value;
    }

    DigitalCounter(const DigitalCounter& counter) 
    {
        value = counter.value;
        max_value = counter.max_value;
        min_value = counter.min_value;
    }

    DigitalCounter(DigitalCounter&& counter) noexcept 
    {
        value = counter.value;
        max_value = counter.max_value;
        min_value = counter.min_value;
        counter.value = 0;
    }

    ~DigitalCounter() {}

    void setMaxValue(int max_value)
    {
        this->max_value = max_value;
    }

    int getMaxValue()
    {
        return max_value;
    }

    void setMinValue(int min_value) 
    {
        this->min_value = min_value;
    }

    int getMinValue()
    {
        return min_value;
    }

    void setValue(int val) 
    {
        try
        {
            if (val < min_value || val > max_value + 1)
            {
                throw out_of_range("Невірне значення. Значення має бути в межах від " + to_string(min_value) + " до " + to_string(max_value));
            }
            else if (cin.fail())
            {
                throw invalid_argument("Введено неправильний тип даних");
            }
            else
            {
                value = val;
                if (value == max_value + 1)
                {
                    value = min_value;
                    cout << "Значення досягло максимуму. Встановлено мінімальне значення: " << min_value << endl;
                }
            }
        }
        catch (const out_of_range& e) 
        {
            cerr << "Помилка: " << e.what() << endl;
        }
        catch (const invalid_argument& e)
        {
            cerr << "Помилка: " << e.what() << endl;
        }
    }

    int getValue()
    {
        return value;
    }

    virtual void printValues()
    {
        cout << "Поточне значення: " << value << endl;
        cout << "Максимальне значення: " << max_value << endl;
        cout << "Мінімальне значення: " << min_value << endl;
    }

    void operator()(int val, int max_val, int min_val) 
    {
        value = val;
        max_value = max_val;
        min_value = min_val;
    }

    DigitalCounter& operator++()
    {
        try
        {
            if (value > max_value)
            {
                throw string("Помилка: Перевищено максимальне значення");
            }
            ++value;
            if (value == max_value + 1)
            {
                value = min_value;
                cout << "Значення досягло максимуму. Встановлено мінімальне значення: " << min_value << endl;
            }
        }
        catch (const string& errorMsg)
        {
            cerr << errorMsg << endl;
        }
        return *this;
    }

    DigitalCounter& operator--()
    {
        try
        {
            if (value > min_value)
            {
                --value;
            }
            else
            {
                throw string("Помилка: Значення вже досягло мінімального значення.");
            }
        }
        catch (const string& errorMessage)
        {
            cerr << errorMessage << endl;
        }
        return *this;
    }

    DigitalCounter& operator+=(int val)
    {
        try
        {
            if (value + val > max_value + 1)
            {
                throw string("Помилка: Спроба збільшити значення настільки, що воно перевищить максимально допустиме значення.");
            }
            value += val;
            if (value == max_value + 1)
            {
                value = min_value;
                cout << "Значення досягло максимуму. Встановлено мінімальне значення: " << min_value << endl;
            }
        }
        catch (const string& errorMessage)
        {
            cerr << errorMessage << endl;
        }
        return *this;
    }

    DigitalCounter& operator-=(int val)
    {
        try
        {
            if (value - val >= min_value)
            {
                value -= val;
            }
            else
            {
                throw string("Помилка: Значення виходить за межі діапазону.");
            }
        }
        catch (const string& errorMessage)
        {
            cerr << errorMessage << endl;
        }
        return *this;
    }

    bool operator==(const DigitalCounter& other)
    {
        return value == other.value && max_value == other.max_value && min_value == other.min_value;
    }

    DigitalCounter& operator=(const DigitalCounter& counter) 
    {
        if (this != &counter) 
        {
            value = counter.value;
            max_value = counter.max_value;
            min_value = counter.min_value;
        }
        return *this;
    }

    DigitalCounter& operator=(DigitalCounter&& counter) noexcept
    {
        if (this != &counter) 
        {
            value = counter.value;
            max_value = counter.max_value;
            min_value = counter.min_value;
            counter.value = 0;
        }
        return *this;
    }

    friend istream& operator>>(istream& is, DigitalCounter& counter) 
    {
        is >> counter.value;
        is >> counter.max_value;
        is >> counter.min_value;
        return is;
    }

    friend ostream& operator<<(ostream& os, const DigitalCounter& counter) 
    {
        os << "Поточне значення: " << counter.value << endl;
        os << "Максимальне значення: " << counter.max_value << endl;
        os << "Мінімальне значення: " << counter.min_value << endl;
        return os;
    }
};

class Stopwatch : public DigitalCounter 
{
    bool running;
public:
    Stopwatch() : DigitalCounter()
    {
        running = false;
    }

    Stopwatch(int value, int max_value, int min_value, bool running) : DigitalCounter(value, max_value, min_value)
    {
        this->running = running;
    }

    void start() 
    { 
        running = true;
    }

    void stop() 
    { 
        running = false;
    }

    bool isRunning()
    { 
        return running;
    }

    void increaseValue()
    {
        ++(*this);
    }

    void decreaseValue()
    {
        --(*this);
    }

    void increaseValueBy(int increment)
    {
        *this += increment;
    }

    void decreaseValueBy(int decrement)
    {
        *this -= decrement;
    }

    void assignValue(int newValue)
    {
        setValue(newValue);
    }

    void printValues() override 
    {
        DigitalCounter::printValues();
        cout << "Стан секундоміра: " << (running ? "Включено" : "Виключено") << endl;
    }

    friend ostream& operator<<(ostream& os, Stopwatch& stopwatch) 
    {
        os << "Поточне значення: " << stopwatch.getValue() << endl;
        os << "Максимальне значення: " << stopwatch.getMaxValue() << endl;
        os << "Мінімальне значення: " << stopwatch.getMinValue() << endl;
        os << "Стан секундоміра: " << (stopwatch.running ? "Включено" : "Виключено") << endl;
        return os;
    }
};

class RaceResults 
{
    MyVector<Stopwatch> races;
public:
    void addRace(Stopwatch race) 
    {
        races.push_back(race);
    }

    Stopwatch& getRace(int index)
    {
        if (index >= 0 && index < races.size()) 
        {
            return races[index];
        }
        else 
        {
            throw out_of_range("Неприпустимий індекс забігу.");
        }
    }

    int getSize()
    {
        return races.size();
    }

    int minTime()
    {
        if (races.empty())
        {
            cerr << "Масив перегонів порожній!" << endl;
            return -1;
        }

        auto minRace = min_element(races.begin(), races.end(),
            [](Stopwatch& a, Stopwatch& b) 
            {
                return a.getValue() < b.getValue();
            });

        return minRace->getValue();
    }

    int maxTime()
    {
        if (races.empty()) 
        {
            cerr << "Масив перегонів порожній!" << endl;
            return -1; 
        }

        auto maxRace = max_element(races.begin(), races.end(),
            [](Stopwatch& a, Stopwatch& b) 
            {
                return a.getValue() < b.getValue();
            });

        return maxRace->getValue();
    }

    double averageTime()
    {
        if (races.empty()) 
        {
            cerr << "Масив перегонів порожній!" << endl;
            return -1;
        }

        int sum = 0;
        for (auto& race : races) 
        {
            sum += race.getValue();
        }

        return static_cast<double>(sum) / races.size();
    }

    MyVector<int>& winners()
    {
        if (races.empty())
        {
            cerr << "Масив перегонів порожній!" << endl;
            static MyVector<int> emptyVector;
            return emptyVector;
        }

        MyVector<int> times;
        for (auto& race : races) 
        {
            times.push_back(race.getValue());
        }

        sort(times.begin(), times.end());

        static MyVector<int> winners;
        winners = MyVector<int>();
        for (int i = 0; i < 3 && i < times.size(); ++i) 
        {
            winners.push_back(times[i]);
        }
        return winners;
    }

    void readFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Неможливо відкрити файл " << filename << endl;
            return;
        }

        int value, max_value, min_value;
        bool running;
        while (file >> value >> max_value >> min_value >> running)
        {
            races.push_back(Stopwatch(value, max_value, min_value, running));
        }

        file.close();
    }

    void writeToFile(const string& filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Неможливо відкрити файл " << filename << " для написання." << endl;
            return;
        }
        file.clear();
        for (auto& race : races)
        {
            file << race.getValue() << " " << race.getMaxValue() << " " << race.getMinValue() << " " << race.isRunning() << endl;
        }

        file.close();
    }
};

void startNewRace(RaceResults& raceResults)
{
    Stopwatch newRace;
    newRace.start();
    cout << "Запишіть результат: " << endl;
    int result;
    cin >> result;
    try
    {
        if (result < newRace.getMinValue() || result > newRace.getMaxValue())
        {
            throw out_of_range("Невірне значення");
        }
        else if (cin.fail())
        {
            throw invalid_argument("Введено неправильний тип даних");
        }
        else
        {
            newRace.setValue(result);
            newRace.stop();
            raceResults.addRace(newRace);
        }
    }
    catch (const out_of_range& e)
    {
        cerr << "Помилка: " << e.what() << endl;
    }
    catch (const invalid_argument& e)
    {
        cerr << "Помилка: " << e.what() << endl;
    }
}

void displayRecords(RaceResults& raceResults)
{
    cout << "Рекорди:" << endl;
    cout << "Мінімальний час: " << raceResults.minTime() << endl;
    cout << "Максимальний час: " << raceResults.maxTime() << endl;
    cout << "Середній час: " << raceResults.averageTime() << endl;
    cout << "Перші три переможці: ";
    MyVector<int> winners = raceResults.winners();
    for (int time : winners) 
    {
        cout << time << " ";
    }
    cout << endl;
}

void displayMenu() 
{
    cout << "Меню:" << endl;
    cout << "1. Додати результати забігу" << endl;
    cout << "2. Показати рекорди" << endl;
    cout << "3. Вивести інформацію про забіг за його номером" << endl;
    cout << "4. Змінити значення забігу" << endl;
    cout << "5. Зберегти результати у файл" << endl;
    cout << "6. Зчитати результати з файлу" << endl;
    cout << "7. Вийти" << endl;
    cout << "Виберіть опцію: ";
}

void changeValue(RaceResults& raceResults)
{
    cout << "1. Збільшити значення забігу на 1" << endl;
    cout << "2. Зменшити значення забігу на 1" << endl;
    cout << "3. Збільшити значення забігу на вказане число" << endl;
    cout << "4. Зменшити значення забігу на вказане число" << endl;
    cout << "5. Присвоїти нове значення забігу" << endl;
    cout << "Виберіть опцію: ";
    unsigned choice;
    cin >> choice;
    int index;
    cout << "Введіть індекс забігу, який бажаєте змінити: ";
    cin >> index;
    switch (choice)
    {
    case 1:
        if (index >= 0 && index < raceResults.getSize())
        {
            Stopwatch& race = raceResults.getRace(index);
            race.increaseValue();
        }
        else
        {
            cout << "Невірний індекс." << endl;
        }break;
    case 2:
        if (index >= 0 && index < raceResults.getSize())
        {
            Stopwatch& race = raceResults.getRace(index);
            race.decreaseValue();
        }
        else
        {
            cout << "Невірний індекс." << endl;
        }break;
    case 3:
        if (index >= 0 && index < raceResults.getSize())
        {
            int i;
            cout << "Введіть значення: ";
            cin >> i;
            Stopwatch& race = raceResults.getRace(index);
            race.increaseValueBy(i);
        }
        else
        {
            cout << "Невірний індекс." << endl;
        }break;
    case 4:
        if (index >= 0 && index < raceResults.getSize())
        {
            int i;
            cout << "Введіть значення: ";
            cin >> i;
            Stopwatch& race = raceResults.getRace(index);
            race.decreaseValueBy(i);
        }
        else
        {
            cout << "Невірний індекс." << endl;
        }break;
    case 5:
        if (index >= 0 && index < raceResults.getSize())
        {
            int i;
            cout << "Введіть значення: ";
            cin >> i;
            Stopwatch& race = raceResults.getRace(index);
            race.assignValue(i);
        }
        else
        {
            cout << "Невірний індекс." << endl;
        }break;
    default:  cout << "Помилка при виборі пункту меню." << endl; break;
    }
}

void displayValues(DigitalCounter& counter) 
{
    counter.printValues();
}

void displayCurrentValue(RaceResults& races, size_t index)
{
    index -= 1;
    if (index < races.getSize())
    {
        try
        {
            cout << "Вивести інформацію разом зі станом секундоміра?\n1. Так\n2. Ні" << endl;
            unsigned choice;
            cin >> choice;
            if (cin.fail() || (choice < 1 && choice > 2))
            {
                throw exception("Помилка при введенні значення.");
            }
            else if (choice == 1)
            {
                Stopwatch& race = races.getRace(index);
                displayValues(race);
            }
            else if (choice == 2)
            {
                DigitalCounter& race = races.getRace(index);
                DigitalCounter race1 = race;
                displayValues(race1);
            }
        }
        catch (exception& e)
        {
            cerr << "Помилка: " << e.what() << endl;
        }
    }
    else
    {
        cout << "Невірний індекс." << endl;
    }
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    RaceResults raceResults;
    unsigned choice;
    bool stopwork = false;
    while (stopwork != true)
    {
        displayMenu();

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        cin >> choice;
        switch (choice)
        {
        case 1: startNewRace(raceResults); break;
        case 2: displayRecords(raceResults); break;
        case 3: int index;
            cout << "Введіть номер результату, який хочете переглянути: ";
            cin >> index;
            displayCurrentValue(raceResults, index); break;
        case 4: changeValue(raceResults); break;
        case 5: raceResults.writeToFile("RaceResults.txt");
            cout << "Результати збережено у файл " << "RaceResults" << endl; break;
        case 6: raceResults.readFromFile("RaceResults.txt");
            cout << "Результати зчитано з файлу " << "RaceResults" << endl; break;
        case 7: stopwork = true; break;
        default:cout << "Помилка при виборі пункту меню." << endl; break;
        }
    }
    system("pause");
    return 0;
}
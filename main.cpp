#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <sstream>
using namespace std;
struct EVB
{
	string surname;
	string name;
	int yearOfBithDay;
};
struct Data
{
	int id;
	EVB info;
};

int add(const char* path, int &primaryKey);
void del(const char* path, int& primaryKey);
void change(const char* path, int& primaryKey);
void printConsole(const char* path);
void printConsoleWithOption(const char* path);
void menu();
int readData(int &primaryKey);

int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();
    int processing = 1;
    int size = 0;
    int primaryKey = 0;
    readData(primaryKey);
    while(processing)
    {
    	int selectFunc = 0;
    	cout << "Оберіть команду за номером(1, 2, 3, 4, 5, 6, 7): ";
    	cin >> selectFunc;
    	switch(selectFunc)
    	{
    		case 1: add("F:\\t\\src.txt", primaryKey); break;
    		case 2: del("F:\\t\\src.txt", primaryKey); break;
    		case 3: change("F:\\t\\src.txt", primaryKey); break;
    		case 4: printConsole("F:\\t\\src.txt"); break;
    		case 5: printConsoleWithOption("F:\\t\\src.txt"); break;
    		case 6: menu(); break;
    		case 7: processing = 0; break;
    		default: cout<< "Ви ввели неправильний номер команди. Спробуйте ще раз!" << endl; break;
		};
	}
    return 0;
}

int add(const char* path, int &primaryKey) {
    ofstream file(path, ios::app);
    if (file) {
    	Data data;
    	data.id = primaryKey++;
        cout << "Введіть прізвище жителя: ";
        cin >> data.info.surname;
        cout << "Введіть ім'я' жителя: ";
        cin >> data.info.name;
        cout << "Введіть рік народження жителя: ";
        cin >> data.info.yearOfBithDay;
        file << data.id << " "  << data.info.surname << " " << data.info.name << " " << data.info.yearOfBithDay << endl;
        file.close();
        cout << "Дані записані у файл успішно" << endl;
    } 
	else {
        cout << "Не вдалося відкрити файл для додавання." << endl;
    }
    ofstream updateData("F:\\t\\data.ini");
    if (!updateData) {
        cout << "Не вдалося прочитати файл конфігурації проєкту." << endl;
    } 
    else
	 {
        updateData << primaryKey;
        updateData.close();
    }
    return primaryKey;
}
void del(const char* path, int& primaryKey) {
    int DELprimaryKey;
    cout << "Введіть первинний ключ елемента, який Ви хочете видалити: ";
    cin >> DELprimaryKey; 
    if(DELprimaryKey > primaryKey)
    {
    	cout << "Первинний ключ запису позамежами стеку" << endl;
	}
	else
	{
		ifstream inputFile(path);
    	ofstream outputFile("temp.txt");
    	if (inputFile && outputFile) {
       	Data data;
        	while (inputFile >> data.id >> data.info.surname >> data.info.name >> data.info.yearOfBithDay) {
            	if (data.id != DELprimaryKey) {
            		if(data.id > DELprimaryKey)
            		{
            			outputFile << data.id - 1 << " " << data.info.surname << " " << data.info.name << " " << data.info.yearOfBithDay << endl;
					}
                	else
                	{
                		outputFile << data.id << " " << data.info.surname << " " << data.info.name << " " << data.info.yearOfBithDay << endl;
					}
            	}
        	}
        	inputFile.close();
        	outputFile.close();
        	remove(path);
        	rename("temp.txt", path);
        	cout << "Запис з первинним ключем " << DELprimaryKey << " був видалений успішно!" << endl;
    	} else {
        	cout << "Помилка у читанні або створені файлу!" << endl;
    	}
    	int coutOfprimaryKey = primaryKey - 1;
    	ofstream updateData("F:\\t\\data.ini");
    	if (!updateData) {
        	cout << "Не вдалося прочитати файл конфігурації проєкту." << endl;
    	} 
    	else
	 	{
        	updateData << coutOfprimaryKey;
        	updateData.close();
    	}
	}
    
}
void change(const char* path, int& primaryKey) {
    int CHANGEprimaryKey;
    cout << "Введіть первинний ключ елемента, який Ви хочете оновити: ";
    cin >> CHANGEprimaryKey; 
    if(CHANGEprimaryKey > primaryKey)
    {
    	cout << "Первинний ключ запису позамежами стеку" << endl;
	}
	else
	{
		ifstream inputFile(path);
    	ofstream outputFile("temp.txt");
    	if (inputFile && outputFile) {
       		Data data;
        	while (inputFile >> data.id >> data.info.surname >> data.info.name >> data.info.yearOfBithDay) {
            	if (data.id == CHANGEprimaryKey) {
            		cout << "Введіть нові дані" << endl;
            		cout << "Введіть прізвище жителя: ";
        			cin >> data.info.surname;
        			cout << "Введіть ім'я' жителя: ";
        			cin >> data.info.name;
        			cout << "Введіть рік народження жителя: ";
        			cin >> data.info.yearOfBithDay;
					outputFile << data.id << " " << data.info.surname << " " << data.info.name << " " << data.info.yearOfBithDay << endl;
        			cout << "Дані змінені у файл успішно" << endl;   	
            	}
                else
                {
                	outputFile << data.id << " " << data.info.surname << " " << data.info.name << " " << data.info.yearOfBithDay << endl;
				}
        	}
        	inputFile.close();
        	outputFile.close();
        	remove(path);
        	rename("temp.txt", path);
        	cout << "Запис з первинним ключем " << CHANGEprimaryKey << " був змінений успішно!" << endl;
    	} else {
        	cout << "Помилка у читанні або створені файлу!" << endl;
    	}
	}
}
void printConsole(const char* path)
{
	ifstream file(path);
	if(file)
	{
		string line;
		while(getline(file, line))
		{
			cout << line << endl;
		}
	}
	else
	{
		cout << "Не вдалося прочитати файл" << endl;
	}
}
void printConsoleWithOption(const char* path)
{
	int counOfResidents = 0;
    ifstream file(path);
    if(file)
    {
        Data data;
        while (file >> data.id >> data.info.surname >> data.info.name >> data.info.yearOfBithDay)
        {
        	if(data.info.yearOfBithDay > 1990)
        	{
        		cout << data.info.surname << " " << data.info.name << " " << data.info.yearOfBithDay << endl;
        		counOfResidents++;
			}
        }
        file.close(); 
    }
    else
    {
        cout << "Не вдалося відкрити файл для читання." << endl;
    }
    cout << "Кількість жителів народжених після 1990 року: " << counOfResidents << endl;
}
void menu()
{
    cout << "                  Меню                 \n";
    cout << "____________________________________________" << endl;
    cout << "Список команд:\n1. Додати до файлу наступний запис;\n2. Видалити з файлу вказаний запис;\n3. Змінити у файлі вказаний запис;\n4. Вивести дані у консоль;\n5. Вивести дані у консоль за певною умовою;\n6. Вивести меню;\n7. Завершити роботу програми." << endl;
}
int readData(int &primaryKey)
{
	ifstream file("F:\\t\\data.ini");
    if (!file) {
        cout << "Не вдалося прочитати файл конфігурації проєкту." << endl;
    }
	string line;
    if (getline(file, line)) {
        primaryKey = atoi(line.c_str());
        file.close();
        return primaryKey;
    } 
    else 
    {
        primaryKey = 0;
        file.close();
        return primaryKey;
    }
}

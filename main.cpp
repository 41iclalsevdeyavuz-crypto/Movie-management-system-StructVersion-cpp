#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

struct Movie;
void Find(Movie* movies, int& CURRENTSIZE);
void New(Movie*& movies, int& CURRENTSIZE, int& CAPACITY);
void List(Movie* movies, int& CURRENTSIZE);
void showmenu(Movie*& movies, int& CURRENTSIZE, int& CAPACITY);
void submenu(Movie* movies, int& CURRENTSIZE, int& index);
void Edit(Movie* movies, int index);
void Delete(Movie* movies, int& CURRENTSIZE, int index);
void expandArray(Movie*& arr, int& capacity, int currentSize);
void saveToFile(Movie* movies, int size, const string& filename);
void loadFromFile(Movie*& movies, int& size, int& capacity, const string& filename);
bool isValidDate(string input);
bool isValidNumber(string input);
long getNumberInput(string prompt);
string getDateInput(string prompt);
string getStringInput(string prompt);


struct Movie {
    string Movie_Title;
    string Domestic_Distributor;
    long int Budget;
    long int Domestic_Box_Office;
    string Domestic_Release_Date;
    string Director_Name;
    int Running_Time_MIN;
    
    void display(int index) const;
    void input();
};
void Movie::display(int index) const {
    cout << "-----------Movie Found-------\n";
    cout << "Index: " << index << "\n";
    cout << "Movie Title:               " << Movie_Title << "\n";
    cout << "Domestic Distributor:      " << Domestic_Distributor << "\n";
    cout << "Budget ($):                " << Budget << "\n";
    cout << "Domestic Box Office ($):   " << Domestic_Box_Office << "\n";
    cout << "Domestic Release Date:     " << Domestic_Release_Date << "\n";
    cout << "Director's Name:           " << Director_Name << "\n";
    cout << "Running Time (minutes):    " << Running_Time_MIN << "\n";
}
void Movie::input() {
    Movie_Title = getStringInput("Movie Title(String):\n");
    Domestic_Distributor = getStringInput("Domestic Distributor(String):\n");
    Budget = getNumberInput("Budget($):\n");
    Domestic_Box_Office = getNumberInput("Domestic Box Office(integer):\n");
    Domestic_Release_Date = getDateInput("Domestic_Release_Date(string DD.MM.YYYY format):\n");
    Director_Name = getStringInput("Director Name(string):\n");
    Running_Time_MIN = getNumberInput("Running_Time_MIN(integer):\n");
}

int main()
{
    int CAPACITY = 5;
    int CURRENTSIZE = 0;
    Movie* movies = new Movie[CAPACITY];
    string filename = "movies.txt";
    loadFromFile(movies, CURRENTSIZE, CAPACITY, filename);
    showmenu(movies, CURRENTSIZE, CAPACITY);
    saveToFile(movies, CURRENTSIZE, filename);

    delete[] movies;
    return 0;
}

bool isValidNumber(string input)
{
    if (input.empty()) return false;
    for (int i = 0; i < (int)input.length(); i++) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}

bool isValidDate(string input)
{
    if (input.length() != 10) return false;
    if (input[2] != '.' || input[5] != '.') return false;

    if (!isdigit(input[0]) || !isdigit(input[1])) return false;
    if (!isdigit(input[3]) || !isdigit(input[4])) return false;
    for (int i = 6; i < 10; i++) {
        if (!isdigit(input[i])) return false;
    }

    int day = 0;
    day = day + (input[0] - '0') * 10;
    day = day + (input[1] - '0');

    int month = 0;
    month = month + (input[3] - '0') * 10;
    month = month + (input[4] - '0');

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}

long getNumberInput(string prompt)
{
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (isValidNumber(input)) {
            return stol(input);
        }
        cout << "Invalid input! Please enter numbers only.\n";
    }
}

string getDateInput(string prompt)
{
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (isValidDate(input)) {
            return input;
        }
        cout << "Invalid date format!\n";
    }
}

string getStringInput(string prompt)
{
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);

        if (input.empty()) {
            cout << "Input cannot be empty! Please try again.\n";
            continue;
        }

        if (input.length() < 2) {
            cout << "Input too short! Please enter at least 2 characters.\n";
            continue;
        }

        bool allSpaces = true;
        for (int i = 0; i < (int)input.length(); i++) {
            if (input[i] != ' ') {
                allSpaces = false;
                break;
            }
        }
        if (allSpaces) {
            cout << "Input cannot be only spaces! Please try again.\n";
            continue;
        }

        bool hasLetter = false;
        for (int i = 0; i < (int)input.length(); i++) {
            if (isalpha(input[i])) {
                hasLetter = true;
                break;
            }
        }
        if (!hasLetter) {
            cout << "Input must contain at least one letter! Please try again.\n";
            continue;
        }

        return input;
    }
}
void expandArray(Movie*& arr, int& capacity, int currentSize) {
    int newCapacity = capacity * 2;
    Movie* newArr = new Movie[newCapacity];

    for (int i = 0; i < currentSize; i++) {
        newArr[i] = arr[i];
    }
    
    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
    
    cout << "Array expanded! New capacity: " << capacity << "\n";
}

void saveToFile(Movie* movies, int size, const string& filename) {
    ofstream outFile(filename);
    
    if (!outFile) {
        cout << "Error: Could not save to file!\n";
        return;
    }
    
    outFile << size << "\n";
    
    for (int i = 0; i < size; i++) {
        outFile << movies[i].Movie_Title << "\n";
        outFile << movies[i].Domestic_Distributor << "\n";
        outFile << movies[i].Budget << "\n";
        outFile << movies[i].Domestic_Box_Office << "\n";
        outFile << movies[i].Domestic_Release_Date<< "\n";
        outFile << movies[i].Director_Name<< "\n";
        outFile << movies[i].Running_Time_MIN<< "\n";
    }
    
    outFile.close();
    cout << "Data saved successfully to " << filename << "\n";
}

void loadFromFile(Movie*& movies, int& size, int& capacity, const string& filename) {
    ifstream inFile(filename);
    
    if (!inFile) {
        cout << "No existing data file. Starting fresh.\n";
        return;
    }
    
    int fileSize;
    inFile >> fileSize;
    inFile.ignore();
    
    while (fileSize > capacity) {
        expandArray(movies, capacity, capacity);
    }
    
    for (int i = 0; i < fileSize; i++) {
        getline(inFile, movies[i].Movie_Title);
        getline(inFile, movies[i].Domestic_Distributor);
        inFile >> movies[i].Budget;
        inFile >> movies[i].Domestic_Box_Office;
        inFile.ignore();
        getline(inFile, movies[i].Domestic_Release_Date);
        getline(inFile, movies[i].Director_Name);
        inFile >> movies[i].Running_Time_MIN;
        inFile.ignore();
    }
    
    size = fileSize;
    inFile.close();
    cout << "Loaded " << size << " movies from file.\n";
}


void showmenu(Movie*& movies, int& CURRENTSIZE, int& CAPACITY)
{
    int choice;
    int back = 1;
    do
    {
        cout << "------Welcome---------\n";
        cout << "     1. New\t\n";
        cout << "     2. Find\t\n";
        cout << "     3. List\t\n";
        cout << "     4. Save\t\n";
        cout << "     5. Exit\t\n";
        cout << "----------------------\n";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            New(movies, CURRENTSIZE, CAPACITY);
            break;
        case 2:
            Find(movies, CURRENTSIZE);
            break;
        case 3:
            List(movies, CURRENTSIZE);
            break;
        case 4:
            saveToFile(movies, CURRENTSIZE, "movies.txt");
            break;
        case 5:
            back = 0;
            break;
        default:
            cout << "enter a valid argument\n";
        }
    } while (back);
}

void submenu(Movie* movies, int& CURRENTSIZE, int& index)
{
    int subchoice;
    int back = 1;
    do
    {
        cout << "------Welcome--------" << "\n";
        cout << "    1. Edit\t\t\n";
        cout << "    2. Delete\t\t\n";
        cout << "    3. Exit\t\t\n";
        cout << "---------------------";
        cin >> subchoice;
        cin.ignore();
        switch (subchoice)
        {
        case 1:
            Edit(movies, index);
            break;
        case 2:
            Delete(movies, CURRENTSIZE, index);
            break;
        case 3:
            back = 0;
            break;
        default:
            cout << "Enter a valid argument \n";
        }
    } while (back);
}

void Edit(Movie* movies, int index)
{
    int back = 1;
    do {
        int subsubchoice;
        cout << "Please select the environment you want to edit\n";
        cout << "1. Movie Title:               \n";
        cout << "2. Domestic Distributor:      \n";
        cout << "3. Budget ($):                \n";
        cout << "4. Domestic Box Office ($):   \n";
        cout << "5. Domestic Release Date:     \n";
        cout << "6. Director's Name:           \n";
        cout << "7. Running Time (minutes):    \n";
        cin >> subsubchoice;
        cin.ignore();

        switch (subsubchoice)
        {
        case 1:
            movies[index].Movie_Title = getStringInput("Enter the New Movie Title:\n");
            back = 0;
            break;
        case 2:
            movies[index].Domestic_Distributor = getStringInput("Enter the Domestic Distributor:\n");
            back = 0;
            break;
        case 3:
            movies[index].Budget = getNumberInput("Enter the Budget ($):\n");
            back = 0;
            break;
        case 4:
            movies[index].Domestic_Box_Office = getNumberInput("Enter the Domestic Box Office ($):\n");
            back = 0;
            break;
        case 5:
            movies[index].Domestic_Release_Date = getDateInput("Enter the Domestic Release Date (DD.MM.YYYY):\n");
            back = 0;
            break;
        case 6:
            movies[index].Director_Name = getStringInput("Enter the Director's Name:\n");
            back = 0;
            break;
        case 7:
            movies[index].Running_Time_MIN = getNumberInput("Enter the Running Time (minutes):\n");
            back = 0;
            break;
        default:
            cout << "Enter a valid argument\n";
        }
    } while (back);
}

void Delete(Movie* movies, int& CURRENTSIZE, int index)
{
    int deletechoice;
    cout << "!!!!!!WARNING!!!!!\n";
    cout << "If you delete the Movie title, then you delete the whole data";
    cout << "Do you want to delete " << movies[index].Movie_Title << "?, If so please enter 1 else enter 0\n";
    cin >> deletechoice;
    cin.ignore();

    if (deletechoice == 1)
    {
        movies[index].Movie_Title = "";
        movies[index].Domestic_Distributor = "";
        movies[index].Budget = 0;
        movies[index].Domestic_Box_Office = 0;
        movies[index].Domestic_Release_Date = "";
        movies[index].Director_Name = "";
        movies[index].Running_Time_MIN = 0;

        for (int i = index; i < CURRENTSIZE - 1; i++)
        {
            movies[i].Movie_Title = movies[i+1].Movie_Title;
            movies[i].Domestic_Distributor = movies[i+1].Domestic_Distributor;
            movies[i].Budget = movies[i+1].Budget;
            movies[i].Domestic_Box_Office = movies[i+1].Domestic_Box_Office;
            movies[i].Domestic_Release_Date = movies[i+1].Domestic_Release_Date;
            movies[i].Director_Name = movies[i+1].Director_Name;
            movies[i].Running_Time_MIN = movies[i+1].Running_Time_MIN;
        }
        CURRENTSIZE--;
        cout << "Movie successfully deleted!\n";
    }
    else
    {
        cout << "Movie Did not deleted\n";
    }
}

void New(Movie*& movies, int& CURRENTSIZE, int& CAPACITY)
{
    if (CURRENTSIZE >=CAPACITY)
    {
        expandArray(movies, CAPACITY, CURRENTSIZE);
    }

    movies[CURRENTSIZE].Movie_Title = getStringInput("Movie Title(String):\n");
    movies[CURRENTSIZE].Domestic_Distributor = getStringInput("Domestic Distributor(String):\n");
    movies[CURRENTSIZE].Budget = getNumberInput("Budget($):\n");
    movies[CURRENTSIZE].Domestic_Box_Office = getNumberInput("Domestic Box Office(integer):\n");
    movies[CURRENTSIZE].Domestic_Release_Date = getDateInput("Domestic_Release_Date(string DD.MM.YYYY format):\n");
    movies[CURRENTSIZE].Director_Name = getStringInput("Director Name(string):\n");
    movies[CURRENTSIZE].Running_Time_MIN = getNumberInput("Running_Time_MIN(integer):\n");

    CURRENTSIZE++;
    cout << "Movie Added Successfully!\n";
}

void Find(Movie* movies, int& CURRENTSIZE)
{
    int searchChoice;
    cout << "Search by:\n";
    cout << "1. Movie Title\n";
    cout << "2. Director Name\n";
    cout << "Enter your choice: ";
    cin >> searchChoice;
    cin.ignore();

    string look;
    int find = 0, index;

    if (searchChoice == 1)
    {
        do {
            cout << "Enter the Movie title\n";
            getline(cin, look);
            for (int i = 0; i < CURRENTSIZE; i++)
            {
                if (movies[i].Movie_Title == look)
                {
                    find = 1;
                    index = i;
                    break;
                }
            }
            if (find)
            {
                movies[index].display(index);
                submenu(movies, CURRENTSIZE, index);
            }
            else
            {
                cout << "Please try again!\n";
            }

        } while (find == 0);
    }
    else if (searchChoice == 2)
    {

        while (true)
        {
            cout << "Enter the Director Name:\n";
            getline(cin, look);

            int matches[100];
            int matchCount = 0;

            for (int i = 0; i < CURRENTSIZE; i++)
            {
                if (movies[i].Director_Name == look)
                {
                    matches[matchCount] = i;
                    matchCount++;
                }
            }

            if (matchCount == 0)
            {
                cout << "No movie found for this director. Please try again!\n";
                continue;
            }

            cout << "-----------Movies(s) Found (" << matchCount << ")-------\n";
            for (int k = 0; k < matchCount; k++)
            {
                int i = matches[k];
                cout << k + 1 << ") "
                     << "Index: " << i
                     << " | Title: " << movies[i].Movie_Title
                     << " | Release: " << movies[i].Domestic_Release_Date
                     << "\n";
            }

            int select;
            cout << "Select a movie (1-" << matchCount << "): ";
            cin >> select;
            cin.ignore();

            if (select < 1 || select > matchCount)
            {
                cout << "Invalid selection. Please try again!\n";
                continue;
            }

            index = matches[select - 1];
            find = 1;

            movies[index].display(index);
            submenu(movies, CURRENTSIZE, index);
            break;
        }
    }
    else
    {
        cout << "Invalid Input!\n";
        return;
    }
}

void List(Movie* movies, int& CURRENTSIZE)
{
    if (CURRENTSIZE == 0)
    {
        cout << "No movies to display.\n";
        return;
    }

    int size = CURRENTSIZE;
    cout << "The List:" << "\n";
    cout << left;

    cout << setw(55) << "Movie_Title";
    cout << setw(40) << "Domestic_Distributor";
    cout << setw(20) << "Budget";
    cout << setw(23) << "Domestic_Box_Office";
    cout << setw(25) << "Domestic_Release_Date";
    cout << setw(20) << "Director_Name";
    cout << setw(10) << "Running_Time_MIN";
    cout << "\n\n";

    for (int i = 0; i < size; i++)
    {
        cout << setw(55) << movies[i].Movie_Title;
        cout << setw(40) << movies[i].Domestic_Distributor;
        cout << setw(20) << movies[i].Budget;
        cout << setw(23) << movies[i].Domestic_Box_Office;
        cout << setw(25) << movies[i].Domestic_Release_Date;
        cout << setw(25) << movies[i].Director_Name;
        cout << setw(10) << movies[i].Running_Time_MIN;
        cout << "\n";
    }
}

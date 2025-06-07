#include "chashmap.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Constructor  bi initializes kol buckets to nullptr fi el bdya
HashMap::HashMap() {
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        buckets[i] = nullptr;
    }
}

// Insert a task into the appropriate category bucket
void HashMap::insert(Category category, Task task) {
    int index = static_cast<int>(category);
    Node* newNode = new Node(task);
    newNode->next = buckets[index];
    buckets[index] = newNode;
}


// Retrieve the head of the linked list for a specific category
Node* HashMap::getTasks(Category category) {
    int index = static_cast<int>(category);
    return buckets[index];
}

// Print tasks in a same specified category
void HashMap::printTasks(Category category) {
    int index = static_cast<int>(category);
    Node* current = buckets[index];
    std::cout << "Tasks for category: " << categoryNames[index] << "\n";
    while (current) {
        std::cout << "Title: " << current->task.title
            << ", Description: " << current->task.description
            << ", Priority: " << current->task.priority
            << ", Completed: " << (current->task.isCompleted ? "Yes" : "No") << "\n";
        current = current->next;
    }
    std::cout << std::endl;
}

// Destructor to clean up el dynami allocat kolo
HashMap::~HashMap() {
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        Node* current = buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}
// function batat3ml m3 el due date
void HashMap::printOverdueTasks() {
    time_t now = time(nullptr); // hat el current time
    std::cout << "Overdue Tasks:\n";

    for (int i = 0; i < CATEGORY_COUNT; i++) {
        Node* current = buckets[i];
        while (current) {
            if (current->task.dueDate < now) { // at2kd el task overdue wala la
                char dateBuffer[26]; // Buffer for formatted date
                ctime_s(dateBuffer, sizeof(dateBuffer), &current->task.dueDate); // Format the due date
                std::cout << "Category: " << categoryNames[i] << "\n"
                    << "Title: " << current->task.title
                    << ", Due Date: " << dateBuffer;
            }
            current = current->next;
        }
    }
    std::cout << std::endl;
}



void HashMap::printTasksSortedByDueDate() {
    struct CategorizedTask {
        std::string category;
        Task task;

        CategorizedTask() : category(""), task("", "", 0, false, 0) {}
        CategorizedTask(std::string cat, Task t) : category(cat), task(t) {}
    };

    // Estimate the total number of tasks
    int maxTasks = 0;
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        Node* current = buckets[i];
        while (current) {
            maxTasks++;
            current = current->next;
        }
    }

    if (maxTasks == 0) {
        std::cout << "No tasks to display.\n";
        return;
    }

    // Dynamically bi store fih kol el all tasks by allocation
    CategorizedTask* taskList = new CategorizedTask[maxTasks];
    int taskCount = 0;

    // gam3 el tasks fi array
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        Node* current = buckets[i];
        while (current) {
            taskList[taskCount++] = CategorizedTask(categoryNames[i], current->task);
            current = current->next;
        }
    }

    // Sort tasks dueDate using bubble sort
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (taskList[j].task.dueDate > taskList[j + 1].task.dueDate) {
                // dy lu el swayping
                CategorizedTask temp = taskList[j];
                taskList[j] = taskList[j + 1];
                taskList[j + 1] = temp;
            }
        }
    }

    // yatb3 el sortated tasks
    std::cout << "Tasks Sorted by Due Date:\n";
    for (int i = 0; i < taskCount; i++) {
        char dateBuffer[26];
        ctime_s(dateBuffer, sizeof(dateBuffer), &taskList[i].task.dueDate);
        std::cout << "Category: " << taskList[i].category << "\n"
            << "Title: " << taskList[i].task.title
            << ", Due Date: " << dateBuffer;
    }
    std::cout << std::endl;

    // Free dynamically allocated memory
    delete[] taskList;
}





void HashMap::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return;
    }

    
    //3shan yaloop 3ala kolo w yaktbo fi el file
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        Node* current = buckets[i];
        if (current) {
            // byktb el head bat3 el categroy
            file << (i + 1) << ") " << categoryNames[i] << ":\n";

            // Iterate through tasks in the current category
            while (current) {
                file << current->task.title << ", "
                    << current->task.description << ", "
                    << current->task.priority << ", "
                    << current->task.isCompleted << ", "
                    << current->task.dueDate << "\n";
                current = current->next;
            }
            file << "\n"; // Separate categories with a blank line
        }
    }

    file.close();
    cout << "Tasks saved to file: " << filename << endl;
}




void HashMap::printTasksDueToday() {
    time_t now = time(nullptr);
    tm now_tm;
    localtime_s(&now_tm, &now);

    now_tm.tm_hour = 0;
    now_tm.tm_min = 0;
    now_tm.tm_sec = 0;
    time_t startOfDay = mktime(&now_tm);

    now_tm.tm_hour = 23;
    now_tm.tm_min = 59;
    now_tm.tm_sec = 59;
    time_t endOfDay = mktime(&now_tm);

    std::cout << "Tasks Due Today:\n";

    for (int i = 0; i < CATEGORY_COUNT; i++) {
        Node* current = buckets[i];
        while (current) {
            if (current->task.dueDate >= startOfDay && current->task.dueDate <= endOfDay) {
                char dateBuffer[26];
                ctime_s(dateBuffer, sizeof(dateBuffer), &current->task.dueDate);
                std::cout << "Category: " << categoryNames[i] << "\n"
                    << "Title: " << current->task.title
                    << ", Due Date: " << dateBuffer;
            }
            current = current->next;
        }
    }
    std::cout << std::endl;
}



void HashMap::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for reading: " << filename << endl;
        return;
    }

    string line;
    int categoryIndex = -1;

    while (getline(file, line)) {
        // at2akd men el category line mawgood
        if (line.find(")") != string::npos) {
            size_t pos = line.find(")");
            categoryIndex = stoi(line.substr(0, pos)) - 1;
            continue;
        }

        // 3dy el line el fdya
        if (line.empty()) {
            continue;
        }

        // extracting information mo3yana
        size_t firstComma = line.find(", ");
        size_t secondComma = line.find(", ", firstComma + 2);
        size_t thirdComma = line.find(", ", secondComma + 2);
        size_t fourthComma = line.find(", ", thirdComma + 2);

        string title = line.substr(0, firstComma);
        string description = line.substr(firstComma + 2, secondComma - firstComma - 2);
        int priority = stoi(line.substr(secondComma + 2, thirdComma - secondComma - 2));
        bool isCompleted = stoi(line.substr(thirdComma + 2, fourthComma - thirdComma - 2));
        time_t dueDate = stol(line.substr(fourthComma + 2));

        // Create and insert the task into the corresponding category
        Task task(title, description, priority, isCompleted, dueDate);
        insert(static_cast<Category>(categoryIndex), task);
    }

    file.close();
    cout << "Tasks loaded from file: " << filename << endl;
}
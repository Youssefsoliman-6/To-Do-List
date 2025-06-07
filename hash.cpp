#pragma once
#include "chashmap.h"
using namespace std;

int main() {
    HashMap toDoList;
    // asm el file
    const string filename = "task.txt";
    // laod men el file
    toDoList.loadFromFile(filename);



    // test cases
    Task task1("Math Homework", "Complete exercises 1-10", 3, false, time(nullptr) - 3600);  // Overdue
    Task task2("Clean Kitchen", "Wash dishes", 2, false, time(nullptr) + 3600);  // Due soon
    Task task3("Workout", "Run 5km", 1, false, time(nullptr) + 86400 * 3);  // Future task
    Task task4("Physics Homework", "Complete chapter 5 problems", 5, false, time(nullptr) - 7200);  // Overdue
    Task task5("Grocery Shopping", "Buy vegetables and fruits", 4, false, time(nullptr) + 3600); /

        // Insert el taskes fi el category
        toDoList.insert(STUDYING, task1);
        toDoList.insert(KITCHEN, task2);
        toDoList.insert(FITNESS, task3);
        toDoList.insert(STUDYING, task4);
        toDoList.insert(KITCHEN, task5);

        // bytb3 el tasks
        cout << "All Tasks in Their Categories:\n";
        toDoList.printTasks(STUDYING);
        toDoList.printTasks(KITCHEN);
        toDoList.printTasks(FITNESS);

        // bytb3 el over due task
        cout << "\nOverdue Tasks:\n";
        toDoList.printOverdueTasks();

        // bybtb3 el tasks el due today
        cout << "\nTasks Due Today:\n";
        toDoList.printTasksDueToday();

        // atb3 el tasks bel sorting by due
        cout << "\nTasks Sorted by Due Date:\n";
        toDoList.printTasksSortedByDueDate();
        // save men el file
        toDoList.saveToFile(filename);


    return 0;
}
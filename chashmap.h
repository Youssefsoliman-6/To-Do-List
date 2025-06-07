#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <ctime>
#include <iostream>

using namespace std;

// Task struct representing a single to-do task
struct Task {
    std::string title;
    std::string description;
    int priority;       // Higher value = higher priority
    bool isCompleted;   // Completion status
    time_t dueDate;     // Deadline for the task

    Task(std::string t, std::string desc, int prio, bool completed, time_t due)
        : title(t), description(desc), priority(prio), isCompleted(completed), dueDate(due) {}
};

// Enum representing predefined categories
enum Category {
    STUDYING,
    KITCHEN,
    WORK,
    FITNESS,
    HOBBIES,
    CATEGORY_COUNT // Used to define the number of categories
};

const std::string categoryNames[] = {
    "Studying",
    "Kitchen",
    "Work",
    "Fitness",
    "Hobbies"
};

// Node struct for chaining in each bucket
struct Node {
    Task task;
    Node* next;

    Node(Task t) : task(t), next(nullptr) {}
};

// HashMap class for managing the tasks
class HashMap {
private:
    Node* buckets[CATEGORY_COUNT]; // One bucket per category

public:
    HashMap();
    void insert(Category category, Task task);
    Node* getTasks(Category category);
    // Functions to deal with dueDate
    void printOverdueTasks();
    void printTasksDueToday();
    void printTasksSortedByDueDate();
    void printTasks(Category category);
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    ~HashMap();
};

#endif // HASHMAP_H
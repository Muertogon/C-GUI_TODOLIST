#include "TasksFile.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<std::string> TasksFile::getTasks() {
    TasksFile tasksFile;
    std::vector<std::string> tasks;

    std::ifstream file(tasksFile.filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening tasks.json" << std::endl;
        return tasks;
    }

    json j;
    file >> j;

    for (const auto& task : j["tasks"]) {
        tasks.push_back(task["name"].get<std::string>());
    }

    return tasks;
}
void TasksFile::addTaskToJSON(const std::string& taskName) {
    std::ifstream file(filePath);
    json j;
    file >> j;

    bool exists = std::any_of(j["tasks"].begin(), j["tasks"].end(),
        [&taskName](const auto& task) { return task["name"] == taskName; });

    if (!exists) {

        json newTask = { {"name", taskName} };

        j["tasks"].push_back(newTask);

        std::ofstream outfile(filePath);
        outfile << std::setw(4) << j << std::endl;
    }
    else {
        std::cout << "Task already exists." << std::endl;
    }
}

void TasksFile::removeTaskToJSON(const std::string& taskName) {
    std::ifstream file(filePath);
    if (!file) return;

    json j;
    file >> j;
    file.close();

    auto& tasks = j["tasks"];
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
        [&taskName](const json& task) {
            return task.contains("name") && task["name"] == taskName;
        }), tasks.end());

    std::ofstream(filePath) << j.dump(4);
}
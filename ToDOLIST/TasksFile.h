#pragma once

#include <vector>
#include <string>

class TasksFile{
public:
	std::vector<std::string> getTasks();
	void addTaskToJSON(const std::string& taskName);
	void removeTaskToJSON(const std::string& taskName);
private:
	std::string filePath = "D:\\Programming\\C++\\ToDO\\ToDOLIST\\ToDOLIST\\tasks.json";
};
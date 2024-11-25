#include "MainFrame.h"
#include "TasksFile.h"
#include <wx/wx.h>
#include <string>
#include <sstream>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	TasksFile tasksFile;
	CreateWidgets();
	BindEventHandles();
	RefreshTasks();
}
void MainFrame::OnAddButtonClicked(wxCommandEvent& evt) {
	AddTaskToList();
}

void MainFrame::OnResetButtonClicked(wxCommandEvent& evt) {
	ResetInput();
}

void MainFrame::CreateWidgets() {
	panel = new wxPanel(this);
	addButton = new wxButton(panel, wxID_ANY, "Add Task", wxPoint(50, 100), wxSize(100, 35));
	resetButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(150, 100), wxSize(100, 35));
	inputText = new wxTextCtrl(panel, wxID_ANY, "Your task here", wxPoint(50, 50), wxSize(200, 20));
	tasksList = new wxListBox(panel, wxID_ANY, wxPoint(40, 150), wxSize(220, 300));
	tip = new wxStaticText(panel, wxID_ANY, "TIP: Double click a task, to remove it", wxPoint(50, 500));
}

void MainFrame::BindEventHandles() {
	addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
	resetButton->Bind(wxEVT_BUTTON, &MainFrame::OnResetButtonClicked, this);
	tasksList->Bind(wxEVT_LISTBOX_DCLICK, &MainFrame::OnTaskDoubleClick, this);
}
void MainFrame::OnTaskDoubleClick(wxCommandEvent& evt) {
	wxListBox* listBox = dynamic_cast<wxListBox*>(evt.GetEventObject());
	int selectedIndex = tasksList->GetSelection();

	if (selectedIndex != wxNOT_FOUND) {
		wxString selectedItem = tasksList->GetString(selectedIndex);
		std::string convertedValue = selectedItem.ToStdString();
		tasksFile.removeTaskToJSON(convertedValue);
		RefreshTasks();
	}
}

void MainFrame::RefreshTasks() {
	tasksList->Clear();
	std::vector<std::string> tasks = tasksFile.getTasks();
	for (const auto& task : tasks) {
		tasksList->Insert(task, tasksList->GetCount());
	}
}

void MainFrame::AddTaskToList() {

	wxString value = inputText->GetValue();
	if (!inputText->IsEmpty()) {
		std::string convertedValue = value.ToStdString();
		tasksFile.addTaskToJSON(convertedValue);
	}
	RefreshTasks();
}

void MainFrame::ResetInput() {
	inputText->Clear();
}
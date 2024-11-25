#pragma once
#include <wx/wx.h>
#include "TasksFile.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void BindEventHandles();
	void CreateWidgets();
	void RefreshTasks();
	void OnAddButtonClicked(wxCommandEvent& evt);
	void AddTaskToList();
	void OnResetButtonClicked(wxCommandEvent& evt);
	void ResetInput();
	void OnTaskDoubleClick(wxCommandEvent& evt);
	TasksFile tasksFile;
	wxPanel* panel;
	wxTextCtrl* inputText;
	wxButton* addButton;
	wxButton* resetButton;
	wxListBox* tasksList;
	wxStaticText* tip;
};


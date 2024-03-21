#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include "DrawingPanel.h"
#include "Settings.h"

class MainWindow : public wxFrame {
private:
    Settings settings; // Non-pointer instance of Settings
    wxButton* button1;
    wxButton* button2;
    DrawingPanel* drawingPanel;
    wxBoxSizer* boxSizer;
    wxStatusBar* statusBar;
    wxToolBar* toolBar; // Change toolbar variable name
    wxTimer* timer; // Declare timer variable
    int generationCount; // Update generation count variable name
    int timerInterval = 50; // Timer interval in milliseconds
    int livingCellsCount; // Declare livingCellsCount variable
    int countLivingCells(); // Declare countLivingCells method
    std::vector<std::vector<bool>> gameBoard; // Add game board variable
    int gridSize = 10; // Add grid size variable
    int countLivingNeighbors(int row, int col);
    void OnButtonClick(wxCommandEvent& event);
    void OnNextButtonClick(wxCommandEvent& event);
    void OnSizeChange(wxSizeEvent& event);
    void initializeGrid();
    void updateStatusBar();
    void OnPlay(wxCommandEvent& event); // Event handler for play button
    void OnPause(wxCommandEvent& event); // Event handler for pause button
    void OnNext(wxCommandEvent& event);
    void OnTrash(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event); // Event handler for timer
    void StartTimer(); // Method to start the timer
    void StopTimer(); // Method to stop the timer
    void calculateNextGeneration(); // Method to calculate the next generation
    void OnToolBarClick(wxCommandEvent& event);
    enum {
        wxID_TOOLBAR_NEXT = wxID_HIGHEST + 1,
        wxID_TRASH,
        wxID_PLAY,
        wxID_PAUSE
    };

public:
    MainWindow();
    virtual ~MainWindow();
    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H

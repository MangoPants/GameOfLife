#include <wx/wx.h>
#include "MainWindow.h"
#include "DrawingPanel.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_BUTTON(10001, MainWindow::OnButtonClick)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_TOOL(wxID_ANY, MainWindow::OnToolBarClick)
EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "COS1 Example", wxPoint(100, 100), wxSize(300, 200)) {
    button1 = new wxButton(this, 10001, "Click on Me", wxPoint(20, 50), wxSize(75, 25));
    button2 = new wxButton(this, 10002, "No, Click on Me", wxPoint(145, 50), wxSize(125, 25));

    drawingPanel = new DrawingPanel(this);

    boxSizer = new wxBoxSizer(wxVERTICAL);
    boxSizer->Add(drawingPanel, 1, wxEXPAND | wxALL);
    SetSizer(boxSizer);

    statusBar = CreateStatusBar();
    toolBar = CreateToolBar();
    toolBar->AddTool(wxID_ANY, "Next", wxBitmap("next.xpm"));
    toolBar->Realize();

    initializeGrid();
    updateStatusBar();

    // Initialize the timer
    timer = new wxTimer(this, wxID_ANY);
    // Connect the timer event to the event handler
    timer->Bind(wxEVT_TIMER, &MainWindow::OnTimer, this);
}

void MainWindow::initializeGrid() {
    gameBoard.resize(gridSize, std::vector<bool>(gridSize, false));
    livingCellsCount = 0; // Initialize livingCellsCount
}

void MainWindow::updateStatusBar() {
    statusBar->SetStatusText(wxString::Format("Generation: %d | Living Cells: %d", generationCount, livingCellsCount), 0);
}

int MainWindow::countLivingNeighbors(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Skip the current cell
            int r = row + i;
            int c = col + j;
            if (r >= 0 && r < gridSize && c >= 0 && c < gridSize && gameBoard[r][c]) {
                count++;
            }
        }
    }
    return count;
}

// Define countLivingCells method
int MainWindow::countLivingCells() {
    int count = 0;
    for (size_t i = 0; i < gameBoard.size(); ++i) {
        for (size_t j = 0; j < gameBoard[i].size(); ++j) {
            if (gameBoard[i][j]) {
                count++;
            }
        }
    }
    return count;
}

void MainWindow::calculateNextGeneration() {
    std::vector<std::vector<bool>> sandbox = gameBoard;

    for (size_t i = 0; i < gameBoard.size(); ++i) {
        for (size_t j = 0; j < gameBoard[i].size(); ++j) {
            int livingNeighbors = countLivingNeighbors(i, j);

            if (gameBoard[i][j]) {
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    sandbox[i][j] = false; // Cell dies
                }
            }
            else {
                if (livingNeighbors == 3) {
                    sandbox[i][j] = true; // Cell becomes alive
                }
            }
        }
    }

    gameBoard.swap(sandbox);

    // Update generation count and living cells count
    generationCount++;
    livingCellsCount = countLivingCells(); // Update living cells count

    updateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::OnNextButtonClick(wxCommandEvent& event) {
    calculateNextGeneration();
}

void MainWindow::OnSizeChange(wxSizeEvent& event) {
    wxSize size = event.GetSize();
    drawingPanel->SetSize(size);
    event.Skip();
}

void MainWindow::OnButtonClick(wxCommandEvent& event) {
    if (event.GetId() == 10001) {
        button1->SetLabelText("Hello");
    }
}

void MainWindow::OnToolBarClick(wxCommandEvent& event) {
    switch (event.GetId()) {
    case wxID_TRASH: // ID for the "Trash" button
        OnTrash(event);
        break;
    case wxID_PLAY: // ID for the "Play" button
        OnPlay(event);
        break;
    case wxID_PAUSE: // ID for the "Pause" button
        OnPause(event);
        break;
    default:
        break;
    }
}

void MainWindow::OnTrash(wxCommandEvent& event) {
    // Clear the game board
    for (size_t i = 0; i < gameBoard.size(); ++i) {
        for (size_t j = 0; j < gameBoard[i].size(); ++j) {
            gameBoard[i][j] = false;
        }
    }

    // Reset generation count and living cells count
    generationCount = 0;
    livingCellsCount = 0;

    // Update status bar and refresh drawing panel
    updateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::OnPlay(wxCommandEvent& event) {
    StartTimer(); // Start the timer
}

void MainWindow::OnPause(wxCommandEvent& event) {
    StopTimer(); // Stop the timer
}

void MainWindow::OnNext(wxCommandEvent& event)
{
}

void MainWindow::OnTimer(wxTimerEvent& event) {
    calculateNextGeneration(); // Call the method to calculate the next generation
}

void MainWindow::StartTimer() {
    timer->Start(50); // Start the timer with an interval of 50 milliseconds
}

void MainWindow::StopTimer() {
    timer->Stop(); // Stop the timer
}

MainWindow::~MainWindow() {
    // Clean up resources if needed
}

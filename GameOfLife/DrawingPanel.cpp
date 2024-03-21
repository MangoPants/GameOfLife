#include "DrawingPanel.h"
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <vector>

std::vector<std::vector<bool>> DrawingPanel::dummyBoard;

DrawingPanel::DrawingPanel(wxWindow* parent) : wxPanel(parent), m_gridSize(15), gameBoard(dummyBoard) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    // Initialize gameBoard here or pass it as a parameter
}

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board)
    : wxPanel(parent), m_gridSize(15), gameBoard(board) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event) {
    // Get mouse coordinates
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    // Calculate cell width and height
    int panelWidth, panelHeight;
    GetSize(&panelWidth, &panelHeight);
    int cellWidth = panelWidth / gameBoard.size();
    int cellHeight = panelHeight / gameBoard.size();

    // Calculate row and column of the clicked cell
    int row = mouseY / cellHeight;
    int col = mouseX / cellWidth;

    // Update game board cell state
    if (row >= 0 && row < static_cast<int>(gameBoard.size()) && col >= 0 && col < static_cast<int>(gameBoard[row].size())) {
        gameBoard[row][col] = !gameBoard[row][col]; // Toggle the cell state
        Refresh(); // Trigger a repaint to update the display
    }
}

void DrawingPanel::SetSize(wxSize& size) {
    wxPanel::SetSize(size);
    Refresh();
}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (!gc) {
        return;
    }

    // Calculate cell width and height
    int panelWidth, panelHeight;
    GetSize(&panelWidth, &panelHeight);
    int cellWidth = panelWidth / gameBoard.size();
    int cellHeight = panelHeight / gameBoard.size();

    // Draw the grid and cells
    for (size_t i = 0; i < gameBoard.size(); ++i) {
        for (size_t j = 0; j < gameBoard[i].size(); ++j) {
            int x = j * cellWidth;
            int y = i * cellHeight;

            // Set brush color based on cell status
            if (gameBoard[i][j]) {
                gc->SetBrush(*wxLIGHT_GREY_BRUSH); // Living cell
            }
            else {
                gc->SetBrush(*wxWHITE_BRUSH); // Dead cell
            }

            // Draw cell rectangle
            gc->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }

    delete gc;
}

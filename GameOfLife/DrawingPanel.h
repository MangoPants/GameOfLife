#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <wx/wx.h>
#include <vector>
#include "Settings.h"

class DrawingPanel : public wxPanel {
private:
    Settings* settingsPtr;
    int m_gridSize; // Corrected member variable name
    std::vector<std::vector<bool>>& gameBoard; // Reference to the game board
    static std::vector<std::vector<bool>> dummyBoard;  // Define a dummy board to initialize the gameBoard reference

public:
    DrawingPanel(wxWindow* parent, Settings* settings) : wxPanel(parent), settingsPtr(settings) {}

    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board); // Constructor

    DrawingPanel(wxWindow* parent);

    void OnMouseUp(wxMouseEvent& event); // Mouse event handler

    void SetSize(wxSize& size); // Method for setting size

    void OnPaint(wxPaintEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H

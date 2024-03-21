// Settings.h
#ifndef SETTINGS_H
#define SETTINGS_H

#include <wx/wx.h>

struct Settings {
    unsigned int livingRed = 128;
    unsigned int livingGreen = 128;
    unsigned int livingBlue = 128;
    unsigned int livingAlpha = 255;

    unsigned int deadRed = 255;
    unsigned int deadGreen = 255;
    unsigned int deadBlue = 255;
    unsigned int deadAlpha = 255;

    int gridSize = 15;
    int interval = 50;

    wxColor GetLivingCellColor() const {
        return wxColor(livingRed, livingGreen, livingBlue, livingAlpha);
    }

    wxColor GetDeadCellColor() const {
        return wxColor(deadRed, deadGreen, deadBlue, deadAlpha);
    }

    void SetLivingCellColor(const wxColor& color) {
        color.GetRGBA(&livingRed, &livingGreen, &livingBlue, &livingAlpha);
    }

    void SetDeadCellColor(const wxColor& color) {
        color.GetRGBA(&deadRed, &deadGreen, &deadBlue, &deadAlpha);
    }
};

#endif // SETTINGS_H

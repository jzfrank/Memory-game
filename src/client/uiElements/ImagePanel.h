//
// Created by Jin on 5/10/22.
//

#ifndef MEMORY_GAME_IMAGEPANEL_H
#define MEMORY_GAME_IMAGEPANEL_H

#include <wx/wx.h>
#include <wx/sizer.h>

class ImagePanel : public wxPanel {
    wxImage _image;
    wxBitmap _bitmap;

    double _rotation;

    int _width;
    int _height;

public:
    ImagePanel(wxWindow* parent, wxString file, wxBitmapType format,
               wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize, double rotation=0.0);

    void paintEvent(wxPaintEvent& event);
    void onSize(wxSizeEvent& event);

};


#endif //MEMORY_GAME_IMAGEPANEL_H

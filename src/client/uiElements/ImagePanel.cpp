//
// Created by Jin on 5/10/22.
//

#include "ImagePanel.h"
#include <wx/filefn.h>

ImagePanel::ImagePanel(wxWindow *parent, wxString file, wxBitmapType format,
                       wxPoint position, wxSize size, double rotation)
: wxPanel(parent, wxID_ANY, position, size)
{
    if (!wxFileExists(file)) {
        wxMessageBox("Could not find file: " + file, "File error", wxICON_ERROR);
        return;
    }

    if (!this->_image.LoadFile(file, format)) {
        wxMessageBox("Could not load file: " + file, "File error", wxICON_ERROR);
        return;
    }

    this->_rotation = rotation;

    this->_width = -1;
    this->_height = -1;

    this->Bind(wxEVT_PAINT, &ImagePanel::paintEvent, this);
}

void ImagePanel::paintEvent(wxPaintEvent &event) {
    // this code is called when the system requests this panel to be redrawn

    if (!this->_image.IsOk()) {
        return;
    }

    wxPaintDC deviceContext = wxPaintDC(this);

    int newWidth;
    int newHeight;
    deviceContext.GetSize(&newWidth, &newHeight);

    if (newWidth != this->_width || newHeight != this->_height) {
        wxImage transformed;

//        std::cout << "old width, height: " << this->_width << ", " << this->_height << std::endl;
//        std::cout << "new width, height: " << newWidth << ", " << newHeight << std::endl;

        if (this->_rotation == 0.0) {
            transformed = this->_image.Scale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH);
        } else {
            wxPoint centerOfRotation = wxPoint(this->_image.GetWidth() / 2, this->_image.GetHeight() / 2);
            transformed = this->_image.Rotate(this->_rotation, centerOfRotation, true);
            transformed = transformed.Scale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH);
        }
        this->_bitmap = wxBitmap(transformed);
        this->_width = transformed.GetWidth();
        this->_height = transformed.GetHeight();

        deviceContext.DrawBitmap(this->_bitmap, 0, 0, false);
    } else {
//        std::cout << "old w,h equal new w,h" << std::endl;
        deviceContext.DrawBitmap(this->_bitmap, 0, 0, false);
    }

}

void ImagePanel::onSize(wxSizeEvent &event) {

    // when the user resizes this panel, the image should redraw itself
    Refresh();

    // skip any other effects of this event
    event.Skip();
}
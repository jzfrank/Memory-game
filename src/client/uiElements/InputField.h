//
// Created by Jin on 5/10/22.
//

#ifndef MEMORY_GAME_INPUTFIELD_H
#define MEMORY_GAME_INPUTFIELD_H
#include <wx/wx.h>

class InputField : public wxPanel {
public:
    InputField(wxWindow* parent, const wxString& labelText, int labelWidth,
               const wxString& fieldValue, int fieldWidth);
//    wxString getValue();

private:
    wxStaticText* _label;
    wxTextCtrl* _field;
};

#endif //MEMORY_GAME_INPUTFIELD_H

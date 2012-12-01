//==========================================================================
// Name:            dlg_comports.cpp
// Purpose:         Creates simple wxWidgets dialog GUI to select
//                  real/virtual Comm ports.
// Date:            May 11 2012
// Authors:         David Rowe, David Witten
// 
// License:
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.1,
//  as published by the Free Software Foundation.  This program is
//  distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
//  License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, see <http://www.gnu.org/licenses/>.
//
//==========================================================================
#include "dlg_comports.h"
#include "fdmdv2_main.h"

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=
// Class ComPortsDlg
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=
ComPortsDlg::ComPortsDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
/*
    if(!bBitmapLoaded) 
    {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }
*/
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mainSizer);
    
/*    
    wxStaticBoxSizer* staticBoxSizer28 = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _("Audio Tone")), wxVERTICAL);
    mainSizer->Add(staticBoxSizer28, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    m_ckPTTRtChan = new wxCheckBox(this, wxID_ANY, _("PTT tone on right audio channel"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_ckPTTRtChan->SetValue(false);
    staticBoxSizer28->Add(m_ckPTTRtChan, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5);
*/

    wxStaticBoxSizer* staticBoxSizer17 = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _("Hardware PTT Settings")), wxVERTICAL);
    mainSizer->Add(staticBoxSizer17, 1, wxEXPAND, 5);
    wxStaticBoxSizer* staticBoxSizer31 = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _("PTT Port")), wxVERTICAL);
    staticBoxSizer17->Add(staticBoxSizer31, 1, wxEXPAND, 5);

    m_ckUseSerialPTT = new wxCheckBox(this, wxID_ANY, _("Use Serial Port PTT"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_ckUseSerialPTT->SetValue(false);
    staticBoxSizer31->Add(m_ckUseSerialPTT, 0, wxALIGN_LEFT, 20);

    wxArrayString m_listCtrlPortsArr;
    m_listCtrlPorts = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(-1,45), m_listCtrlPortsArr, wxLB_SINGLE);
    staticBoxSizer31->Add(m_listCtrlPorts, 1, wxALIGN_CENTER, 0);

    wxBoxSizer* boxSizer19 = new wxBoxSizer(wxVERTICAL);
    staticBoxSizer17->Add(boxSizer19, 1, wxEXPAND, 5);
    wxStaticBoxSizer* staticBoxSizer16 = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _("Signal polarity")), wxHORIZONTAL);
    boxSizer19->Add(staticBoxSizer16, 1, wxEXPAND|wxALIGN_CENTER|wxALIGN_RIGHT, 5);

    wxGridSizer* gridSizer17 = new wxGridSizer(2, 2, 0, 0);
    staticBoxSizer16->Add(gridSizer17, 1, wxEXPAND|wxALIGN_RIGHT, 5);

/*
    m_ckUseSerialPTT = new wxCheckBox(this, wxID_ANY, _("Use Serial Port PTT"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_ckUseSerialPTT->SetValue(false);
    gridSizer17->Add(m_ckUseSerialPTT, 0, wxALIGN_CENTER, 10);
    gridSizer17->Add(0, 0, 0, 0, 5);
*/
    m_rbUseDTR = new wxRadioButton(this, wxID_ANY, _("Use DTR"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_rbUseDTR->SetToolTip(_("Toggle DTR line for PTT"));
    m_rbUseDTR->SetValue(1);
    gridSizer17->Add(m_rbUseDTR, 0, wxALIGN_CENTER|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);

    m_ckDTRPos = new wxCheckBox(this, wxID_ANY, _("DTR = +V"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_ckDTRPos->SetToolTip(_("Set Polarity of the DTR line"));
    m_ckDTRPos->SetValue(false);
    gridSizer17->Add(m_ckDTRPos, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 5);

    m_rbUseRTS = new wxRadioButton(this, wxID_ANY, _("Use RTS"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_rbUseRTS->SetToolTip(_("Toggle the RTS pin for PTT"));
    m_rbUseRTS->SetValue(1);
    gridSizer17->Add(m_rbUseRTS, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 5);

    m_ckRTSPos = new wxCheckBox(this, wxID_ANY, _("RTS = +V"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_ckRTSPos->SetValue(false);
    m_ckRTSPos->SetToolTip(_("Set Polarity of the RTS line"));
    gridSizer17->Add(m_ckRTSPos, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 5);

    wxBoxSizer* boxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(boxSizer12, 0, wxLEFT|wxRIGHT|wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);

    m_buttonOK = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_buttonOK->SetDefault();

    boxSizer12->Add(m_buttonOK, 0, wxLEFT|wxRIGHT|wxTOP|wxBOTTOM, 5);
    m_buttonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxSize(-1,-1), 0);
    boxSizer12->Add(m_buttonCancel, 0, wxLEFT|wxRIGHT|wxTOP|wxBOTTOM, 5);

    m_buttonApply = new wxButton(this, wxID_APPLY, _("Apply"), wxDefaultPosition, wxSize(-1,-1), 0);
    boxSizer12->Add(m_buttonApply, 0, wxLEFT|wxRIGHT|wxTOP|wxBOTTOM, 5);

    SetSizeHints(450,300);
    if ( GetSizer() ) 
    {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);

    // Connect events
    this->Connect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(ComPortsDlg::OnInitDialog), NULL, this);
//    m_ckPTTRtChan->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ComPortsDlg::PTTAudioClick), NULL, this);
//    m_listCtrlPorts->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(ComPortsDlg::PTTPortSlelcted), NULL, this);
    m_ckUseSerialPTT->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ComPortsDlg::PTTUseSerialClicked), NULL, this);
    m_rbUseDTR->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ComPortsDlg::UseDTRCliched), NULL, this);
    m_ckRTSPos->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ComPortsDlg::DTRVPlusClicked), NULL, this);
    m_rbUseRTS->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ComPortsDlg::UseRTSClicked), NULL, this);
    m_ckDTRPos->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ComPortsDlg::RTSVPlusClicked), NULL, this);
    m_buttonOK->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ComPortsDlg::OnOK), NULL, this);
    m_buttonCancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ComPortsDlg::OnCancel), NULL, this);
    m_buttonApply->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ComPortsDlg::OnApply), NULL, this);
}

//-------------------------------------------------------------------------
// ~ComPortsDlg()
//-------------------------------------------------------------------------
ComPortsDlg::~ComPortsDlg()
{
    // Disconnect Events
    this->Disconnect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(ComPortsDlg::OnInitDialog), NULL, this);
//    m_ckPTTRtChan->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ComPortsDlg::PTTAudioClick), NULL, this);
//    m_listCtrlPorts->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(ComPortsDlg::PTTPortSlelcted), NULL, this);
    m_ckUseSerialPTT->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ComPortsDlg::PTTUseSerialClicked), NULL, this);
    m_rbUseDTR->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ComPortsDlg::UseDTRCliched), NULL, this);
    m_ckRTSPos->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ComPortsDlg::DTRVPlusClicked), NULL, this);
    m_rbUseRTS->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ComPortsDlg::UseRTSClicked), NULL, this);
    m_ckDTRPos->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ComPortsDlg::RTSVPlusClicked), NULL, this);
    m_buttonOK->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ComPortsDlg::OnOK), NULL, this);
    m_buttonCancel->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ComPortsDlg::OnCancel), NULL, this);
    m_buttonApply->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ComPortsDlg::OnApply), NULL, this);
}

//-------------------------------------------------------------------------
// OnInitDialog()
//-------------------------------------------------------------------------
void ComPortsDlg::OnInitDialog(wxInitDialogEvent& event)
{
    populatePortList();
    ExchangeData(EXCHANGE_DATA_IN);
}

//-------------------------------------------------------------------------
// populatePortList()
//-------------------------------------------------------------------------
void ComPortsDlg::populatePortList()
{
    int i = 0;
    wxListItem inf;
    wxString buf;
    
    m_listCtrlPorts->Clear();
    std::vector<std::string>result;
    wxArrayString aStr;

    ctb::GetAvailablePorts(result, false);
    for(int i = 0; i < result.size(); i++) 
    {
        aStr.Add(result[i], 1);
    }
    m_listCtrlPorts->Append(aStr);
}

//-------------------------------------------------------------------------
// ExchangeData()
//-------------------------------------------------------------------------
void ComPortsDlg::ExchangeData(int inout)
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    wxString str;
    long l;
    int i;
    
    if(inout == EXCHANGE_DATA_IN)
    {
//        m_ckUsePTTRtChan->SetValue(wxGetApp().m_boolUseTonePTT);
        m_ckUseSerialPTT->SetValue(wxGetApp().m_boolUseSerialPTT);
        str = wxGetApp().m_strRigCtrlPort;
        m_listCtrlPorts->SetStringSelection(str);
        str = wxGetApp().m_strRigCtrlBaud;

//        m_listCtrlBaudrates->SetStringSelection(str);
//        m_textRigCtrlDatabits->SetValue(wxGetApp().m_strRigCtrlDatabits);
//        m_textRigCtrlStopbits->SetValue(wxGetApp().m_strRigCtrlStopbits);
//        m_textRigCtrlParity->SetValue(wxGetApp().m_strRigCtrlParity);

        m_rbUseRTS->SetValue(wxGetApp().m_boolUseRTS);
        m_ckRTSPos->SetValue(wxGetApp().m_boolRTSPos);
        m_rbUseDTR->SetValue(wxGetApp().m_boolUseDTR);
        m_ckDTRPos->SetValue(wxGetApp().m_boolDTRPos);
    }
    if(inout == EXCHANGE_DATA_OUT)
    {
        wxGetApp().m_boolUseSerialPTT           = m_ckUseSerialPTT->IsChecked();
//        wxGetApp().m_boolUseTonePTT             = m_ckUsePTTRtChan->IsChecked();
        wxGetApp().m_strRigCtrlPort             = m_listCtrlPorts->GetStringSelection();
        wxGetApp().m_boolUseRTS                 = m_rbUseRTS->GetValue();
        wxGetApp().m_boolRTSPos                 = m_ckRTSPos->IsChecked();
        wxGetApp().m_boolUseDTR                 = m_rbUseDTR->GetValue();
        wxGetApp().m_boolDTRPos                 = m_ckDTRPos->IsChecked();
        
        pConfig->Write(wxT("/Rig/UseRTS"),          wxGetApp().m_boolUseRTS);
        pConfig->Write(wxT("/Rig/RTSPolarity"),     wxGetApp().m_boolRTSPos);
        pConfig->Write(wxT("/Rig/UseDTR"),          wxGetApp().m_boolUseDTR);
        pConfig->Write(wxT("/Rig/DTRPolarity"),     wxGetApp().m_boolDTRPos);
        pConfig->Write(wxT("/Rig/UseTonePTT"),      wxGetApp().m_boolUseTonePTT);
        pConfig->Write(wxT("/Rig/UseSerialPTT"),    wxGetApp().m_boolUseSerialPTT);

//        wxGetApp().m_strRigCtrlBaud             = m_listCtrlBaudrates->GetStringSelection();
//        wxGetApp().m_strRigCtrlDatabits         = m_textRigCtrlDatabits->GetValue();
//        wxGetApp().m_strRigCtrlStopbits         = m_textRigCtrlStopbits->GetValue();
//        wxGetApp().m_strRigCtrlParity           = m_textRigCtrlParity->GetValue();

//        pConfig->Write(wxT("/Rig/Port"),        wxGetApp().m_strRigCtrlPort);
//        pConfig->Write(wxT("/Rig/Baud"),        wxGetApp().m_strRigCtrlBaud);
//        pConfig->Write(wxT("/Rig/DataBits"),    wxGetApp().m_strRigCtrlDatabits);
//        pConfig->Write(wxT("/Rig/StopBits"),    wxGetApp().m_strRigCtrlStopbits);
//        pConfig->Write(wxT("/Rig/Parity"),      wxGetApp().m_strRigCtrlParity);
        //m_textRigCtrlFlowControl
        pConfig->Flush();
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

//-------------------------------------------------------------------------
// DTRVPlusClicked()
//-------------------------------------------------------------------------
void ComPortsDlg::DTRVPlusClicked(wxCommandEvent& event)
{
    //wxMessageBox(wxT("DTRVPlusClicked"));
}

//-------------------------------------------------------------------------
// PTTAudioClick()
//-------------------------------------------------------------------------
void ComPortsDlg::PTTAudioClick(wxCommandEvent& event)
{
}

//-------------------------------------------------------------------------
// PTTUseSerialClicked()
//-------------------------------------------------------------------------
void ComPortsDlg::PTTUseSerialClicked(wxCommandEvent& event)
{
}

//-------------------------------------------------------------------------
// RTSVPlusClicked()
//-------------------------------------------------------------------------
void ComPortsDlg::RTSVPlusClicked(wxCommandEvent& event)
{
}

//-------------------------------------------------------------------------
// OnCancel()
//-------------------------------------------------------------------------
void ComPortsDlg::UseDTRCliched(wxCommandEvent& event)
{
}

//-------------------------------------------------------------------------
// UseRTSClicked()
//-------------------------------------------------------------------------
void ComPortsDlg::UseRTSClicked(wxCommandEvent& event)
{
}

//-------------------------------------------------------------------------
// OnApply()
//-------------------------------------------------------------------------
void ComPortsDlg::OnApply(wxCommandEvent& event)
{
    ExchangeData(EXCHANGE_DATA_OUT);
}

//-------------------------------------------------------------------------
// OnCancel()
//-------------------------------------------------------------------------
void ComPortsDlg::OnCancel(wxCommandEvent& event)
{
    this->EndModal(wxID_CANCEL);
}

//-------------------------------------------------------------------------
// OnClose()
//-------------------------------------------------------------------------
void ComPortsDlg::OnOK(wxCommandEvent& event)
{
    ExchangeData(EXCHANGE_DATA_OUT);
    this->EndModal(wxID_OK);
}


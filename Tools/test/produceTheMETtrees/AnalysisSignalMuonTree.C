#define AnalysisTTbar_cxx
#include "AnalysisTTbar.h"
#include "MuonPogTree.h"


//==============================================================================
//
// Data members
//
//==============================================================================

float               luminosity;
Float_t             event_weight;

TFile*              root_output;
TString             filename;


//------------------------------------------------------------------------------
// Loop
//------------------------------------------------------------------------------
void AnalysisSignalMuonTree::Loop(TString sample)
{

  TH1::SetDefaultSumw2();

  luminosity = 1.0;  // fb-1 luminosity to be used 
  filename   = sample;

  gSystem->mkdir("rootfiles", kTRUE);
  //gSystem->mkdir("txt",       kTRUE);

  root_output = new TFile("rootfiles/" + filename + ".root", "recreate");

 
  // Add new branches to the root file. 
  //----------------------------------------------------------------------------


  // Loop over events
  //----------------------------------------------------------------------------

if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    
    if (ientry < 0) break;
    
    fChain->GetEntry(jentry);



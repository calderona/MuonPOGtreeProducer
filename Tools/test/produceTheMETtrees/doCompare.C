#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TTree.h"


const UInt_t nProcesses = 2;

enum {iA, iB};


TFile* input[nProcesses];

TString process[nProcesses];
Color_t color[nProcesses];




void doCompare() {

process[iA]  = "allplotsNewMiniAod_RunE_03Feb";
process[iB]  = "allplotsNewMiniAod_RunE_23Sep";

color[iA]  = kRed+1;
color[iB]  = kAzure-5;

// LOADING MACROS. 
  //gROOT->LoadMacro("../utils/TResultsTable.C+");
  //gInterpreter->LoadMacro   ("../utils/draw.C+");
  //gInterpreter->LoadMacro   ("../utils/utils.C+"); 
  //gInterpreter->ExecuteMacro("../utils/ChargeRatioStyle.C");
  gStyle      ->SetOptStat  (0);
  gStyle      ->SetPalette  (1);


//------------------------------------------------------------------------------
// Files and variables
//------------------------------------------------------------------------------


TString path = "plotfiles/";
  
  for (UInt_t ip=0; ip<nProcesses; ip++) 
    input[ip] = new TFile(path + process[ip] + ".root", "read");

 
  TH1F* hist_allmuons_dR[nProcesses];
  TH1F* hist_allmuons_eta[nProcesses];
  TH1F* hist_allmuons_pt[nProcesses];
  TH1F* hist_allmuons_chi2[nProcesses];

 
  for (UInt_t ip=0; ip<nProcesses; ip++) {

      hist_allmuons_dR[ip] = (TH1F*)input[ip]->Get("allMuonsdRclosest");
      hist_allmuons_eta[ip] = (TH1F*)input[ip]->Get("allMuonsEta");
      hist_allmuons_pt[ip] = (TH1F*)input[ip]->Get("allMuonsPt");
      hist_allmuons_chi2[ip] = (TH1F*)input[ip]->Get("allMuonsChi2");

  }

 TCanvas * all_muons = new TCanvas("all_muons", "all_muons", 750, 750);
 
 all_muons->cd();

 hist_allmuons_eta[iA]->SetLineColor(kRed);
 hist_allmuons_eta[iB]->SetLineColor(color[iB]);
 hist_allmuons_eta[iB]->Draw();
 hist_allmuons_eta[iA]->Draw("same");


}

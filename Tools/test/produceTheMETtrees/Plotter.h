#pragma once

#ifndef Plotter_h
#define Plotter_h

#include "TCanvas.h"
#include "TFile.h"
#include "TString.h"
#include "THStack.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TTree.h"

#include <string>
#include <memory>
#include <vector>

/**
 * \class Plotter
 * \brief Plots data and MC expectations using histograms produced 
 * Simulated processes are drawn in a stacked plot. The data histogram is optional.
 */
class Plotter
{
 public:
  /**
   * \brief Constructor
   * 
   * Takes as the argument the name of a directory with the  ROOT files. 
   */
  
 Plotter(std::string const &srcDirName);

 ~Plotter() {}    
/**
 * \brief Adds an MC files
 * 
 * The name is used to get the files from the source directory. The legend label is put into the
 * legend. Each call to this method adds a new MC histogram to the list.
 */
 
 public: 

 void AddDataHist(TString const &name, TString const &legendLabel);

 void AddMCHist(TString const &name, Color_t colour, TString const &legendLabel);

 void Plot(TString const &variable, TString const &axiLabel, bool residuals = false, bool setLogy = false, bool isStack = false);

 TLegend* DrawLegend(Float_t x1, Float_t y1, TH1*    hist, TString label, TString option, Float_t tsize, Float_t xoffset, Float_t yoffset);

 void DrawTLatex(Double_t x, Double_t y, Double_t tsize, const char* text);
 
 void Pad2TAxis(TH1* hist, TString xtitle, TString ytitle);


 private:
    /// Directory with the ROOT files that contains histograms to be plotted
    TString srcDir;
    
    /// Files fostd::vector<TString>  legend;r pseudo-data 
    TFile *dataFile; 
    TString  legend_data;

    /// Files for simulation
    std::vector<TFile *>  mcFiles;
    std::vector<TString>  process;
    std::vector<Color_t>  color;
    std::vector<TString>  legend;

    /// Histogram for pseudo-data
    TH1* dataHist;
    
    /// Histograms for simulation
    std::vector<TH1 *> mcHists;
    
   
    /// Indicates if the data/MC residuals should be plotted
    bool plotResiduals;

    // Indicates more options in the function. 
    Bool_t   savePlots;
    Bool_t   setLogy;

};

#endif

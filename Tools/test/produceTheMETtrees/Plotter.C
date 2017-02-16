#include "Plotter.h"

#include "THStack.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TSystem.h"
#include "TTree.h"
#include "math.h"

#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;

const int ncut = 1;

enum {
  allMuons
};

const TString scut[ncut] = {
  "allMuons"
};


//------------------------------------------------------------------------------
// Plotter
//------------------------------------------------------------------------------

Plotter::Plotter(string const &srcDirName):
  srcDir(srcDirName),
  plotResiduals(false),
  setLogy(false)
{}


void Plotter::AddDataHist(TString const &name,  TString const &legendLabel)
{
  
  dataFile  =  new TFile( srcDir + name + ".root", "read"); 
  
  cout << "File \"" << name << "with colour: " << kBlack << endl;
   
  legend_data = legendLabel;

}

void Plotter::AddMCHist(TString const &name, Color_t colour, TString const &legendLabel)
{
  
  TFile *file =  new TFile( srcDir + name + ".root", "read");

  // Add the file to the collection of simulated processes

  mcFiles.push_back(file);
  process.push_back(name);
  color.push_back(colour);
  legend.push_back(legendLabel);
  
  cout << "File \"" << name << "with colour: " << colour << endl;
   

}

void Plotter::Plot(TString const &variable, TString const &axiLabel, bool residuals, bool setLogy, bool isStack)
{


  // Global decoration settings
    gStyle->SetErrorX(0.);
    gStyle->SetHistMinimumZero(kTRUE);
    gStyle->SetOptStat(0);
    gStyle->SetStripDecimals(kFALSE);
    TGaxis::SetMaxDigits(3);
    
    plotResiduals = residuals;

    if (mcFiles.size() == 0)
      throw runtime_error("No MC histograms have beed provided.");

    int nCuts = sizeof(scut) / sizeof(TString); 
  
    for ( int iscut = 0; iscut < nCuts; iscut++) { 

      mcHists.clear();
    
      TString title = Form(scut[iscut] + variable); 
  
      TCanvas* canvas;
      
      TPad* pad1;
      
      TPad* pad2;

      if (plotResiduals) {

	canvas = new TCanvas(title, title, 550, 1.2*600);

	pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1);
	pad1->SetTopMargin   (0.05);
	pad1->SetBottomMargin(0.02);
	pad1->Draw();
	
	pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3); 
	pad2->SetTopMargin   (0.08);
	pad2->SetBottomMargin(0.35);
	pad2->Draw();
      }
      else {
	canvas = new TCanvas(title, title, 550, 600);
	pad1 = (TPad*)canvas->GetPad(0);
      }
      
      canvas->Draw(); canvas->Update();
  

    //----------------------------------------------------------------------------
    // pad1
    //----------------------------------------------------------------------------
    pad1->cd();
    
    pad1->SetLogy(setLogy);
    
    
    // First work with data 
    dataHist = (TH1F*)dataFile->Get(title);
    dataHist->SetMarkerStyle(kFullCircle);
    dataHist->SetMarkerSize(0.5);
    dataHist->SetTitle(title);
    
    // Second work with all the Monte Carlos 
    
    
    THStack*  hstack = new THStack(title, title);
    
    int nProcesses = mcFiles.size();
    
    for (UInt_t ip=0; ip<nProcesses; ip++) {

      TH1F *hist = (TH1F*)mcFiles[ip]->Get(title);
      
      mcHists.push_back(hist);
      
      hist->SetName(title + "_" + process[ip]);
      
      //hist->SetFillColor(color[ip]);
      hist->SetFillStyle(1001);
      hist->SetLineColor(color[ip]);
      
      if (isStack)  hstack->Add(hist);

    }


    // Axis labels
    //----------------------------------------------------------------------------
    TAxis* xaxis = dataHist->GetXaxis();
    TAxis* yaxis = dataHist->GetYaxis();
    
    TString ytitle = Form("entries / %s.%df", "%", 1);
    
    xaxis->SetTitle(axiLabel);
    yaxis->SetTitle(Form(ytitle.Data(), dataHist->GetBinWidth(0)));
    yaxis->SetTitleOffset(1.6);
    
  

    // Draw
    //----------------------------------------------------------------------------
    //xaxis->SetRangeUser(xmin, xmax);
    
    dataHist->Draw("ep");

    if (isStack) {
      hstack     ->Draw("hist,same");
    } else {
      for (UInt_t ip=0; ip<nProcesses; ip++) {	
	mcHists[ip]->Draw("hist,same");
      }
    }


    dataHist->Draw("ep,same");
    

    // Legend
    //----------------------------------------------------------------------------
    Double_t yoffset = (plotResiduals) ? 0.054 : 0.048;
    Double_t x0      = (plotResiduals) ? 0.170 : 0.200; 
   
    
    DrawLegend(x0, 0.74 + 2.*(yoffset+0.001), dataHist, legend_data,    "lp", 0.035, 0.2, yoffset);
    
    for (UInt_t ip=0; ip<nProcesses; ip++) {
      
      int off = -ip+1;
      
      DrawLegend(x0, 0.74 + off *(yoffset+0.001), mcHists[ip],  legend[ip],  "f",  0.035, 0.2, yoffset);
      
    }


    // All MC
    //----------------------------------------------------------------------------
    TH1F* allmc = (TH1F*)dataHist->Clone("allmc");

    allmc->SetFillColor  (kGray+2);
    allmc->SetFillStyle  (   3345);
    allmc->SetLineColor  (kGray+2);
    allmc->SetMarkerColor(kGray+2);
    allmc->SetMarkerSize (      0);
    
    for (UInt_t ibin=1; ibin<=allmc->GetNbinsX(); ibin++) {

      Double_t binValue = 0;
      Double_t binError = 0;

      for (UInt_t ip=0; ip<nProcesses; ip++) {

	Double_t binContent = mcHists[ip]->GetBinContent(ibin);
      
	binValue += binContent;
	binError += (mcHists[ip]->GetBinError(ibin) * mcHists[ip]->GetBinError(ibin));

	binError = sqrt(binError);

	allmc->SetBinContent(ibin, binValue);
	allmc->SetBinError  (ibin, binError);
      }

    }
  
    /*
    //----------------------------------------------------------------------------
    // pad2
    //----------------------------------------------------------------------------
    if (plotResiduals) {
      
      pad2->cd();
      
      TH1F* ratio       = (TH1F*) dataHist->Clone("ratio");
      TH1F* uncertainty = (TH1F*) allmc->Clone("uncertainty");

      for (UInt_t ibin=1; ibin<=ratio->GetNbinsX(); ibin++) {

	Double_t mcValue = allmc->GetBinContent(ibin);
	Double_t mcError = allmc->GetBinError  (ibin);

	Double_t dtValue = ratio->GetBinContent(ibin);
	Double_t dtError = ratio->GetBinError  (ibin);

	Double_t ratioValue       = (mcValue > 0) ? dtValue/mcValue : 0.0;
	Double_t ratioError       = (mcValue > 0) ? dtError/mcValue : 0.0;
	Double_t uncertaintyError = (mcValue > 0) ? mcError/mcValue : 0.0;

	ratio->SetBinContent(ibin, ratioValue);
	ratio->SetBinError  (ibin, ratioError);

	uncertainty->SetBinContent(ibin, 1.0);
	uncertainty->SetBinError  (ibin, uncertaintyError);
      }
    
      uncertainty->Draw("e2");
      ratio      ->Draw("ep,same");

      uncertainty->GetYaxis()->SetRangeUser(0.4, 1.6);

      Pad2TAxis(uncertainty, dataHist->GetXaxis()->GetTitle(), "data / prediction");

    }
    */

    //Save the histogram.
    //---------------------------------------------------------------------------  
    canvas->Modified(); 

    canvas->Update();
    
    TString outname = Form("plots/"+ title + ".png"); 
    canvas->SaveAs(outname);

    //canvas->Print();
    
  }

}


TLegend* Plotter::DrawLegend(Float_t x1, Float_t y1, TH1*    hist, TString label, TString option, Float_t tsize, Float_t xoffset, Float_t yoffset)
{
 
 TLegend* legend = new TLegend(x1,y1,x1 + xoffset,y1 + yoffset);
  
 legend->SetBorderSize(    0);
 legend->SetFillColor (    0);
 legend->SetTextAlign (   12);
 legend->SetTextFont  (   42);
 legend->SetTextSize  (tsize);

 legend->AddEntry(hist, label.Data(), option.Data());
 legend->Draw();

 return legend;
}


void Plotter::DrawTLatex(Double_t x, Double_t y, Double_t tsize, const char* text)
{
  TLatex* tl = new TLatex(x, y, text);

  tl->SetNDC();
  tl->SetTextAlign(   32);
  tl->SetTextFont (   42);
  tl->SetTextSize (tsize);

  tl->Draw("same");
}



void Plotter::Pad2TAxis(TH1* hist, TString xtitle, TString ytitle)
{
  TAxis* xaxis = (TAxis*)hist->GetXaxis();
  TAxis* yaxis = (TAxis*)hist->GetYaxis();

  xaxis->SetLabelFont  (    42);
  xaxis->SetLabelOffset( 0.025);
  xaxis->SetLabelSize  (   0.1);
  xaxis->SetNdivisions (   505);
  xaxis->SetTitle      (xtitle);
  xaxis->SetTitleFont  (    42);
  xaxis->SetTitleOffset(  1.35);
  xaxis->SetTitleSize  (  0.11);
  
  yaxis->CenterTitle   (      );
  yaxis->SetLabelFont  (    42);
  yaxis->SetLabelOffset(  0.02);
  yaxis->SetLabelSize  (   0.1);
  yaxis->SetNdivisions (   505);
  yaxis->SetTitle      (ytitle);
  yaxis->SetTitleFont  (    42);
  yaxis->SetTitleOffset(  0.75);
  yaxis->SetTitleSize  (  0.11);
}

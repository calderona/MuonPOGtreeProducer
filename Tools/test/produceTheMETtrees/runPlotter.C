#include "Plotter.h"

# ifndef __CINT__
int main()
{
    // Create a plotter
    Plotter plotter("plotfiles/");
    
    // Specify the data histogram, along with a label to be used in the legend
    plotter.AddDataHist("allplotsNewMiniAod_RunE_03Feb", "03Feb");
    
    // Specify MC histograms, along with their colours and legend labels
    plotter.AddMCHist("allplotsNewMiniAod_RunE_23Sep", kRed + 1, "23Sep");
 
    // Produce files with pictures
    /*plotter.Plot("dRclosest", "dR");
    plotter.Plot("Pt", "Pt", 0, 1, 0);
    plotter.Plot("Eta", "Eta");
    plotter.Plot("dxy", "dxy", 0, 1, 0);
    plotter.Plot("dz", "dz", 0, 1, 0);
    plotter.Plot("Chi2", "Chi2", 0, 1, 0);
    plotter.Plot("StaChi2", "StaChi2");
    plotter.Plot("TrkChi2", "TrkChi2");
    plotter.Plot("trkRatio", "trkRatio");
    plotter.Plot("SegComp", "SegComp");
    plotter.Plot("finalAlgo", "finalAlgo");
    plotter.Plot("initialAlgo", "initialAlgo");
    plotter.Plot("isTight", "isTight");
    plotter.Plot("isMedium", "isMedium");
    plotter.Plot("isTrackerTightMuon", "isTrackerTightMuon");
    plotter.Plot("isIsolatedMuon", "isIsolatedMuon");
    plotter.Plot("IsGlobalORTracker", "IsGlobalORTracker");
    plotter.Plot("isTrkMuOST", "isTrkMuOST");
    plotter.Plot("isTrkHP", "isTrkHP");
    plotter.Plot("trkValidHitFrac", "trkValidHitFrac");
    plotter.Plot("isGoodPFmuon", "isGoodPFmuon");
    plotter.Plot("isGoodPFmuonWithClones", "isGoodPFmuonWithClones");
    plotter.Plot("isGoodPFmuonCloseBy", "isGoodPFmuonCloseBy");
    plotter.Plot("isGoodPFmuonSharingSeg", "isGoodPFmuonSharingSeg");
    plotter.Plot("isClosestMuon", "isClosestMuon");*/
    plotter.Plot("matchesStations","matchesStations");

    return 0;
}
# endif

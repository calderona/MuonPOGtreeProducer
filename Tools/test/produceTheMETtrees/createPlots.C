TChain *chain, *chainBad;
TFile *outputFile;

void doAPlot(TChain *theChain, TString tag, TString namePlot, TString theVar, TString cut,  int nBins, float lowerBin, float higherBin){
  cout << "hello ! doing the plot " << tag << " " << namePlot << endl;
  TH1F *histo = new TH1F(tag+namePlot, "", nBins, lowerBin, higherBin);
  theChain->Draw(theVar+">>"+tag+namePlot, cut);
  outputFile->cd();
  histo->Write();
  delete histo;
}


void createPlots(){
  outputFile = new TFile("plotfiles/allplotsNewMiniAod_RunE_23Sep.root", "RECREATE");
  chain = new TChain("probeMuons");
  //chain->Add("/tmp/hbrun/muonTreeFile_*.root");
  chain->Add("rootfiles/probeMuonTree_RunE_23Sep.root");
  chainBad = new TChain("badMuons");
  chainBad->Add("rootfiles/probeMuonTree_RunE_23Sep.root");

  TString typeRECO = "03FebMiniAOD";

  TString tag = "allMuons";
//typeRECO+"allMuons";
  TString theCut = "invMassWithTag>80&&invMassWithTag<100&&isPF==1";
  doAPlot(chain, tag, "Pt", "aProbeMuon.pt", theCut, 100, 0, 500);
  doAPlot(chain, tag, "Eta", "aProbeMuon.eta", theCut, 100, -2.4, 2.4);
  doAPlot(chain, tag, "dRclosest", "aProbeMuon.dRclosest", theCut, 100, 0, 4);
  doAPlot(chain, tag, "dxy", "aProbeMuon.dxy", theCut, 100, -4, 4);
  doAPlot(chain, tag, "dz", "aProbeMuon.dz", theCut, 100, -50, 50);
  doAPlot(chain, tag, "Chi2", "aProbeMuon.glbNormChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "StaChi2", "aProbeMuon.trkStaChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "TrkChi2", "aProbeMuon.trkNormChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "trkRatio", "aProbeMuon.pt_global/aProbeMuon.pt_standalone", theCut, 100, 0, 20);
  doAPlot(chain, tag, "SegComp", "aProbeMuon.muSegmComp", theCut, 50, 0, 1);
  doAPlot(chain, tag, "finalAlgo", "aProbeMuon.finalAlgo", theCut, 20, 0, 20);
  doAPlot(chain, tag, "initialAlgo", "aProbeMuon.originalAlgo", theCut, 20, 0, 20);
  doAPlot(chain, tag, "isTight", "aProbeMuon.isTight", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isMedium", "aProbeMuon.isMedium", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGlobalTightMuon", "aProbeMuon.isGlobalTightMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isTrackerTightMuon", "aProbeMuon.isTrackerTightMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isIsolatedMuon", "aProbeMuon.isIsolatedMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "IsGlobalORTracker", "(aProbeMuon.isGlobalTightMuon||aProbeMuon.isTrackerTightMuon)", theCut, 2, 0, 2);
  doAPlot(chain, tag, "matchesStations", "aProbeMuon.trkMuonMatchedStations", theCut, 7, 0, 7);
  doAPlot(chain, tag, "isTrkMuOST", "aProbeMuon.isTrkMuOST", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isTrkHP", "aProbeMuon.isTrkHP", theCut, 2, 0, 2);
  doAPlot(chain, tag, "trkValidHitFrac", "aProbeMuon.trkValidHitFrac", theCut, 50, 0, 1);
  doAPlot(chain, tag, "isGoodPFmuon", "aProbeMuon.isGoodPFmuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonWithClones", "aProbeMuon.isGoodPFmuonWithClones", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonCloseBy", "aProbeMuon.isGoodPFmuonCloseBy", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonSharingSeg", "aProbeMuon.isGoodPFmuonSharingSeg", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isClosestMuon", "aProbeMuon.isGoodPFmuonWithClones||(!(aProbeMuon.isGoodPFmuonCloseBy||aProbeMuon.isGoodPFmuonSharingSeg))", theCut, 2, 0, 2);

  tag = "goodMuons";//typeRECO+"_goodMuons";
  theCut = "invMassWithTag>80&&invMassWithTag<100&&isPF==1&&isGoodPFmuon";
  doAPlot(chain, tag, "Pt", "aProbeMuon.pt", theCut, 100, 0, 500);
  doAPlot(chain, tag, "Eta", "aProbeMuon.eta", theCut, 100, -2.4, 2.4);
  doAPlot(chain, tag, "dRclosest", "aProbeMuon.dRclosest", theCut, 100, 0, 4);
  doAPlot(chain, tag, "dxy", "aProbeMuon.dxy", theCut, 100, -4, 4);
  doAPlot(chain, tag, "dz", "aProbeMuon.dz", theCut, 100, -50, 50);
  doAPlot(chain, tag, "Chi2", "aProbeMuon.glbNormChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "StaChi2", "aProbeMuon.trkStaChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "TrkChi2", "aProbeMuon.trkNormChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "trkRatio", "aProbeMuon.pt_global/aProbeMuon.pt_standalone", theCut, 100, 0, 20);
  doAPlot(chain, tag, "SegComp", "aProbeMuon.muSegmComp", theCut, 50, 0, 1);
  doAPlot(chain, tag, "finalAlgo", "aProbeMuon.finalAlgo", theCut, 20, 0, 20);
  doAPlot(chain, tag, "initialAlgo", "aProbeMuon.originalAlgo", theCut, 20, 0, 20);
  doAPlot(chain, tag, "isTight", "aProbeMuon.isTight", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isMedium", "aProbeMuon.isMedium", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGlobalTightMuon", "aProbeMuon.isGlobalTightMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isTrackerTightMuon", "aProbeMuon.isTrackerTightMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isIsolatedMuon", "aProbeMuon.isIsolatedMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "IsGlobalORTracker", "(aProbeMuon.isGlobalTightMuon||aProbeMuon.isTrackerTightMuon)", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isTrkMuOST", "aProbeMuon.isTrkMuOST", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isTrkHP", "aProbeMuon.isTrkHP", theCut, 2, 0, 2);
  doAPlot(chain, tag, "trkValidHitFrac", "aProbeMuon.trkValidHitFrac", theCut, 50, 0, 1);
  doAPlot(chain, tag, "isGoodPFmuon", "aProbeMuon.isGoodPFmuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonWithClones", "aProbeMuon.isGoodPFmuonWithClones", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonCloseBy", "aProbeMuon.isGoodPFmuonCloseBy", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonSharingSeg", "aProbeMuon.isGoodPFmuonSharingSeg", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isClosestMuon", "aProbeMuon.isGoodPFmuonWithClones||(!(aProbeMuon.isGoodPFmuonCloseBy||aProbeMuon.isGoodPFmuonSharingSeg))", theCut, 2, 0, 2);

  tag = "goodMuonsClosest"; //typeRECO+"_goodMuonsClosest";
  theCut = "invMassWithTag>80&&invMassWithTag<100&&isPF==1&&(aProbeMuon.isGoodPFmuonWithClones||(!(aProbeMuon.isGoodPFmuonCloseBy||aProbeMuon.isGoodPFmuonSharingSeg)))";
  doAPlot(chain, tag, "Pt", "aProbeMuon.pt", theCut, 100, 0, 500);
  doAPlot(chain, tag, "Eta", "aProbeMuon.eta", theCut, 100, -2.4, 2.4);
  doAPlot(chain, tag, "dRclosest", "aProbeMuon.dRclosest", theCut, 100, 0, 4);
  doAPlot(chain, tag, "dxy", "aProbeMuon.dxy", theCut, 100, -4, 4);
  doAPlot(chain, tag, "dz", "aProbeMuon.dz", theCut, 100, -50, 50);
  doAPlot(chain, tag, "Chi2", "aProbeMuon.glbNormChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "StaChi2", "aProbeMuon.trkStaChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "TrkChi2", "aProbeMuon.trkNormChi2", theCut, 100, 0, 20);
  doAPlot(chain, tag, "trkRatio", "aProbeMuon.pt_global/aProbeMuon.pt_standalone", theCut, 100, 0, 20);
  doAPlot(chain, tag, "SegComp", "aProbeMuon.muSegmComp", theCut, 50, 0, 1);
  doAPlot(chain, tag, "finalAlgo", "aProbeMuon.finalAlgo", theCut, 20, 0, 20);
  doAPlot(chain, tag, "initialAlgo", "aProbeMuon.originalAlgo", theCut, 20, 0, 20);
  doAPlot(chain, tag, "isTight", "aProbeMuon.isTight", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isMedium", "aProbeMuon.isMedium", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGlobalTightMuon", "aProbeMuon.isGlobalTightMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isTrackerTightMuon", "aProbeMuon.isTrackerTightMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isIsolatedMuon", "aProbeMuon.isIsolatedMuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "IsGlobalORTracker", "(aProbeMuon.isGlobalTightMuon||aProbeMuon.isTrackerTightMuon)", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isTrkMuOST", "aProbeMuon.isTrkMuOST", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isTrkHP", "aProbeMuon.isTrkHP", theCut, 2, 0, 2);
  doAPlot(chain, tag, "trkValidHitFrac", "aProbeMuon.trkValidHitFrac", theCut, 50, 0, 1);
  doAPlot(chain, tag, "isGoodPFmuon", "aProbeMuon.isGoodPFmuon", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonWithClones", "aProbeMuon.isGoodPFmuonWithClones", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonCloseBy", "aProbeMuon.isGoodPFmuonCloseBy", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isGoodPFmuonSharingSeg", "aProbeMuon.isGoodPFmuonSharingSeg", theCut, 2, 0, 2);
  doAPlot(chain, tag, "isClosestMuon", "aProbeMuon.isGoodPFmuonWithClones||(!(aProbeMuon.isGoodPFmuonCloseBy||aProbeMuon.isGoodPFmuonSharingSeg))", theCut, 2, 0, 2);


  outputFile->Close();

}

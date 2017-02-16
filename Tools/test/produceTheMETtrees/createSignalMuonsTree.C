#include "MuonPogTree.h"

struct numberIndex {
  int   index;
  float value;
};

float deltaR(float eta1, float eta2, float phi1, float phi2){
  float deltaR = sqrt(pow(eta2-eta1,2)+ pow(acos(cos(phi2-phi1)),2)) ;
  return deltaR;
}

bool isMatchedWithTrigger(muon_pog::Muon theMuon, std::vector<muon_pog::HLTObject> theTriggerObjects){
  float minDr = 9999;
  for(int j=0 ; j<theTriggerObjects.size(); j++){
    muon_pog::HLTObject aTriggerObject = theTriggerObjects.at(j);
    float theDr = deltaR(aTriggerObject.eta, theMuon.eta, aTriggerObject.phi, theMuon.phi);
    //cout << "HLT obj, eta=" << aTriggerObject.eta << " phi=" << aTriggerObject.phi << " deltaR=" << theDr << endl;
    if (minDr>theDr) minDr=theDr;
  }
  //cout  << "minDR=" << minDr << endl;
  if (minDr<0.1) return true;
  else return false;
}

std::vector<muon_pog::HLTObject> skimHLTobject(std::vector<muon_pog::HLTObject> HLTobjects, TString theFilterName){
//std::vector<muon_pog::HLTObject> HLTobjects = ev->hlt.objects;
  int nbHLTobject = HLTobjects.size();
  std::vector<muon_pog::HLTObject> HLTobjectsSkimed;
  if (nbHLTobject==0) return HLTobjectsSkimed;
  for (int j=0 ; j<nbHLTobject ; j++){
    muon_pog::HLTObject aHLTobject = HLTobjects.at(j);
    if (aHLTobject.filterTag==theFilterName)
    HLTobjectsSkimed.push_back(aHLTobject);
  }
  return HLTobjectsSkimed;
}
std::vector<muon_pog::Muon> goodMuons(std::vector<muon_pog::Muon> rawMuons){
   std::vector<muon_pog::Muon> theGoodMuons;
    for (int m = 0 ; m < rawMuons.size() ; m++){
      muon_pog::Muon aMuon = rawMuons.at(m);
      if (!((aMuon.pt>25)&&(fabs(aMuon.eta)<2.4))) continue;
      if (!((aMuon.isGlobal==1)||(aMuon.isTracker==1))) continue;
      theGoodMuons.push_back(aMuon);
    }
    return theGoodMuons;
}

numberIndex dRclosestMuons( std::vector<muon_pog::Muon> allMuons, muon_pog::Muon theMuon){
  float dRmin = 9999;
  int index = -1;
  for (int i = 0 ; i < allMuons.size(); i++){
    muon_pog::Muon oneMuon = allMuons.at(i);
    float theDr = deltaR(oneMuon.eta, theMuon.eta, oneMuon.phi, theMuon.phi);
    if ((theDr<0.00000001)&&(oneMuon.pt==theMuon.pt)) continue;
    if (!(oneMuon.isPF==1)) continue;
    if (theDr<dRmin){
      dRmin = theDr;
      index = i;
    }
  }
  numberIndex theResult;
  theResult.index = index;
  theResult.value = dRmin;
  return theResult;
}




TString theFilterName = "hltL3crIsoL1sSingleMu20erL1f0L2f10QL3f22QL3trkIsoFiltered0p09::HLT";

void createSignalMuonsTree(TString inputFileName){
  TFile *myOutFile = new TFile("probeMuonTree.root", "RECREATE");

  TTree *mytreeEvent_ = new TTree("eventTree","");
  int nbOfMuons, nbOfPFmuons, nbOfMuonsLowDR, nbOfPFmuonsLowDR;
  mytreeEvent_->Branch("nbOfMuons", &nbOfMuons,"nbOfMuons/I");
  mytreeEvent_->Branch("nbOfPFmuons", &nbOfPFmuons,"nbOfPFmuons/I");
  mytreeEvent_->Branch("nbOfMuonsLowDR", &nbOfMuonsLowDR,"nbOfMuonsLowDR/I");
  mytreeEvent_->Branch("nbOfPFmuonsLowDR", &nbOfPFmuonsLowDR,"nbOfPFmuonsLowDR/I");


  muon_pog::Muon aProbeMuon;
  TTree *mytree_ = new TTree("probeMuons","");
  mytree_->Branch("aProbeMuon", &aProbeMuon, 64000 ,2);
  muon_pog::Muon aBadMuon;
  TTree *mytreeBad_ = new TTree("badMuons","");
  mytreeBad_->Branch("aBadMuon", &aBadMuon, 64000 ,2);
  muon_pog::Muon aBadMuonLowMass;
  TTree *mytreeBadLowMass_ = new TTree("badMuonsLowMass","");
  mytreeBadLowMass_->Branch("aBadMuonLowMass", &aBadMuonLowMass, 64000 ,2);

  TFile* inputFile = TFile::Open(inputFileName,"READONLY");
  TTree* tree = (TTree*)inputFile->Get("MuonPogTree/MUONPOGTREE");
   if (!tree) cout << "oupssss" << endl;

   muon_pog::Event* ev = new muon_pog::Event();

   evBranch = tree->GetBranch("event");
   evBranch->SetAddress(&ev);


   int nEvents = evBranch->GetEntries();
   cout << "Events=" << nEvents << endl;


   for (int i=0 ; i<nEvents ; i++){
     evBranch->GetEntry(i);
     if (i%10000==0) cout << "Event=" << i  << endl;

    //std::vector<muon_pog::HLTObject> HLTobjectsSkimed = skimHLTobject(ev->hlt.objects, theFilterName);

     //cout << "nomber of good filters=" << HLTobjectsSkimed.size() << endl;
     ////// now, try to find a tag muon_pog
     std::vector<muon_pog::Muon> allMuons = ev->muons;
     nbOfMuons = allMuons.size();
     nbOfPFmuons = 0;
     nbOfMuonsLowDR = 0;
     nbOfPFmuonsLowDR = 0;
     for (int k = 0 ; k<nbOfMuons ; k++){
       muon_pog::Muon aCountMuon = allMuons.at(k);
       if (aCountMuon.isPF) nbOfPFmuons++;
       numberIndex checkIsACloseMuon = dRclosestMuons(allMuons,aCountMuon);
       if (checkIsACloseMuon.value<0.1){
         nbOfMuonsLowDR++;
         if (aCountMuon.isPF) nbOfPFmuonsLowDR++;
       }
     }
     mytreeEvent_->Fill();
     std::vector<muon_pog::Muon> allGoodMuons = goodMuons(allMuons);
     if (allGoodMuons.size()<2) continue;
     for (int m = 0 ; m < allGoodMuons.size() ; m++){
       muon_pog::Muon tagMuons = allGoodMuons.at(m);
       if (!(tagMuons.isTight==1)) continue;
       if (!(tagMuons.isoPflow04<0.15)) continue;
       //if (!(isMatchedWithTrigger(tagMuons, HLTobjectsSkimed))) continue;
       //cout << "is matched=" << isMatchedWithTrigger(tagMuons, HLTobjectsSkimed) << endl;
       for (int n = 0 ; n < allGoodMuons.size() ; n++){
         if (m==n) continue;
         muon_pog::Muon probeMuons = allGoodMuons.at(n);
         TLorentzVector probeMuonsQuadri;
         probeMuonsQuadri.SetPtEtaPhiM(probeMuons.pt,probeMuons.eta,probeMuons.phi,.10565);
         TLorentzVector tagMuonsQuadri;
         tagMuonsQuadri.SetPtEtaPhiM(tagMuons.pt,tagMuons.eta,tagMuons.phi,.10565);
         float mass = (tagMuonsQuadri+probeMuonsQuadri).M();
         aProbeMuon = probeMuons;
         aProbeMuon.invMassWithTag = mass;
         numberIndex dRclosestToProbe = dRclosestMuons(allMuons, aProbeMuon);
         //cout << "dRclosestToProbe=" << dRclosestToProbe <<  endl;
         aProbeMuon.dRclosest = dRclosestToProbe.value;
         if (dRclosestToProbe.index!=-1){
           if ((mass>80)&&(mass<100)){
             if (dRclosestToProbe.value < 0.1){
               aBadMuon = allMuons.at(dRclosestToProbe.index);
               aBadMuon.dRclosest = dRclosestToProbe.value;
               mytreeBad_->Fill();
             }
           }
           else if (mass<5) {
             if (dRclosestToProbe.value < 0.1){
               aBadMuonLowMass = allMuons.at(dRclosestToProbe.index);
               aBadMuonLowMass.dRclosest = dRclosestToProbe.value;
               mytreeBadLowMass_->Fill();
             }
           }

         }
         mytree_->Fill();
       }
     }
  }
  myOutFile->cd();
  mytree_->Write();
  mytreeBad_->Write();
  mytreeBadLowMass_->Write();
  mytreeEvent_->Write();
  myOutFile->Close();
}

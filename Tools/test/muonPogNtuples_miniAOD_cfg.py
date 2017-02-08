
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

import subprocess

import sys

options = VarParsing.VarParsing()

options.register('globalTag',
                 '80X_dataRun2_Prompt_v16', #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Global Tag")

options.register('nEvents',
                 1000, #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Maximum number of processed events")

options.register('eosInputFolder',
                 '/tmp/calderon/eos/cms/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver3-v1/80000/', #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "EOS folder with input files")

options.register('ntupleName',
                 '88639E52-7DEA-E611-9102-A0369F310374.root', #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Folder and name ame for output ntuple")

options.register('runOnMC',
                 False, #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Run on DATA or MC")

options.register('hltPathFilter',
                 "all", #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Filter on paths (now only accepts all or IsoMu20)")

options.register('minMuPt',
                 5., #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.float,
                 "Skim the ntuple selecting only STA || TRK || GLB muons with pT > of this value")

options.register('minNMu',
                 1, #default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "number of TRK or GLB muons with pT > minMuPt to pass the skim")


options.parseArguments()

if options.hltPathFilter == "all" :
    pathCut   = "all"
    filterCut = "all"
elif options.hltPathFilter == "IsoMu20" :
    pathCut   = "HLT_IsoMu20_v"
    filterCut = "hltL3crIsoL1sMu16L1f0L2f10QL3f20QL3trkIsoFiltered0p09"
else :
    print "[" + sys.argv[0] + "]:", "hltPathFilter=", options.hltPathFilter, "is not a valid parameter!"
    sys.exit(100)

process = cms.Process("NTUPLES")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.nEvents))

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = cms.string(options.globalTag)

process.source = cms.Source("PoolSource",
                            
        fileNames = cms.untracked.vstring(),
        secondaryFileNames = cms.untracked.vstring()

)

#files = subprocess.check_output([ "/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select", "ls", options.eosInputFolder ])
files = subprocess.check_output([ "ls", options.eosInputFolder ])
process.source.fileNames = [ "file:"+options.eosInputFolder+"/"+f for f in files.split() ]    

process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
#process.load("Geometry.CommonDetUnit.globalTrackingGeometry_cfi")
#process.load("RecoMuon.DetLayers.muonDetLayerGeometry_cfi")

from MuonPOGtreeProducer.Tools.MuonPogNtuples_cff import appendMuonPogNtuple, customiseHlt, customiseMuonCuts
    
appendMuonPogNtuple(process,options.runOnMC,"HLT",options.ntupleName)

customiseHlt(process,pathCut,filterCut)
customiseMuonCuts(process,options.minMuPt,options.minNMu)

process.MuonPogTree.MuonTag = cms.untracked.InputTag("slimmedMuons")
process.MuonPogTree.PrimaryVertexTag = cms.untracked.InputTag("offlineSlimmedPrimaryVertices")
process.MuonPogTree.TrigResultsTag = cms.untracked.InputTag("TriggerResults")
process.MuonPogTree.TrigSummaryTag = cms.untracked.InputTag("none")
process.MuonPogTree.PFMetTag = cms.untracked.InputTag("slimmedMETs")
process.MuonPogTree.PFChMetTag = cms.untracked.InputTag("none")
process.MuonPogTree.CaloMetTag = cms.untracked.InputTag("none")


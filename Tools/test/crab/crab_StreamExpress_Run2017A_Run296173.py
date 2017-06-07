from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'Run2017A_StreamExpress_Run296173'

config.section_('JobType')
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = '../muonPogNtuples_cfg.py'
#config.JobType.outputFiles = ['muonNTuple.root']
config.JobType.pyCfgParams = ['globalTag=',
                              'ntupleName=muonPOGNtuple_StreamExpressRun2017A_PromptReco.root',
                              'nEvents=-1',
                              'runOnMC=False',
                              'hltPathFilter=all',
                              'minMuPt=10.0',
                              'minNMu=2'
               ]
config.JobType.allowUndistributedCMSSW = True  # To fix cmssw releases

config.section_('Data')
config.Data.inputDataset = '/StreamExpress/Run2017A-PromptCalibProd-Express-v1/ALCAPROMPT'

config.Data.runRange = '296173'
#config.Data.allowNonValidInputDataset = True

config.Data.splitting    = 'LumiBased'
config.Data.unitsPerJob  = 150  # Since files based, 10 files per job
config.Data.inputDBS     = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.outLFNDirBase  = '/store/group/phys_higgs/cmshww/calderon/test92X'
#'/store/group/phys_muon/calderon/NTuplesMuonPOG'

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'


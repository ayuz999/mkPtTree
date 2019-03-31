#include "StMomentsMaker.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StThreeVectorF.hh"
#include "TFile.h"
#include "Stiostream.h"
#include <TMath.h>
#include "TH1F.h"
#include "TH2F.h"
#include "TH2D.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "phys_constants.h"
#include "StBTofUtil/tofPathLength.hh"
#include <fstream>
#include <vector>
#include <algorithm>
#include "TProfile.h"
#include "TTree.h"

ClassImp(StMomentsMaker)

struct Event
{

  Int_t RunId;
  Int_t TriggerId;

  Double_t Vr;
  Double_t Vz;
  Double_t VzVpd;

  Int_t refMult;
  Int_t refMult2;
  Int_t refMult3;
  Int_t refMult4;
  Int_t TofMultiplicity;

  Float_t ZDCx;

  Float_t nTofMatch;
  Float_t Beta_eta1;

  Int_t NumOfTracks;

  Int_t Charge[10000];
  Int_t nHitsFit[10000];
  Int_t nHitsdEdx[10000];
  Int_t nHitsMax[10000];
  Double_t Px[10000];
  Double_t Py[10000];
  Double_t Pz[10000];
  Double_t Pt[10000];
  Double_t MassSquare[10000]; 
  Double_t Eta[10000];
  Double_t Dca[10000];
  Double_t Phi[10000];
  Float_t nSigmaProton[10000];
  Float_t nSigmaKaon[10000];
  Float_t nSigmaPion[10000];
    
}; 
Event event;

  StMomentsMaker::StMomentsMaker(const char *name, StPicoDstMaker *picoMaker, const char *outName): StMaker(name){
	mOutputName = outName;
	mPicoDstMaker = picoMaker;
	mPicoDst = 0;
  }

StMomentsMaker::~StMomentsMaker(){}

Int_t StMomentsMaker::Init(){

  mFileOut = new TFile(mOutputName, "recreate");
  stree = new TTree("SmallerTree","smaller tree");
  //stree->Branch("TriggerId", &event.TriggerId, "TriggerId/I");
  //stree->Branch("RunId", &event.RunId, "RunId/I");
  stree->Branch("Vz", &event.Vz, "Vz/D");
  //stree->Branch("VzVpd", &event.VzVpd, "VzVpd/D");
  //stree->Branch("Vr", &event.Vr, "Vr/D");
  //stree->Branch("refMult", &event.refMult, "refMult/I");
  //stree->Branch("refMult2", &event.refMult2, "refMult2/I");
  stree->Branch("refMult3", &event.refMult3, "refMult3/I");
  //stree->Branch("refMult4", &event.refMult4, "refMult4/I");
  //stree->Branch("TofMultiplicity", &event.TofMultiplicity, "TofMultiplicity/I");
  //stree->Branch("ZDCx", &event.ZDCx, "ZDCx/F");

  stree->Branch("NumOfTracks", &event.NumOfTracks, "NumOfTracks/I");
  //stree->Branch("nTofMatch", &event.nTofMatch, "nTofMatch/I");
  //stree->Branch("Beta_eta1", &event.Beta_eta1, "Beta_eta1/I");
  //stree->Branch("Charge", event.Charge, "Charge[NumOfTracks]/I");
  //stree->Branch("nHitsFit", event.nHitsFit, "nHitsFit[NumOfTracks]/I");
  //stree->Branch("nHitsdEdx", event.nHitsdEdx, "nHitsdEdx[NumOfTracks]/I");
  //stree->Branch("nHitsMax", event.nHitsMax, "nHitsMax[NumOfTracks]/I");
  //stree->Branch("Px", event.Px, "Px[NumOfTracks]/F");
  //stree->Branch("Py", event.Py, "Py[NumOfTracks]/F");
  //stree->Branch("Pz", event.Pz, "Pz[NumOfTracks]/F");
  stree->Branch("Pt", event.Pt, "Pt[NumOfTracks]/D");
  //stree->Branch("MassSquare", event.MassSquare, "MassSquare[NumOfTracks]/D");
  //stree->Branch("Eta", event.Eta, "Eta[NumOfTracks]/D");
  //stree->Branch("Dca", event.Dca, "Dca[NumOfTracks]/D");
  //stree->Branch("Phi", event.Phi, "Phi[NumOfTracks]/D");
  //stree->Branch("nSigmaProton", event.nSigmaProton, "nSigmaProton[NumOfTracks]/F");
  //stree->Branch("nSigmaPion", event.nSigmaPion, "nSigmaPion[NumOfTracks]/F");
  //stree->Branch("nSigmaKaon", event.nSigmaKaon, "nSigmaKaon[NumOfTracks]/F");


  return kStOK;
}

//---------------------------------------------------------
Int_t StMomentsMaker::Finish() {
  mFileOut->cd();
  stree->Write();
  mFileOut->Close();
  cout<<"Compare Here, nTracks: "<<nTracks<<endl;
  return kStOK;
}

void  StMomentsMaker::Clear(Option_t *opt) {}

//---------------------------------------------------------------
Int_t StMomentsMaker::Make() {
  if(!mPicoDstMaker) {
	LOG_WARN << " No PicoDstMaker! Skip! " << endm;
	return kStWarn;
  }

  mPicoDst = mPicoDstMaker->picoDst();
  if(!mPicoDst) {
	LOG_WARN << " No PicoDst! Skip! " << endm;
	return kStWarn;
  }

  if(!mPicoDst) return kStOk;

  //Load event
  mPicoEvent = (StPicoEvent*)mPicoDst->event();
  if(!mPicoEvent){
	cerr<<"Error opening picoDst Event, skip!"<<endl;
	return kStOk;
  }
  if( !mPicoEvent->isTrigger(610051)) 
    {
      if( !mPicoEvent->isTrigger(610041)) 
      {
          if( !mPicoEvent->isTrigger(610031)) 
          {
              if( !mPicoEvent->isTrigger(610021)) 
              {
                  if( !mPicoEvent->isTrigger(610011)) 
                  {
                      if( !mPicoEvent->isTrigger(610001)) 
                      {
                          return kStOk;
                      }
                  }
              }
          }
      }
  }



  pVtx    = mPicoEvent->primaryVertex();

 
  vx = pVtx.X();
  vy = pVtx.Y();
  vz = pVtx.Z();

  if(TMath::Abs(vx) < 1.e-5 && TMath::Abs(vy) < 1.e-5 && TMath::Abs(vz) < 1.e-5) return kStOk;
  if(sqrt(pow(vx, 2.0) + pow(vy, 2.0)) >= 2.0) return kStOk;
  if(TMath::Abs(vz) > 60)  return kStOk;

  for(int i=0;i<10000;++i){
    event.Pt[i] = 0;
  }


  nTofMultplicity = mPicoEvent->btofTrayMultiplicity();
  nTpcRefMult     = mPicoEvent->refMult();
  int refMult3 = mPicoEvent->refMult3();

  //std::vector<unsigned int> mTriggerIds =  mPicoEvent->triggerIds();
  //event.TriggerId = mTriggerIds[0];
  //event.RunId = mPicoEvent->runId();

  event.Vz = vz;
  //event.VzVpd = mPicoEvent->vzVpd();
  //event.Vr = sqrt(pow(vx, 2.0) + pow(vy, 2.0));

  //event.ZDCx = mPicoEvent->ZDCx();
  //event.refMult  = mPicoEvent->refMult();
  //event.refMult2 = mPicoEvent->refMult2();
  event.refMult3 = refMult3;
  //event.refMult4 = mPicoEvent->refMult4();
  //event.TofMultiplicity = mPicoEvent->btofTrayMultiplicity();

  mBField  = mPicoEvent->bField();
  
  //------------------------track loop-------------
  nTracks = mPicoDst->numberOfTracks();
  int nTofMatch = 0;
  int beta_eta1 = 0;
  int SelectedTracks=0;

  for(unsigned int iTrack = 0; iTrack < nTracks; iTrack++) {

	  picoTrack = (StPicoTrack*) mPicoDst->track(iTrack);
	  if(!picoTrack) break;

	  bool isPtr = picoTrack->isPrimary();
	  if(!isPtr) continue;
          
    StPicoPhysicalHelix helix = picoTrack->helix(mBField);
	  double dca = helix.geometricSignedDistance(pVtx);
	  if(dca < 0) dca = fabs(dca);

	  pmomentum = picoTrack->pMom();
    double  p = pmomentum.Mag();
	  double  pz  = pmomentum.Z();
	  double  px   = pmomentum.X();
	  double  py   = pmomentum.Y();
	  double  eta = pmomentum.PseudoRapidity();
    float phi = pmomentum.Phi();

	  double EP = sqrt(p * p + 0.938 * 0.938);
	  YP = 0.5 * log((EP + pz)/(EP - pz));
	  if(YP!= YP) YP = -999;

	  int nhitsFit  = picoTrack->nHitsFit();
	  int nhitsdEdx = picoTrack->nHitsDedx();
	  int nhitsPoss = picoTrack->nHitsMax();
	  float ratio   = (1 + fabs(nhitsFit))/(1 + nhitsPoss);
	  float nSigmaProton = picoTrack->nSigmaProton();
	  float nSigmaKaon = picoTrack->nSigmaKaon();
	  float nSigmaPion = picoTrack->nSigmaPion();
	  float charge  = picoTrack->charge();

	  Int_t   btofMatchFlag =  0;
	  int index2tof = picoTrack->bTofPidTraitsIndex();

	  float beta = -1.;
	  if(index2tof >= 0) {
	    StPicoBTofPidTraits *tofPid = mPicoDst->btofPidTraits(index2tof);
	    btofMatchFlag = tofPid->btofMatchFlag();
	    if(tofPid) {
	  	beta = tofPid->btofBeta();
          double tof = tofPid->btof();
          if(beta < 1e-4){
              TVector3 btofHitPos_ = tofPid->btofHitPos();
              const StThreeVectorF *btofHitPos = new StThreeVectorF(btofHitPos_.X(),btofHitPos_.Y(),btofHitPos_.Z());
              const StThreeVectorF *vertexPos_ = new StThreeVectorF(pVtx.X(), pVtx.Y(), pVtx.Z());
              double L = tofPathLength(vertexPos_, btofHitPos, helix.curvature());
              if(tof>0) beta = L/(tof*(C_C_LIGHT/1.e9));
              else  beta = std::numeric_limits<float>::quiet_NaN();
          }
	    }
	  }
    if( btofMatchFlag > 0 && fabs(eta) < 0.5 && dca < 3 && nhitsFit > 10 ) nTofMatch++;
    if( beta > 0.1 && fabs(eta) < 1 && dca < 3 && nhitsFit > 10 ) beta_eta1++;

	  bool isGoodTof = btofMatchFlag >0 && beta > 0;
	  float msquare = 0.;
	  if(isGoodTof){
	    msquare = p * p * (1./pow(beta,2)-1);
	  } else {
	    msquare = 0.0;
        continue;
	  }

	  //-------track quality------
	  if(nhitsdEdx <= 5) continue;
	  if(nhitsFit <= 20) continue;
	  if(ratio <= 0.52)  continue;
	  if(dca >= 1)       continue;

    if(fabs(YP)>0.5) continue;

    //PID
    if(picoTrack->nSigmaProton()>2.0) continue;
    if(p>3.0) continue;
    if(msquare<0.6 || msquare>1.2) continue;

    //event.nHitsFit[SelectedTracks] = nhitsFit;
    //event.nHitsdEdx[SelectedTracks] = nhitsdEdx;
    //event.nHitsMax[SelectedTracks] = nhitsPoss;
    //event.Px[SelectedTracks] = px;
    //event.Py[SelectedTracks] = py;
    //event.Pz[SelectedTracks] = pz;
    event.Pt[SelectedTracks] = picoTrack->charge() * sqrt(px*px + py*py);
    //event.MassSquare[SelectedTracks]= msquare;
    //event.nSigmaProton[SelectedTracks] = nSigmaProton;
    //event.nSigmaKaon[SelectedTracks] = nSigmaKaon;
    //event.nSigmaPion[SelectedTracks] = nSigmaPion;
    //event.Eta[SelectedTracks]= eta;
    //event.Dca[SelectedTracks]= dca;
    //event.Phi[SelectedTracks]= phi;
    //event.Charge[SelectedTracks] = charge;

    SelectedTracks++;
  }//PicoTracks loop end

  if( (nTofMultplicity < (3.0 * nTpcRefMult - 110 )) || (nTofMultplicity > ( 3.55 * nTpcRefMult + 316 )) ) return kStOk;
  if( nTofMatch < (nTpcRefMult * 0.38 - 7.6 ) ) return kStOK;
  if( beta_eta1 < (refMult3 * 0.573 - 33 ) ) return kStOK;

  event.NumOfTracks = SelectedTracks;
  //event.nTofMatch = nTofMatch;
  //event.Beta_eta1 = beta_eta1;

  stree->Fill();

  return kStOK;
}


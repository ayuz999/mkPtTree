#ifndef STAR_StMomentsMaker
#define STAR_StMomentsMaker
#include "StMaker.h"
#include "StThreeVectorF.hh"
#include "TString.h"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StarClassLibrary/StThreeVectorD.hh"

class StPicoDst;
class StPicoEvent;
class StPicoTrack;
class StPicoDstMaker;
class StRefMultCorr;
class TH1F;
class TH2F;
class TH3F;
class TProfile;
class TTree;
#include "TVector3.h"

class StMomentsMaker : public StMaker {
  public:
	StMomentsMaker(const char *name, StPicoDstMaker *picoMaker, const char *outName="Pt_Tree.root");
	virtual ~StMomentsMaker();

	virtual Int_t Init();
	virtual Int_t Make();
	virtual void  Clear(Option_t *opt="");
	virtual Int_t Finish();

	bool isPrimary();
 
	std::vector<Int_t> mBadRun;
    bool isBadRunsId(const Int_t RunId);
    void readBadRunsId();

	 double NN(double num, int order);
	  int Centrality(int gRefMult);
	  
  private:
	StPicoDstMaker *mPicoDstMaker;
	StPicoDst      *mPicoDst;
	StPicoEvent	   *mPicoEvent;
	StPicoTrack    *picoTrack;

	//StThreeVectorF pVtx(-999.,-999.,-999.);
	//StThreeVectorF pVtxErr(0.,0.,0.);
	TVector3 pVtx;
	TVector3 pVtxErr;
	TVector3 pmomentum;

	unsigned int nTracks;
	float  B;
	float  mBField;

	int m;
	int runid;
	int runnumber;
	float PI;

	float  vx;
	float  vy;
	float  vz;
	float  VzVpd;
	float  YP;
	float  EP;

	int proton1;
	int aproton1;
	int proton2;
	int aproton2;
	int proton;
	int aproton;
	int netproton;
	int totproton;

	int refmult3;

	float nTofMultplicity;
	int   nTpcRefMult;

	TString mOutputName;
	TFile* mFileOut;
  TTree *stree;


	ClassDef(StMomentsMaker, 1)
};

#endif

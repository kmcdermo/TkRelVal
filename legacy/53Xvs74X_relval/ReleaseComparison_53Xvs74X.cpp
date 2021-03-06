//INDIVIDUAL/MULTI-FILE COMPARISON

//***This macro produces overlaying histograms from either individual or sets of input files

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TPad.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TString.h"
#include "TF1.h"
#include "TPaveStats.h"
#include "TPaveText.h"

using namespace std;

void V1_V2_trkComparison(string fileName1, string fileName2, int scale);
bool createPlot(TString hname, TString dirname1, TString dirname2, TFile *V1file, TString runstring1, TString relstring1, TFile *V2file, TString runstring2, TString relstring2, int scale);
void setTDRStyle();

void V1_V2_trkComparison(string fileName1, string fileName2, int scale) {
  
  gROOT->SetBatch(kTRUE);

  gROOT->SetStyle("Default");
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(111101);

  gStyle->SetOptFit(1);

  int pos = fileName1.find("_R0");
  std::string runString1 = fileName1.substr (pos+5,6);
  int pos1 = fileName1.find("CMSSW")+6;
  int pos2 = fileName1.find("/MinimumBias");
  if (pos2 == -1 ) pos2 = fileName1.find("/Jet");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-PRE");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-FT");

  std::string relString1 = fileName1.substr (pos1,pos2-pos1); 
  TFile *file1 = TFile::Open(fileName1.c_str(),"READ");
  std::cout << "Getting histos for run number... " << runString1 
	    <<" for release " << relString1 << std::endl;  
  if ( file1->IsZombie() )
    std::cout << "File: " << fileName1 << " cannot be opened!" << std::endl;
  pos = fileName2.find("_R0");

  std::string runString2 = fileName2.substr (pos+5,6);
  pos1 = fileName2.find("CMSSW")+6;
  pos2 = fileName2.find("/MinimumBias");
  if (pos2 == -1 ) pos2 = fileName2.find("/Jet");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-PRE");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-FT");

  std::string relString2 = fileName2.substr (pos1,pos2-pos1);
  TFile *file2 = TFile::Open(fileName2.c_str(),"READ");
  std::cout << "Getting histos for run number... " << runString2 
	    <<" for release " << relString2 << std::endl;  
  if ( file2->IsZombie() )
    std::cout << "File: " << fileName2 << " cannot be opened!" << std::endl;

  // save comparisons in root file

  //  TFile * outputRoot = TFile::Open("53xvs74X.root","RECREATE");

  // Histograms in BeamSpotParameters directory
  TString dirname1 = "";
  TString dirname2 = "";

  // Histograms in GeneralProperties directory

  dirname1 = "/Tracking/Run summary/TrackParameters/GeneralProperties";
  dirname2 = "/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties";
  //  createPlot("algorithm", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("NumberOfTracks", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("Chi2", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("Chi2oNDF", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("Chi2Prob", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("DistanceOfClosestApproachToBS", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("TrackPhi_ImpactPoint", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   createPlot("TrackEta_ImpactPoint", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);

  //  createPlot("TrackPt_ImpactPoint", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // goodTracks props
  dirname1 = "/Tracking/Run summary/TrackParameters/GeneralProperties/GoodTracks";
  dirname2 = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/GeneralProperties";
  // createPlot("algorithm", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("NumberOfTracks", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("FractionOfGoodTracks", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("Chi2oNDF", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("Chi2Prob", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("TrackEta_ImpactPoint", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("TrackPhi_ImpactPoint", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  // createPlot("TrackPt_ImpactPoint", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   
  //Histograms for high purity HitProperties
  /*dirname1 = "/Tracking/Run summary/TrackParameters/HitProperties/GoodTracks";
  dirname2 = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties";
  createPlot("NumberOfRecHitsPerTrack", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfValidRecHitsPerTrack", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   
  // Histograms in HitProperties directory -- genTracks
  dirname1 = "/Tracking/Run summary/TrackParameters/HitProperties";
  dirname2 = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties";
  createPlot("NumberOfRecHitsPerTrack", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfValidRecHitsPerTrack", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfLostRecHitsPerTrack", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfLayersPerTrack", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   
  dirname1 = "/Tracking/Run summary/TrackParameters/HitProperties/TIB";
  dirname2 = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TIB";
  createPlot("NumberOfRecHitsPerTrack_TIB", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfLayersPerTrack_TIB", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   
  dirname1 = "/Tracking/Run summary/TrackParameters/HitProperties/TOB";
  dirname2 = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TOB";
  createPlot("NumberOfRecHitsPerTrack_TOB", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfLayersPerTrack_TOB", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);

  dirname1 = "/Tracking/Run summary/TrackParameters/HitProperties/TID";
  dirname2 = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TID";
  createPlot("NumberOfRecHitsPerTrack_TID", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfLayersPerTrack_TID", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   
  dirname1 = "/Tracking/Run summary/TrackParameters/HitProperties/TEC";
  dirname2 = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TEC";
  createPlot("NumberOfRecHitsPerTrack_TEC", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfLayersPerTrack_TEC", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   
  dirname1 = "/Tracking/Run summary/TrackParameters/HitProperties/PixBarrel";
  dirname2 = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixBarrel";
  createPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfLayersPerTrack_PixBarrel", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   
  dirname1 = "/Tracking/Run summary/TrackParameters/HitProperties/PixEndcap";
  dirname2 = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixEndcap";
  createPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
  createPlot("NumberOfLayersPerTrack_PixEndcap", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);
   
  //Primary vertices
  dirname1 = "/OfflinePV/Run summary/offlinePrimaryVertices";
  dirname2 = "/OfflinePV/Run summary/offlinePrimaryVertices";
  createPlot("vtxNbr", dirname1, dirname2, file1, runString1, relString1, file2, runString2, relString2, scale);*/
}

bool createPlot(TString hname, TString dirname1, TString dirname2, TFile *V1file, TString runstring1, TString relstring1, TFile *V2file, TString runstring2, TString relstring2, int scale) {

  TCanvas *canvas = new TCanvas(hname.Data(),hname.Data(),1);

  setTDRStyle();

  if (dirname1.Contains("/Tracking/Run summary/TrackParameters/GeneralProperties/GoodTracks",TString::kExact)){
    TString canvname = hname;
    canvname.Prepend("GoodTracks");
    canvas->SetName(canvname.Data());
    canvas->SetTitle(canvname.Data());
  }
 
  int SetScale = scale;

  //IF =0 --> No scale applied ('direct' comparison)
  //IF =1 --> Scale INDIVIDUALLY (scale histograms individually) 
  //IF =2 --> Scale all GLOBALLY (scale all histograms to #tracks=1)
  //IF =3 --> Scale all GLOBALLY nEVENTS (scale all histos to nEntries in nTracks per Event)

  bool DrawRatio = true;
  canvas->cd();
  TPad* mainpad = new TPad("mainpad","mainpad",0.0,0.0,0.9,1.0);
  mainpad->Draw();
  mainpad->cd();
  setTDRStyle();
  // ************ Get name of histos and get histos ************* //
  
  TString basename1 = "DQMData/Run ";
  basename1.Append(runstring1);

  TString hnameV1 = basename1;
  hnameV1.Append(dirname1+"/");

  TString hname1 = hname;

  if (dirname1.Contains("/Tracking/Run summary/TrackParameters/GeneralProperties/GoodTracks",TString::kExact)){
    if (hname.Contains("algorithm",TString::kExact)){hname1 = "GoodTrackAlgorithm";}
    else if (hname.Contains("NumberOfTracks",TString::kExact)){hname1 = "NumberOfGoodTracks";}
    else if (hname.Contains("Chi2oNDF",TString::kExact)){hname1 = "GoodTrackChi2oNDF";}
    else if (hname.Contains("Chi2Prob",TString::kExact)){hname1 = "GoodTrackChi2Prob";}
    else if (hname.Contains("TrackEta_ImpactPoint",TString::kExact)){hname1 = "GoodTrackEta_ImpactPoint";}
    else if (hname.Contains("TrackPhi_ImpactPoint",TString::kExact)){hname1 = "GoodTrackPhi_ImpactPoint";}
    else if (hname.Contains("TrackPt_ImpactPoint",TString::kExact)){hname1 = "GoodTrackPt_ImpactPoint";}
  }
  else if(dirname1.Contains("/Tracking/Run summary/TrackParameters/HitProperties/GoodTracks",TString::kExact)){
    if (hname.Contains("NumberOfRecHitsPerTrack",TString::kExact)){hname1 = "GoodTrackNumberOfRecHitsPerTrack";}
    else if (hname.Contains("NumberOfValidRecHitsPerTrack",TString::kExact)){hname1 = "GoodTrackNumberOfRecHitsFoundPerTrack";}
  }
  else if(dirname1.Contains("/Tracking/Run summary/TrackParameters/HitProperties",TString::kExact)){
    if (hname.Contains("NumberOfValidRecHitsPerTrack",TString::kExact)){hname1 = "NumberOfRecHitsFoundPerTrack";}
    else if (hname.Contains("NumberOfLostRecHitsPerTrack",TString::kExact)){hname1 = "NumberOfRecHitsLostPerTrack";}
    else if (hname.Contains("NumberOfRecHitsPerTrack_TIB",TString::kExact)){hname1 = "NumberOfTIBRecHitsPerTrack";}
    else if (hname.Contains("NumberOfLayersPerTrack_TIB",TString::kExact)){hname1 = "NumberOfTIBLayersPerTrack";}
    else if (hname.Contains("NumberOfRecHitsPerTrack_TOB",TString::kExact)){hname1 = "NumberOfTOBRecHitsPerTrack";}
    else if (hname.Contains("NumberOfLayersPerTrack_TOB",TString::kExact)){hname1 = "NumberOfTOBLayersPerTrack";}
    else if (hname.Contains("NumberOfRecHitsPerTrack_TEC",TString::kExact)){hname1 = "NumberOfTECRecHitsPerTrack";}
    else if (hname.Contains("NumberOfLayersPerTrack_TEC",TString::kExact)){hname1 = "NumberOfTECLayersPerTrack";}
    else if (hname.Contains("NumberOfRecHitsPerTrack_TID",TString::kExact)){hname1 = "NumberOfTIDRecHitsPerTrack";}
    else if (hname.Contains("NumberOfLayersPerTrack_TID",TString::kExact)){hname1 = "NumberOfTIDLayersPerTrack";}
    else if (hname.Contains("NumberOfRecHitsPerTrack_PixBarrel",TString::kExact)){hname1 = "NumberOfPixBarrelRecHitsPerTrack";}
    else if (hname.Contains("NumberOfLayersPerTrack_PixBarrel",TString::kExact)){hname1 = "NumberOfPixBarrelLayersPerTrack";}
    else if (hname.Contains("NumberOfRecHitsPerTrack_PixEndcap",TString::kExact)){hname1 = "NumberOfPixEndcapRecHitsPerTrack";}
    else if (hname.Contains("NumberOfLayersPerTrack_PixEndcap",TString::kExact)){hname1 = "NumberOfPixEndcapLayersPerTrack";}
  }

  hnameV1.Append(hname1);

  if (hname != "vtxNbr"){
    hnameV1.Append("_GenTk");
  }

  TH1F * hBinTempV1 = new TH1F();
  hBinTempV1 = (TH1F*)V1file->Get(hnameV1);
  if ( hBinTempV1 == (TH1F*) NULL ) {
    cout << "histV1 failed on " << hnameV1  << endl << " for file " << V1file->GetName() << endl;
    exit(1);
  }

  TString basename2 = "DQMData/Run ";
  basename2.Append(runstring2);

  TString hnameV2 = basename2;
  hnameV2.Append(dirname2+"/");
  hnameV2.Append(hname);
  
  if (hname != "vtxNbr"){
    hnameV2.Append("_GenTk");
  }

  TH1F * hBinTempV2 = new TH1F();
  hBinTempV2 = (TH1F*)V2file->Get(hnameV2);
  if ( hBinTempV2 == (TH1F*) NULL ) {
    cout << "histV2 failed on " << hnameV2  << endl << " for file " << V2file->GetName() << endl;
    exit(1);
  }
  
  // Check that bins match for ratio plot

  TH1F * histV1 = 0;
  TH1F * histV2 = 0;

  Double_t h1_xlow = hBinTempV1->GetXaxis()->GetBinLowEdge(hBinTempV1->GetXaxis()->GetFirst());
  Double_t h2_xlow = hBinTempV2->GetXaxis()->GetBinLowEdge(hBinTempV2->GetXaxis()->GetFirst());

  Double_t h1_xup = hBinTempV1->GetXaxis()->GetBinUpEdge(hBinTempV1->GetXaxis()->GetLast());
  Double_t h2_xup = hBinTempV2->GetXaxis()->GetBinUpEdge(hBinTempV2->GetXaxis()->GetLast());

  Int_t h1_nbins = hBinTempV1->GetNbinsX();
  Int_t h2_nbins = hBinTempV2->GetNbinsX();

  Double_t h1_binWidth = (h1_xup - h1_xlow) / (Double_t)h1_nbins;
  Double_t h2_binWidth = (h2_xup - h2_xlow) / (Double_t)h2_nbins;

  Double_t h1_nEntries = hBinTempV1->GetEntries();
  Double_t h2_nEntries = hBinTempV2->GetEntries();

  //  if (hname1.Contains("NumberOfGoodTracks",TString::kExact)) {
  //histV1 = (TH1F*)V1file->Get(hnameV1);
  // histV2 = (TH1F*)V2file->Get(hnameV2);
  //}
  if ((h1_xlow == h2_xlow) && (h1_xup == h2_xup) && (h1_binWidth == h2_binWidth)){
    histV1 = (TH1F*)V1file->Get(hnameV1);
    histV2 = (TH1F*)V2file->Get(hnameV2);
  }
  else if((h1_xlow == h2_xlow) && (h1_xup < h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV2 = (TH1F*)V2file->Get(hnameV2); // copy histV2 

    histV1 = new TH1F(hBinTempV1->GetName(),hBinTempV1->GetTitle(),h2_nbins,h2_xlow,h2_xup);
    histV1->SetXTitle(hBinTempV1->GetXaxis()->GetTitle());
    histV1->SetYTitle(hBinTempV1->GetYaxis()->GetTitle());
    for (Int_t ibin = 1; ibin <= h2_nbins; ibin++){
      if (ibin <= h1_nbins){
	histV1->SetBinContent(ibin,hBinTempV1->GetBinContent(ibin));
      }
      else if (ibin > h1_nbins){
	histV1->SetBinContent(ibin,0.0); 
      }
    }
  }
  else if((h1_xlow == h2_xlow) && (h1_xup > h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV1 = (TH1F*)V1file->Get(hnameV1); // copy histV1 

    histV2 = new TH1F(hBinTempV2->GetName(),hBinTempV2->GetTitle(),h1_nbins,h1_xlow,h1_xup);
    histV2->SetXTitle(hBinTempV2->GetXaxis()->GetTitle());
    histV2->SetYTitle(hBinTempV2->GetYaxis()->GetTitle());
    for (Int_t ibin = 1; ibin <= h1_nbins; ibin++){
      if (ibin <= h2_nbins){
	histV2->SetBinContent(ibin,hBinTempV2->GetBinContent(ibin));
      }
      else if (ibin > h2_nbins){
	histV2->SetBinContent(ibin,0.0); 
      }
    }
  }
  else if(h1_binWidth != h2_binWidth){
    if ((h1_xlow < h2_xlow) && (h1_xup == h2_xup)){
      histV1 = (TH1F*)V1file->Get(hnameV1);

      histV2 = new TH1F(hBinTempV2->GetName(),hBinTempV2->GetTitle(),h2_nbins,h1_xlow,h2_xup);
      histV2->SetXTitle(hBinTempV2->GetXaxis()->GetTitle());
      histV2->SetYTitle(hBinTempV2->GetYaxis()->GetTitle());
      for (Int_t ibin = 1; ibin <= h1_nbins; ibin++){
	histV2->SetBinContent(ibin,hBinTempV2->GetBinContent(ibin));
      }
    }
    else if ((h2_xlow < h1_xlow) && (h1_xup == h2_xup)){
      histV2 = (TH1F*)V2file->Get(hnameV2);

      histV1 = new TH1F(hBinTempV1->GetName(),hBinTempV1->GetTitle(),h1_nbins,h2_xlow,h1_xup);
      histV1->SetXTitle(hBinTempV1->GetXaxis()->GetTitle());
      histV1->SetYTitle(hBinTempV1->GetYaxis()->GetTitle());
      for (Int_t ibin = 1; ibin <= h2_nbins; ibin++){
	histV1->SetBinContent(ibin,hBinTempV1->GetBinContent(ibin));
      }
    }
  }
  else{
    cout << "Bin Check Failed... here's what happened: " << endl;
    cout << "histV1 failed on " << hnameV1  << endl << " for file " << V1file->GetName() << endl;
    cout << "       bin info: " << h1_xlow << " " << h1_xup << " " << h1_nbins << endl;
    cout << "histV2 failed on " << hnameV2  << endl << " for file " << V2file->GetName() << endl;
    cout << "       bin info: " << h2_xlow << " " << h2_xup << " " << h2_nbins << endl;
    exit(1);
  }
  
  // Don't look at zero bin -- > Also could use this for truncation and bin setting -->Range is binlower to upper
  
  if (hname1.Contains("NumberOfTracks",TString::kExact)){
    
    std::cout << "here1" << std::endl;

    histV1->GetXaxis()->SetRangeUser(10,2000);
    histV2->GetXaxis()->SetRangeUser(10,2000);
    
  }
  else if (hname1.Contains("NumberOfGoodTracks",TString::kExact)){

    std::cout << "here2" << std::endl;

    histV1->GetXaxis()->SetRangeUser(5,250);
    histV2->GetXaxis()->SetRangeUser(5,250);

  }
  /*  else {

    std::cout << "here3" << std::endl;

    histV1->GetXaxis()->SetRangeUser(.1,1.0);
    histV2->GetXaxis()->SetRangeUser(.1,1.0); //fracion

    
  }
  */
 
  histV1->SetEntries(h1_nEntries);
  histV2->SetEntries(h2_nEntries);



  //+++**************** Get histo integrals ***********************//

  
  double V1_integral = 1.0;
  double V2_integral = 1.0;

  TH1F * hNormTempV1 = 0;
  TH1F * hNormTempV2 = 0;

  if (SetScale==1){    
    V1_integral = histV1->Integral();
    V2_integral = histV2->Integral();
  }
  else if ( (SetScale==2) || (SetScale==3) ){
    if (hname != "NumberOfTracks"){

      //    std::cout << "Using Scale for this histogram: " << hnameV1 << std::endl;

      TString hTempNameV1 = basename1;
      hTempNameV1.Append("/Tracking/Run summary/TrackParameters/GeneralProperties/NumberOfTracks_GenTk");
      hNormTempV1 = (TH1F*)V1file->Get(hTempNameV1);
      
      TString hTempNameV2 = basename2;
      hTempNameV2.Append("/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties/NumberOfTracks_GenTk");
      hNormTempV2 = (TH1F*)V2file->Get(hTempNameV2);
    }
    else{
      hNormTempV1 = (TH1F*)histV1->Clone("hNormTempV1");
      hNormTempV2 = (TH1F*)histV2->Clone("hNormTempV2");
    }

    if (SetScale==2){
      V1_integral = hNormTempV1->GetBinContent(2);
      V2_integral = hNormTempV2->GetBinContent(2);

      std::cout << "The number of single tracks for V1 is " << V1_integral << std::endl;
      std::cout << "The number of single tracks for V2 is " << V2_integral << std::endl;
    }
    else if (SetScale==3){
      V1_integral = hNormTempV1->GetEntries();
      V2_integral = hNormTempV2->GetEntries();

      //      std::cout << "The number of events for V1 is " << V1_integral << std::endl;
      //      std::cout << "The number of events for V2 is " << V2_integral << std::endl;
    }
  }
 
  //+++***NORMALIZING V1-V2****************************************

  if(V1_integral>V2_integral) {
    histV1->Scale(V2_integral / V1_integral);
    histV2->Scale(1);

    //    std::cout << "Set scale: " << V2_integral / V1_integral << std::endl;
  } 
  else if(V2_integral>V1_integral){
    histV1->Scale(1);
    histV2->Scale(V1_integral / V2_integral);

    //    std::cout << "Set scale: " << V1_integral / V2_integral << std::endl;
  }
  
  //+++**NORMALIZING V1-V2*end***************************************
  
  //+++Name the files under comparison***
  TString V1_V1run = "5_3_X (Run 208307)";
  TString V2_V2run = "7_4_X (Run 208307)";

  histV1->SetName(V1_V1run);
  histV2->SetName(V2_V2run);

  double max = 0;
  double V1max = histV1->GetBinContent(histV1->GetMaximumBin());
  double V2max = histV2->GetBinContent(histV2->GetMaximumBin());

  double min = 0;
  double V1min = histV1->GetBinContent(histV1->GetMinimumBin());
  double V2min = histV2->GetBinContent(histV2->GetMinimumBin());

  max = (V1max>V2max) ? V1max : V2max;
  min = (V1min<V2min) ? V1min : V2min;

  histV1->SetTitle("");
  histV1->SetLineStyle(1);
  histV1->GetYaxis()->SetLabelSize(0.038);
  histV1->SetLineWidth(5);
  histV1->SetLineColor(kRed);

  if (hname1.Contains("GoodTrackAlgorithm",TString::kExact)){
    histV1->GetYaxis()->SetRangeUser(5000,60000000);
  }

  if (hname1.Contains("algorithm",TString::kExact)){
    histV1->GetYaxis()->SetRangeUser(9000,200000000);
  }


  if (hname.Contains("algorithm",TString::kExact)){
    TString labels[18] = {"","","","","","InitialStep","LowPtTriplets","PixelPairs","DetachedTriplets","MixedTriplets","PixelLess","TobTec","JetCore","","MuonSeededInOut","MuonSeededOutIn","",""};
    histV1->GetXaxis()->SetRangeUser(4,17);
    /*
    float hist1algo[16];
    float hist1algotemp[16];

    for (int ibin = 1; ibin<= 15;ibin++){
      hist1algo[ibin] = histV1->GetBinContent(ibin);
      hist1algotemp[ibin] = histV1->GetBinContent(ibin);
    }

    hist1algo[6] = hist1algotemp[8];
    
    for (int ibin = 7; ibin<= 15;ibin++){
      if (ibin < 9){
	hist1algo[ibin] = hist1algotemp[ibin-1];
      }
      else{
	hist1algo[ibin] = hist1algotemp[ibin];
      }
    }

    */
    for (int ibin = 1; ibin<= 17;ibin++){
      histV1->GetXaxis()->SetBinLabel(ibin,labels[ibin].Data());
      //      histV1->SetBinContent(ibin,hist1algo[ibin]);
      //      std::cout << ibin << " hist1: " << histV1->GetBinContent(ibin) << " hist2: " << histV2->GetBinContent(ibin) << std::endl;
    }
  }




  //  histV1->SetMaximum(max*(1.1));
  //  histV1->SetMinimum(10000);
  histV1->SetStats(false);
  histV1->SetMinimum(0.);
  histV1->Draw();
  histV2->SetTitle("");
  histV2->SetLineWidth(3);
  histV2->SetLineStyle(1);
  histV2->SetLineColor(kBlue);
  histV2->SetStats(false);
  histV2->SetMinimum(0.);
  histV2->Draw("sames");

  //  mainpad->SetLogy(1);

  //  if (hname.Contains("TrackPt_ImpactPoint",TString::kExact)){
  // mainpad->SetLogx(1);
  // }
  
  if (hname1.Contains("NumberOfGoodTracks",TString::kExact)) {
    histV1->GetXaxis()->SetRangeUser(0,500);
    histV2->GetXaxis()->SetRangeUser(0,500);
  }
  else if (hname.Contains("TrackPhi_ImpactPoint",TString::kExact)){
    histV1->SetMinimum(min*(0.9));
  }
  else if (hname.Contains("Chi2oNDF",TString::kExact)) {
    histV1->GetXaxis()->SetRangeUser(0,10);
    histV2->GetXaxis()->SetRangeUser(0,10);
  }
  else if (hname.Contains("TrackPt_ImpactPoint",TString::kExact)){
    //    histV1->GetXaxis()->SetRangeUser(0,10);
    //    histV2->GetXaxis()->SetRangeUser(0,10);
  }
  
  if (hname.Contains("vtxNbr")){
    histV1->GetXaxis()->SetTitle("Number of Primary Vertices per Event");
    histV1->GetYaxis()->SetTitle("Number of Events");
  }

  


  mainpad->Update();

  /*  TPaveStats *st1 = (TPaveStats*)(histV1->GetListOfFunctions()->FindObject("stats"));
  if ( (hname.Contains("FractionOfGoodTracks",TString::kExact)) || (hname1.Contains("GoodTrackChi2Prob",TString::kExact)) ){
    st1->SetX1NDC(0.57);
  }
  else if ( (hname.Contains("TrackPhi_ImpactPoint",TString::kExact)) || (hname.Contains("TrackEta_ImpactPoint",TString::kExact)) ){
    st1->SetX1NDC(0.54);
  }
  else{
    st1->SetX1NDC(0.77);
  }
  st1->SetY1NDC(0.80);

  if ( (hname.Contains("FractionOfGoodTracks",TString::kExact)) || (hname1.Contains("GoodTrackChi2Prob",TString::kExact)) ){
    st1->SetX2NDC(0.78);
  }
  else if ( (hname.Contains("TrackPhi_ImpactPoint",TString::kExact)) || (hname.Contains("TrackEta_ImpactPoint",TString::kExact)) ){
    st1->SetX2NDC(0.75);
  }
  else{
    st1->SetX2NDC(0.98);
  }
  st1->SetY2NDC(0.97);

  Double_t defaulth = st1->GetY2NDC() - st1->GetY1NDC();
  Double_t gaph = 0.02;
  TPaveStats *st2 = (TPaveStats*)(histV2->GetListOfFunctions()->FindObject("stats"));
  if ( (hname.Contains("FractionOfGoodTracks",TString::kExact)) || (hname1.Contains("GoodTrackChi2Prob",TString::kExact)) ){ 
    st2->SetX1NDC(0.57);  
  }
  else{
    st2->SetX1NDC(0.77);
  }

  if ( (hname.Contains("TrackPhi_ImpactPoint",TString::kExact)) || (hname.Contains("TrackEta_ImpactPoint",TString::kExact)) ){
    st2->SetY1NDC(0.80);
  }
  else{
    st2->SetY1NDC(st1->GetY1NDC() - 1.0*defaulth - gaph);
  }

  if ( (hname.Contains("FractionOfGoodTracks",TString::kExact)) || (hname1.Contains("GoodTrackChi2Prob",TString::kExact)) ){ 
    st2->SetX2NDC(0.78);    
  }
  else{
    st2->SetX2NDC(0.98);
  }

  if ( (hname.Contains("TrackPhi_ImpactPoint",TString::kExact)) || (hname.Contains("TrackEta_ImpactPoint",TString::kExact)) ){
    st2->SetY2NDC(0.97);
  }
  else{
    st2->SetY2NDC(st1->GetY1NDC() - gaph);
  }
  */
  if ( (hname.Contains("NumberOfTracks",TString::kExact)) || (hname.Contains("vtxNbr",TString::kExact)) || (hname.Contains("algorithm",TString::kExact))){
    TLegend *leg = new TLegend(0.5,0.86,0.6,0.97);
    leg->SetTextSize(0.042);
    leg->SetTextFont(42);
    leg->SetFillColor(10); 
    leg->SetBorderSize(1); // no frame, no shadow
    leg->AddEntry(histV1, "5_3_X", "L" );
    leg->AddEntry(histV2, "7_4_X", "L" );
    leg->Draw("SAME");
  }
  else {
    //    TLegend *leg = new TLegend(0.8,0.8,0.91,0.91);
    TLegend *leg = new TLegend(0.45,0.25,0.55,0.35);
    leg->SetTextSize(0.042);
    leg->SetTextFont(42);
    leg->SetFillColor(10); 
    leg->SetBorderSize(0); // no frame, no shadow
    leg->AddEntry(histV1, "Run I RECO", "L" );
    leg->AddEntry(histV2, "Run II RECO", "L" );
    leg->Draw("SAME");
  }

  TPaveText * tpt = new TPaveText();
  tpt->SetBorderSize(0);
  tpt->SetTextFont(42);
  tpt->SetTextSize(0.042);
  tpt->SetFillColor(10);
  tpt->SetX1NDC(0.42);
  tpt->SetY1NDC(0.15);
  tpt->SetX2NDC(0.9);
  tpt->SetY2NDC(0.2);
  tpt->AddText("CMS Preliminary #sqrt{s} = 8 TeV");
  tpt->Draw("SAME");




  // Draw ratio histogram
  //   if (DrawRatio){
  //   canvas->cd();
  //   TPad* respad = new TPad("respad","respad",0.0,0.81,1.0,0.98);
  //   respad->SetTopMargin(1.05);
  //   respad->Draw();
  //   respad->cd();
  //   TH1F* hratio = (TH1F*) histV2->Clone("hratio");



  // if (hname1.Contains("NumberOfTracks",TString::kExact)){
    
  //   std::cout << "here1" << std::endl;
  //   //hratio->SetMaximum(1.5);
  //   // hratio->SetMinimum(0.5);
  //   hratio->GetXaxis()->SetRangeUser(10,2000);

    
  // }
  // else if (hname1.Contains("NumberOfGoodTracks",TString::kExact)){

  //   std::cout << "here2" << std::endl;
  //   //    hratio->SetMaximum(2.0);
  //   //hratio->SetMinimum(0.5);
  //   hratio->GetXaxis()->SetRangeUser(5,250);


  // }
  // else {

  //   //    std::cout << "here3" << std::endl;
  //   //hratio->SetMaximum(2.0);
  //   // hratio->SetMinimum(0);
  //   //    hratio->GetXaxis()->SetRangeUser(.1,1.0); //fraction of good
  //   hratio->GetXaxis()->SetRangeUser(4,17); // algo
  //   // hratio->GetYaxis()->SetRangeUser(0,2.0); // algo zoom
  // }

  
  //   if (hname.Contains("Chi2oNDF",TString::kExact)) {
  //     hratio->GetXaxis()->SetRangeUser(0,10);
  //   }/*
  //   else if (hname1.Contains("NumberOfGoodTracks",TString::kExact)) {
  //     hratio->GetXaxis()->SetRangeUser(0,500);
    
  //     for (int jk =0; jk<= 500; jk++){
  // 	std::cout << hratio->GetBinContent(jk) << " " << histV1->GetBinContent(jk) << " " << (hratio->GetBinContent(jk) / histV1->GetBinContent(jk)) << std::endl;

  //     }
    
  //   }  */
  //   hratio->Divide(histV1);
  //   if (hname.Contains("TrackPt_ImpactPoint",TString::kExact)){
  //     hratio->SetMaximum(hratio->GetMaximum()*1.1); // used this for min bias 
  //     hratio->SetMinimum(hratio->GetMinimum()*0.9); // used this for min bias 
  //     //      hratio->SetMaximum(1.2);
  //     //      hratio->SetMinimum(0.6); // used for zmumu + jetht 
  //   }    
  //   else if (hname1.Contains("GoodTrackChi2oNDF",TString::kExact)) {
  //     hratio->SetMaximum(1.4);
  //     hratio->SetMinimum(0.8); // used for all samples nology for chi2ndof
  //   }
  //   else if (hname1.Contains("Chi2oNDF",TString::kExact)) {
  //     hratio->SetMaximum(1.2);
  //     hratio->SetMinimum(0.6); // used for all samples nology for chi2ndof
  //   }
  //   /*    else{
  //     hratio->SetMaximum(hratio->GetMaximum()*1.1);
  //     hratio->SetMinimum(hratio->GetMinimum()*0.9);
  //   }
  //   */
  //   //if (hratio->GetMinimum()==0.0) hratio->SetMinimum(1.0/hratio->GetMaximum());
  //   //    hratio->SetMinimum(1.0/hratio->GetMaximum());
  //   hratio->GetYaxis()->SetLabelSize(0.1);
  //   hratio->GetXaxis()->SetLabelSize(0);
  //   hratio->GetXaxis()->SetTitleSize(0);
  //   hratio->GetYaxis()->SetTitleSize(0.22);
  //   hratio->GetYaxis()->SetTitleOffset(0.26);
  //   hratio->GetYaxis()->SetLabelSize(0.2);
  //   hratio->GetYaxis()->SetNdivisions(5);
  //   hratio->GetYaxis()->SetTitle("74X/53X");
  //   hratio->SetTitle("");
  //   hratio->SetStats(0);
  //   hratio->Draw();
  // }

  TString filename = hname;

  if (hname.Contains("vtxNbr")){
    filename = "NumberOfPrimaryVertices";
  }

  if (dirname2.Contains("highPurityTracks/pt_1/GeneralProperties",TString::kExact)){    
    filename.Prepend("RunComparison/GoodTracks_");
  }
  else if (dirname2.Contains("highPurityTracks/pt_1/HitProperties",TString::kExact)){
    filename.Prepend("RunComparison/GoodTracks_");
  }
  else{
    filename.Prepend("RunComparison/");
  }

  filename.Append(".png");

  canvas->Print(filename);
  canvas->Close();
  //  canvas->Write();

  if ( histV1 ) {histV1->Delete();}
  if ( histV2 ) {histV2->Delete();}

  if ( hNormTempV1 ) {hNormTempV1->Delete();}
  if ( hNormTempV2 ) {hNormTempV2->Delete();}

  //  if ( hBinTempV1 ) {hBinTempV1->Delete();} // why cant this work?! 
  //  if ( hBinTempV2 ) {hBinTempV2->Delete();}

  return true;
}

void setTDRStyle() {

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  
  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);

  // Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

  // For the Global title:
  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.052, "XYZ");
  tdrStyle->SetTitleXOffset(0.875);
  tdrStyle->SetTitleYOffset(1.05);

  // For the axis labels:
  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:
  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  // Postscript options:
  tdrStyle->SetPaperSize(20.,20.);

  tdrStyle->cd();

}

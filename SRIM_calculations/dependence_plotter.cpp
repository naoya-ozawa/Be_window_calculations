#include <bits/stdc++.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLatex.h>
#include <TRint.h>
using namespace std;

int main(int argc, char** argv){
	TRint rootapp("app",&argc,argv);
	TCanvas *c1 = new TCanvas();
	c1->Divide(2,2);


  // Part 1: dependence on the Be thickness
  double Be_thickness[3] = {20.0,25.0,30.0}; // um
  double Be_thickness_err[3] = {0.0,0.0,0.0};

  c1->cd(1);
  // When E = 113 MeV, T_He = 8 mm
  double energyloss_113mev_8mm[3] = {113.0-99.7,113.0-96.3,113.0-92.9};
  double energyloss_113mev_8mm_err[3] = {0.2,0.2,0.2};

  TGraphErrors *g_Be_thicknessdep_113mev = new TGraphErrors(3,Be_thickness,energyloss_113mev_8mm,Be_thickness_err,energyloss_113mev_8mm_err);
  g_Be_thicknessdep_113mev->SetTitle("Dependence on the Be Thickness;Total Be Thickness T_{Be} (#mum);Net Energy Loss E_{loss} (MeV)");
  g_Be_thicknessdep_113mev->Draw("AP*");

  TF1 *f_Be_thickness = new TF1("Be Thickness Fit","[0]+[1]*x");
  f_Be_thickness->SetParameters(1.0,1.0);
  g_Be_thicknessdep_113mev->Fit(f_Be_thickness);

  double C_Be = f_Be_thickness->GetParameter(1); // MeV/um
  double C_Be_err = f_Be_thickness->GetParError(1);
  TLatex *l_Be_thickness = new TLatex();
  l_Be_thickness->DrawLatex(20.,20.,Form("C_{Be} = %g#pm%3.2f MeV/#mum",C_Be,C_Be_err));

  // Part 2: dependence on the He thickness
  double He_thickness[3] = {8.0,16.0,24.0}; // mm
  double He_thickness_err[3] = {0.0,0.0,0.0};

  c1->cd(2);
  // When T_Be = 20 um, in_energy = 113 MeV
  double energyloss_113mev_20um[3] = {113.0-99.7,113.0-99.0,113.0-98.3};
  double energyloss_113mev_20um_err[3] = {0.2,0.5,0.2};

  TGraphErrors *g_He_thicknessdep_113mev = new TGraphErrors(3,He_thickness,energyloss_113mev_20um,He_thickness_err,energyloss_113mev_20um_err);
  g_He_thicknessdep_113mev->SetTitle("Dependence on He Thickness;Total He Thickness T_{He} (mm);Net Energy Loss E_{loss} (MeV)");
  g_He_thicknessdep_113mev->Draw("AP*");

  TF1 *f_He_thickness = new TF1("He Thickness Fit","[0]+[1]*x");
  f_He_thickness->SetParameters(1.0,1.0);
  g_He_thicknessdep_113mev->Fit(f_He_thickness);

  double C_He = f_He_thickness->GetParameter(1); // MeV/mm
  double C_He_err = f_He_thickness->GetParError(1);
  TLatex *l_He_thickness = new TLatex();
  l_He_thickness->DrawLatex(8.,14.7,Form("C_{He} = %g#pm%4.3f MeV/mm",C_He,C_He_err));

  // Part 3: dependence on the incident beam energy
  double in_energy[6] = {109.0,113.0,116.0,122.0,126.0,130.0}; // MeV
  double in_energy_err[6] = {0.,0.,0.,0.,0.,0.};

  TMultiGraph *mg_energydep = new TMultiGraph();
  mg_energydep->SetTitle("Dependence on the Incident Beam Energy;Incident Beam Energy E_{incident} (MeV);Net Energy Loss E_{loss} (MeV)");

  c1->cd(3);
  // When T = 20 um, angle = 0deg
  double energyloss_20um_0deg[6] = {109.0-96.0,113.0-99.7,116.0-103.4,122.0-109.4,126.0-113.8,130.0-118.1};
  double energyloss_20um_0deg_err[6] = {0.2,0.2,0.1,0.4,0.2,0.1};

  TGraphErrors *g_energydep_20um = new TGraphErrors(6,in_energy,energyloss_20um_0deg,in_energy_err,energyloss_20um_0deg_err);
  g_energydep_20um->SetMarkerColor(2);
  g_energydep_20um->SetTitle("10 #mum Be + 8 mm He + 10 #mum Be");
  TF1 *f_energydep_20um = new TF1("10 #mum Be + 8 mm He + 10 #mum Be","[0]+[1]/x+[2]*x*x+[3]");
  f_energydep_20um->SetTitle("Model (C_{E0} and C_{E1}) fit to 10 #mum Be case");
  f_energydep_20um->SetParameters(1.0,1.0,1.0,1.0);
//  f_energydep_20um->FixParameter(1,0.0);
  f_energydep_20um->FixParameter(2,0.0);
  f_energydep_20um->FixParameter(3,C_Be*20.0+C_He*8.0);
  f_energydep_20um->SetLineColor(2);
  g_energydep_20um->Fit(f_energydep_20um);
  double C_E0 = f_energydep_20um->GetParameter(0);
  double C_E0_err = f_energydep_20um->GetParError(0);
  double C_E1 = f_energydep_20um->GetParameter(1);
  double C_E1_err = f_energydep_20um->GetParError(1);

  // When T = 30 um, angle = 0deg
  double energyloss_30um_0deg[6] = {109.0-89.0,113.0-92.9,116.0-96.8,122.0-103.1,126.0-107.6,130.0-112.1};
  double energyloss_30um_0deg_err[6] = {0.2,0.2,0.2,0.2,0.2,0.9};

  TGraphErrors *g_energydep_30um = new TGraphErrors(6,in_energy,energyloss_30um_0deg,in_energy_err,energyloss_30um_0deg_err);
  g_energydep_30um->SetMarkerColor(4);
  g_energydep_30um->SetTitle("15 #mum Be + 8 mm He + 15 #mum Be");
  TF1 *f_energydep_30um = new TF1("15 #mum Be + 8 mm He + 15 #mum Be","[0]+[1]/x+[2]*x*x+[3]",105.,135.);
  f_energydep_30um->SetTitle("Estimated curve based on 10 #mum Be case");
  f_energydep_30um->SetParameters(f_energydep_20um->GetParameter(0),f_energydep_20um->GetParameter(1),f_energydep_20um->GetParameter(2),C_Be*30.0+C_He*8.0);
//  f_energydep_30um->FixParameter(1,0.0);
//  f_energydep_30um->FixParameter(2,0.0);
//  f_energydep_30um->FixParameter(3,C_Be*30.0+C_He*8.0);
  f_energydep_30um->SetLineColor(4);

  mg_energydep->Add(g_energydep_20um);
  mg_energydep->Add(g_energydep_30um);

  mg_energydep->Draw("AP*");
  f_energydep_20um->Draw("SAME");
  f_energydep_30um->Draw("SAME");
//  g_energydep_30um->Fit(f_energydep_30um);

  c1->cd(3)->BuildLegend();

  c1->cd(4);

  TLatex *l_model = new TLatex();
  l_model->DrawLatex(0.2,0.8,"Model Assumption:");
  l_model->DrawLatex(0.23,0.7,"E_{loss} = C_{E0} + #frac{C_{E1}}{E_{incident}} + C_{Be}T_{Be} + C_{He}T_{He}");
  l_model->DrawLatex(0.23,0.5,Form("C_{E0} = %3.2f #pm %3.2f MeV",C_E0,C_E0_err));
  l_model->DrawLatex(0.23,0.4,Form("C_{E1} = %3.2f #pm %3.2f MeV MeV(incident)",C_E1,C_E1_err));


  rootapp.Run();
  c1->Update();
  c1->Modified();

  return 0;
}

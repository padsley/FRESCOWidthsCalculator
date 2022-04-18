#include "/home/padsley/codes/nuclear_dynamics_calculator/function_library.h"
#include <TMath.h>
#include <TGraph.h>
#include <iostream>
#include <TCanvas.h>
#include <TParticlePDG.h>
#include <TDatabasePDG.h>
#include <TMultiGraph.h>

double Sn = 6.76116; //MeV
double Ex = 8.068; //MeV

int Ln =2;

int J2 = 3;

double DWUCKWidth = 3.4230E-1*1.e6; //eV

TSpline3 *sp;

double SplineFunction(double *x, double *pars)
{
    return sp->Eval(x[0]);
}

void PartialWidthCalculation(double a=1., double sigma_a = 0.1, double R=7.)
{
//     Ex = Sn+0.1;//temp checking thing
//     DWUCKWidth =  6.0657E-4*1.e6;//eV
    
//     TCanvas *c1 = new TCanvas("c1","c1",800,800);
    
    TGraph *gWfn = new TGraph();
    gWfn->SetName("gWfn");
    
    TGraph *gPartWidth = new TGraph();
    gPartWidth->SetName("gPartWidth");
    
    TGraph *gPenetrability = new TGraph();
    gPenetrability->SetName("gPenetrability");
    
    TGraph *gANC = new TGraph();
    gANC->SetName("gANC");
    
    TGraph *gWhittakerRatio = new TGraph();
    gWhittakerRatio->SetName("gWhittakerRatio");
    
    TGraph *gWhittakerRatio2 = new TGraph();
    gWhittakerRatio2->SetName("gWhittakerRatio2");
    
    TGraph *gDWUCKRatio = new TGraph();
    gDWUCKRatio->SetName("gDWUCKRatio");
    
    //// open file wave function (fort.46)
    ifstream infile("fort.46");
    //    ifstream infile(Form("./fort.46/fort_%2.0f_1_pot_1_NEW.46", Ex_17O[i]));
    //    cout << Form("./fort.46/fort_%2.0f_1_pot_1_NEW.46", Ex_17O[i]) << endl;
    if (!infile) cout << "no file" << endl;
    
    //// skip first lines (read channel 3 : 13C+alpha)
    Char_t line[256];
    for (Int_t j = 0; j < 594; j++) infile.getline(line, sizeof(line));
    
//     double ANC_Const = 0.000238082;
    
    //// read data
    Double_t u_r, b, whit, c, d, wf2;
    
//     cout << "reduced mass: " << mu_calc(1.,20.) << endl;
    
//     cout << "hbarc: " << TMath::Hbar()/TMath::Qe()*TMath::C()*1.e15 << " eV fm" << endl;
    
    TDatabasePDG *pdg = new TDatabasePDG();
    pdg->ReadPDGTable("/home/padsley/codes/root_build/etc/pdg_table.txt");
    
    TParticlePDG *neutron = pdg->GetParticle("neutron");
    cout << "neutron mass: " << neutron->Mass()*1000 << " MeV/c/c" << endl;
    
    double constant = 0.5*pow(TMath::Hbar()/TMath::Qe()*TMath::C()*1.e15,2.)  / mu_calc(1.,20.) /( neutron->Mass()*1000.*1e6); //1e15 for fm, 1e6 for MeV - formulate everything in eV
    
    cout << "constant: " << constant << endl;
    
//     double S = pow(0.191999,2.); //Spectroscopic factor - this has to change
    
    cout << endl << "**************************" << endl << endl;
    
    cout << "Neutron energy: " << Ex - Sn << endl << endl;
    
    double radius = 0;
    
    double S = pow(a,2.);
    
    if(infile.is_open())
    {
        while(infile >> radius >> b >> u_r >> whit >> c >> d)
        {
            
            double ANC = S*pow(u_r,2)/pow(whit,2);
            gANC->SetPoint(gANC->GetN(),radius,ANC);
            
            wf2 = pow(u_r/radius,2);
//             cout << "wf2= " << wf2 << endl;
            
            gWfn->SetPoint(gWfn->GetN(),radius,wf2);
            
            //       red_width_17O = cst_17O * radius * wf2 * S; // in MeV 
            
            double reduced_width = constant * radius * wf2 * S;
//             cout << "reduced_width: " << reduced_width << endl;
            
            double P_l = penetrability(0, 10, 1, 20, Ln, Ex - Sn, radius);
//             cout << "P_l: " << P_l << endl;
            gPenetrability->SetPoint(gPenetrability->GetN(),radius,P_l);
            
            double partial_width = 2 * reduced_width * P_l; // in eV
            
//             cout << "Constant: " << pow(TMath::Hbar()/TMath::Qe()*TMath::C()*1.e15,2.)/ (mu_calc(1.,20.)*( neutron->Mass()*1000.*1e6)) << endl;
//             cout << "other PW calculation: " << P_l * S * wf2 * pow(TMath::Hbar()/TMath::Qe()*TMath::C()*1.e15,2.)/ (mu_calc(1.,20.)*( neutron->Mass()*1000.*1e6)) / (radius/1.e15)*pow(TMath::C(),2.) << endl;
            
            gPartWidth->SetPoint(gPartWidth->GetN(),radius,partial_width);
            
            gDWUCKRatio->SetPoint(gDWUCKRatio->GetN(),radius,partial_width/DWUCKWidth);
            
//             ANC_Const = ANC;
            
            gWhittakerRatio->SetPoint(gWhittakerRatio->GetN(),radius,ANC);
        
            gWhittakerRatio2->SetPoint(gWhittakerRatio2->GetN(),ANC,radius);
            
        }
    }
    
    for(int i=0;i<gWhittakerRatio->GetN();i++)
    {
        gWhittakerRatio->SetPoint(i,gWhittakerRatio->GetPointX(i),gWhittakerRatio->GetPointY(i)/gWhittakerRatio->GetPointY(gWhittakerRatio->GetN()-1));
     
        gWhittakerRatio2->SetPoint(i,gWhittakerRatio2->GetPointX(i)/gWhittakerRatio2->GetPointX(gWhittakerRatio2->GetN()-1),gWhittakerRatio2->GetPointY(i));
    }
    
    infile.close();
    
    cout << "penetrability: " << penetrability(0, 10, 1, 20, Ln, Ex - Sn, R) << endl << endl;
    
    gWhittakerRatio->Draw("AL");
    
    double WhittakerRatioLimit = 0.99;
    
    cout << "Finding the radius where the Whittaker ratio is at " <<  WhittakerRatioLimit*100 <<  "%: " << gWhittakerRatio2->Eval(WhittakerRatioLimit) << " fm" << endl;
    
    cout << "Partial width at R=" << R << " fm: " << gPartWidth->Eval(R) << " eV +- " << gPartWidth->Eval(R)*2*sigma_a/a << endl;
    
    cout << "Partial width at R=" << gWhittakerRatio2->Eval(WhittakerRatioLimit) << " fm: " << gPartWidth->Eval(gWhittakerRatio2->Eval(WhittakerRatioLimit)) << " eV +- " << gPartWidth->Eval(gWhittakerRatio2->Eval(WhittakerRatioLimit))*2*sigma_a/a << endl;
    
    cout << endl << "**************************" << endl << endl;
    
//     gANC->Draw("AL");
//     gPartWidth->Draw("AL");
//     gPenetrability->Draw("AL");
//     gWfn->Draw("AL");
    
    cout << "ANC at chosen radius " << R << " is " << gANC->Eval(R) << endl;
    
    TMultiGraph *mg = new TMultiGraph();
    gDWUCKRatio->SetLineColor(1);
    mg->Add(gDWUCKRatio);
    
    gWhittakerRatio->SetLineColor(2);
    mg->Add(gWhittakerRatio);
    
//     c1->SetLogy();
//     mg->GetXaxis()->SetRangeUser(0,15);
//     mg->Draw("AL");
//     mg->SetMinimum(1.e-3);
//     c1->Update();
    
//     return gPartWidth->Eval(R);
}

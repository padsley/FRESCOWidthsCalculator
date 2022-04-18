{
//     gROOT->ProcessLine(".L PartialWidthCalculation.cpp");
    
    TF1 *f2 = new TF1("f2","[0] + [1] * x + [2] * x * x",-2,2);
    
    TGraphErrors *ge1 = new TGraphErrors(); //do low spin first then high spin
    ge1->SetName("PartialWidth1");
    
    TGraphErrors *ge2 = new TGraphErrors();
    ge2->SetName("PartialWidth2");
    
    // 3/2 case
    ge1->SetPoint(0,0.1,1506.23);
    ge2->SetPoint(0,0.1,1612.2);
//     ge1->SetPointError(0,0,0.197);
    
    ge1->SetPoint(1,0.2,1499.79);
    ge2->SetPoint(1,0.2,1614.34);
//     ge1->SetPointError(1,0,0.193);    
    
    ge1->SetPoint(2,0.3,1495.79);
    ge2->SetPoint(2,0.3,1618.53);
//     ge1->SetPointError(2,0,0.195);
    
    ge1->SetPoint(3,0.4,1493.17);
    ge2->SetPoint(3,0.4,1624.08);
//     ge1->SetPointError(3,0,0.196);
    
    ge1->SetPoint(4,0.5,1491.72);
    ge2->SetPoint(4,0.5,1630.63);
//     ge1->SetPointError(4,0,0.194);
    
    ge1->SetPoint(5,0.75,1491.05);
    ge2->SetPoint(5,0.75,1649.66);
//     ge1->SetPointError(5,0,0.194);
    
    ge1->SetPoint(6,1.0,1493.18);
    ge2->SetPoint(6,1.0,1670.82);
//     ge1->SetPointError(6,0,0.195);
    
    ge1->SetPoint(7,1.25,1496.5);
    ge2->SetPoint(7,1.25,1692.16);
//     ge1->SetPointError(7,0,0.197);
    
    ge1->SetPoint(8,1.5,1500.29);
    ge2->SetPoint(8,1.5,1713.85);
//     ge1->SetPointError(8,0,0.195);
    
    ge1->Draw("AL");
    
    TFitResultPtr r = ge1->Fit("pol2","S");
    
    f2->SetParameter(0,r->Parameter(0));
    f2->SetParameter(1,r->Parameter(1));
    f2->SetParameter(2,r->Parameter(2));
    
    cout << "Partial width at resonance energy: " << f2->Eval(-1.3068) << endl;
    
    ge2->Draw("AL");
    
    r = ge2->Fit("pol2","S");
    f2->SetParameter(0,r->Parameter(0));
    f2->SetParameter(1,r->Parameter(1));
    f2->SetParameter(2,r->Parameter(2));
    
    cout << "Partial width at resonance energy: " << f2->Eval(-1.3068) << endl;
    
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(ge1);
    ge2->SetLineColor(2);
    ge2->SetMarkerColor(2);
    mg->Add(ge2);
    
    TGraphErrors *geR = new TGraphErrors();
    geR->SetName("geR");
    
    geR->SetPoint(0,0.1,6.76294);
    geR->SetPoint(1,0.2,6.75899);
    geR->SetPoint(2,0.3,6.75583);
    geR->SetPoint(3,0.4,6.75264);
    geR->SetPoint(4,0.5,6.74983);
    geR->SetPoint(5,0.75,6.74332);
    geR->SetPoint(6,1.0,6.73802);
    geR->SetPoint(7,1.25,6.73413);
    geR->SetPoint(8,1.5,6.73035);
    
//     geR->Draw("AL");
    
//     mg->Draw("AL");
    
//     TGraphErrors *grint = new TGraphErrors();
//     grint->SetName("grint");
//     grint->SetPoint(0,-1.428,0);
//     
//     (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint);
//     
//     cout << grint->GetX()[0] << "\t" << grint->GetY()[0] << "\t" << grint->GetErrorY(0) << endl;
//     
// //     // 5/2 case
// //     
//     ge2->SetPoint(0,0.1,1.075);
//     ge2->SetPointError(0,0,0.140);
//     
//     ge2->SetPoint(1,0.2,1.077);
//     ge2->SetPointError(1,0,0.140);    
//     
//     ge2->SetPoint(2,0.3,1.077);
//     ge2->SetPointError(2,0,0.140);
//     
//     ge2->SetPoint(3,0.4,1.078);
//     ge2->SetPointError(3,0,0.141);
//     
//     ge2->SetPoint(4,0.5,1.078);
//     ge2->SetPointError(4,0,0.141);
//     
//     ge2->SetPoint(5,0.75,1.080);
//     ge2->SetPointError(5,0,0.143);
//     
//     ge2->SetPoint(6,1.0,1.084);
//     ge2->SetPointError(6,0,0.141);
//     
//     ge2->SetPoint(7,1.25,1.089);
//     ge2->SetPointError(7,0,0.141);
//     
//     ge2->SetPoint(8,1.5,1.095);
//     ge2->SetPointError(8,0,0.144);
//     
//     ge2->Draw("AP");
//     ge2->GetXaxis()->SetTitle("Binding Energy [MeV]");
//     ge2->GetYaxis()->SetTitle("#Gamma_{n0} [keV]");
//     ge2->GetXaxis()->CenterTitle();
//     ge2->GetYaxis()->CenterTitle();
//     
//     r = ge2->Fit("pol2","S");
//     
//     f2->SetParameter(0,r->Parameter(0));
//     f2->SetParameter(1,r->Parameter(1));
//     f2->SetParameter(2,r->Parameter(2));
//     
//     cout << "Partial width at resonance energy: " << f2->Eval(-1.428) << endl;
//     
//     grint->SetPoint(0,-1.428,0);
//     
//     (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint);
//     
//     cout << grint->GetX()[0] << "\t" << grint->GetY()[0] << "\t" << grint->GetErrorY(0) << endl;
}

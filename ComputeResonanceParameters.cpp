{
    ifstream mInput;
    mInput.open("fort.44");
    
    double Ecm = 0, delta = 0, a, b, c, d, e;
    
    TGraph *gPS = new TGraph();
    gPS->SetName("gPS");
    
    TGraph *gPS2 = new TGraph();
    gPS2->SetName("gPS2");
    
    TGraph *gGamma = new TGraph();
    gGamma->SetName("gGamma");
    
    while(mInput >> Ecm >> delta >> a >> b >> c >> d >>e)
    {
        gPS->SetPoint(gPS->GetN(),Ecm,delta);
        gPS2->SetPoint(gPS2->GetN(),delta,Ecm);
    }
    
    gPS->Draw("AL");
    
//     gPS2->Draw("AL");
 
    std::cout << "Resonance Energy: " << gPS2->Eval(90.) << std::endl;
    
    double Er = gPS2->Eval(90.);
        
    double StepForWidth = 0.01;
    
    std::cout << "Gamma = " << 2*(Er - gPS2->Eval(45.)) << std::endl;

    double Gamma = 2*(Er - gPS2->Eval(45.));
    
    std::cout << "Gamma2 = " << 2*(gPS2->Eval(135.) - Er) << std::endl;
    
//     std::cout << "Gamma3 = " << 
    
    gPS->Draw("AL");
    
    TLine *lEr = new TLine(Er,0,Er,150);
    lEr->SetLineColor(2);
    lEr->Draw("same");
    
    TLine *lGammaLow = new TLine(Er - 0.5*Gamma,0,Er - 0.5*Gamma,150);
    lGammaLow->SetLineColor(2);
    lGammaLow->SetLineStyle(2);
    lGammaLow->Draw("same");
    
    TLine *lGammaHigh = new TLine(Er + 0.5*Gamma,0,Er + 0.5*Gamma,150);
    lGammaHigh->SetLineColor(2);
    lGammaHigh->SetLineStyle(2);
    lGammaHigh->Draw("same");
    
}

{
    //Phil Adsley - this is an horribly hacky code using ROOT to call FRESCO and mess around with it a bit to:
    //  (1) Get the right central potential depth to give a resonance in the right place, and
    //  (2) find the single-particle width from the slope of the phase-shift function and then calculate the actual width by comparing the data to a transfer reaction differential cross section
    
    // To use this code you need (a) a working FRESCO input for your reaction and (b) a FRESCO search file which will be used at the end of find a minimisation for the spectroscopic factor for the reaction. This code should NOT be used for any initial work on e.g. which orbital angular momentum transfer works best because it's very very slow (like me) and will generally not be the right tool for that. In addition, you must always be very careful to check these results because using this code might cause FRESCO to go into a region in which it's rather numerically upset and the results are then untrustworthy.
    
    //THESE ARE THE THINGS TO CHANGE
    
    TString FrescoInput = ""; //the name of the FRESCO input for your calculations - end it with .in because that's the convention that I use and I wrote this for me and didn't think about other people
    TString SfrescoInput = ""; //the name of the sFRESCO input for your calculations which should be calling the FRESCO input within itself - end the filename with .search
    
    int ell = 1; //orbital angular momentum for the transfer reaction
    
    double Er = 30; //resonance energy in keV
    
    
    //Store the output information in 
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //          Calculate the right binding potential for the resonance
    //
    //
    ///////////////////////////////////////////////////////////////////////////////
    
    
    
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    //          Calculate the single-particle width
    //
    //
    ///////////////////////////////////////////////////////////////////////////////
    
    
    std::cout << "The single-particle width is " << Gamma_SP << " eV" << std::endl;
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    //
    // Got the right binding pot, now run SFresco search, get Spectroscopic factor, calculate final answer
    //
    //
    ///////////////////////////////////////////////////////////////////////////////
    
    
    //sfresco search
    
    
    //Extract the spectroscopic factor
    
    

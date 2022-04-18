{
    
    string filename="ne20_d_p_8068_FR.in";
    
    double be = 0;
    
//     gROOT->ProcessLine(".! rm PartialWidth.dat");
    ofstream mOutput;
    mOutput.open("PartialWidth.dat");
    mOutput.close();
    mOutput.open("PartialWidthFixed.dat");
    mOutput.close();
    //The lines above clear the files
    
    double StepSize = 0.05;
    
    std::cout << Form(".! sed -i \"s/be=3.05/be=0.05/\" %s",filename.c_str()) << std::endl;
    gROOT->ProcessLine(Form(".! sed -i \"s/be=3.05/be=0.05/\" %s",filename.c_str()));
    
    for (double be=0.05;be<3.0;be+=StepSize)
    {
        gROOT->ProcessLine(".! /home/padsley/codes/FRESCO/fres/source/sfresco < ne20_d_p_8068_CM.batch > tmp.out");
        
        gROOT->ProcessLine(Form(".! root -l -b PartialWidthCalculation.cpp\\(1.0,0.0,7.0,%f\\)",be));
        
        std::cout << Form(".! sed -i \"s/be=%4.2lf/be=%4.2lf/\" %s",be,be+StepSize,filename.c_str()) << std::endl;
        gROOT->ProcessLine(Form(".! sed -i \"s/be=%4.2lf/be=%4.2lf/\" %s",be,be+StepSize,filename.c_str()));
        
        gROOT->ProcessLine(Form(".! cp search.plot figures/search_%f.plot",be));
        
    }
    
    
    
    gROOT->ProcessLine(".q");
}

#ifndef LARLITE_MUONDECAY_CXX
#define LARLITE_MUONDECAY_CXX

#include "MuonDecay.h"

namespace larlite {

  bool MuonDecay::initialize() {

    //
    // This function is called in the beginning of event loop
    // Do all variable initialization you wish to do here.
    // If you have a histogram to fill in the event loop, for example,
    // here is a good place to create one on the heap (i.e. "new TH1D"). 
    //

    _electron_E = new TH1D("electron_energy","title;x;y",100,0,100);

    return true;
  }
  
  bool MuonDecay::analyze(storage_manager* storage) {

    auto event_shower=storage->get_data<event_mcshower>("mcreco");

    int c=0;
    while(c<event_shower->size()){

      auto shower=event_shower->at(c);

      std::cout<<"This shower's pdg is "<<shower.PdgCode()<<"\n";

      c++;

      if(shower.PdgCode()!=11 || shower.MotherPdgCode()!=13 || shower.Process()!="muMinusCaptureAtRest"){

        //ignore this iteration of the loop                                                           
        continue;
      }

      double electron_energy = shower.Start().E();

      // Fill histogram                                                                               
      _electron_E->Fill(electron_energy);
   }     
  
    //
    // Do your event-by-event analysis here. This function is called for 
    // each event in the loop. You have "storage" pointer which contains 
    // event-wise data. To see what is available, check the "Manual.pdf":
    //
    // http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
    // 
    // Or you can refer to Base/DataFormatConstants.hh for available data type
    // enum values. Here is one example of getting PMT waveform collection.
    //
    // event_fifo* my_pmtfifo_v = (event_fifo*)(storage->get_data(DATA::PMFIFO));
    //
    // if( event_fifo )
    //
    //   std::cout << "Event ID: " << my_pmtfifo_v->event_id() << std::endl;
    //
  
    return true;
  }

  bool MuonDecay::finalize() {

    _electron_E->Write();

    // This function is called at the end of event loop.
    // Do all variable finalization you wish to do here.
    // If you need, you can store your ROOT class instance in the output
    // file. You have an access to the output file through "_fout" pointer.
    //
    // Say you made a histogram pointer h1 to store. You can do this:
    //
    // if(_fout) { _fout->cd(); h1->Write(); }
    //
    // else 
    //   print(MSG::ERROR,__FUNCTION__,"Did not find an output file pointer!!! File not opened?");
    //
  
    return true;
  }

}
#endif

#ifndef LARLITE_MICHELSPECTRUM_CXX
#define LARLITE_MICHELSPECTRUM_CXX

#include "MichelSpectrum.h"

namespace larlite {

  bool MichelSpectrum::initialize() {

    //
    // This function is called in the beggining of event loop
    // Do all variable initialization you wish to do here.
    // If you have a histogram to fill in the event loop, for example,
    // here is a good place to create one on the heap (i.e. "new TH1D"). 
    //

    std::cout<<"I am being initialized\n";

    _event_counter=0;

    // Unit: MeV
    _muon_E=new TH1D("muon_energy","x;y;title",1000,0,1e4);

    return true;
  }
  
  bool MichelSpectrum::analyze(storage_manager* storage) {
  
    std::cout<<"I am being called"<<_event_counter<<"\n";
    _event_counter++;

    // Just memorize the line below
    // storage: pointer to file manager
    // get data: template function and I'm asking it in <> to give me a specific type of data (event_mctrack)
    //("...") is where we specify the producer name
    auto event_mctracks = storage->get_data<event_mctrack>("mcreco");
    
    // event_mctracks is a vector of the mctrack tracks
    std::cout << "I see " << event_mctracks->size() << "in this event\n";

    for(int i = 0; i < event_mctracks->size(); i++){

      auto track=event_mctracks->at(i);

      if(track.PdgCode()!=13){

	//ignore this iteration of the loop 
	continue;

      }

      std::cout<<"On Track"<<i<<"and particle type is"<<track.PdgCode()<<"\n";

      double muon_energy = track.Start().E();

      // Fill histogram
      _muon_E->Fill(muon_energy);

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

  bool MichelSpectrum::finalize() {

    std::cout<<"I am being analyzed\n";

    _muon_E->Write();

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

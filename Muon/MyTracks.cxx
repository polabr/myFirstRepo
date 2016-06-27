#ifndef LARLITE_MYTRACKS_CXX
#define LARLITE_MYTRACKS_CXX

#include "MyTracks.h"

namespace larlite {
  
  bool MyTracks::initialize() {
    
    //
    // This function is called in the beggining of event loop
    // Do all variable initialization you wish to do here.
    // If you have a histogram to fill in the event loop, for example,
    // here is a good place to create one on the heap (i.e. "new TH1D"). 
    //

    counter=0;
    return true;
  }
  
  bool MyTracks::analyze(storage_manager* storage) {
  
    counter++;
    
    auto event_tracks=storage->get_data<event_track>("pandoraNuKHit");
    auto event_mctracks=storage->get_data<event_mctrack>("mcreco");
    auto event_mcshowers=storage->get_data<event_mcshower>("mcreco");
    
    std::cout << event_tracks->size();
    
    // Tracks within an event
    int trackCounter=0;
    
    for(size_t i = 0; i < event_mctracks->size(); i++){
      
      auto mctrack=event_mctracks->at(i);
      
      if(mctrack.PdgCode()!=13){
	
        return false;
	
      }
      
      std::cout<<"This track's pdg is "<<mctrack.PdgCode()<<"\n";
      std::cout<<"This track's process is "<<mctrack.Process()<<"\n";
      
    }
    
    for(size_t i = 0; i < event_mcshowers->size(); i++){
      
      auto mcshower=event_mcshowers->at(i);
      
      if(mcshower.PdgCode()==11 || mcshower.PdgCode()==22){
	
        return false;
	
      }
      
      std::cout<<"This shower's pdg is "<<mcshower.PdgCode()<<"\n";
      std::cout<<"This shower's process is "<<mcshower.Process()<<"\n";
      
    }
    
    for (size_t i=0;i<event_tracks->size();i++){
      
      auto track=event_tracks->at(i);
      
      trackCounter++;
      
      //      double muon_energy=track.Start().E();
      
      
      // Inside an individual track
      for (size_t j=0;j<track.NumberTrajectoryPoints();j++){
	
	TVector3 v1 = track.LocationAtPoint(j);
	
	vx.push_back(v1.X());
	vy.push_back(v1.Y());
	vz.push_back(v1.Z());
	
      }

      tracker=new TGraph2D(vx.size(),&(vx[0]),&(vy[0]),&(vz[0]));
      //      tracker=new TGraph(vx.size(),&(vx[0]),&(vy[0]));
      tracker->SetName(Form("Track%i_Event%i",trackCounter,counter));
      tracker->Write();
      delete tracker;
      vx.clear();
      vy.clear();
      vz.clear();
      
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

  bool MyTracks::finalize() {
    
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

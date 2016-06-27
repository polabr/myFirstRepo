/**
 * \file MyTracks.h
 *
 * \ingroup Muon
 * 
 * \brief Class def header for a class MyTracks
 *
 * @author polabr
 */

/** \addtogroup Muon

    @{*/

#ifndef LARLITE_MYTRACKS_H
#define LARLITE_MYTRACKS_H

#include "Analysis/ana_base.h"

// We need to request the "track" class, which is located in DataFormat (under core)
#include "DataFormat/track.h"
#include "DataFormat/mctrack.h"
#include "DataFormat/mcshower.h"


// Include class for making TGraphs:
#include "TGraph2D.h"
//#include "TGraph.h"

namespace larlite {
  /**
     \class MyTracks
     User custom analysis class made by SHELL_USER_NAME
   */
  class MyTracks : public ana_base{
  
  public:

    /// Default constructor
    MyTracks(){ _name="MyTracks"; _fout=0;}

    /// Default destructor
    virtual ~MyTracks(){}

    /** IMPLEMENT in MyTracks.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in MyTracks.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in MyTracks.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

  protected:

  private:
    // List the variables we need
    int counter;
    TGraph2D* tracker;
    //TGraph* tracker;
    std::vector<double> vx;
    std::vector<double> vy;
    std::vector<double> vz;
    
  };
}
#endif

//**************************************************************************
// 
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 

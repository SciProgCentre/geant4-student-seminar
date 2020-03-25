//
// Created by zelenyy on 04.02.2020.
//

#ifndef PI_DECAY_TRACKINGSD_HH
#define PI_DECAY_TRACKINGSD_HH


#include <G4VSensitiveDetector.hh>
#include "TupleId.hh"
#include "DetectorConstruction.hh"
#include <vector>
#include "GeometrySize.hh"

const int numberOfCell = number_of_tracking_cell *number_of_tracking_cell;


struct Adress {
    int detector = 0;
    int segment = 0;
    int layer = 0;
    int cell = 0;
};

struct TrackingData{
    Adress adress = {};
    double time = 0;
    double deposit = 0 ;
};



class TrackingSD : public G4VSensitiveDetector {
public:
    explicit TrackingSD(std::string name, TupleId *tupleId, TrackingCellCoord *coords) : G4VSensitiveDetector(name),
                                                                                         tupleId(tupleId),
                                                                                         coords(coords) {

    };

    void Initialize(G4HCofThisEvent *event) override;

    void EndOfEvent(G4HCofThisEvent *event) override;

protected:
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;

private:
    TupleId *tupleId;
    TrackingCellCoord *coords;
    std::vector<TrackingData> data;
};


#endif //PI_DECAY_TRACKINGSD_HH

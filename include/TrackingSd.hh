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



struct TrackingData{
    G4ThreeVector position;
    double time = 0;
    double deposit = 0 ;
};



class TrackingSD : public G4VSensitiveDetector {
public:
    explicit TrackingSD(std::string name, TupleId *tupleId) : G4VSensitiveDetector(name),
                                                                                         tupleId(tupleId) {
        empty.position = G4ThreeVector(0,0,0);

    };

    void Initialize(G4HCofThisEvent *event) override;

    void EndOfEvent(G4HCofThisEvent *event) override;

protected:
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;

private:
    int eventID = 0;
    TupleId *tupleId;
    TrackingData leftData[4];
    TrackingData rightData[4];

    double left_cur_z = 0;
    int left_indx = 0;
    double rigth_cur_z = 0;
    int rigth_indx = 0;

    TrackingData empty;

//    std::vector<TrackingData> dropRepeated(std::vector<TrackingData> data){
//        std::vector<TrackingData> new_data;
//        if (data.size() >1){
//            new_data.push_back(data.front());
//            double current_z = data.front().position.getZ();
//            for (auto it : data){
//                if (abs(current_z - it.position.getZ()) > 2*tracking_thickness){
//                    current_z =  it.position.getZ();
//                    new_data.push_back(it);
//                }
//            }
//        }
//        if (new_data.size() < 4){
//            for (int i = 0; i < 4 - data.size(); ++i){
//                new_data.push_back(empty);
//            }
//        }
//        return new_data;
//    }
    
};


#endif //PI_DECAY_TRACKINGSD_HH

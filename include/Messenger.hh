//
// Created by zelenyy on 15.04.2020.
//

#ifndef PI_DECAY_MESSENGER_HH
#define PI_DECAY_MESSENGER_HH

#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include "G4UIcmdWithAnInteger.hh"
#include "G4UImessenger.hh"
#include "Settings.hh"

using namespace std;

class Messenger : public G4UImessenger {
public:
    Messenger(Settings *settings) : G4UImessenger(), settings(settings) {
        directory = new G4UIdirectory(directory_p.c_str());
        output = new G4UIcmdWithAString(output_p.c_str(), this);
        output->SetParameterName("file", false);
        mode = new G4UIcmdWithAString(mode_p.c_str(), this);
        mode->SetParameterName("mode", false);

        field = new G4UIcmdWithADoubleAndUnit(field_p.c_str(), this);
        field->SetParameterName("field", false, false);
        field->SetDefaultUnit("kilogauss");

        channel = new G4UIcmdWithAnInteger(channel_p.c_str(), this);
        channel->SetParameterName("channel", false);

    }

    G4String GetCurrentValue(G4UIcommand *command) override {

    }

    void SetNewValue(G4UIcommand *command, G4String newValue) override {
        if (command == mode) {
            settings->mode = newValue;
        } else if (command == output) {
            settings->output = newValue;
        } else if (command == field) {
            settings->field = G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue);
        } else if (command == channel) {
            settings->channel = G4UIcmdWithAnInteger::GetNewIntValue(newValue);
        } else {
            G4UImessenger::SetNewValue(command, newValue);
        }
    }

private:
    Settings *settings;
    G4UIdirectory *directory;
    G4UIcmdWithAString *output;
    G4UIcmdWithAString *mode;
    G4UIcmdWithADoubleAndUnit *field;
    G4UIcmdWithAnInteger * channel;
private:
    string directory_p = "/mipt/";
    string field_p = directory_p + "field";
    string output_p = directory_p + "output";
    string mode_p = directory_p + "mode";
    string channel_p = directory_p + "channel";
};


#endif //PI_DECAY_MESSENGER_HH

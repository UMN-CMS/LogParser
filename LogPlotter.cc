// Standard Libraries
#include <iostream>  // cout, endl
#include <string>

// ROOT Libraries
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

int make_plot(const std::string INPUT_FILE, const std::string OUTPUT_FILE) {
    // Open the TFile and extract the TTree
    TFile input_tfile(INPUT_FILE.c_str(), "READ");
    // Get the TTree by its name; this is the name displayed when reading the
    // rootfile with a TBrowser
    TTree* input_ttree = dynamic_cast<TTree*>(input_tfile.Get("outtree"));
    // Set the branches. These are decided at write time.
    int year;
    input_ttree->SetBranchAddress("year", &year);
    int month;
    input_ttree->SetBranchAddress("month", &month);
    int day;
    input_ttree->SetBranchAddress("day", &day);
    int hour;
    input_ttree->SetBranchAddress("hour", &hour);
    int minute;
    input_ttree->SetBranchAddress("minute", &minute);
    int second;
    input_ttree->SetBranchAddress("second", &second);
    double temperature;
    input_ttree->SetBranchAddress("temperature", &temperature);
    double voltage_out;
    input_ttree->SetBranchAddress("voltage_out", &voltage_out);
    bool power_good;
    input_ttree->SetBranchAddress("power_good", &power_good);
    bool margin_up;
    input_ttree->SetBranchAddress("margin_up", &margin_up);
    bool margin_down;
    input_ttree->SetBranchAddress("margin_down", &margin_down);
    bool high_load;
    input_ttree->SetBranchAddress("high_load", &high_load);
    double input_voltage;
    input_ttree->SetBranchAddress("input_voltage", &input_voltage);
    double input_current;
    input_ttree->SetBranchAddress("input_current", &input_current);
    double total_power;
    input_ttree->SetBranchAddress("total_power", &total_power);
    double aux_output_voltage_a;
    input_ttree->SetBranchAddress("aux_output_voltage_a", &aux_output_voltage_a);
    double aux_output_voltage_b;
    input_ttree->SetBranchAddress("aux_output_voltage_b", &aux_output_voltage_b);
    double aux_output_voltage_c;
    input_ttree->SetBranchAddress("aux_output_voltage_c", &aux_output_voltage_c);
    double aux_output_voltage_d;
    input_ttree->SetBranchAddress("aux_output_voltage_d", &aux_output_voltage_d);
    double secondary_input_current;
    input_ttree->SetBranchAddress("secondary_input_current", &secondary_input_current);
    double secondary_input_voltage;
    input_ttree->SetBranchAddress("secondary_input_voltage", &secondary_input_voltage);

    // Make a TH1D to store out plot in
    const int X_PIXELS = 800;
    const int Y_PIXELS = 800;
    TCanvas canvas("canvas", "canvas", X_PIXELS, Y_PIXELS);
    canvas.cd();
    TH1D histo("temperature", "Temperature", 100, 0, 100);
    histo.SetMarkerStyle(kFullCircle);
    histo.SetMarkerColor(kBlack);

    // Loop over all events in the TTree
    const int N_ENTRIES = input_ttree->GetEntries();
    for (int i = 0; i < N_ENTRIES; ++i) {
        // This line "fills" the variables above with the new event information
        input_ttree->GetEntry(i);
        histo.Fill(temperature);
    }

    // Draw the plot
    histo.Draw("E");

    // Save the plot
    canvas.Print(OUTPUT_FILE.c_str(), "png");

    // Exit OK
    return 0;
}

int main(int argc, char* argv[]) {
    // We expect 3 arguments: The script itself (always arg0), the input root
    // file, and the output plot file
    const int N_ARGS = 3;
    if (argc != N_ARGS) {
        return 1;
    }

    const std::string INPUT_FILE(argv[1]);
    const std::string OUTPUT_FILE(argv[2]);

    // Call the plotting function
    const int RET_CODE = make_plot(INPUT_FILE, OUTPUT_FILE);
    return RET_CODE;
}

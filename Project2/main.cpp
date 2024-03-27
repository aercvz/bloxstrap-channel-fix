#include <iostream>
#include <fstream>
#include <filesystem>
#include "json.hpp"
namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace std;

int main() {
    cout << "checking for local appdata..." << endl;
    string local_appdata = getenv("LOCALAPPDATA");
    if (local_appdata.empty()) {
        cout << "failed to get local appdata directory" << endl;
        return 1;
    }

    cout << "checking for bloxstrap directory..." << endl;
    fs::path local_appdata_path(local_appdata);
    fs::path bloxstrap_directory = local_appdata_path / "Bloxstrap";

    if (!fs::exists(bloxstrap_directory)) {
        cout << "bloxstrap not found" << endl;
        return 1;
    }

    cout << "checking for settings.json..." << endl;
    fs::path settings_file = bloxstrap_directory / "Settings.json";

    if (!fs::exists(settings_file)) {
        cout << "settings file not found" << endl;
        return 1;
    }


    cout << "getting json data..." << endl;
    json json_data;
    ifstream input_settings_data(settings_file);
    input_settings_data >> json_data;
    input_settings_data.close();

    json_data["Channel"] = "Live";
    json_data["OhHeyYouFoundMe"] = true;

    cout << "setting json data..." << endl;
    ofstream output_settings_data(settings_file);
    output_settings_data << json_data.dump();
    output_settings_data.close();

    
    cout << "done!" << endl;

    for (;;);

    return 0;
}

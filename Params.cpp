// Created by Murtaza & Yash on 2/14/2025
#include "Params.hpp"

Params::Params(const int argc, char *const argv[]): pathname(nullptr) {
    const struct option longOpts[] = {
        {"verbose", no_argument, nullptr, 'v'},
        {"output", required_argument, nullptr, 'o'},
        {"ignore", no_argument, nullptr, 0},
        {"dir", required_argument, nullptr, 0},
        {nullptr, 0, nullptr, 0}
    };
    int code, ch{}, optx{};
    for (int j = 0; j < argc; j++) command += string(argv[j]) + " ";
    for (;;) {
        // Process the command-line switches
        ch = getopt_long(argc, argv, "vo:", longOpts, &code);
        if (ch == -1) break; // No more recognized short switches.
        switch (ch) {
            case 'v': switches[0] = true;
                break; // These switches do not have arguments.
            case 'o': filename = optarg;
                break; // These switches require arguments break;
            case 0: {
                // Convert code for long switch to full
                // printf("\n\tSwitch: %s ", longOpts[code].name );
                if (longOpts[code].name == "dir") chdir(pathname = optarg);
                else if (longOpts[code].name == "ignore") switches[1] = true;
                //if( optarg != nullptr ) printf(" \targument: %s", optarg);
                break;
            }
            case '?': // Check for invalid switches.
            default: usage();
        }
    }
    if (filename == nullptr || pathname == nullptr)
        cerr << "Error Opening File" << endl;
    out.open(string(pathname) + string(filename), ios::app);
    cout << " -------------------------------------------\n";
    out << " -------------------------------------------\n";
    for (optx = optind; optx < argc; ++optx) {
        wlist += string(argv[optx]) + " ";
        cout << "\t Argument: " << argv[optx] << endl;
        out << "\t Argument: " << argv[optx] << endl;
    }
    cout << " -------------------------------------------\n\n";;
    out << " -------------------------------------------\n\n";
}

void Params::print(){
    cout << "Command: " << command << endl;
    out << "Command: " << command << endl;
    cout << "Start at: " << pathname << endl;
    out << "Start at: " << pathname << endl;
    cout << "Output file name: " << filename<< endl;
    out << "Output file name: " << filename<< endl;
    cout << "Verbose? " << (switches[0]? "Yes" : "No") << endl; //Verbose Switch
    out << "Verbose? " << (switches[0]? "Yes" : "No") << endl;
    cout << "Ignore case? " << (switches[1]? "Yes": "No") << endl; //Ignore Switch
    out << "Ignore case? " << (switches[1]? "Yes": "No") << endl;
}

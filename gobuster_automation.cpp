#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void printMenu() {
    cout << "Select a Gobuster mode:\n";
    cout << "1. Directory and File Brute-Forcing (dir mode)\n";
    cout << "2. DNS Subdomain Brute-Forcing (dns mode)\n";
    cout << "3. Virtual Host Brute-Forcing (vhost mode)\n";
    cout << "4. S3 Bucket Brute-Forcing (s3 mode)\n";
    cout << "5. Google Cloud Storage Brute-Forcing (gcs mode)\n";
    cout << "6. Fuzzing Mode (fuzz mode)\n";
    cout << "Type 'exit' to quit.\n";
    cout << "Enter your choice (1-6 or 'exit'): ";
}

void executeGobusterCommand(const string& command) {
    cout << "Executing: " << command << endl;
    int result = system(command.c_str());
    if (result != 0) {
        cout << "Error executing Gobuster command. Please check your inputs.\n";
    }
}

int main() {
    string input;
    while (true) {
        printMenu();
        cin >> input;

        // Check if the user wants to exit
        if (input == "exit") {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }

        // Convert input to integer (choice)
        int choice;
        try {
            choice = stoi(input);
        } catch (invalid_argument&) {
            cout << "Invalid input. Please enter a number (1-6) or 'exit'.\n";
            cin.ignore(); // Clear the input buffer
            continue;
        }

        cin.ignore(); // Clear the input buffer

        string url, wordlist, outputFile, extensions, domain, prefix;

        switch (choice) {
            case 1: // dir mode
                cout << "Enter target URL: ";
                getline(cin, url);
                cout << "Enter path to wordlist: ";
                getline(cin, wordlist);
                cout << "Enter file extensions to append (e.g., php,txt): ";
                getline(cin, extensions);
                cout << "Enter output file (optional, press Enter to skip): ";
                getline(cin, outputFile);

                if (!outputFile.empty()) {
                    executeGobusterCommand("gobuster dir -u " + url + " -w " + wordlist + " -x " + extensions + " -o " + outputFile);
                } else {
                    executeGobusterCommand("gobuster dir -u " + url + " -w " + wordlist + " -x " + extensions);
                }
                break;

            case 2: // dns mode
                cout << "Enter target domain: ";
                getline(cin, domain);
                cout << "Enter path to wordlist: ";
                getline(cin, wordlist);
                executeGobusterCommand("gobuster dns -d " + domain + " -w " + wordlist);
                break;

            case 3: // vhost mode
                cout << "Enter target URL: ";
                getline(cin, url);
                cout << "Enter path to wordlist: ";
                getline(cin, wordlist);
                executeGobusterCommand("gobuster vhost -u " + url + " -w " + wordlist);
                break;

            case 4: // s3 mode
                cout << "Enter path to wordlist: ";
                getline(cin, wordlist);
                cout << "Enter bucket name prefix (optional, press Enter to skip): ";
                getline(cin, prefix);
                if (!prefix.empty()) {
                    executeGobusterCommand("gobuster s3 -w " + wordlist + " -p " + prefix);
                } else {
                    executeGobusterCommand("gobuster s3 -w " + wordlist);
                }
                break;

            case 5: // gcs mode
                cout << "Enter path to wordlist: ";
                getline(cin, wordlist);
                cout << "Enter bucket name prefix (optional, press Enter to skip): ";
                getline(cin, prefix);
                if (!prefix.empty()) {
                    executeGobusterCommand("gobuster gcs -w " + wordlist + " -p " + prefix);
                } else {
                    executeGobusterCommand("gobuster gcs -w " + wordlist);
                }
                break;

            case 6: // fuzz mode
                cout << "Enter target URL (include FUZZ keyword): ";
                getline(cin, url);
                cout << "Enter path to wordlist: ";
                getline(cin, wordlist);
                executeGobusterCommand("gobuster fuzz -u " + url + " -w " + wordlist);
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
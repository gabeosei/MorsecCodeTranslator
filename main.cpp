#include <iostream>
#include <windows.h>
#include <chrono>
#include <string>
#include <map>

using namespace std;

void translateMorse(string code) {
    //dictionary linking Morse code to letters
    static const map<string, string> morseMap = {
        {".-", "A"}, {"-...", "B"}, {"-.-.", "C"}, {"-..", "D"}, {".", "E"},
        {"..-.", "F"}, {"--.", "G"}, {"....", "H"}, {"..", "I"}, {".---", "J"},
        {"-.-", "K"}, {".-..", "L"}, {"--", "M"}, {"-.", "N"}, {"---", "O"},
        {".--.", "P"}, {"--.-", "Q"}, {".-.", "R"}, {"...", "S"}, {"-", "T"},
        {"..-", "U"}, {"...-", "V"}, {".--", "W"}, {"-..-", "X"}, {"-.--", "Y"},
        {"--..", "Z"}
    };

    // Look up the code in map
    auto it = morseMap.find(code);
    if (it != morseMap.end()) {
        cout << "\n-> Translated: " << it->second << "\n";
    } else {
        cout << "\n-> Unknown code: " << code << "\n";
    }
}

int main() {
    cout << "\n";
    cout << "  __  __                  ____          _                  _              " << endl;
    cout << " |  \\/  | ___  _ __ ___  / ___|___   __| | ___   _ __ __ _| |_ ___  _ __  " << endl;
    cout << " | |\\/| |/ _ \\| '__/ __| | |   / _ \\ / _` |/ _ \\ | '__/ _` | __/ _ \\| '__| " << endl;
    cout << " | |  | | (_) | |  \\__ \\ | |__| (_) | (_| |  __/ | | | (_| | || (_) | |    " << endl;
    cout << " |_|  |_|\\___/|_|  |___/  \\____\\___/ \\__,_|\\___| |_|  \\__,_|\\__\\___/|_|    " << endl;
    cout << "\n";
    cout << "==========================================================================" << endl;
    cout << "Press the 'q' to quit:" << endl;
    cout << "Quick tap = dot(.), longer hold = dash (-)\n";

    string current_morse = "";
    while(true){
        
        if (GetAsyncKeyState('Q') & 0x8000) {
            cout << "\nExiting..." << endl;
            break;
        }

        // Check for Enter key to translate current sequence
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (!current_morse.empty()) {
                translateMorse(current_morse);
                current_morse = ""; // Reset for next letter
            }
            Sleep(300); // Prevent double-triggering
            continue;
        }

        // Check Spacebar for dot/dash
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            auto start = chrono::steady_clock::now();
            while (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                Sleep(10);
            }
            auto end = chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            if (duration < 250) {
                current_morse += ".";
                cout << "." << flush;
            } else {
                current_morse += "-";
                cout << "-" << flush;
            }
        }

        Sleep(10);
    }

    return 0;
}
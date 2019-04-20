#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

const int WHITESPACE = 30; //whitespace between pictures


//user settings
void settings(std::string &filename, int &waittime, int & repeats) {
    std::cout << "Enter filename: ";
    std::cin >> filename;
    std::cout << "Enter delay between frames in milliseconds: ";
    std::cin >> waittime;
    std::cout << "Enter amount of repeats (0 = infinite): ";
    std::cin >> repeats;

}

void picturegen(std::string filename, std::vector<std::string> &pictures) {
    std::string white(WHITESPACE, '\n');
    std::ifstream input(filename.c_str(), std::ios::in);
    std::string currentline, previous;
    std::string currentpicture;

    getline(input, currentline);

    while(!input.eof()) {
        if (currentline.length() != 0 && previous.length() == 0) {
            pictures.push_back(currentpicture);
            currentpicture = white;
        } else {
            if (currentline.length() != 0) {
                currentpicture.push_back('\n');
                currentpicture.append(currentline);
            }
        }
        previous = currentline;
        getline(input, currentline);

    }
}

void pictureshow(int waittime, std::vector<std::string> pictures) {
    std::vector<std::string>::iterator it;
    for (it = pictures.begin(); it != pictures.end(); ++it) {
                std::cout << *it;
                usleep(waittime * 1000);
            }
}

int main() {
    std::string filename; //filename
    int waittime; //waittime between frames in ms
    int repeats; //amount of repeats the animation should do
    std::vector<std::string> pictures; //storage of pictures
    std::vector<std::string>::iterator it;

    //ask user for settings
    settings(filename, waittime, repeats); 

    //make picture vector
    picturegen(filename, pictures);

    //cout everything
    if (repeats != 0) {
        for (int i = 0; i < repeats; i++) {
            pictureshow(waittime, pictures);
        }
    } else {
        while (true) {
            pictureshow(waittime, pictures);
        }
    }

    //newline at end
    std::cout << std::endl;

    return 0;
}
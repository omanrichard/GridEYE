//
//  graphicClasses.h
//  GridEYE
//
//  Created by Grant Hilgert on 12/1/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <mouse.hpp>
#include "projectClasses.h"

#ifndef graphicClasses_h
#define graphicClasses_h

using namespace std;

/*/ --------------- Terminal (Stack) Class --------------- /*/
class terminal{
private:
    string rootText; //Text before input
    vector<string> stack;
    sf::Font terminalFont;
    sf::Text terminalText1;
    sf::Text terminalText2;
    sf::Text terminalText3;
    sf::Text terminalText4;
    sf::Text terminalText5;
    sf::Text terminalText6;
    sf::RectangleShape terminalHeader;
    sf::RectangleShape terminalBackground;
    //Text vector
public:
    terminal(int size, string text = "root");
    void setRoot(string text);//Sets text before input
    void print(string input); //Prints on same line
    void print(string input, string text);
    string read(int index);//Function to allow SFML to read lines from the terminal
    virtual void draw(sf::RenderWindow &window);
    
    
};

/*/ --------------- ETerminal (Stack) Class --------------- /*/


/*/ ---------------  Toolbar Class --------------- /*/
class toolbar{
private:
    int menuLayer = 0;//Default
    //Toolbar Texture Objects
    sf::Texture t_settings;
    sf::Texture t_record;
    sf::Texture t_stop;
    sf::Texture t_play;
    sf::Texture t_trash;
    sf::Texture t_save;
    sf::Texture t_quit;
    //Toolbar Sprite Objects
    sf::Sprite settings;
    sf::Sprite record;
    sf::Sprite play;
    sf::Sprite stop;
    sf::Sprite save;
    sf::Sprite trash;
    sf::Sprite quit;
    //Toolbar Background Shapes
    sf::RectangleShape toolbarFrame;
    sf::RectangleShape toolbarHeader;
    //Toolbar Selection Objects
    sf::Font toolbarFont;
    sf::RectangleShape selection;
    sf::RectangleShape selectionTextBox;
    sf::Text selectionText;
    
public:
    toolbar(void);
    int exit(void);//Changes menu layer
    void sync(int newMenuLayer);
    virtual void draw(sf::RenderWindow &window);
    virtual void event(sf::Event &toolbarEvent);
    virtual void onClick(sf::RenderWindow &window, terminal &stackward);
};
/*/ --------------- End Toolbar Class --------------- /*/

/*/ --------------- Settings Menu Class --------------- /*/
class settingsMenu{
private:
    int menuLayer = 1;
    int rootx = 150;//Settings Menu upper left corner
    int rootY = 100;//Settings Menu upper left corner
    int recordMins = 0; //Seconds to be recorded - Is this still being used?
    int recordSeconds = 0;//Minuetes to be recorded - Is this still being used?
    sf::Font settingsFont;
    // Settings Text Declare
    sf::Text settingsFPSText;
    sf::Text settingsFPSTextValTen;
    sf::Text settingsFPSTextValOne;
    sf::Text settingsCollectionText;
    sf::Text settingsMinsText;
    sf::Text settingsSecondsText;
    sf::Text settingsRangeText;
    sf::Text settingsRangeTextTrue;
    sf::Text settingsRangeTextHuman;
    sf::Text settingsResetText;
    sf::Text settingsApplyText;
    //Settings Object Declare
    sf::RectangleShape settingsBackground;
    sf::Sprite settingsExit;
    sf::Texture t_close;
    //Settings Button Declare
    sf::RectangleShape settingsTenFPS;
    sf::RectangleShape settingsOneFPS;
    sf::RectangleShape settingsMinsUp;
    sf::RectangleShape settingsMinsDown;
    sf::RectangleShape settingsSecondsUp;
    sf::RectangleShape settingsSecondsDown;
    sf::RectangleShape settingsRangeTrue;
    sf::RectangleShape settingsRangeHuman;
    sf::RectangleShape settingsReset;
    sf::RectangleShape settingsApply;
    sf::RectangleShape settingsMinsBox;
    sf::RectangleShape settingsSecondsBox;
    
    
public:
    settingsMenu(void);
    void onClick(sf::RenderWindow &window);
    
    int exit(void);
    virtual void draw(sf::RenderWindow &window);
    
};

class topBar {
    private:
        int mode = 0; //Default
    sf::Text modeText;
    sf::Text titleText;
    sf::Text subText;
    sf::Font topBarFont;
    sf::RectangleShape background;
    sf::RectangleShape header;
    
public:
    topBar(void);
    virtual void draw(sf::RenderWindow &window);
    void update(void);
    void setMode(int newMode);
   
};
class playBar {
private:
    sf::Font playBarFont;
    sf::Texture t_background;
    sf::Texture t_fillBar;
    sf::Sprite background;
    sf::Sprite fillBar;
    sf::Vector2f fillPos;
    sf::Text currentTimeText;
    sf::Text endTimeText;
    
    char timeTextBuffer[8];
    struct tm * timeTextStruct;
    time_t clipStart;
    time_t clipEnd;
    time_t playbackStart;
    double playbackTime = 0;
    double elapsedTime = 0;
public:
    playBar(sf::Vector2f position, int scale);
    void onClick(sf::RenderWindow &window);
    void setClipStartTime(time_t start);
    void setClipEndTime(time_t end);
    void setPlaybackStartTime(time_t start);
    void setPlaybackEndTime(time_t end);
    void setCurrentTime(void);
    void record(void);
    void playback(void);
    virtual void draw(sf::RenderWindow &window);
};

#endif /* graphicClasses_h */

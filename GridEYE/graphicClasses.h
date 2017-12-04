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


//Interactive Base Class
class interactiveObject {
    protected:
    sf::Font defaultFont;                                       //Font for Each object to use
    int menuLayer = 0;                                          //Each Object
   
    public:
    interactiveObject(void);
    
    virtual void draw(sf::RenderWindow &window){};
    virtual void onClick(sf::RenderWindow &window){};
    virtual void event(sf::Event &toolbarEvent){};
};

/*/ --------------- Terminal (Stack) Class --------------- /*/

class terminal : interactiveObject {
friend class interactiveObject;
private:
    
    string rootText; //Text before input
    vector<string> stack; //Stack Vector
    
    //SFML Objects
    sf::Text terminalText1;
    sf::Text terminalText2;
    sf::Text terminalText3;
    sf::Text terminalText4;
    sf::Text terminalText5;
    sf::Text terminalText6;
    sf::RectangleShape terminalHeader;
    sf::RectangleShape terminalBackground;
    
public:
    
    //Setup Functions
    terminal(int size, string text = "root");
    void setRoot(string text);//Sets text before input
    
    //Event Functions
    void draw(sf::RenderWindow &window);
    
    //Action Functions
    void print(string input); //Prints on same line
    void print(string input, string text);
  
    
    
};

/*/ --------------- ETerminal (Stack) Class --------------- /*/


/*/ ---------------  Toolbar Class --------------- /*/
class toolbar : interactiveObject {
private:
    
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
    sf::RectangleShape selection;
    sf::RectangleShape selectionTextBox;
    sf::Text selectionText;
    
public:
    //Setup Functions
    toolbar(void);
    
    //Event Functions
    void draw(sf::RenderWindow &window);
    void event(sf::Event &toolbarEvent);
    void onClick(sf::RenderWindow &window, terminal &stackward);
    //Action Functions
    
    int exit(void);//Changes menu layer
    void sync(int newMenuLayer);
  
};
/*/ --------------- End Toolbar Class --------------- /*/

/*/ --------------- Settings Menu Class --------------- /*/
class settingsMenu : interactiveObject {
private:
    int menuLayer = 1;
    int rootx = 150;//Settings Menu upper left corner
    int rootY = 100;//Settings Menu upper left corner
    int recordMins = 0; //Seconds to be recorded - Is this still being used?
    int recordSeconds = 0;//Minuetes to be recorded - Is this still being used?

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
    //Setup Functions
    settingsMenu(void);
   
    //Event Functions
    void draw(sf::RenderWindow &window);
    void onClick(sf::RenderWindow &window);
    
    //Action Functions
    int exit(void);
    
    
};

class topBar : interactiveObject {
    private:
        int mode = 0;                   //Mode
        struct tm * clockStruct;        //Time structure required for formatted time
        char clockTextBuffer[11];      //Holds formatted time
    
        sf::Text modeText;              //SFML Text Object
        sf::Text titleText;             //SFML Text Object
        sf::Text subText;               //SFML Text Object
        sf::Text clockText;             //SFML Text Object
    
        sf::RectangleShape background;
        sf::RectangleShape header;
    
        void updateMode(void);
    public:
    
    //Setup Functions
    topBar(void);
    void setMode(int newMode);
    
    //Event Functions
    void draw(sf::RenderWindow &window);
   
    //Action Functions
    void updateClock(time_t currentTime);
    

   
};
class playBar : interactiveObject {
private:

    sf::Texture t_background;
    sf::Texture t_fillBar;
    sf::Sprite background;
    sf::Sprite fillBar;
    sf::Vector2f fillPos;
    sf::Text currentTimeText;
    sf::Text endTimeText;
    sf::Vector2f origin;
    char timeTextBuffer[25];//Buffer for sprintf. 
    string bufferA;
    string bufferB;
    struct tm * timeTextStruct;
    time_t clipStart; //Actual time at which clip was recorded
    time_t clipEnd; //Actual time at which clip was finished recording
    time_t playbackStart; //Actual time that the replay started playing
    double playbackTime = 0; //Length of the clip in seconds. Calculated from clipStart and clip Ends
    double elapsedTime = 0; //Curent lenght of the playpack in seconds. Calculated from playbackStart and time(NULL)
public:
  
    //Setup Functions
    playBar(sf::Vector2f position, int scale);
    void setClipStartTime(time_t start);
    void setClipEndTime(time_t end);
    void setPlaybackStartTime(time_t start);
    void setPlaybackEndTime(time_t end);
    void setCurrentTime(void);
    
    //Event Functions
    void onClick(sf::RenderWindow &window,terminal &Terminal);
    void draw(sf::RenderWindow &window);
   
    //Action Functions
    void record(void);
    void playback(topBar &TopBar, terminal &Terminal, bool &playbackStatus);
    
};

#endif /* graphicClasses_h */

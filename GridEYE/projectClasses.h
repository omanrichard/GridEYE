//
//  projectClasses.h
//  Project
//
//  Created by Richard Oman on 11/11/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>

#ifndef projectClasses_h
#define projectClasses_h

using namespace std;

/*/ ----------- GrideEye Class ---------- /*/
class GridEYE{
    friend class video;
    
private:
    float mean;
    short max;
    short sensor_values[8][8];
    int FPS;
    
 //   virtual void set_max();
 //   virtual void set_mean();
    
public:
    GridEYE(int address); //Hint: My board has it set at 0x68 :)
    
    short read(int row, int col);
    void reset(void);
    void test(int row, int col);    //Draw Test pattern
    int runTime;                    // Run Time in Seconds
    short pixelL;
    int r,g,b;
    int getFPS();
    
 //   virtual void print();
    void setFPS( int temp );
};

/*/ ---------- End GridEYE Class ---------- /*/

/*/ --------------- Frame Class --------------- /*/
class frame{                        //      Stores sensor data
                                    //     0  1  2  3  4  5  6  7
private:                            // 0  [] [] [] [] [] [] [] []
    float mean;                     // 1  [] [] [] [] [] [] [] []
    short max;                      // 3  [] [] [] [] [] [] [] []
    short sensor_values[8][8];      // 4  [] [] [] [] [] [] [] []
                                    // 4  [] [] [] [] [] [] [] []
    virtual void set_max();         // 5  [] [] [] [] [] [] [] []
    virtual void set_mean();        // 6  [] [] [] [] [] [] [] []
                                    // 7  [] [] [] [] [] [] [] []
public:
    frame();
    frame(GridEYE gridward);
    ~frame();
    
    short access( short row , short col );
    short get_max();
    float get_mean();
    
    void new_max( short newMax );
    void new_mean( float newMean );
    
    virtual void print();

};

/*
class pixelMask {
private:
 short r;
 short g;
 short b;
    
public:
    frame_mask();
    ~frame_mask();
    
    void setMask( short temp ); // Uses algorithm to determine RGB values
};
*/

/*/ --------------- End Frame Class --------------- /*/

/*/ --------------- Video Class --------------- /*/
class video : public frame{
private:
    short frameCount;       // 10 Frames -> 1 Second
    vector< frame* > data;  // Storing up to 31,800 frames maximum
    
    void set_max();
    void set_mean();
    
public:
    video();
    video( GridEYE gridward );
    ~video();
    
    void addFrame(GridEYE gridward);

    void exportVideo( string filename );
    void print();
};
/*/ --------------- End Video Class --------------- /*/

/*/ --------------- Session Class --------------- /*/
class session{
private:
    vector< video* > current; // session.current[vCount] 
    int vCount;
    
public:
    session();
    session( video* newVid );
    ~session();
    
    void addVideo( video* newVid ); // Implement Save button
    void undoRec();                 // Implement Delete Button
    void print();
};
/*/ --------------- End Session Class --------------- /*/

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

/*/ --------------- End Terminal (Stack) Class --------------- /*/
class playBar{
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
    time_t startTime;
    time_t endTime;
    time_t currentTime;
public:
    playBar(sf::Vector2f position, int scale);
    void record(time_t currentTime);
    void setStartTime(time_t start);
    void setTime(time_t start,time_t end);
    void setCurrentTime(time_t currentTime);
    virtual void draw(sf::RenderWindow &window);
};



#endif /* projectClasses_h */


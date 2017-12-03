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
#include <mouse.hpp>
#ifndef projectClasses_h
#define projectClasses_h

using namespace std;

//-----------------------------------------------------------------
// GridEYE
//-----------------------------------------------------------------
class GridEYE{
    friend class video;
private:
    int runtime;
    int FPS;
    
    
    
public:
    GridEYE(); //Hint: My board has it set at 0x68 :)
    GridEYE( int frames, int time );
    GridEYE( int address );
    ~GridEYE();
    
    int read(int pixAddr);
    
    void reset(void);
    void test(int row, int col);    //Draw Test pattern
    
    short pixelL;
    int r,g,b;

    void setRunTime( int newTime );
    int getFPS();
    void setFPS( int temp );
};


//-----------------------------------------------------------------
// Frame
//-----------------------------------------------------------------
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


//-----------------------------------------------------------------
// Video
//-----------------------------------------------------------------
class video{
private:
    short frameCount;       // 10 Frames -> 1 Second
    vector< frame* > data;  // Storing up to 31,800 frames maximum
    
   // void set_max();
    //void set_mean();
    
public:
    video();
    video( GridEYE gridward );
    ~video();
    
    void addFrame(frame* fptr);
    int getframeCount();
    void exportVideo( string filename );
    void print();
};


//-----------------------------------------------------------------
// Session
//-----------------------------------------------------------------
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
//-----------------------------------------------------------------

#endif /* projectClasses_h */

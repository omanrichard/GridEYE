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
#include <cmath>
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
    int FPS;        // 1 or 10 FPS
    int runtime;    // Run Time in seconds
    bool DR;        // True: TRUE, Human: FALSE
    int fd;         // File Descriptor for I2C functions

public:
    GridEYE();      //Hint: My board has it set at 0x68 :)
    GridEYE( int frames, int time );
    GridEYE( int address );
    ~GridEYE();
    
    int read(int pixAddr);
    
    void reset(void);
    
    //removing soon
    void test(int row, int col);    //Draw Test pattern
    short pixelL;
    int r,g,b;
    //
    void setRunTime( int nTime );
    void setFPS( int nFPS );
    void setDR( bool nDR );
    
    int getRuntime();
    int getFPS();
    bool getDR();
    int getfd();
};

//-----------------------------------------------------------------
// pixMask Class
//-----------------------------------------------------------------
class pixMask{
private:
    int r,g,b;
    
public:
    pixMask();
    ~pixMask();
    
    void update( short temp );
    void testUpdate( short temp ); //New implimentation for speeed improvements
    int getr();    // access r value
    int getg();    // access g value
    int getb();    // access b value
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
    void set_max();                 // 5  [] [] [] [] [] [] [] []
    void set_mean();                // 6  [] [] [] [] [] [] [] []
                                    // 7  [] [] [] [] [] [] [] []
public:
    frame();
    frame(GridEYE gridward);
    frame( GridEYE* gPtr );
    ~frame();
    
    short access( short row , short col );
    short get_max();
    float get_mean();
    
    void new_max( short newMax );
    void new_mean( float newMean );
    
    void updateFrame( GridEYE PGE );
    void print();
    
};

//-----------------------------------------------------------------
// Video
//-----------------------------------------------------------------
class video{
private:
    short frameCount;       // 10 Frames -> 1 Second
    vector< frame* > data;  // Storing up to 31,800 frames maximum
    
    short max;
    float mean;
    
    void set_max();
    void set_mean();
    
public:
    video();
    video( GridEYE gridward );
    // Call using pointer or object?
    video( GridEYE* gPtr );
    ~video();
    
    void addFrame(frame* fptr);
    int getframeCount();
    void exportVideo( string filename );
    void print();
    frame* getFrame( int temp );
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

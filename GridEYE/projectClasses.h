//  projectClasses.h
//
//  Data Processing Application for Panasonic GridEYE using
//  RaspberryPi 3 and C++
//
//  Created by Grant Hilgert and Richard Oman on 12/1/17.
//
//  ECE 3220 Software Design in C and C++
//  Instructor: Dr. Luis Rivera
//  University of Missouri
//  Department of Electrical and Computer Engineering

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <cmath>
#include "Mouse.hpp"
#ifndef projectClasses_h
#define projectClasses_h

using namespace std;

//-----------------------------------------------------------------
// GridEYE
//-----------------------------------------------------------------
class GridEYE{
    friend class video;
private:
    int fd;         // File Descriptor for I2C functions

public:
    GridEYE();      //Hint: My board has it set at 0x68
    GridEYE( int frames, int time );
    GridEYE( int address );
    ~GridEYE();
    
    int FPS;        //1 or 10 FPS
    int runtime;    //Run Time in seconds
    bool DR;        //True: TRUE, Human: FALSE
    
    void setFD(void);
    int getfd();

    float read(int pixAddr);
    void reset(void);
    
    void setFPS( int nFPS );
 
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
    
    void update(float temp);
    void fastUpdate(float temp); //New implimentation for speeed improvements
    void monoUpdate(float temp);
    void newUpdate(float temp);
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
    float sensor_values[8][8];      // 4  [] [] [] [] [] [] [] []
                                    // 4  [] [] [] [] [] [] [] []
    void set_max();                 // 5  [] [] [] [] [] [] [] []
    void set_mean();                // 6  [] [] [] [] [] [] [] []
                                    // 7  [] [] [] [] [] [] [] []
public:
    frame();
    frame( GridEYE* gPtr );
    ~frame();
    
    short access( short row , short col );
    short get_max();
    float get_mean();
};

//-----------------------------------------------------------------
// Video
//-----------------------------------------------------------------
class video{
private:
    short frameCount;       //10 Frames -> 1 Second
    vector< frame* > data;  //Storing up to 31,800 frames maximum
    
    short max;
    float mean;
    void set_max();
    void set_mean();
    
public:
    video();
    ~video();
    
    void addFrame(frame* fptr);
    void exportVideo( string filename );
    void setframeCount( int count );
    
    int getframeCount();
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
    ~session();
    
    void addVideo( video* newVid ); // Implement Save button
    void undoRec();                 // Implement Delete Button
    void print();
    video* getVideo( int index );
};
//-----------------------------------------------------------------

#endif /* projectClasses_h */

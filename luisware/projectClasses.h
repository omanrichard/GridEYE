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

#ifndef projectClasses_h
#define projectClasses_h

using namespace std;

/*/ ----------- GrideEye Class ---------- /*/
class GridEYE{
friend class frame;
    
private:
    
public:
    GridEYE(int address); //Hint: its at 0x68
    
    int read(int row, int col);
    void reset(void);
    void update(void);
    void test(int row, int col);//Draw Test pattern
    int r,g,b;
    int FPS = 10;
    int runTime;            // Run Time in Seconds
    short pixelL;
};

/*/ ---------- End GridEYE Class ---------- /*/

/*/ --------------- Frame Class --------------- /*/
class frame{                        //      Stores sensor data
friend class GridEYE;               //     0  1  2  3  4  5  6  7
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
    void import_data( GridEYE gridward );

};
/*
class frame_mask : public frame {
private:
    vector< string > scale;
    string mask[8][8];
    
public:
    frame_mask();
    ~frame_mask();
    
    void print();
    void set_mask();
    
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
    video( GridEYE gridward );
    ~video();
    
    void exportVideo( string filename );
    void print();
};
/*/ --------------- End Video Class --------------- /*/

/*/ --------------- Session Class --------------- /*/
class session{
private:
    vector< class video* > currentSession;
    
public:
    session();
    ~session();
    
    void print();
};
/*/ --------------- End Session Class --------------- /*/

#endif /* projectClasses_h */


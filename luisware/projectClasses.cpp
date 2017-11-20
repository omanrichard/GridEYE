//
//  projectClasses.cpp
//  Project
//
//  Created by Grant Hilgert and Richard Oman on 11/11/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "projectClasses.h"

#define gridEyeAddr 0x68 // or 0x69 Address

using namespace std;
int r,c;

/*/ --------------- GridEYE Constructor --------------- /*/
GridEYE::GridEYE(int address){
    /*/
     I2C begin transmission @ address
     //Inisilize sensor
     /*/
}
/*/ --------------- GridEYE Methods --------------- /*/
int GridEYE::read(int row, int col){
    /*/ read code /*/
}
void GridEYE::reset(void){
    FPS = 10;
}
void GridEYE::test(int row, int col){
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
}
void GridEYE::update(void){
    
}
/*/ --------------- End GridEYE --------------- /*/
/*/ --------------- Frame Constructor --------------- /*/

frame::frame(){
    for( r=0 ; r < 8 ; r++ ){
        for( c=0 ; c < 8 ; c++){
            this->sensor_values[r][c] = 0;
        }
    }
    this->mean = 0;
    this->max = 0;
    return;
}

frame::frame(GridEYE gridward){
    for( r=0 ; r < 8 ; r++ ){
        for( c=0 ; c < 8 ;  c++){
            gridward.test( r,c );
            this->sensor_values[r][c] = gridward.pixelL;  // Receive value from device, end transmission
        }
    }
    return;
}

/*/ --------------- Frame Methods --------------- /*/
void frame::set_max(){
    short temp = 0;
    
    for( r=0 ; r < 8 ; r++ ){
        for( c=0 ; c < 8 ; c++ ){
            if( this->sensor_values[r][c] > temp )
                temp = this->sensor_values[r][c];
        }
    }
    this->max = temp;
}

void frame::set_mean(){
    float sum = 0;
    
    for( r=0 ; r < 8 ; r++ ){
        for( c=0 ; c < 8 ; c++ ){
            sum += this->sensor_values[r][c];
        }
    }
    this->mean = sum/64;
}

short frame::get_max(){
    return this->max;
}

float frame::get_mean(){
    return this->mean;
}

void frame::import_data( GridEYE gridward ){
    for( r=0 ; r < 8 ; r++ ){
        for( c=0 ; c < 8 ;  c++){
            gridward.test( r,c );
            this->sensor_values[r][c] = gridward.pixelL;  // Receive value from device, end transmission
        }
    }
    return;
}

void frame::print(){
    
    for( c=0 ; c < 8 ; c++){                                        // Frame No. : 1
        cout << "\t"                                    // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
        << "[ " << this->sensor_values[c][0] << " ] "   // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
        << "[ " << this->sensor_values[c][1] << " ] "   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
        << "[ " << this->sensor_values[c][2] << " ] "   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
        << "[ " << this->sensor_values[c][3] << " ] "   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
        << "[ " << this->sensor_values[c][4] << " ] "   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
        << "[ " << this->sensor_values[c][5] << " ] "   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
        << "[ " << this->sensor_values[c][6] << " ] "   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
        << "[ " << this->sensor_values[c][7] << " ] " << endl;
    }
    return;
}

short frame::access( short row , short col ){
        return this->sensor_values[row][col];    //Accesses data point in data array
}
/*/ ----- Frame Destructor ----- /*/
frame::~frame(){
}
/*/ --------------- End Frame --------------- /*/

/*/ --------------- maskFrame Methods --------------- /*/


/*/ --------------- Video Constructor --------------- /*/
video::video(){
    frame* temp;
    
    for( r=0 ; r<frameCount ; r++){
        GridEYE gridward( gridEyeAddr );    // Initialize and I2C GridEYE stuff
        temp = new frame( gridward );       // Collect data and create frame
        this->data.push_back( temp );       // Store pointer in data Vector
        this->frameCount++;
    }
    
    this->set_max();
    this->set_mean();
    return;
}

/*/ --------------- Video Methods --------------- /*/
void video::exportVideo( string filename ){
    fstream newOutput;  // Creates/Opens new output file
    newOutput.open( filename, ios::out );
    
    frame* temp;

    newOutput << "Number of frames: " << frameCount << " " << endl;    // Copies data from memory to file
    for( r=0; r < frameCount; r++ ){
        newOutput << "Frame No. : " << r << endl;
        temp = this->data[r];
                                                                   // Example Output
        for( c=0; c < 8 ; c++){                                   // Frame No. : 1
                newOutput << "\t[" << this->access( c, 0 ) << "] " // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8]
                          <<   "[" << this->access( c, 1 ) << "] " // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
                          <<   "[" << this->access( c, 2 ) << "] " // TAB [17] [18] [19] [20] [21] [22] [23] [24]
                          <<   "[" << this->access( c, 3 ) << "] " // TAB [25] [26] [27] [28] [29] [30] [31] [32]
                          <<   "[" << this->access( c, 4 ) << "] " // TAB [33] [34] [35] [36] [37] [38] [39] [40]
                          <<   "[" << this->access( c, 5 ) << "] " // TAB [41] [42] [43] [44] [45] [46] [47] [48]
                          <<   "[" << this->access( c, 6 ) << "] " // TAB [49] [50] [51] [52] [53] [54] [55] [56]
                          <<   "[" << this->access( c, 7 ) << "] " // TAB [57] [58] [59] [60] [61] [62] [63] [64]
                          << endl;
        }
        
        newOutput << "\tMax value: " << this->get_max() << endl
                  << "\tAverage: "   << this->get_mean() << endl << endl;
        
    }
    
    newOutput.close( ); // Close file
    return;
}

void video::set_max(){
    short temp;
    
    while(temp < this->frameCount){
        frame* framePtr = data[temp];
        for( r=0 ; r < 8 ; r++ ){
            for( c=0 ; c < 8 ; c++ ){
                if( framePtr->access(r,c) > temp )
                    temp = framePtr->access(r,c);
            }
        }
        framePtr->new_max( temp );
        temp++;
    }
}

void video::set_mean(){
    short temp;
    float sum;
    
    while(temp < this->frameCount){
        frame* framePtr = data[temp];
        for( r=0 ; r < 8 ; r++ ){
            for( c=0 ; c < 8 ; c++ ){
                sum += framePtr->access(r,c);
            }
        }
        sum = sum/64;
        framePtr->new_mean( sum );
        temp++;
    }
 
}
 
/*/ --------------- End Video Methods --------------- /*/


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
int i,j,k;

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
    for( i=0 ; i<8 ; i++ ){
        for( j=0 ; j<8 ;  j++){
            this->sensor_values[i][j] = 0;
        }
    }
    this->mean = 0;
    this->max = 0;
    return;
}

frame::frame(GridEYE gridward){
    for( i=0 ; i < 8 ; i++ ){
        for( j=0 ; j < 8 ;  j++){
            gridward.test( i,j );
            this->sensor_values[i][j] = gridward.pixelL;  // Receive value from device, end transmission
        }
    }
    return;
}

/*/ --------------- Frame Methods --------------- /*/

void frame::set_max(){
    short temp = 0;
    
    for( i=0 ; i < 8 ; i++ ){
        for( j=0 ; j < 8 ; j++ ){
            if( this->sensor_values[i][k] > temp )
                temp = this->sensor_values[i][j];
        }
    }
    return;
}

void frame::set_mean(){
    float sum = 0;
    
    for( i=0 ; i < 8 ; i++ ){
        for( j=0 ; j < 8 ; j++ ){
            sum += this->sensor_values[i][j];
        }
    }
    this->mean = sum/64;
}

void frame::get_data( GridEye gridward ){
    for( i=0 ; i < 8 ; i++ ){
        for( j=0 ; j < 8 ;  j++){
            gridward.test( i,j );
            this->sensor_values[i][j] = gridward.pixelL;  // Receive value from device, end transmission
        }
    }
    return;
}

void frame::print(){
    
    for( j=0 ; j < 8 ; j++){                                        // Frame No. : 1
        cout << "\t"                                    // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
        << "[ " << this->sensor_values[j][0] << " ] "   // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
        << "[ " << this->sensor_values[j][1] << " ] "   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
        << "[ " << this->sensor_values[j][2] << " ] "   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
        << "[ " << this->sensor_values[j][3] << " ] "   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
        << "[ " << this->sensor_values[j][4] << " ] "   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
        << "[ " << this->sensor_values[j][5] << " ] "   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
        << "[ " << this->sensor_values[j][6] << " ] "   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
        << "[ " << this->sensor_values[j][7] << " ] " << endl;
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
    
    for( i=0 ; i<frameCount ; i++){
        temp = new frame( GridEYE gridward );
        this->data.push_back( temp );
        this->frameCount++;
    }
    return;
}

/*/ --------------- Video Methods --------------- /*/
void video::exportVideo( string filename ){
    fstream newOutput;  // Creates/Opens new output file
    newOutput.open( filename, ios::out );
    
    frame* temp;

    newOutput << "Number of frames: " << frameCount << " " << endl;    // Copies data from memory to file
    for( i = 0; i < frameCount; i++ ){
        newOutput << "Frame No. : " << i << endl;
        temp = this->data[i];
                                                                   // Example Output
        for( j=0 ; j < 8 ; j++){                                   // Frame No. : 1
                newOutput << "\t[" << this->access( j, 0 ) << "] " // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8]
                          <<   "[" << this->access( j, 1 ) << "] " // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
                          <<   "[" << this->access( j, 2 ) << "] " // TAB [17] [18] [19] [20] [21] [22] [23] [24]
                          <<   "[" << this->access( j, 3 ) << "] " // TAB [25] [26] [27] [28] [29] [30] [31] [32]
                          <<   "[" << this->access( j, 4 ) << "] " // TAB [33] [34] [35] [36] [37] [38] [39] [40]
                          <<   "[" << this->access( j, 5 ) << "] " // TAB [41] [42] [43] [44] [45] [46] [47] [48]
                          <<   "[" << this->access( j, 6 ) << "] " // TAB [49] [50] [51] [52] [53] [54] [55] [56]
                          <<   "[" << this->access( j, 7 ) << "] " // TAB [57] [58] [59] [60] [61] [62] [63] [64]
                          << endl;
        }
        newOutput << "\tMax value: " << this->get_max() << endl
        << "\tAverage: " << this->get_mean() << endl << endl;
    }
    newOutput.close( ); // Close file
    return;
}

short video::set_max(){
    
    while(temp < this->frameCount){
        frame* framePtr = data[temp];
        for( i=0 ; i < 8 ; i++ ){
            for( j=0 ; j < 8 ; j++ ){
                if( framePtr->sensor_values[i][k] > temp )
                    temp = framePtr->sensor_values[i][j];
            }
        }
        temp++;
    }
}

float video::set_mean(){
    while(temp < this->frameCount){
        frame* framePtr = data[temp];
        for( i=0 ; i < 8 ; i++ ){
            for( j=0 ; j < 8 ; j++ ){
                sum += framePtr->sensor_values[i][j];
            }
        }
        framePtr->mean = sum/64;
        temp++;
    }
}
/*/ --------------- End Video Methods --------------- /*/


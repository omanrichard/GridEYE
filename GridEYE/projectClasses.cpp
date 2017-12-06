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
#include <cmath>
#include "projectClasses.h"
#include <wiringPiI2C.h>

#define PGE 0x68
#define PCR 0x00

using namespace std;
int row,col;

short fastVideo::playVideo(int frameNumber, int row, int col){
    int address = 0x80 + (10*2*row + 2*col);
    return videoFile[frameNumber].frame[address];
}



//-----------------------------------------------------------------
// GridEYE Constructors
//-----------------------------------------------------------------GridEYE::GridEYE(){

GridEYE::GridEYE(){
    
        fd = wiringPiI2CSetup( PGE );
        wiringPiI2CWriteReg16(fd, PCR, 0);
     
        FPS = 10;
        runtime = 10;
}
// Will remove eventually
GridEYE::GridEYE( int address ){
    FPS = 10;
    runtime = 10;
}

//-----------------------------------------------------------------
// GridEYE Methods
//-----------------------------------------------------------------
int GridEYE::read( int pixAddr ){
    int temp = 0;
    float result = 0;
    
    //temp = rand() % 90;
    
    
    wiringPiI2CWriteReg16( fd, pixAddr, 1 );     // Write to pixel, requests data
    temp = wiringPiI2CReadReg16( fd, pixAddr );  // Receive value from pixel
    wiringPiI2CWriteReg16( fd, pixAddr, 0);
                                                // Pixels have 12-bit data
     temp = temp&0x0800;                        // Right shift 1 removes sign
     temp = temp >> 1;                          //
    
    while( temp > 0 ){
        temp -= 0x04;
        result += 0.25
    }
    
    return result;
}

void GridEYE::reset(void){
    FPS = 10;
    runtime = 10;
        wiringPiI2CWriteReg16( fd, 0x02, 0 ); // Resets Frame rate register to default
    DR = true;
    return;
}

void GridEYE::setFD(void){
    //fd = wiringPiI2CSetup( PGE );
}

int GridEYE::getfd(){
    return this->fd;
}

void GridEYE::setFPS(int temp){
    this->FPS = temp;
    
     try{
        if( temp == 1 || temp == 10 )
        throw -1;
        if( temp == 1 )
            wiringPiI2CWriteReg16( fd, 0x02, 1 );   // Sets Frame rate register to 1 FPS
        if( temp == 10 )
            wiringPiI2CWriteReg16(fd, 0x02, 0);     // Sets Frame rate register to 10 FPS
     }
     catch( int ){
         cout << "Exception Handled: invalid setting value" << endl;
     }
    
        return;
     }

GridEYE::~GridEYE(){
    
}


//-----------------------------------------------------------------
// pixMask Methods
//-----------------------------------------------------------------
pixMask::pixMask(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
    
    return;
}

pixMask::~pixMask(){}

int pixMask::getr(){
    return this->r;
}

int pixMask::getg(){
    return this->g;
}

int pixMask::getb(){
    return this->b;
}
void pixMask::lazyUpdate(float temp){
    
    switch(temp){

    
    
    
    }
}
void pixMask::fastUpdate( float temp ){
//Mapped data to a graph and used cos and sin to reconstruct it
//Should increases speed
//0 through 540 degrees of resoultion masked to 0 through 255 color values converted to radians by 180/PI
    int tempr = 255*cos(((540*temp)/255)*(180/3.14159));
    int tempg = -1*255*sin(2*((540*temp)/255)*(180/3.14159));
    int tempb = 255*sin(((540*temp)/255)*(180/3.14159));
    //Bound wave between 0 and 255. Clip wave below 0
    if(tempr > 0 && tempr <= 127){
        this->r = tempr;
    }
    else if(tempr < 1){
        this->r = 0;
    }
    else if(tempr > 127){
        this->r = 127;
    }
    
    if(tempg > 0 && tempr <= 127){
        this->g = tempg;
    }
    else if(tempg < 1){
        this->g = 0;
    }
    else if(tempg > 127){
        this->r = 127;
    }
    if(tempb > 0 && tempr <= 127){
        this->b = tempb;
    }
    else if(tempb < 1){
        this->b = 0;
    }
    else if(tempb > 127){
        this->r = 127;
    }
    
    this->g = -1*255*sin(((540*temp)/255)*(180/3.14159));
    this->b = 255*sin(((540*temp)/255)*(180/3.14159));
}
void pixMask::monoUpdate(float temp){
    this->r = temp;
    this->g = 0;
    this->b = 0;
}
void pixMask::update( float temp ){
    int R1 = 0;
    int G1 = 0;
    int B1 = 0;
    int phase = 1;
    
    for(int i = 0; i < 255; i++){
        if( temp >= i && temp < i+1){
            this->r = R1;
            this->g = G1;
            this->b = B1;
        }
        
        if(phase == 7){
            G1 += 15;
            B1 += 15;
        }
        
        if(phase == 6){
            G1 -= 15;
            if(G1 <= 0)
                phase = 7;
        }
        
        if(phase == 5){
            R1 += 15;
            if(R1 >= 252)
                phase = 6;
        }
        
        if(phase == 4){
            B1 -= 15;
            if(B1 <= 0)
                phase = 5;
        }
        
        if(phase == 3){
            G1 += 15;
            if( G1 >= 252)
                phase = 4;
        }
        
        if(phase == 2){
            R1 -= 15;
            if( R1 <= 0)
                phase = 3;
        }
        
        if(phase == 1){
            R1 += 15;
            B1 += 15;
            if( R1 >= 252)
                phase = 2;
        }
    } // end for
}

//----------------------------------------------------------------
// Frame Methods
//----------------------------------------------------------------
frame::frame(){
    //fastFrame newFrame;
    for( row=0 ; row < 8 ; row++ ){
        for( col=0 ; col < 8 ; col++){
            //newFrame.frame[row][col] = 0;
        }
    }
    this->mean = 0;
    this->max = 0;
    return;
}

/*
frame::frame(GridEYE &gridward){
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            //newFrame.frame[row][col] = gridward.randTemp();
            //this->sensor_values[row][col] = gridward.randTemp();  // Receive value from device, end transmission
        }
    }
    set_max();
    set_mean();
    return;
}
*/

frame::frame(GridEYE* gPtr){
    short temp = 0;
    int pixAddr = 0x80;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            temp = gPtr->read( pixAddr );                   // Read Thermistor Data
            this->sensor_values[row][col] = temp;    // Stores temp value in sensor table
            pixAddr += 2;                                   // Increment to next pixel
        }
    }
    set_max();
    set_mean();
    return;
}
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Frame Methods
//-----------------------------------------------------------------
void frame::set_max(){
    short temp = 0;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            if( this->sensor_values[row][col] > temp )
                temp = this->sensor_values[row][col];
        }
    }
    this->max = temp;
}


void frame::set_mean(){
    float sum = 0;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            sum += this->sensor_values[row][col];
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

short frame::access( short row , short col ){
    return this->sensor_values[row][col];    //Accesses data point in data array
}

frame::~frame(){
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Video Constructors
//-----------------------------------------------------------------
video::video(){
    this->frameCount = 0;
    this->mean = 0;
    this->max = 0;
    
    cout << "Video Created" << endl;
}

video::video( GridEYE* gPtr ){
    frame* temp;
    
    frameCount = ( gPtr->FPS * gPtr->runtime );
    
    for( int x = 0 ; x < frameCount ; x++){
        if( gPtr->FPS == 10 ){
        }
        else{
        }
        temp = new frame( gPtr );       // Collect data and create frame
        this->data.push_back( temp );       // Store pointer in data Vector
    }
    //this->set_max();
    //this->set_mean();
    return;
}
//-----------------------------------------------------------------
// Video Methods
//-----------------------------------------------------------------
void video::addFrame(frame* fPtr){
    this->data.push_back(fPtr);
    this->frameCount++;
    //this->set_max();
    //this->set_mean();
}

int video::getframeCount(){
    return this->frameCount;
}

void video::setframeCount( int count ){
    this->frameCount = count;
}

void video::exportVideo( string filename ){
    frame* temp = NULL;
    fstream newOutput;                      // Creates/Opens new output file
    newOutput.open( filename, ios::out );

    newOutput << "Frame Count: " << this->frameCount
              << " Avg. Temp: "   << this->mean
              << " Max Temp: "    << this->max
              << endl;
    temp = this->getFrame(0);
    for( int x = 0 ; x < frameCount ; x++ ){
        

        newOutput << "Frame No. : " << x + 1 << endl;
        for( row = 0 ; row < 8 ; row++ ){                                        // Frame No. : 1
            newOutput << "\t"                           // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
            << "[ " << temp->access(row, 0) << " ]\t"   // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
            << "[ " << temp->access(row, 1) << " ]\t"   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
            << "[ " << temp->access(row, 2) << " ]\t"   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
            << "[ " << temp->access(row, 3) << " ]\t"   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
            << "[ " << temp->access(row, 4) << " ]\t"   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
            << "[ " << temp->access(row, 5) << " ]\t"   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
            << "[ " << temp->access(row, 6) << " ]\t"   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
            << "[ " << temp->access(row, 7) << " ]\t" << endl;
        }
        temp = this->getFrame(x);
    }
    newOutput.close( ); // Close file
    return;
}

frame* video::getFrame( int frameNum ){
    return this->data[frameNum];
}

/*
void video::set_max(){
    short temp = 0;
    frame* framePtr = NULL;
    
    while(temp < this->frameCount){
        framePtr = data[temp];
        for( row = 0 ; row < 8 ; row++ ){
            for( col = 0 ; col < 8 ;  col++){
                if( framePtr->access(row,col) > temp )
                    temp = framePtr->access(row,col);
            }
        }
        temp++;
    }
    framePtr->new_max( temp );
    return;
}

void video::set_mean(){
    short temp = 0;
    float sum = 0;
    frame* framePtr = NULL;
    
    while(temp < this->frameCount){
        framePtr = data[temp];
        for( row = 0 ; row < 8 ; row++ ){
            for( col = 0 ; col < 8 ;  col++){
                sum += framePtr->get_mean();
            }
        }
        temp++;
    }
    framePtr->new_mean( sum / (64*frameCount) );
}
*/
video::~video(){
    
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Session Methods
//-----------------------------------------------------------------
session::session(){     // Default Constructor
    this->vCount = 0;                           // Initializes video count to zero
    this->current.push_back( NULL );
    cout << "Session Started" << endl << endl;
    return;
}

session::session( video* newVid ){      // constructor adds video pointer to session array
    cout << "Session Started" << endl << endl;
    try{
        if( !( this->vCount < 1 ) )
            throw -1;                       // Maybe throw error class instead, can do something later in main
        this->current.push_back( newVid );  // Adds video pointer into the array in first position
        this->vCount++;
    }
    catch( int ){
        cout << "Exception Handled" << endl;
    }
}

void session::addVideo( video* newVid ){
    if( vCount == 0 )
        this->current[0] = newVid;
    else
        this->current.push_back( newVid );  // Append "active" recording to video stack
    this->vCount++;                         // Update video count value
}

void session::undoRec(){        // Removes "active" recording from the stack of videos
    if( vCount == 0 ){
        this->current.push_back( NULL );
    }
    this->current.pop_back();   // pop_back() removes last value, decrements vector size by 1
    this->vCount--;             // update video count value

}

video* session::getVideo( int index ){
    return this->current[index];
}

session::~session(){}
//-----------------------------------------------------------------




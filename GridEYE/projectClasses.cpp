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
int row,col;

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
    for( row=0 ; row < 8 ; row++ ){
        for( col=0 ; col < 8 ; col++){
            this->sensor_values[row][col] = 0;
        }
    }
    this->mean = 0;
    this->max = 0;
    return;
}

frame::frame(GridEYE gridward){
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            gridward.test( row,col );
            gridward.pixelL = gridward.g;
            this->sensor_values[row][col] = gridward.pixelL;  // Receive value from device, end transmission
        }
    }
    set_max();
    set_mean();
    return;
}

/*/ --------------- Frame Methods --------------- /*/
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

void frame::import_data( GridEYE gridward ){
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            gridward.test( row , col );
            this->sensor_values[row][col] = gridward.pixelL;  // Receive value from device, end transmission
        }
    }
    return;
}

void frame::print(){
    
    for( col = 0 ; col < 8 ; col++){                                        // Frame No. : 1
        cout << "\t"                                    // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
        << "[ " << this->sensor_values[col][0] << " ] "   // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
        << "[ " << this->sensor_values[col][1] << " ] "   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
        << "[ " << this->sensor_values[col][2] << " ] "   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
        << "[ " << this->sensor_values[col][3] << " ] "   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
        << "[ " << this->sensor_values[col][4] << " ] "   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
        << "[ " << this->sensor_values[col][5] << " ] "   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
        << "[ " << this->sensor_values[col][6] << " ] "   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
        << "[ " << this->sensor_values[col][7] << " ] " << endl;
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
video::video( GridEYE gridward ){
    frame* temp;
    gridward.runTime=1;
    
    this->frameCount = (gridward.FPS * gridward.runTime);
    
    for( int x = 0 ; x < frameCount ; x++){
        temp = new frame( gridward );       // Collect data and create frame
        this->data.push_back( temp );       // Store pointer in data Vector
        //this->frameCount++;
    }
    this->set_max();
    this->set_mean();
    return;
}

/*/ --------------- Video Methods --------------- /*/
void video::exportVideo( string filename ){
    fstream newOutput;                      // Creates/Opens new output file
    newOutput.open( filename, ios::out );
    
    newOutput << "*" << frameCount;    // Copies data from memory to file
    
    for( int x = 0; x < frameCount; x++ ){
        frame* temp = (data[x]);
        newOutput << "%" << x;                                              // Begin Packet % indicates frame number
        newOutput << "&" << temp->get_max() << "&" << temp->get_mean();     // & indicates sub-data value
        for( int y = 0; y < 8 ; y++){
                newOutput << "@" << "$" << temp->access( y, 0 )             // @ indicates row begin
                                 << "$" << temp->access( y, 1 )
                                 << "$" << temp->access( y, 2 )                  // $ indicates data value
                                 << "$" << temp->access( y, 3 )
                                 << "$" << temp->access( y, 4 )
                                 << "$" << temp->access( y, 5 )
                                 << "$" << temp->access( y, 6 )
                                 << "$" << temp->access( y, 7 );
        }
        newOutput << "#"; // End Packet
        
    }
    newOutput.close( ); // Close file
    return;
}

void video::set_max(){
    short temp;
    frame* framePtr;
    
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
    short temp;
    float sum;
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

void video::print(){
    frame* temp;
    for( row = 0 ; row < frameCount ; row++ ){
        temp = this->data[row];
        cout << "Frame No. : " << row + 1 << endl;
        for( col = 0 ; col < 8 ; col++){                     // Frame No. : 1
            cout << "\t"                               // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
            << "[ " << temp->access(col, 0) << " ]\t"   // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
            << "[ " << temp->access(col, 1) << " ]\t"   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
            << "[ " << temp->access(col, 2) << " ]\t"   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
            << "[ " << temp->access(col, 3) << " ]\t"   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
            << "[ " << temp->access(col, 4) << " ]\t"   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
            << "[ " << temp->access(col, 5) << " ]\t"   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
            << "[ " << temp->access(col, 6) << " ]\t"   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
            << "[ " << temp->access(col, 7) << " ]" << endl;
        }
    }
}

void frame::new_max( short newMax ){
    this->max = newMax;
}
void frame::new_mean( float newMean ){
    this->mean = newMean;
}
video::~video(){
   
}
/*/ --------------- End Video Methods --------------- /*/

/*/ --------------- Session Methods --------------- /*/
session::session(){     // Default Constructor
    this->vCount = 0;                           // Initializes video count to zero
    cout << "Session Started" << endl << endl;
    return;
}
session::session( video* newVid ){ // Default constructor adds video pointer to session array
    cout << "Session Started" << endl << endl;
    this->current.push_back( newVid );
    this->vCount++;
}


void session::addVideo( video* newVid ){
    this->current.push_back( newVid ); // Append "active" recording to video stack
    this->vCount++;                     // Update video count value
}

void session::undoRec(){        // Removes "active" recording from the stack of videos
    this->current.pop_back();   // pop_back() removes last value, decrements vector size by 1
    this->vCount--;             // update video count value
}

session::~session(){}

/*/ --------------- End Session Methods --------------- /*/


/*/ --------------- Terminal (Stack) Methods --------------- /*/
terminal::terminal(int size, string text){
    for(int i = 0; i <= size; i++){
        stack.push_back(" "); //Adds empty values to prevent crash
   }
    rootText = text;
    
}

void terminal::print(string input){
    stack.insert(stack.begin(),rootText+" : "+input);
    
}
void terminal::print(string input, string text){
    stack.insert(stack.begin(),text+" : "+input);
}
string terminal::read(int index){
    return stack[index];
}
void terminal::setRoot(string text){
    rootText = text;
}
/*/ --------------- End Terminal (Stack) Methods --------------- /*/

playBar::playBar(int x, int y, int scale){
    if (!t_background.loadFromFile("audio-player.png")) {
        return EXIT_FAILURE;
    }
    if (!t_fillBar.loadFromFile("progress.png")) {
        return EXIT_FAILURE;
    }
    background.setTexture(t_background);
    fillBar.setTexture(t_fillBar);
    background.setPosition(x-150,y-150);
    background.scale(scale, scale);
    
    fillBar.setPosition(x,y);
    fillBar.scale(1, 1);
}
void playBar::update(int percent){
  
    
   
    
}
void playBar::draw(sf::RenderWindow &window){
    window.draw(background);
    window.draw(fillBar);
}

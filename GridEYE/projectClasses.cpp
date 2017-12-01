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
//#include <wiringPiI2C.h>

#define gridEyeAddr 0x68

using namespace std;
int row,col;

/*/ --------------- GridEYE Constructor --------------- /*/
GridEYE::GridEYE(int address){
    /*
     I2C begin transmission @ address
     int temp = 0;
     int pixAddr = 0x80;
     
     int fd = wiringPiI2CSetup( gridEyeAddr );
     
     wiringPiI2CWrite( fd, cmd );
     
     for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            wiringPiI2CWriteReg16( fd, pixAddr, 1 );
            temp = wiringPiI2CReadReg16(fd, pixAddr);  // Receive value from device, end transmission
     
            temp = temp >> 4;                   // Thermistor data is 12-bit
                                            // Shift 4 will remove 4-bit precision bits
            this->sensor_values[row][col] = (short)temp;
            pixAddr += 2;
        }
     }
     set_max();
     set_mean();
     return;
     */
}
/*/ --------------- GridEYE Methods --------------- /*/
short GridEYE::read(int row, int col){
    return this->sensor_values[row][col];    //Accesses data point in data array
}

void GridEYE::reset(void){
    FPS = 10;
}
void GridEYE::test(int row, int col){
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
}

int GridEYE::getFPS(){
    return this->FPS;
}

void GridEYE::setFPS(int temp){
    this->FPS = temp;
    return;
}
/*
void GridEYE::set_max(){
    short temp = 0;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            if( this->sensor_values[row][col] > temp )
                temp = this->sensor_values[row][col];
        }
    }
    this->max = temp;
}

void GridEYE::set_mean(){
    float sum = 0;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            sum += this->sensor_values[row][col];
        }
    }
    this->mean = sum/64;
}

short GridEYE::get_max(){
    return this->max;
}

float GridEYE::get_mean(){
    return this->mean;
}

void GridEYE::print(){
    
    for( col = 0 ; col < 8 ; col++){                                        // Frame No. : 1
        cout << "\t"                                      // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
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
*/

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

void frame::print(){
    
    for( col = 0 ; col < 8 ; col++){                                        // Frame No. : 1
        cout << "\t"                                      // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
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
video::video(){
    this->frameCount = 0;
    
}
video::video( GridEYE gridward ){
    frame* temp;
    gridward.runTime = 65;
    gridward.setFPS( 10 );
    
    this->frameCount = (gridward.getFPS() * gridward.runTime);
    
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
void video::addFrame(GridEYE gridward){
    frame* temp = new frame( gridward );
    this->data.push_back(temp);
    this->frameCount++;
    this->set_max();
    this->set_mean();
}

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
                                 << "$" << temp->access( y, 2 )             // $ indicates data value
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
        for( col = 0 ; col < 8 ; col++){                // Frame No. : 1
            cout << "\t"                                // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
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
    this->current.push_back( newVid );  // Append "active" recording to video stack
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
   
    if (!terminalFont.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    terminalText1.setString("UNDEFINED");
    terminalText2.setString("UNDEFINED");
    terminalText3.setString("UNDEFINED");
    terminalText4.setString("UNDEFINED");
    terminalText5.setString("UNDEFINED");
    terminalText6.setString("UNDEFINED");
    
    terminalText1.setFont(terminalFont);
    terminalText2.setFont(terminalFont);
    terminalText3.setFont(terminalFont);
    terminalText4.setFont(terminalFont);
    terminalText5.setFont(terminalFont);
    terminalText6.setFont(terminalFont);
    
    terminalText1.setCharacterSize(12);
    terminalText2.setCharacterSize(12);
    terminalText3.setCharacterSize(12);
    terminalText4.setCharacterSize(12);
    terminalText5.setCharacterSize(12);
    terminalText6.setCharacterSize(12);
   
    terminalBackground.setSize(sf::Vector2f( 625, 94 ));
    terminalHeader.setSize(sf::Vector2f( 625, 10 ));
    
    terminalText1.setFillColor(sf::Color(0,255,0));
    terminalText2.setFillColor(sf::Color(0,255,0));
    terminalText3.setFillColor(sf::Color(0,255,0));
    terminalText4.setFillColor(sf::Color(0,255,0));
    terminalText5.setFillColor(sf::Color(0,255,0));
    terminalText6.setFillColor(sf::Color(0,255,0));
    
    terminalBackground.setFillColor(sf::Color(0,0,0,150));
    terminalHeader.setFillColor(sf::Color(255,94,20,150));
    
    terminalText1.setPosition( 100 , 608);
    terminalText2.setPosition( 100 , 622);
    terminalText3.setPosition( 100 , 636);
    terminalText4.setPosition( 100 , 650);
    terminalText5.setPosition( 100 , 664);
    terminalText6.setPosition( 100 , 678);
    
    terminalBackground.setPosition(94, 606);
    terminalHeader.setPosition(94, 596);
    
    
    
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
void terminal::draw(sf::RenderWindow &window){
    
    terminalText1.setString(stack[5]);
    terminalText2.setString(stack[4]);
    terminalText3.setString(stack[3]);
    terminalText4.setString(stack[2]);
    terminalText5.setString(stack[1]);
    terminalText6.setString(stack[0]);
    
    window.draw(terminalText1);
    window.draw(terminalText2);
    window.draw(terminalText3);
    window.draw(terminalText4);
    window.draw(terminalText5);
    window.draw(terminalText6);
    window.draw(terminalBackground);
    window.draw(terminalHeader);
    
    
    
}
/*/ --------------- End Terminal (Stack) Methods --------------- /*/

playBar::playBar(sf::Vector2f position, int scale){
    if (!t_background.loadFromFile("audio-player.png")) {
        return EXIT_FAILURE;
    }
    if (!t_fillBar.loadFromFile("progress.png")) {
        return EXIT_FAILURE;
    }
    if (!playBarFont.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    background.setTexture(t_background);
    fillBar.setTexture(t_fillBar);
    background.setPosition(position);
    background.scale(scale, scale);
    
    fillPos.x = position.x + 235;
    fillPos.y = position.y + 164;
    fillBar.setPosition(fillPos);
    fillBar.scale(1, 1);
    
    timeTextStruct = localtime(&endTime);
    strftime (timeTextBuffer,8,"%R",timeTextStruct);
    currentTimeText.setString(timeTextBuffer);
    endTimeText.setString(timeTextBuffer);
    
    currentTimeText.setCharacterSize(12);
    currentTimeText.setFillColor(sf::Color::White);
    currentTimeText.setFont(playBarFont);
    currentTimeText.setPosition(position.x+465,position.y+158);
    
    endTimeText.setCharacterSize(12);
    endTimeText.setFillColor(sf::Color::White);
    endTimeText.setFont(playBarFont);
    endTimeText.setPosition(position.x+510,position.y+158);
    
    
    
}
void playBar::setCurrentTime(time_t time){
    currentTime = time;
    double totalSeconds = difftime(endTime,startTime);
    double percent = difftime(currentTime,startTime);
    percent = totalSeconds/percent;
    fillBar.setScale(percent,1);
    
    timeTextStruct = localtime(&currentTime);
    strftime (timeTextBuffer,8,"%M:%S",timeTextStruct);
    currentTimeText.setString(timeTextBuffer);
    
    timeTextStruct = localtime(&endTime);
    strftime (timeTextBuffer,8,"%M:%S",timeTextStruct);
    endTimeText.setString(timeTextBuffer);
}
void playBar::draw(sf::RenderWindow &window){
   
    
    
    window.draw(background);
    window.draw(fillBar);
    window.draw(currentTimeText);
    window.draw(endTimeText);
}
void playBar::setStartTime(time_t start){
    startTime = start;
}
void playBar::setTime(time_t start,time_t end){
    startTime = start;
    endTime = end;
}
void playBar::record(time_t currentTime){
    double seconds = difftime(currentTime,startTime);
    currentTimeText.setString(std::to_string(int(seconds/60))+":"+std::to_string(int(fmod(seconds,60))));
    endTimeText.setString("00:00");
    fillBar.setScale(1,1);
}
toolbar::toolbar(void){
    
    if (!t_settings.loadFromFile("settings.png")) {
        return EXIT_FAILURE;
    }
    if (!t_record.loadFromFile("record.png")) {
        return EXIT_FAILURE;
    }
    if (!t_stop.loadFromFile("stop.png")) {
        return EXIT_FAILURE;
    }
    if (!t_play.loadFromFile("play.png")) {
        return EXIT_FAILURE;
    }
    if (!t_trash.loadFromFile("trash.png")) {
        return EXIT_FAILURE;
    }
    if (!t_save.loadFromFile("save.png")) {
        return EXIT_FAILURE;
    }
    if (!t_quit.loadFromFile("gravestone.png")) {
        return EXIT_FAILURE;
    }
    
    
    
    
    
    play.setTexture( t_play );
    settings.setTexture( t_settings );
    record.setTexture( t_record );
    stop.setTexture( t_stop );
    save.setTexture( t_save );
    trash.setTexture( t_trash );
    quit.setTexture( t_quit );
    
    settings.setPosition( 15, 30 );
    record.setPosition( 15, 109+15 );
    play.setPosition( 15, 188+30 );
    stop.setPosition( 15, 267+45);
    save.setPosition( 15, 346+60 );
    trash.setPosition( 15, 425+75 );
    quit.setPosition( 15, 504+90 );
    toolbarFrame.setPosition(0, 0);
    toolbarHeader.setPosition(89, 0);
    
    toolbarFrame.setFillColor(sf::Color(132, 101, 142,100));
    toolbarHeader.setFillColor(sf::Color(0, 0, 0,100));
    
    settings.scale(0.50, 0.50);
    record.scale(0.50, 0.50);
    play.scale(0.50, 0.50);
    stop.scale(0.50, 0.50);
    save.scale(0.50, 0.50);
    trash.scale(0.50, 0.50);
    quit.scale(0.50, 0.50);
    
    toolbarFrame.setSize(sf::Vector2f( 94, 700 ));
    toolbarHeader.setSize(sf::Vector2f( 5, 700 ));
    
    
    
}
void toolbar::draw(sf::RenderWindow &window){
                    window.draw(toolbarFrame);
                    window.draw(toolbarHeader);
                    window.draw(settings);
                   window.draw(record);
                   window.draw(stop);
                   window.draw(play);
                   window.draw(trash);
                   window.draw(save);
                   window.draw(quit);
}

settingsMenu::settingsMenu(void){
    
    if(!t_close.loadFromFile("cancel.png")){
        return EXIT_FAILURE;
    }
    if (!settingsFont.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    settingsExit.setTexture(t_close);
    settingsExit.setPosition(143,93);
    settingsExit.scale(0.1, 0.1);
    
    
    // Settings Button Position
    settingsTenFPS.setPosition(rootx+100 ,rootY+75 );   //Default
    settingsOneFPS.setPosition(rootx+325 ,rootY+75 );
    settingsMinsBox.setPosition(rootx+75 ,rootY+175 );
    settingsSecondsBox.setPosition(rootx+300 ,rootY+175 );
    settingsMinsUp.setPosition(rootx+150 ,rootY+175);
    settingsMinsDown.setPosition(rootx+150 ,rootY+200);
    settingsSecondsUp.setPosition(rootx+375 ,rootY+175 );
    settingsSecondsDown.setPosition(rootx+375 ,rootY+200 );
    settingsRangeTrue.setPosition(rootx+75 ,rootY+300 );
    settingsRangeHuman.setPosition(rootx+325 ,rootY+300 );
    settingsReset.setPosition(rootx+50 ,rootY+350 );
    settingsApply.setPosition(rootx+300 ,rootY+350 );
    settingsBackground.setPosition(-500, -500);
    settingsBackground.setPosition(rootx,rootY);    //Move settings background in place
    
    
    //Set Char size
    settingsFPSText.setCharacterSize(30);
    settingsFPSTextValTen.setCharacterSize(20);
    settingsFPSTextValOne.setCharacterSize(20);
    settingsCollectionText.setCharacterSize(30);
    settingsMinsText.setCharacterSize(40);
    settingsSecondsText.setCharacterSize(40);
    settingsRangeText.setCharacterSize(30);
    settingsRangeTextTrue.setCharacterSize(20);
    settingsRangeTextHuman.setCharacterSize(20);
    settingsResetText.setCharacterSize(20);
    settingsApplyText.setCharacterSize(20);
    
    //set strings
    settingsFPSText.setString("Frames Per Second");
    settingsFPSTextValTen.setString("10 FPS");
    settingsFPSTextValOne.setString("1 FPS");
    settingsCollectionText.setString("Collection Time");
    settingsMinsText.setString("0");
    settingsSecondsText.setString("0");
    settingsRangeText.setString("Sensor Dynamic Range");
    settingsRangeTextTrue.setString("True");
    settingsRangeTextHuman.setString("Human");
    settingsResetText.setString("Reset Sensor");
    settingsApplyText.setString("Apply Settings");
    //Set font
    settingsFPSText.setFont(settingsFont);
    settingsFPSTextValTen.setFont(settingsFont);
    settingsFPSTextValOne.setFont(settingsFont);
    settingsCollectionText.setFont(settingsFont);
    settingsMinsText.setFont(settingsFont);
    settingsSecondsText.setFont(settingsFont);
    settingsRangeText.setFont(settingsFont);
    settingsRangeTextTrue.setFont(settingsFont);
    settingsRangeTextHuman.setFont(settingsFont);
    settingsResetText.setFont(settingsFont);
    settingsApplyText.setFont(settingsFont);
    //Set Size
    settingsBackground.setSize(sf::Vector2f(500, 400 ));
    settingsTenFPS.setSize(sf::Vector2f(75, 25 ));
    settingsOneFPS.setSize(sf::Vector2f(75, 25 ));
    settingsMinsUp.setSize(sf::Vector2f(50,25 ));
    settingsMinsDown.setSize(sf::Vector2f(50,25));
    settingsSecondsUp.setSize(sf::Vector2f(50,25 ));
    settingsSecondsDown.setSize(sf::Vector2f(50,25 ));
    settingsRangeTrue.setSize(sf::Vector2f(100,25 ));
    settingsRangeHuman.setSize(sf::Vector2f(100,25 ));
    settingsReset.setSize(sf::Vector2f(150,25 ));
    settingsApply.setSize(sf::Vector2f(150, 25 ));
    settingsMinsBox.setSize(sf::Vector2f(50, 50 ));
    settingsSecondsBox.setSize(sf::Vector2f(50, 50 ));
    //Set fill size
    settingsBackground.setFillColor(sf::Color(255, 255, 255,150));
    settingsTenFPS.setFillColor(sf::Color(30,144,255));
    settingsOneFPS.setFillColor(sf::Color(135,206,250));
    settingsMinsUp.setFillColor(sf::Color::Green);
    settingsMinsDown.setFillColor(sf::Color::Red);
    settingsSecondsUp.setFillColor(sf::Color::Green);
    settingsSecondsDown.setFillColor(sf::Color::Red);
    settingsMinsBox.setFillColor(sf::Color::White);
    settingsSecondsBox.setFillColor(sf::Color::White);
    settingsRangeTrue.setFillColor(sf::Color(30,144,255));
    settingsRangeHuman.setFillColor(sf::Color(135,206,250));
    settingsReset.setFillColor(sf::Color(30,144,255));
    settingsApply.setFillColor(sf::Color(30,144,255));
    //Set Boarders
    settingsTenFPS.setOutlineColor(sf::Color::White);
    settingsOneFPS.setOutlineColor(sf::Color::White);
    settingsMinsUp.setOutlineColor(sf::Color::White);
    settingsMinsDown.setOutlineColor(sf::Color::White);
    settingsSecondsUp.setOutlineColor(sf::Color::White);
    settingsSecondsDown.setOutlineColor(sf::Color::White);
    settingsMinsBox.setOutlineColor(sf::Color::White);
    settingsSecondsBox.setOutlineColor(sf::Color::White);
    settingsRangeTrue.setOutlineColor(sf::Color::White);
    settingsRangeHuman.setOutlineColor(sf::Color::White);
    settingsReset.setOutlineColor(sf::Color::White);
    settingsApply.setOutlineColor(sf::Color::White);
    
    // Settings Text Color
   
    settingsFPSText.setFillColor(sf::Color::Black);
    settingsFPSTextValTen.setFillColor(sf::Color::Black);
    settingsFPSTextValOne.setFillColor(sf::Color::Black);
    settingsCollectionText.setFillColor(sf::Color::Black);
    settingsMinsText.setFillColor(sf::Color::Black);
    settingsSecondsText.setFillColor(sf::Color::Black);
    settingsRangeText.setFillColor(sf::Color::Black);
    settingsRangeTextTrue.setFillColor(sf::Color::Black);
    settingsRangeTextHuman.setFillColor(sf::Color::Black);
    settingsResetText.setFillColor(sf::Color::Black);
    settingsApplyText.setFillColor(sf::Color::Black);
    
    // Settings Text Position
    settingsFPSText.setPosition(rootx+50,rootY+25 );
    settingsFPSTextValTen.setPosition(rootx+100+10 ,rootY+75 );
    settingsFPSTextValOne.setPosition(rootx+325+15 ,rootY+75 );
    settingsMinsText.setPosition(rootx+75 ,rootY+175 );
    settingsCollectionText.setPosition(rootx+50, rootY+125);
    settingsSecondsText.setPosition(rootx+300 ,rootY+175 );
    settingsRangeText.setPosition(rootx+50 ,rootY+250 );
    settingsRangeTextTrue.setPosition(rootx+75+30 ,rootY+300 );
    settingsRangeTextHuman.setPosition(rootx+325+20 ,rootY+300 );
    settingsResetText.setPosition(rootx+50+15 ,rootY+350 );
    settingsApplyText.setPosition(rootx+300+13 ,rootY+350 );
    
}

void settingsMenu::onClick(sf::RenderWindow &window){
    // Exit Button
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > 143  && position.x < 173){
            if (position.y > 93 && position.y < 123){//settings Exit Button
                //menuLayer = 0;
                
            }
        }
        
    }
    
    // Select: 30,144,255 Unselect: 135,206,250
    // 10 FPS
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 100)  && position.x < (rootx+175)){
            if (position.y > (rootY+ 75) && position.y < (rootY+100)){
                settingsTenFPS.setFillColor(sf::Color(30,144,255));
                settingsTenFPS.setOutlineThickness(2);
                settingsOneFPS.setFillColor(sf::Color(135,206,250));
                settingsOneFPS.setOutlineThickness(0);
                //gridward.setFPS(10);
            }
        }
    }
    // One FPS
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 325)  && position.x < (rootx+400)){
            if (position.y > (rootY+75) && position.y < (rootY+100)){
                settingsOneFPS.setFillColor(sf::Color(30,144,255));
                settingsOneFPS.setOutlineThickness(2);
                
                settingsTenFPS.setFillColor(sf::Color(135,206,250));
                settingsTenFPS.setOutlineThickness(0);
                
                //gridward.setFPS(1);
            }
        }
    }
    // Minutes UP
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){   // Trigger
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 150)  && position.x < (rootx+200)){
            if (position.y > (rootY+175) && position.y < (rootY+200)){
                settingsMinsUp.setFillColor(sf::Color(255,144,255));
                if(recordMins <= 50){
                    recordMins++;
                    settingsMinsText.setString(std::to_string(recordMins));
                }
            }
        }
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){  // Release
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 150)  && position.x < (rootx+200)){
            if (position.y > (rootY+175) && position.y < (rootY+200)){
                settingsMinsUp.setFillColor(sf::Color(30,144,255));
            }
        }
    }
    // Minutes DOWN
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){   // Trigger
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 150)  && position.x < (rootx +200)){
            if (position.y > (rootY + 200) && position.y < (rootY+225)){
                settingsMinsDown.setFillColor(sf::Color(255,144,255));
                if(recordMins > 0){
                    recordMins--;
                    settingsMinsText.setString(std::to_string(recordMins));
                }
            }
        }
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){  // Release
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 150)  && position.x < (rootx +200)){
            if (position.y > (rootY + 200) && position.y < (rootY+225)){
                settingsMinsDown.setFillColor(sf::Color(135,206,250));
            }
        }
    }
    // Seconds UP
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){   // Trigger
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY + 175) && position.y < (rootY+200)){
                settingsSecondsUp.setFillColor(sf::Color(255,144,255));
                if(recordSeconds < 59){
                    recordSeconds++;
                    if(recordSeconds > 9) settingsSecondsText.setPosition(rootx+300,rootY+175);
                    settingsSecondsText.setString(std::to_string(recordSeconds));
                }
                else if(recordSeconds == 59 && recordMins < 50 ){
                    recordSeconds = 0;
                    recordMins++;
                    settingsMinsText.setString(std::to_string(recordMins));
                    settingsSecondsText.setString(std::to_string(recordSeconds));
                }
            }
        }
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){  // Release
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY + 175) && position.y < (rootY+200)){
                settingsSecondsUp.setFillColor(sf::Color(30,144,255));
            }
        }
    }
    // Seconds DOWN
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){//Trigger
        
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY+200) && position.y < (rootY+225)){
                settingsSecondsDown.setFillColor(sf::Color(255,144,255));
                if(recordSeconds > 0){
                    recordSeconds--;
                    if(recordSeconds > 10) settingsSecondsText.setPosition(rootx+300+5,rootY+175);
                    settingsSecondsText.setString(std::to_string(recordSeconds));
                }
                if(recordSeconds == 0){
                    recordSeconds = 59;
                    settingsSecondsText.setString(std::to_string(recordSeconds));
                }
            }
        }
        
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){//Release
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY+200) && position.y < (rootY+225)){
                settingsSecondsDown.setFillColor(sf::Color(135,206,250));
            }
        }
    }
    // Sensor TRUE
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 75)  && position.x < (rootx + 175)){
            if (position.y > (rootY + 300) && position.y < (rootY + 325)){
                settingsRangeTrue.setFillColor(sf::Color(30,144,255));
                settingsRangeTrue.setOutlineThickness(2);
                settingsRangeHuman.setFillColor(sf::Color(135,206,250));
                settingsRangeHuman.setOutlineThickness(0);
            }
        }
    }
    // Sensor HUMAN
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 325)  && position.x < (rootx + 425)){
            if (position.y > (rootY + 300) && position.y < (rootY + 325)){
                settingsRangeHuman.setFillColor(sf::Color(30,144,255));
                settingsRangeHuman.setOutlineThickness(2);
                settingsRangeTrue.setFillColor(sf::Color(135,206,250));
                settingsRangeTrue.setOutlineThickness(0);
                
            }
        }
    }
    // RESET
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 50)  && position.x < (rootx+200)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsReset.setFillColor(sf::Color(30,144,255));
                //gridward.reset();
                settingsRangeHuman.setOutlineThickness(0);
                settingsRangeHuman.setFillColor(sf::Color(135,206,250));
                settingsRangeTrue.setFillColor(sf::Color(30,144,255));
                settingsRangeTrue.setOutlineThickness(2);
                
                
                settingsTenFPS.setOutlineThickness(2);
                settingsTenFPS.setFillColor(sf::Color(30,144,255));
                settingsOneFPS.setFillColor(sf::Color(135,206,250));
                settingsOneFPS.setOutlineThickness(0);
                recordMins = 0;
                settingsMinsText.setString(std::to_string(recordMins));
                recordSeconds = 0;
                settingsSecondsText.setString(std::to_string(recordSeconds));
                //stackward.print("Reset","Grid-EYE");
                
                
                
            }
        }
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 50)  && position.x < (rootx+200)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsReset.setFillColor(sf::Color(255,144,255));
            }
        }
    }
    // APPLY
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 300)  && position.x < (rootx + 450)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsApply.setFillColor(sf::Color(30,144,255));
                //gridward.update();
                //stackward.print("Settings Applied");
                //menuLayer = 0;
            }
        }
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > (rootx + 300)  && position.x < (rootx + 450)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsApply.setFillColor(sf::Color(255,144,255));
                //gridward.update();
            }
        }
    }
}
void settingsMenu::draw(sf::RenderWindow &window){
    window.draw(settingsBackground);//Draw settings menu when clicked
    // Exit Button
    window.draw(settingsExit);//Exit button settings menu
    
    // Frame Settings
    window.draw(settingsTenFPS);
    window.draw(settingsOneFPS);
    
    window.draw(settingsFPSText);
    window.draw(settingsFPSTextValTen);
    window.draw(settingsFPSTextValOne);
    
    // Collection Settings
    window.draw(settingsMinsUp);
    window.draw(settingsMinsDown);
    
    window.draw(settingsSecondsUp);
    window.draw(settingsSecondsDown);
    
    window.draw(settingsMinsBox);
    window.draw(settingsSecondsBox);
    
    window.draw(settingsCollectionText);
    window.draw(settingsMinsText);
    window.draw(settingsSecondsText);
    
    // Sensor Range Settings
    window.draw(settingsRangeTrue);
    window.draw(settingsRangeHuman);
    
    window.draw(settingsRangeText);
    window.draw(settingsRangeTextTrue);
    window.draw(settingsRangeTextHuman);
    
    
    // Reset Sensor
    window.draw(settingsReset);
    window.draw(settingsResetText);
    
    // Apply Settings
    window.draw(settingsApply);
    window.draw(settingsApplyText);
}



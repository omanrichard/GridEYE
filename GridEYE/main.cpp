
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Event.hpp"
//#include <wiringPi.h> //Include handeling to test system and only call when raspberry pi
#include <Mouse.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "projectClasses.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#define GRIDEYEADDRESS 0x68

using namespace sf;


//Global Objects
GridEYE gridward(GRIDEYEADDRESS); //Creats the Grid Eye Object
terminal stackward(6, "Thermal Camera");//Creats the terminal Stack with 6 blank lines
toolbar toolward;

int i,j;

//Time Variables
int recordMins = 0; //Seconds to be recorded - Is this still being used?
int recordSeconds = 0;//Minuetes to be recorded - Is this still being used?
bool recordStatus = false; //True: Recording; False: Not recording
bool playbackStatus = false;

char recordTimeBuffer[11]; //Holds formatted time
struct tm * currentTimeStruct;//Time structure required for formatted time

time_t currentTime; //Current Time - Displayed when not in recording mode or Playback mode
time_t lastCaptureTime;//Time at which the most recent capture was taken - used for fps control
time_t recordStartTime; //Time when recording starts
time_t recordEndTime; //Time when recording Ends


int menuLayer = 0; //Each "screen" gets its own layer. ie main screen is 0, settings menu is 1, Playback is 2;


int rootx = 150;//Settings Menu upper left corner
int rootY = 100;//Settings Menu upper left corner

int main(int, char const**)
{
    
    
//----------- Frame Capture experiment -----------
    video* vPtr = NULL;
    session currentSession;
   
    
//--------------------- Set up -----------------------------------
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(700, 700), "ECE3220 Final Project");
    

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
   
    //----------------- Camera Grid -----------------
    int gridx, gridy;
    RectangleShape grid[8][8];
    
    for( i=0 ; i < 8 ; i++ ){
        for( j=0 ; j<8 ; j++ ){
            gridx = (164+i*59);
            gridy = (88+j*59);
            RectangleShape newPix(sf::Vector2f(58, 58));
            newPix.setPosition( gridx, gridy );
            gridward.test(i,j);
            newPix.setFillColor(sf::Color(gridward.r,gridward.g,gridward.b));
            grid[i][j] = newPix;
        }
    }
    
    sf::RectangleShape line( Vector2f( 1, 700) );
    line.setFillColor( Color::Black );
    line.setPosition(94, 0);
    
    RectangleShape line2( Vector2f( 625, 1));
    line2.setFillColor( Color::Black );
    line2.setPosition(94, 606);
    
    //---------------Draw Playbar-----------
    playBar progressBar(sf::Vector2f(35, 375),1);
    //----------------Draw Toolbar----------------
   
    
    
 
  
    
    
    
    
    
    
    
    sf::RectangleShape selection(sf::Vector2f( 89, 70 ));
    selection.setFillColor(sf::Color(0, 0, 0, 100));
    selection.setPosition(-100, -100);
    
    sf::RectangleShape selectionTextBox(sf::Vector2f( 94, 20 ));
    selectionTextBox.setFillColor(sf::Color(255, 255, 255, 100));
    selectionTextBox.setPosition(-100, -100);
    
    sf::Text selectionText("void", font, 10);
    selectionText.setFillColor(sf::Color::Black);
    selectionText.setPosition( -100 , -100);
    
    
    
    
    sf::Texture t_background;
    sf::Sprite background;
    background.setPosition(0,0);
    
    if(!t_background.loadFromFile("texture2.jpg")){
        return EXIT_FAILURE;
    }
    background.setTexture(t_background);
    window.draw(background);
    
    //-----------------Draw Terminal Window-------------------

    
  
    
    
    
    
    
    
    

    
    
   
    
    
    //----------------- Background -----------------
    //sf::RectangleShape background(sf::Vector2f( 700, 700 ));
    //background.setFillColor(sf::Color(130, 117, 135));
    //background.setPosition(0, 0);
    
    sf::RectangleShape backgroundHeader(sf::Vector2f( 400, 10 ));
    backgroundHeader.setFillColor(sf::Color(0, 255, 0,150));
    backgroundHeader.setPosition(94, 70);
    
    sf::RectangleShape backgroundHeader2(sf::Vector2f( 400, 10 ));
    backgroundHeader2.setFillColor(sf::Color(0, 255, 0,150));
    backgroundHeader2.setPosition(488, 75);
    backgroundHeader2.rotate(-60);
    
    sf::RectangleShape backgroundHeader3(sf::Vector2f(606, 5 ));
    backgroundHeader3.setFillColor(sf::Color(255, 94, 20,150));
    backgroundHeader3.setPosition(94, 75);
    
    sf::RectangleShape topbarBackground(sf::Vector2f( 606, 75 ));
    topbarBackground.setFillColor(sf::Color(0, 0, 0,50));
    topbarBackground.setPosition(94, 0);
  
    sf::Text text("Thermal Camera", font, 50);
    text.setFillColor(sf::Color::White);
    text.setPosition( 109 , 10);
    
    sf::Text recordText("Standy-by", font, 25);
    recordText.setFillColor(sf::Color::Green);
    recordText.setPosition( 550 , 10);
    
    
    
    currentTime = time(NULL);
    currentTimeStruct = localtime(&currentTime);
    strftime (recordTimeBuffer,11,"%r",currentTimeStruct);
    sf::Text recordingTimeText(recordTimeBuffer, font, 20);
    recordingTimeText.setFillColor(sf::Color::White);
    recordingTimeText.setPosition( 560 , 45);
    

    //----------------- Settings Objects -----------------

    sf::RectangleShape settingsBackground(sf::Vector2f(500, 400 ));
    settingsBackground.setFillColor(sf::Color(255, 255, 255,150));
    settingsBackground.setPosition(-500, -500);
    sf::Texture t_close;
    if(!t_close.loadFromFile("cancel.png")){
        return EXIT_FAILURE;
    }
    
    Sprite settingsExit;
    settingsExit.setTexture(t_close);
    settingsExit.setPosition(143,93);
    settingsExit.scale(0.1, 0.1);
    
    //Settings Buttons Declare
    RectangleShape settingsTenFPS(sf::Vector2f(75, 25 ));
    RectangleShape settingsOneFPS(sf::Vector2f(75, 25 ));
    RectangleShape settingsMinsUp(sf::Vector2f(50,25 ));
    RectangleShape settingsMinsDown(sf::Vector2f(50,25));
    RectangleShape settingsSecondsUp(sf::Vector2f(50,25 ));
    RectangleShape settingsSecondsDown(sf::Vector2f(50,25 ));
    RectangleShape settingsRangeTrue(sf::Vector2f(100,25 ));
    RectangleShape settingsRangeHuman(sf::Vector2f(100,25 ));
    RectangleShape settingsReset(sf::Vector2f(150,25 ));
    RectangleShape settingsApply(sf::Vector2f(150, 25 ));
    RectangleShape settingsMinsBox(sf::Vector2f(50, 50 ));
    RectangleShape settingsSecondsBox(sf::Vector2f(50, 50 ));
    
    // Set Button Colors
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
    
    // Set Borders
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
    
    // Settings Text Declare
    Text settingsFPSText("Frames Per Second",font, 30);
    Text settingsFPSTextValTen("10 FPS", font, 20);
    Text settingsFPSTextValOne("1 FPS",font,20);
    Text settingsCollectionText("Collection Time",font,30);
    Text settingsMinsText("0",font,40);
    Text settingsSecondsText("0",font,40);
    Text settingsRangeText("Sensor Dynamic Range",font,30);
    Text settingsRangeTextTrue("True",font,20);
    Text settingsRangeTextHuman("Human",font, 20);
    Text settingsResetText("Reset Sensor",font, 20);
    Text settingsApplyText("Apply Settings", font, 20);
    
    // Settings Text Color
    settingsBackground.setPosition(rootx,rootY);    //Move settings background in place
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

    
 
/*/---------- Draw ----------/*/
// Play the music
//music.play();

/*/
 ------------------------ Start the game loop -----------------------
 ---------------------------GO Johnny GO!----------------------------
 --------------------------------------------------------------------
 --------------------------------------------------------------------
/*/
    float tempt;
    frame* framePtr;
    int fcount = 0;
    
    while (window.isOpen()) //While the window is open.
    {
        
        //Recording Control
        if(recordStatus == true){
            
            
            
            recordText.setString("Recording");//Changes "Stand-By" To "Recording"
            recordText.setFillColor(sf::Color::Red);//"Sets "Recoding" Text to Red
            recordEndTime = time(NULL);//Sets current time to end time
            progressBar.record(recordEndTime);
            double seconds = difftime(recordEndTime, recordStartTime);//Caculates Elapsed Time
            recordingTimeText.setString(std::to_string(int(seconds/60))+":"+std::to_string(int(fmod(seconds,60)))); //Calculates Time and sets string
        
            
            float tenthSecond = 0.1;
            tempt = (difftime( time(NULL), lastCaptureTime));
            
            if( (tempt) >= 0.1 ){
                cout << tempt << endl << endl;

                lastCaptureTime = time(NULL);
        
                vPtr->addFrame( gridward );
                
            }
            
        }
        if(recordStatus == false){
            recordText.setString("Standy-by");
             recordText.setFillColor(sf::Color::Green);
        }
        
        if(playbackStatus == true){
            recordText.setString("Replaying");//Changes "Stand-By" To "Replaying"
            recordText.setFillColor(sf::Color::Red);//"Sets "Replaying" Text to Red
            
            if( difftime(time(NULL), lastCaptureTime) > 0.1 ){
            for( int x=0 ; x<fcount ; x++ ){
                framePtr = vPtr->getFrame(x);
                for( i=0 ; i < 8 ; i++ ){
                    for( j=0 ; j<8 ; j++ ){
                        gridx = (200+i*51);
                        gridy = (98+j*51);
                        RectangleShape newPix(sf::Vector2f(50, 50));
                        newPix.setPosition( gridx, gridy );             // Eventually
                                                    // pixelMask.setMask( tempFrame->access(short row, short col );
                        newPix.setFillColor(sf::Color(gridward.r, framePtr->access(i, j) ,gridward.b));   // color( pixelMask.r, pixelMask.g, pixelMask.b )
                        grid[i][j] = newPix;
                    }
                }
                lastCaptureTime = time( NULL);
                
            }
                playbackStatus = false;
        
            }
        }
        
        // Eventual Additions to control grid colors
        /*
         activeVid = session.current[ session.vCount ]; // Active frame
         tempFrame = activeVid->data[];                 // Frame to draw controlled somehow
        */
        else{
        //sets each gridward pixel
        for( i=0 ; i < 8 ; i++ ){
            for( j=0 ; j<8 ; j++ ){
                gridx = (200+i*51);
                gridy = (98+j*51);
                RectangleShape newPix(sf::Vector2f(50, 50));
                newPix.setPosition( gridx, gridy );             // Eventually
                gridward.test(i,j);                             // pixelMask.setMask( tempFrame->access(short row, short col );
                newPix.setFillColor(sf::Color(gridward.r,gridward.g,gridward.b));   // color( pixelMask.r, pixelMask.g, pixelMask.b )
                grid[i][j] = newPix;
            }
        }
        }
        window.draw(line);
        
        // Process events. This monitors mouse movements and clicks
        sf::Event event;
        while (window.pollEvent(event)){
            // Menu selection
            if( menuLayer == 0){//This the
            
                if(event.type == sf::Event::MouseMoved){
                    if(event.mouseMove.x > 0 && event.mouseMove.x < 94){
                        if(event.mouseMove.y > 0 && event.mouseMove.y < 119){//Settings
                            selection.setPosition(0, 26);
                            selectionText.setString("Settings");
                            selectionText.setPosition(50 , 89);
                            selectionTextBox.setPosition(50,89);
                        }
                        if(event.mouseMove.y > 119 && event.mouseMove.y < 189){//New Capture
                        selection.setPosition(0, 119);
                        selectionText.setString("Capture");
                        selectionText.setPosition( 50 , 159);
                        selectionTextBox.setPosition(50,159);
                        
                        }
                        if(event.mouseMove.y > 219 && event.mouseMove.y < 308){//Play
                            selection.setPosition(0, 219);
                            selectionText.setString("Play Capture");
                            selectionText.setPosition( 50 , 278);
                            selectionTextBox.setPosition(50,278);
                        }
                        if(event.mouseMove.y > 308 && event.mouseMove.y < 402){//Stop
                            selection.setPosition(0, 308);
                            selectionText.setString("Stop Capture");
                            selectionText.setPosition( 30 , 372);
                            selectionTextBox.setPosition(30,372);
                        }
                        if(event.mouseMove.y > 402 && event.mouseMove.y < 496){//Save
                            selection.setPosition(0, 402);
                            selectionText.setString("Save Capture");
                            selectionText.setPosition( 30 , 439);
                            selectionTextBox.setPosition(30,439);
                        }
                        if(event.mouseMove.y > 496 && event.mouseMove.y < 590){//Delete
                            selection.setPosition(0, 496);
                            selectionText.setString("Delete Capture");
                            selectionText.setPosition( 30 , 560);
                            selectionTextBox.setPosition(30,560);
                        }
                        if(event.mouseMove.y > 590 && event.mouseMove.y < 700){//Quit
                            selection.setPosition(0, 590);
                            selectionText.setString("Close Application");
                            selectionText.setPosition( 30 , 670);
                            selectionTextBox.setPosition(30,670);
                        }
                    }
                    
                }
                else if(event.mouseMove.x > 94){        //Mouse not over on toolbar
                    selection.setPosition(-100, -100);  //Move Offscreen
                    selectionText.setString("Void");
                    selectionText.setPosition( -100 , -100);//Move Offscreen
                    selectionTextBox.setPosition(-100,-100);//Move Offscreen
                }
            }            
            if( menuLayer == 1 ){
                if(event.type == sf::Event::MouseMoved){
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2i position = sf::Mouse::getPosition(window);
                        if (position.x > 0 && position.x < 95){         //Within toolbar
                            if (position.y > 0 && position.y < 119){
                                settingsBackground.setPosition(150, 100);
                                menuLayer = 1;
                            }
                        }
                    }
                }
            }
            /*/----left click----/*/
            
            /*/----Layer 0 "Home"----/*/
            if(menuLayer == 0){//Base Layer
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){//If left button is pressed
                    sf::Vector2i position = sf::Mouse::getPosition(window);//Get position of mouse
                     if (position.x > 0 && position.x < 95){     //Within toolbar
                         
                         //Settings
                        if (position.y > 0 && position.y < 119){
                            menuLayer = 1; //Change layer to settings layer
                        }
                         //Start Capture
                        if (position.y > 119 && position.y < 189){
                            recordStatus = true;//Start recording data
                            recordStartTime = time(NULL); //Set current time as start time
                            lastCaptureTime = recordStartTime;
                            progressBar.setStartTime(recordStartTime);
                            stackward.print("Starting Capture");
                            
                            vPtr = new video;
                            
                            //set led to green
                            }
                         //Play capture
                         if (position.y > 189 && position.y < 308){
                             recordStatus = false;//Stop recording data
                             stackward.print("Entering Playback Mode");
                             menuLayer = 2;//Change layer to playback
                             
                             playbackStatus = true;
                             fcount = vPtr->getframeCount();
                         }
                         //Stop capture
                         if (position.y >308 && position.y < 402){
                             recordStatus = false;//Stop recording data
                             stackward.print("Stopping Capture");
                             //set led to red
                             
                             currentSession.addVideo(vPtr);
                             
                         }
                         //Save capture
                         if (position.y > 402 && position.y < 496){
                             recordStatus = false;//Stop recording data
                             stackward.print("Saving Capture");
                             
                             cout << "Exporting Video" << endl;
                             vPtr->exportVideo( "Test1.txt" );
                             cout << "Success" << endl;
                             //set led to red
                         }
                         //Delete capture
                         if (position.y > 496 && position.y < 590){
                             recordStatus = false;//Stop recording data
                              stackward.print("Deleting Capture");
                             //set led to red
                         }
                         //exit
                        if (position.y > 590 && position.y < 700){
                            window.close();//Close Window
                        
                        }
                    }//End within toolbar
                
                }//End left mouse button click
            }//End Menu layer 1
            
            /*/---------- Layer 1 "Settings" ----------/*/
            if(menuLayer == 1){
                // Exit Button
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > 143  && position.x < 173){
                        if (position.y > 93 && position.y < 123){//settings Exit Button
                            menuLayer = 0;

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
                            gridward.setFPS(10);
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
                            
                            gridward.setFPS(1);
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
                            gridward.reset();
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
                            stackward.print("Reset","Grid-EYE");
                    
                            
                            
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
                            stackward.print("Settings Applied");
                            menuLayer = 0;
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
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
   
        // Clear screen
        window.clear();
        
        //Background
        window.draw(background);
        
        // Draw the placeholder text
        window.draw(topbarBackground);
       // window.draw(backgroundHeader);
        //window.draw(backgroundHeader2);
        window.draw(backgroundHeader3);
        
        window.draw(text);
        window.draw(recordText);
        window.draw(recordingTimeText);
        
        
        /*/---Draw Settings Window----/*/
            if(menuLayer == 1){
                
                // Settings Background
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
        
          
        /*/---------- Draw Toolbar ----------/*/
            
      
            
        
        
        window.draw(selection);
        window.draw(selectionTextBox);
        window.draw(selectionText);
        
        // Draw output Grid
       
        if(menuLayer == 0){
            for( i=0 ; i < 8 ; i++ ){
                for( j=0 ; j<8 ; j++ ){
                    window.draw(grid[i][j]);
                }
            }
        }
       
        // Draw the Terminal window
        toolward.draw(window);
        stackward.draw(window);
        progressBar.draw(window);
        
        
        
        //window.draw(line);
        //window.draw(line2);
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}


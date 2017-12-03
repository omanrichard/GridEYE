
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
#include "graphicClasses.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#define PDE 0x68

using namespace sf;


//Global Objects
GridEYE gridward(PDE); //Creats the Grid Eye Object
terminal stackward(6, "Thermal Camera");//Creats the terminal Stack with 6 blank lines
toolbar toolward;
settingsMenu setward;
topBar topward;
playBar progressBar(sf::Vector2f(35, 375),1);
int i,j;

//Time Variables

bool recordStatus = false; //True: Recording; False: Not recording
bool playbackStatus = false;

char recordTimeBuffer[11]; //Holds formatted time
struct tm * currentTimeStruct;//Time structure required for formatted time

time_t currentTime; //Current Time - Displayed when not in recording mode or Playback mode
time_t lastCaptureTime;//Time at which the most recent capture was taken - used for fps control
time_t recordStartTime; //Time when recording starts
time_t recordEndTime; //Time when recording Ends


int menuLayer = 0; //Each "screen" gets its own layer. ie main screen is 0, settings menu is 1, Playback is 2;



int main(int, char const**)
{
    
    
//----------- Frame Capture experiment -----------
    video* vPtr = NULL;
    session currentSession; // Begins session
   
    
//--------------------- Set up --------------------//
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(700, 700), "PGE-DPA v.2"); //Creates Winodw
    
    //Loads font - soon to be depreciated
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
    
    sf::RectangleShape line( Vector2f( 1, 700) );//What is this? - Can we move it or deleted it
    line.setFillColor( Color::Black );
    line.setPosition(94, 0);
    

    
 
    //----------------- Background -----------------//
   
    sf::Texture t_background;//Background text - stays global for now
    sf::Sprite background;//Background Sprite - stays global for now
    
    if(!t_background.loadFromFile("texture2.jpg")){//Load backgroud image
        return EXIT_FAILURE;//Exit program and report error if file can be found
    }
    background.setTexture(t_background);//maps background text to background sprite
    background.setPosition(0,0);//move background sprite to origin
    window.draw(background);//draws background

    topward.setMode(0);
    
    currentTime = time(NULL);
    currentTimeStruct = localtime(&currentTime);
    strftime (recordTimeBuffer,11,"%r",currentTimeStruct);
    sf::Text recordingTimeText(recordTimeBuffer, font, 20);
    recordingTimeText.setFillColor(sf::Color::White);
    recordingTimeText.setPosition( 560 , 45);
    



 
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
    GridEYE* gPtr;
    
    while (window.isOpen()) //While the window is open.
    {
        
        //Recording Control
        if(recordStatus == true){
            
            
            
            topward.setMode(1);//Changes "Stand-By" To "Recording"
            recordEndTime = time(NULL);//Sets current time to end time
            progressBar.record(recordEndTime);
            double seconds = difftime(recordEndTime, recordStartTime);//Caculates Elapsed Time
            recordingTimeText.setString(std::to_string(int(seconds/60))+":"+std::to_string(int(fmod(seconds,60)))); //Calculates Time and sets string
        
            
            float tenthSecond = 0.1;
            tempt = (difftime( time(NULL), lastCaptureTime));
            
            if( (tempt) >= 0.1 ){
                cout << tempt << endl << endl;

                lastCaptureTime = time(NULL);
                framePtr = new frame(gridward);
                // Eventually: gPtr= new GridEYE( GRIDEYEADDRESS );
                vPtr->addFrame( framePtr );
                
            }
            
        }
        if(recordStatus == false){
            topward.setMode(0);
        
        }
        
        if(playbackStatus == true){
            topward.setMode(3);//Changes "Stand-By" To "Replaying"
           
            if( difftime(time(NULL), lastCaptureTime) > 0.1 ){
           
                lastCaptureTime = time( NULL);
                
            }
                playbackStatus = false;
        
            }
        
        
        // Eventual Additions to control grid colors
        /*
         activeVid = session.current[ session.vCount ]; // Active frame
         tempFrame = activeVid->data[];                 // Frame to draw controlled somehow
        */
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
    
        window.draw(line);
        
        // Process events. This monitors mouse movements and clicks
        sf::Event event;
        while(window.pollEvent(event)){
            // Menu selection
            if( menuLayer == 0){
                toolward.event(event);//Handles Mouse moving events
                toolward.onClick(window,stackward);//Handles Mouse click events
            
                //Base Layer
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){//If left button is pressed
                    sf::Vector2i position = sf::Mouse::getPosition(window);//Get position of mouse
                     if (position.x > 0 && position.x < 95){     //Within toolbar
                         
                         
                       
                         //Start Capture
                        if (position.y > 119 && position.y < 189){
                            recordStatus = true;//Start recording data
                            recordStartTime = time(NULL); //Set current time as start time
                            lastCaptureTime = recordStartTime;
                            progressBar.setStartTime(recordStartTime);
                            
                            
                            vPtr = new video;
                            
                            //set led to green
                            }
                         //Play capture
                         if (position.y > 189 && position.y < 308){
                             recordStatus = false;//Stop recording data
                             
                             
                             playbackStatus = true;
                             fcount = vPtr->getframeCount();
                         }
                         //Stop capture
                         if (position.y >308 && position.y < 402){
                             recordStatus = false;//Stop recording data
                             
                             //set led to red
                             
                             currentSession.addVideo(vPtr); // Adds recorded video to the video stack
                             
                         }
                         //Save capture
                         if (position.y > 402 && position.y < 496){
                             recordStatus = false;//Stop recording data
                             
                             
                             stackward.print("Exporting Video");
                             vPtr->exportVideo( "Test1.txt" );
                             stackward.print("Success");
                             //set led to red
                         }
                         //Delete capture
                         if (position.y > 496 && position.y < 590){
                             recordStatus = false;//Stop recording data
                              
                             //set led to red
                             
                             currentSession.undoRec(); // Removes recorded video from the video stack
                         }
                      
                        
                        
                    }
                
                }
            
                menuLayer = toolward.exit();//Allows toolbar to change Menu layer
            }
            //Settings Menu
            if(menuLayer == 1){
                setward.onClick(window); //Scans buffer for corosponing inputs.
                menuLayer = toolward.exit();
                menuLayer = setward.exit();//Allows settings menu to Menu layers
            }
            //Playback Mode
            if(menuLayer == 2){
                menuLayer = toolward.exit();
            }
            
            //Sync all elements
            toolward.sync(menuLayer);
            
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
       
        window.draw(recordingTimeText);
        
        /*/-------- Layer control -------/*/
        switch(menuLayer){
            case 0: //Home Screen
                toolward.draw(window); //Toolbar
                stackward.draw(window);//Terminal
                progressBar.draw(window);//Playback bar
                topward.draw(window);
                //Grid
                for( i=0 ; i < 8 ; i++ ){
                    for( j=0 ; j<8 ; j++ ){
                        window.draw(grid[i][j]);
                    }
                }
                
                break;
            case 1: //Settings Menu
                toolward.draw(window);//Toolbar
                stackward.draw(window);//Terminal
                setward.draw(window);//Settings Menu
                topward.draw(window);
                break;
            case 2: //Capture Mode
                topward.draw(window);
                toolward.draw(window);
                stackward.draw(window);
                break;
            case 3://PlaybackMode
                topward.draw(window);
                toolward.draw(window);
                stackward.draw(window);
                break;
            case 4://Stop Capture
                topward.draw(window);
                toolward.draw(window);
                stackward.draw(window);
                break;
            case 5://Save Capture
                topward.draw(window);
                toolward.draw(window);
                stackward.draw(window);
                break;
            case 6://Delete Capture
                break;
                topward.draw(window);
                toolward.draw(window);
                stackward.draw(window);
            case 7://Exit Program
                topward.draw(window);
                toolward.draw(window);
                stackward.draw(window);
                break;
        }
        
    
        
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}


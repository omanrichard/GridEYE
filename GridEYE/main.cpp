
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
playBar playward(sf::Vector2f(35, 375),1);

int i,j;
int gridx, gridy;

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
    frame activeFrame;
    pixMask pixel;
    int temp = 0;
    int pixAddr = 0x80;
    
    
//--------------------- Set up --------------------//
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(700, 700), "PGE-DPA v.2"); //Creates Winodw
    window.setFramerateLimit(60);   // Sets Window Framerate to 60 FPS

    //Loads font - soon to be depreciated
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
   
    //----------------- Camera Grid -----------------
    sf::RectangleShape grid[8][8];
    RectangleShape newPix(sf::Vector2f(50, 50));

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
    vPtr = new video;
    

    while (window.isOpen()) //While the window is open.
    {
        currentTime = time(NULL);//Updates Current Time
        
        
        //Recording Control
        if(recordStatus == true){
            
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
     
        
        if(playbackStatus == true){
            
           
            if( difftime(time(NULL), lastCaptureTime) > 0.1 ){
                lastCaptureTime = time( NULL);
                
            }
            
        
            }
        
        // For real-time window drawing experiment
        pixAddr = 0x80;
        temp = 0;
        
        // Draws the Grid
        for( i=0 ; i < 8 ; i++ ){
            for( j=0 ; j<8 ; j++ ){
                gridx = (200+i*51);
                gridy = (98+j*51);
                newPix.setPosition( gridx, gridy );
                
                gridward.test(i,j);
                newPix.setFillColor(sf::Color(gridward.r,gridward.g,gridward.b));
                
                /*
                pixel.update( gridward.read(pixAddr) );
                newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb());
                */
                grid[i][j] = newPix;
            }
        }
    
   
        
/*/ --------- Process events ---------/*/
        sf::Event event;
        while(window.pollEvent(event)){
            toolward.event(event);//Handles Mouse moving events
            
            //The Follow events only happen on each click
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                toolward.onClick(window,stackward);//Handles Mouse click events
                if(recordStatus == true){//Stop recording video on click
                    recordEndTime = time(NULL);
                    recordStatus = false;
                }
                //Settings Menu
                if(menuLayer == 1){
                    setward.onClick(window); //Scans buffer for corosponing inputs.
                    menuLayer = setward.exit();//Allows settings menu to Menu layers
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                
                //Capture Video
                if(menuLayer == 2){//Executes Once when Capture is clicked
                    recordStartTime = time(NULL);
                    recordStatus = true;
                    //Insert Code Here
                    
                    
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                //Playback Viode
                if(menuLayer == 3){//Executes Once when Playback is clicked
                    
                    
                    //Insert Code Here
                    
                    
                     toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                if(menuLayer == 4){//Executes Once when Stop is clicked
                    recordEndTime = time(NULL);
                    recordStatus = false;
                    //Insert Code Here
               
                
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                //Export Video
                if(menuLayer == 5){//Executes Once when Export is clicked
                    stackward.print("Exporting Video");
                    vPtr->exportVideo( "Test1.txt" );
                    stackward.print("Success");
                    menuLayer = 0;
                    toolward.sync(menuLayer);
                }
                if(menuLayer == 6){///Executes Once when Delete is clicked
                
                
                    //Insert Code to Delete Video Here
                
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                
                menuLayer = toolward.exit();//Changes menu Lever to what is stored in toolbar
                stackward.print(std::to_string(menuLayer));//Debug function -Prints Menu level to terminal
                topward.setMode(menuLayer);//Set topbar to current mode
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
       
        window.draw(recordingTimeText);
        
        topward.draw(window);
        toolward.draw(window); //Toolbar
        stackward.draw(window);//Terminal
        /*/-------- Layer control -------/*/
        
        
        switch(menuLayer){
               
                
                break;
            default:
                //Grid
                for( i=0 ; i < 8 ; i++ ){
                    for( j=0 ; j<8 ; j++ ){
                        window.draw(grid[i][j]);
                    }
                }
                toolward.draw(window);
                stackward.draw(window);
                break;
            case 1: //Settings Menu
                setward.draw(window);//Settings Menu
                break;
            case 2: //Capture Mode
                playward.draw(window);
                break;
            case 3://PlaybackMode
                playward.draw(window);
                break;
            case 4://Stop Capture
              
                
                
                currentSession.addVideo(vPtr);
               
                break;
          
        
            
        }
        
    
        //Sync all elements
        toolward.sync(menuLayer);
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}


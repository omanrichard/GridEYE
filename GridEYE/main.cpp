
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>                //Grahpics Librars
#include "Event.hpp"                        //Mouse Move Events
#include "Mouse.hpp"                       //Mouse Clicks

#include <wiringPi.h>                     //Raspberry Pi GPIO
#include <iostream>
#include <fstream>                          //FILE I/O
#include <vector>
#include <string>
#include <time.h>                           //Time Functions
#include <math.h>                           //Math Functions
#include <stdio.h>

#include "projectClasses.h"                 //Video File Objects Classes
#include "graphicClasses.h"                 //User Interface Objects Classes

//GPIO
#define GREENLED 4                         //GPIO pin connected to Green LED Anode
#define REDLED   5                   //GPIO Pin connected to Red LED Anode
#define PDE 0x68                            //Grid-EYE I2C Address
#define xGrid 200
#define yGrid 98


//Global Objects
GridEYE gridward(PDE);                      //Grid Eye Object
GridEYE* gPtr = &gridward;
pixMask pixel;                              // Pixel Obj, stores RBG values

terminal stackward(6, "Thermal Camera");    //Terminal Stack with 6 blank lines
toolbar toolward;                           //Toolbar
settingsMenu setward;                       //Settings Menu
topBar topward;                             //Top Status Bar
playBar playward(sf::Vector2f(35, 375),1);  //Playback bar
fastVideo vidward;                          //Test Video Implementation
 fastFrame newFrame;
//State Variables
int menuLayer = 0;                          //0:Home;1:Settings;2:Record;3:Playback;
                                            //4:Stop;5:Save;6:Delete
bool recordStatus = false;                  //True: Recording; False: Not Recording
bool playbackStatus = false;                //True: Playing Clip; False: Not Playing Clip

int recordTime = 0;                         //Time to record the video

int i, j;
int xPix, yPix;

int pixScale = 51;



int main(int, char const**)
{
    wiringPiSetup();
    pinMode(GREENLED, OUTPUT);
    pinMode(REDLED,OUTPUT);
   
    digitalWrite(GREENLED, 1);
    digitalWrite(REDLED, 1);
//-----------------------------------------------------------------
// Video Capture Experiment Variables - Can we delete this? -- Eventually
//-----------------------------------------------------------------
    session currentSession; // Begins session

    video* vPtr = NULL;
    frame* fPtr = NULL;
    
    int tempCount = 0;
    int temp = 0;       // Stores value from GridEYE pixel
    int pixAddr = 0x80; // GridEYE pixel 1
    
    time_t tempTime = time(NULL);
    
    
    
//-----------------------------------------------------------------
// Set Up
//-----------------------------------------------------------------
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(700, 700), "PGE-DPA v.2"); //Creates Winodw
    // window.setFramerateLimit(60);   // Sets Window Framerate to 60 FPS

    //----------------- Camera Grid -----------------
    sf::RectangleShape newPix(sf::Vector2f(50, 50));

    //----------------- Background ------------------
   
   // sf::Texture t_background;//Background text - stays global for now
   // sf::Sprite background;//Background Sprite - stays global for now
    
   // if(!t_background.loadFromFile("texture2.jpg")){//Load backgroud image
    //    return EXIT_FAILURE;//Exit program and report error if file can be found
    //}
    //background.setTexture(t_background);//maps background text to background sprite
    //background.setPosition(0,0);//move background sprite to origin
    //window.draw(background);//draws background

//-----------------------------------------------------------------
// Draw Loop
//-----------------------------------------------------------------
    
// Play the music
// music.play();

/*/
 ------------------------ Start the game loop -----------------------
 ---------------------------GO Johnny GO!----------------------------
 --------------------------------------------------------------------
 --------------------------------------------------------------------
/*/
    frame* framePtr;
    int fcount = 0;
    tempCount=0;
    recordTime = gridward.getRuntime();

    
    topward.setMode(0); //Set Mode to standy By
    while (window.isOpen()) //While the window is open.
    {
        //-----------------------------------------------------------------
        // Process Events
        //-----------------------------------------------------------------
        sf::Event event;
        
        while(window.pollEvent(event)){
            toolward.event(event);//Handles Mouse moving events
            
            //The Following events only happen on each click
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                toolward.onClick(window,stackward);//Handles Mouse click events
                
                if(recordStatus == true){//Stop recording video on click
                    menuLayer = 4;
                   
                    
                    //Insert Code Here
                    
                    
                    toolward.sync(menuLayer);
                }
                menuLayer = toolward.exit();//Changes menu Lever to what is stored in toolbar
        
                //Settings Menu
                if(menuLayer == 1){
                    digitalWrite(GREENLED,0);
                    setward.onClick(window, gridward, stackward); //Scans buffer for corosponing inputs.
                    recordTime = setward.syncRecordLength();
                    menuLayer = setward.exit();//Allows settings menu to Menu layers
                    
                    //Insert Code Here
                    
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                // Capture Video
                if(menuLayer == 2){//Executes Once when Capture is clicked
                    digitalWrite(REDLED,0);
                    playward.setClipStartTime(time(NULL));
                    recordStatus = true;
                    
                    vPtr = new video;
                    
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                // Playback Video
                if(menuLayer == 3){//Executes Once when Playback is clicked
                    playward.onClick(window,stackward);
                    playward.setPlaybackStartTime(time(NULL));
                
                    //Insert Code Here
                  
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                // Record Video
                if(menuLayer == 4){//Executes Once when Stop is clicked
                    if(recordStatus == true){
                    
                    recordStatus = false;
                    playward.setClipEndTime(time(NULL));
                    }
                    
                    //Insert Code Here
                    
                    menuLayer = 0; //Return to home
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                // Export Video
                if(menuLayer == 5){//Executes Once when Export is clicked
                    stackward.print("Exporting Video");
                    vPtr->exportVideo( "Test1.txt" );   // Exports data packet
                    stackward.print("Success");
                    menuLayer = 0;
                    
                    toolward.sync(menuLayer);
                }
                if(menuLayer == 6){///Executes Once when Delete is clicked
                
                    //Insert Code to Delete Video Here
                
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                
                
                topward.setMode(menuLayer);//Set topbar to current mode
            }
           
            
            //Terminate Applicaiton Events
            
            //On Window Close Click
            if (event.type == sf::Event::Closed) {
                
                window.close();                 //Close Window / Quit Application
            }
            //On Key Press
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        
                window.close();                 //Close Window / Quit Application
            }
        }
   
        
        topward.updateClock(time(NULL));        //Updates Clock
        
        window.clear();                         //Clears Screen Object of all Elements
        
        //window.draw(background);                //Draws Background Object First
        topward.draw(window);                   //Draws Top Bar
        stackward.draw(window);                 //Draws Terminal
        toolward.draw(window);                  //Draws Toolbar
       
        
        
//-----------------------------------------------------------------
// Layer Control
//-----------------------------------------------------------------
        switch(menuLayer){
            
            default:    //Streams Live data from sensor but not recording
                pixAddr = 0x80;
                
                for( i = 0 ; i < 8 ; i++ ){
                    for( j = 0 ; j < 8 ; j ++ ){
                    
                        //Test Function
                        //pixel.fastUpdate( rand() % 255 );
                        //newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                        
                        // Pixel Position
                        xPix = (xGrid + i*51);
                        yPix = (yGrid + j*51);
                        newPix.setPosition( xPix, yPix );
                        
                        
                         //Hardware Function
                         pixel.fastUpdate( gridward.read(pixAddr) );
                         newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                        
                        //Memory Registers
                        if(pixAddr < 0xFF && pixAddr >= 0x80) //Error Protection
                            pixAddr += 2;           //Incriment to next Register
                        
                        // Draw the Pixel
                        window.draw( newPix );
                    }
                }
                break;
                
            case 1:   //Settings Menu
                setward.draw(window);//Draw Settings Menu
                break;
            
            case 2:  //Capture Mode
                
                for( i = 0 ; i < 8 ; i++ ){
                    for( j = 0 ; j < 8 ; j++ ){
                        //Memory Registers
                        int index = 10*i + j;
                        int address = 0x80 + 20*i+2*j;
        
                        newFrame.frame[index] = (rand() % 255);
                        pixel.fastUpdate(newFrame.frame[index]);
                        newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                        
                        // Pixel Position
                        xPix = (xGrid + i*51);
                        yPix = (yGrid + j*51);
                        newPix.setPosition( xPix, yPix );
                        
                        /*
                         //Hardware Function
                         pixel.fastUpdate( gridward.read(pixAddr) );
                         newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                         */
                        
                        // Draw the Pixel
                        window.draw( newPix );
                    }
                }
            
                
                    if(recordStatus == true){
                        vidward.addFrame(newFrame);
                    }
                playward.record(topward,stackward,recordStatus,recordTime);//Playbar Recording Control
                playward.draw(window);//Draws playbar element to window object
                break;

            case 3:     //Playback Mode
                
               /* do{
                    fPtr = vPtr->getFrame( tempCount ); //Playback Grid
                    for( i = 0 ; i < 8 ; i++ ){
                        for( j = 0 ; j < 8 ; j++ ){
                            xPix = (xGrid + i*pixScale);
                            yPix = (yGrid + j*pixScale);
                            newPix.setPosition( xPix, yPix );
                            
                            pixel.fastUpdate( fPtr->access(i,j) );
                            newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                            
                            if( difftime( time(NULL), tempTime) >= (1/gridward.getFPS())){
                                window.draw(newPix);
                            }
                        }
                    }
                    tempCount++;
                } while(tempCount < vPtr->getframeCount());
                
                */
                
                playward.draw(window);//Update window object
                playward.playback(topward,stackward,playbackStatus);//Playbar Playback animations

                break;
        }// End Layer Control Switch
        
        //Sync all elements
        toolward.sync(menuLayer);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}



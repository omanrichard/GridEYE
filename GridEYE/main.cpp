
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>                //Grahpics Librars
#include "Event.hpp"                        //Mouse Move Events
#include "Mouse.hpp"                        //Mouse Clicks

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
#define GREENLED 4                          //GPIO pin connected to Green LED Anode
#define REDLED   5                          //GPIO Pin connected to Red LED Anode
#define PDE 0x68                            //Grid-EYE I2C Address
#define xGrid 200
#define yGrid 98


//Global Objects

pixMask pixel;                              // Pixel Obj, stores RBG values

terminal stackward(6, "Thermal Camera");    //Terminal Stack with 6 blank lines
toolbar toolward;                           //Toolbar
settingsMenu setward;                       //Settings Menu
topBar topward;                             //Top Status Bar
playBar playward(sf::Vector2f(35, 375),1);  //Playback bar
fastVideo vidward;                          //Test Video Implementation


int menuLayer = 0;                          //0:Home;1:Settings;2:Record;3:Playback;
                                            //4:Stop;5:Save;6:Delete
bool recordStatus = false;                  //True: Recording; False: Not Recording
bool playbackStatus = false;                //True: Playing Clip; False: Not Playing Clip

int recordTime = 10;                         //Time to record the video, default 10 seconds

int i, j;
int xPix, yPix;

int pixScale = 51;



int main(int, char const**)
{
    // Wiring Pi Setup
    GridEYE gridward;                       //Grid Eye Object
    GridEYE* gPtr = &gridward;
    gridward.setFD();//Fix
   
    wiringPiSetup();                        //WiringPiSetup
    pinMode(GREENLED, OUTPUT);              //Configure Green Led Pin
    pinMode(REDLED,OUTPUT);                 //Configure Red Led Pin
   
    digitalWrite(GREENLED, 0);              //Turns Green Led On
    digitalWrite(REDLED, 1);                //Turns Red Led Off
    
//-----------------------------------------------------------------
// Set Up
//-----------------------------------------------------------------
    session currentSession; // Begins session
    int sessionIndex = 0;

    int tempFPS;
    int fCount = 0;
    int tempCount = 0;
    
    video* vPtr = NULL;
    frame* fPtr = NULL;
    frame* prevFrame = NULL;

    int temp = 0;       // Stores value from GridEYE pixel
    int pixAddr = 0x80; // GridEYE pixel 1
    
    std::string filename;
    
    time_t recordStart;
    time_t tempTime;
    
    setward.setDefaultRecordTime(recordTime); //sync settings layer to default values - in seconds
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(700, 700), "PGE-DPA v.2"); //Creates Winodw
    //----------------- Camera Grid -----------------
    sf::RectangleShape newPix(sf::Vector2f(50, 50));

    
    //Background is obmitted to improve speed during demo
    //----------------- Background ------------------
    // sf::Texture t_background;//Background text - stays global for now
    // sf::Sprite background;//Background Sprite - stays global for now
    
    // if(!t_background.loadFromFile("texture2.jpg")){//Load backgroud image
    //    return EXIT_FAILURE;//Exit program and report error if file can be found
    //}
    //background.setTexture(t_background);//maps background text to background sprite
    //background.setPosition(0,0);//move background sprite to origin
    //window.draw(background);//draws background
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    
//-----------------------------------------------------------------
// Draw Loop
//-----------------------------------------------------------------
    
// Play the music
// music.play();

/*/
 ------------------------ Start the main loop -----------------------
/*/
    tempCount = 0;
    recordTime = gridward.runtime;

    
    topward.setMode(0); //Set Mode to standy By
    
    while (window.isOpen()) //While the window is open.
    {
      //LED Control
        if(recordStatus == true){ //Turns Red Led on and Green Led off when recording
           
            digitalWrite(GREENLED,1);
            digitalWrite(REDLED,0);
            
        }
        else if(recordStatus == false){//Turns Red Led off and Green Led on when in stand-by
           
            digitalWrite(GREENLED,0);
            digitalWrite(REDLED,1);
            
        }
        
        //-----------------------------------------------------------------
        // Process Events - These are user input including Mouse Clicks and Mouse Moves
        //-----------------------------------------------------------------
        sf::Event event;                                            //Create SFML event object
        
        while(window.pollEvent(event)){
            toolward.event(event);                                  //Handles Mouse moving events
            
            //The Following events only happen on each click
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                toolward.onClick(window,stackward);                 //Handles Mouse click events
                
                if(recordStatus == true){                           //Stop recording video on click
                    menuLayer = 4;                                  //When recoding, any mouse click will exicute stop function
                    toolward.sync(menuLayer);//Syncs the toolbar with the new menu layer
                }
                menuLayer = toolward.exit();                        //Changes menu Lever to what is stored in toolbar
        
                //Settings Menu
                if(menuLayer == 1){
                    setward.onClick(window, gPtr, stackward); //Scans buffer for corosponing inputs.
                    
                    recordTime = setward.syncRecordLength();
                    gridward.runtime = recordTime;
                    menuLayer = setward.exit();//Allows settings menu to Menu layers
                
                    toolward.sync(menuLayer);//Sync toolbar to current menu layer
                }
                // Capture Video
                if(menuLayer == 2){//Executes Once when Capture is clicked
                    vPtr = currentSession.getVideo(sessionIndex);
                    if( vPtr == NULL )
                        sessionIndex = 0;
                    else
                        sessionIndex++;
                    
                    try{
                        vPtr = new video;
                        
                        if( vPtr == NULL )
                            throw "Could not Allocate memory to store capture video";
                    }
                    catch( string error ){
                        stackward.print( error );
                        sessionIndex--;
                        menuLayer = 0;
                    }
                    
                    currentSession.addVideo(vPtr);
                    
                    recordStatus = true;                        //Switichs device into Record Mode
                    playward.setClipStartTime(time(NULL));      //Sets the clip start time in the playbar
                    toolward.sync(menuLayer);                   //Sync toolbar to current menu layer
                    recordStart = time(NULL);                   //sets absolute timee recording starts
                }
                // Playback Video
                if(menuLayer == 3){//Executes Once when Playback is clicked
                    try{
                        vPtr = currentSession.getVideo(0);
                        if( vPtr == NULL )
                            throw 0;
                        playward.onClick(window,stackward);
                        playward.setPlaybackStartTime(time(NULL));  //Sets playback start time in playbar
                        playbackStatus = true;                      //Switchs device into payback mode
                        toolward.sync(menuLayer);//Sync toolbar to current menu layer
                        vPtr = currentSession.getVideo( sessionIndex );
                        recordStart = time( NULL );
                    }
                    catch( int ){
                        stackward.print("No videos stored in current session");
                        menuLayer = 0;
                    }
                }
                // Stop-Record
                if(menuLayer == 4){//Executes Once when Stop is clicked
                        
                    recordStatus = false;
                    
                    stackward.print("Recording Ended, Discarded Recording");
                    try{
                        vPtr = currentSession.getVideo(sessionIndex);
                        if( vPtr == NULL )
                            throw 0;
                        currentSession.undoRec();
                        sessionIndex--;
                        menuLayer = 0; //Return to home
                        toolward.sync(menuLayer);//Sync toolbar to current menu layer
                    }
                    catch( int x )
                    {
                        stackward.print( "No videos stored in current Session ");
                        menuLayer = 0; //Return to home
                        toolward.sync(menuLayer);//Sync toolbar to current menu layer
                    }
                }
                // Export Video
                if(menuLayer == 5){//Executes Once when Export is clicked
                    stackward.print("Exporting Video");
                    
                    try{
                        vPtr = currentSession.getVideo( sessionIndex );
                        if( vPtr == NULL )  // Checks session stack for a valid video pointer
                            throw 0;
                    
                        filename = "pge_vid_";                      // Base string for file name
                        filename += std::to_string(sessionIndex+1); // Converts the video index to a string,
                                                                    // appends to the base
                        filename += ".txt";                         // appends .txt
                        vPtr->exportVideo( filename );              // Exports data file with created filename

                        stackward.print("Success");                 // Reports to user the file was successfully created
                        menuLayer = 0;
                        toolward.sync(menuLayer);
                    }
                    catch( int x ){
                        if( x == 0 )    // Error message if no videos are present on the stack
                            stackward.print( "Unable to export video. Error 0x0: No videos stored in current session");
                    }
                }
                if(menuLayer == 6){//Executes Once when Delete is clicked
                    vPtr = currentSession.getVideo( sessionIndex );
                    try{
                        if( vPtr == NULL )
                            throw 0;
                        if( sessionIndex < 0 )
                            throw "exception handled";
                        currentSession.undoRec();
                        sessionIndex--;
                    }
                    catch( int x ){
                        stackward.print( "Error 0x00: Cannot delete video. No videos stored in current session");
                    }
                    catch( string error ){
                        stackward.print(error);
                        sessionIndex = 0;
                    }
                    toolward.sync(menuLayer);// Sync toolbar to current menu layer
                }
                topward.setMode(menuLayer);// Set topbar to current mode
            }
           
            //Terminate Applicaiton Events
            
            //On Window Close Click
            if (event.type == sf::Event::Closed) {
                
                window.close();                 // Close Window / Quit Application
            }
            //On Key Press
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        
                window.close();                 // Close Window / Quit Application
            }
        }
   
        topward.updateClock(time(NULL));        // Updates Clock
        
        window.clear();                         // Clears Screen Object of all Elements
        
        //window.draw(background);                //Draws Background Object First
        topward.draw(window);                   //Draws Top Bar
        stackward.draw(window);                 //Draws Terminal
        toolward.draw(window);                  //Draws Toolbar
       
        
        
        //-----------------------------------------------------------------
        // Layer Control
        //-----------------------------------------------------------------
        switch(menuLayer){
            default:    //Live Feed, not recording.
                pixAddr = 0x80;
                for( i = 0 ; i < 8 ; i++ ){
                    for( j = 0 ; j < 8 ; j++ ){
                        //Pixel Position
                        xPix = (xGrid + i*51);
                        yPix = (yGrid + j*51);
                        newPix.setPosition( xPix, yPix );
                        
                        //Hardware Function
                        pixel.lazyUpdate( gridward.read(pixAddr) );
                        newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                        
                        //Memory Registers
                        if(pixAddr < 0xFF && pixAddr >= 0x80)   //Error Protection
                            pixAddr += 2;                       //Increment to next Register
                        
                        // Draw the Pixel
                        window.draw( newPix );
                    }
                }
                break;
                
            case 1:   //Settings Menu
                setward.draw(window);   //Draw Settings Menu
                break;
            
            case 2:  //Capture Mode
                    if( difftime( time(NULL), tempTime) >= 1 ){     //Records and displays data after 1 second has elapsed
                        try{
                            fPtr = new frame( gPtr );
                            if( fPtr == NULL )  // Check to see if memory was allocated for the frame
                                throw "Could not allocate memory for new frame...";
                        }
                        catch( string error ){
                            stackward.print(error);
                        }
                        
                        vPtr->addFrame( fPtr );
                        
                        for( i = 0 ; i < 8 ; i++ ){
                            for( j = 0 ; j < 8 ; j++ ){
                                //Memory Registers
                                int index = 10*i + j;
                                int address = 0x80 + 20*i+2*j;
                                
                                pixel.lazyUpdate(fPtr->access(i,j));
                                newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                                
                                //Pixel Position
                                xPix = (xGrid + i*51);
                                yPix = (yGrid + j*51);
                                newPix.setPosition( xPix, yPix );
                                
                                //Draw the Pixel
                                window.draw( newPix );
                            }
                        }
                        
                        prevFrame = fPtr;
                        fCount++;
                        //Exits Capture when the record time is reached
                        if( difftime( time(NULL), recordStart ) >= gridward.runtime || fCount == (gridward.FPS * gridward.runtime) ){
                            menuLayer = 0;
                            recordStatus = false;
                            topward.setMode(0);
                            playward.setClipEndTime(time(NULL));
                            currentSession.addVideo(vPtr);
                            fCount = 0;
                            stackward.print("Capture Finished");
                        }
                        tempTime = time(NULL);
                    }
                    else{
                        for( i = 0 ; i < 8 ; i++ ){
                            for( j = 0 ; j < 8 ; j++ ){
                                //Memory Registers
                                int index = 10*i + j;
                                int address = 0x80 + 20*i+2*j;
                                
                                pixel.lazyUpdate(prevFrame->access(i,j));
                                newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                                
                                // Pixel Position
                                xPix = (xGrid + i*51);
                                yPix = (yGrid + j*51);
                                newPix.setPosition( xPix, yPix );
                                
                                // Draw the Pixel
                                window.draw( newPix );
                            }
                        }
                    }
                    playward.record(topward,stackward,recordStatus,recordTime);//Playbar Recording Control
                    playward.draw(window);//Draws playbar element to window object
                    break;
                
            case 3:     //Playback Mode
                //After a second has passed, display the next frame
                if( difftime( time(NULL), tempTime) >= 1 ){
                    try{
                        if( fCount > ( gridward.runtime * gridward.FPS ))
                            throw 2;
                        
                        fPtr = vPtr->getFrame(fCount);
                    
                
                    for( i = 0 ; i < 8 ; i++ ){
                        for( j = 0 ; j < 8 ; j++ ){
                            pixel.lazyUpdate(fPtr->access(i,j));
                            newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                            
                            // Pixel Position
                            xPix = (xGrid + i*51);
                            yPix = (yGrid + j*51);
                            newPix.setPosition( xPix, yPix );
                            
                            // Draw the Pixel
                            window.draw( newPix );
                        }
                    }
                    
                    prevFrame = fPtr;
                    fCount++;
                    
                    //Exits Playback if record time is reached
                    if( difftime( time(NULL), recordStart ) >= gridward.runtime || fCount == (gridward.runtime * gridward.FPS) ){
                        menuLayer = 0;
                        recordStatus = false;
                        topward.setMode(0);
                        fCount = 0;
                        toolward.sync(menuLayer);
                        stackward.print("Playback Complete");
                    }
                    tempTime = time(NULL);
                    
                    }
                    catch( int x ){ //Exits Playback if playback extends past framecount
                        menuLayer = 0;
                        recordStatus = false;
                        topward.setMode(0);
                        fCount = 0;
                        toolward.sync(menuLayer);
                        stackward.print("Playback Complete");
                    }
                }
                else{   //Displays previous frame if less than a second has passed
                    for( i = 0 ; i < 8 ; i++ ){
                        for( j = 0 ; j < 8 ; j++ ){
                            
                            pixel.lazyUpdate(prevFrame->access(i,j));
                            newPix.setFillColor(sf::Color(pixel.getr(),pixel.getg(), pixel.getb()));
                            
                            // Pixel Position
                            xPix = (xGrid + i*51);
                            yPix = (yGrid + j*51);
                            newPix.setPosition( xPix, yPix );
                            
                            // Draw the Pixel
                            window.draw( newPix );
                        }
                    }
                }
              
                playward.draw(window);//Update window object
                playward.playback(topward,stackward,playbackStatus);//Playbar Playback animations
                break;
                
            case 4: // White Grid
                
                for( i = 0 ; i < 8 ; i++ ){
                    for( j = 0 ; j < 8 ; j++ ){
                        // Pixel Position
                        xPix = (xGrid + i*51);
                        yPix = (yGrid + j*51);
                        newPix.setPosition( xPix, yPix );
                        
                        newPix.setFillColor(sf::Color(255,255,255));
                        
                        // Draw the Pixel
                        window.draw( newPix );
                    }
                }
                playward.draw(window);//Update window object
                playward.playback(topward,stackward,playbackStatus);//Playbar Playback animations
        }// End Layer Control Switch
        
        //Sync all elements
        toolward.sync(menuLayer);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}



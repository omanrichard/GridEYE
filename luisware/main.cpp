
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
//#include <wiringPi.h>
#include <Mouse.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#define GRIDEYEADDRESS 0x68

using namespace sf;

class GridEYE{
    private:
    
    public:
    GridEYE(int address); //Hint: its at 0x68
    int read(int row, int col);
    void reset(void);
    void update(void);
    void test(int row, int col);//Draw Test pattern
    int r,g,b;
    int FPS = 10;
    short pixelL;
};

GridEYE::GridEYE(int address){
    /*/
     I2C begin transmission @ address
     //Inisilize sensor
    /*/
}
int GridEYE::read(int row, int col){
    /*/ read code /*/
}
void GridEYE::reset(void){

}
void GridEYE::test(int row, int col){
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
    pixelL = rand() % 255;
}
void GridEYE::update(void){
    
}


/*/
class terminal {
    private:
    std::string Row1;
    std::string Row2;
    std::string Row3;
    std::string Row4;
    std::string Row5;
    std::string Row6;
    std::string Row7;
    
    public:
    terminal(int x1,int y1,int length,int width);
    void write(std::string newText);
    void clear(void);
    void draw(void);
};
//length = 625, width = 94, x1 = 94, y1 = 596
terminal::terminal(int x1, int y1, int length, int width){
    sf::RectangleShape terminal(sf::Vector2f( length, width ));
    terminal.setFillColor(sf::Color::Black);
    terminal.setPosition(x1, y1+10);
    
    sf::RectangleShape terminalHeader(sf::Vector2f( length, 10 ));
    terminalHeader.setFillColor(sf::Color(255,94,20));
    terminalHeader.setPosition(x1, y1);
}
void terminal::draw(void){
    window.draw(terminalHeader);
    window.draw(terminal);
}
/*/


GridEYE gridward(GRIDEYEADDRESS);

// Here is a small helper for you! Have a look.
//#include "ResourcePath.hpp"

int i,j;
int recordMins = 0;
int recordSeconds = 0;

int menuLayer = 0; //Each "screen" gets its own layer. ie main screen is 0, settings menu is 1, ect.
int rootx = 150;
int rootY = 100;

int main(int, char const**)
{
    
//--------------------- Set up -----------------------------------
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(700, 700), "ECE3220 Final Project");
/*
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Boss Camera", font, 50);
    text.setFillColor(sf::Color::Black);

    // Load a music to play
*    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
*/
    
    // Load sprites to display
    
    //----------------- Menu ---------------------
    Texture t_background;
    if(!t_background.loadFromFile("texture2.jpg")){
        return EXIT_FAILURE;
    }
    Texture t_settings;
    if (!t_settings.loadFromFile("settings.png")) {
        return EXIT_FAILURE;
        
    }
    Texture t_record;
    if (!t_record.loadFromFile("record.png")) {
        return EXIT_FAILURE;
    }
    Texture t_stop;
    if (!t_stop.loadFromFile("stop.png")) {
        return EXIT_FAILURE;
    }
    Texture t_play;
    if (!t_play.loadFromFile("play.png")) {
        return EXIT_FAILURE;
    }
    Texture t_trash;
    if (!t_trash.loadFromFile("trash.png")) {
        return EXIT_FAILURE;
    }
    Texture t_save;
    if (!t_save.loadFromFile("save.png")) {
        return EXIT_FAILURE;
    }
    Texture t_quit;
    if (!t_quit.loadFromFile("gravestone.png")) {
        return EXIT_FAILURE;
    }
    Texture t_close;
    if(!t_close.loadFromFile("cancel.png")){
        return EXIT_FAILURE;
    }
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
   
    
    //----------------- Camera Grid ----------------
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
    
 /*/----------------Draw Toolbar----------------/*/
   
    sf::RectangleShape toolbarFrame(sf::Vector2f( 94, 700 ));
    toolbarFrame.setFillColor(sf::Color(132, 101, 142,100));
    toolbarFrame.setPosition(0, 0);
    
    sf::RectangleShape toolbarHeader(sf::Vector2f( 5, 700 ));
    toolbarHeader.setFillColor(sf::Color(0, 0, 0,100));
    toolbarHeader.setPosition(89, 0);
    
    Sprite background(t_background);
    background.setPosition(0,0);
    
    sf::RectangleShape selection(sf::Vector2f( 89, 70 ));
    selection.setFillColor(sf::Color(0, 0, 0, 100));
    selection.setPosition(-100, -100);
    
    sf::RectangleShape selectionTextBox(sf::Vector2f( 94, 20 ));
    selectionTextBox.setFillColor(sf::Color(255, 255, 255, 100));
    selectionTextBox.setPosition(-100, -100);
    
    sf::Text selectionText("void", font, 10);
    selectionText.setFillColor(sf::Color::Black);
    selectionText.setPosition( -100 , -100);
    
    
    
    Sprite settings( t_settings );
    settings.setPosition( 15, 30 );
    settings.scale(0.50, 0.50);
    
    Sprite record( t_record );
    record.setPosition( 15, 109+15 );
    record.scale(0.50, 0.50);
    
    Sprite play( t_play );
    play.setPosition( 15, 188+30 );
    play.scale(0.50, 0.50);
    
    Sprite stop( t_stop );
    stop.setPosition( 15, 267+45);
    stop.scale(0.50, 0.50);

    Sprite save( t_save );
    save.setPosition( 15, 346+60 );
    save.scale(0.50, 0.50);
    
    Sprite trash( t_trash );
    trash.setPosition( 15, 425+75 );
    trash.scale(0.50, 0.50);
    
    Sprite quit( t_quit );
    quit.setPosition( 15, 504+90 );
    quit.scale(0.50, 0.50);
    
    
    
 /*/-----------------Draw Terminal Window-------------------/*/
    
    
    
    std::string terminalTextArray[6];
    
    sf::Text terminalText1("root@thermalCamera: Terminal text placeholder line 1", font, 12);
    terminalText1.setFillColor(sf::Color(0,255,0));
    terminalText1.setPosition( 100 , 608);
    
    sf::Text terminalText2("root@thermalCamera: Terminal text placeholder line 2", font, 12);
    terminalText2.setFillColor(sf::Color(0,255,0));
    terminalText2.setPosition( 100 , 622);
    
    sf::Text terminalText3("root@thermalCamera: Terminal text placeholder line 3", font, 12);
    terminalText3.setFillColor(sf::Color(0,255,0));
    terminalText3.setPosition( 100 , 636);
    
    sf::Text terminalText4("root@thermalCamera: Terminal text placeholder line 4", font, 12);
    terminalText4.setFillColor(sf::Color(0,255,0));
    terminalText4.setPosition( 100 , 650);
    
    sf::Text terminalText5("root@thermalCamera: Terminal text placeholder line 5", font, 12);
    terminalText5.setFillColor(sf::Color(0,255,0));
    terminalText5.setPosition( 100 , 664);
    
    sf::Text terminalText6("root@thermalCamera: Terminal text placeholder line 6", font, 12);
    terminalText6.setFillColor(sf::Color(0,255,0));
    terminalText6.setPosition( 100 , 678);
    
    sf::RectangleShape terminal(sf::Vector2f( 625, 94 ));
    terminal.setFillColor(sf::Color(0,0,0,150));
    terminal.setPosition(94, 606);
    
    sf::RectangleShape terminalHeader(sf::Vector2f( 625, 10 ));
    terminalHeader.setFillColor(sf::Color(255,94,20,150));
    terminalHeader.setPosition(94, 596);
   
    
    
    /*/---------------Background---------------/*/
    
    
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
    
    sf::Text r_text("Standy-by", font, 25);
    r_text.setFillColor(sf::Color::Green);
    r_text.setPosition( 550 , 10);
    
    sf::Text recordingTimeText("00:00", font, 20);
    recordingTimeText.setFillColor(sf::Color::White);
    recordingTimeText.setPosition( 590 , 45);
    
    
    
    /*/----Settings Objects----/*/
    sf::RectangleShape settingsBackground(sf::Vector2f(500, 400 ));
    settingsBackground.setFillColor(sf::Color(255, 255, 255,150));
    settingsBackground.setPosition(-500, -500);
    
    Sprite settingsExit(t_close);
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
    
    //Set Button Colors
    settingsTenFPS.setFillColor(sf::Color(30,144,255));
    settingsOneFPS.setFillColor(sf::Color::White);
    
    settingsMinsUp.setFillColor(sf::Color::Green);
    settingsMinsDown.setFillColor(sf::Color::Red);
    settingsSecondsUp.setFillColor(sf::Color::Green);
    settingsSecondsDown.setFillColor(sf::Color::Red);
    settingsMinsBox.setFillColor(sf::Color::White);
    settingsSecondsBox.setFillColor(sf::Color::White);
   
    settingsRangeTrue.setFillColor(sf::Color(30,144,255));
    settingsRangeHuman.setFillColor(sf::Color::White);
    
    settingsReset.setFillColor(sf::Color(30,144,255));
    settingsApply.setFillColor(sf::Color(30,144,255));
    
   
    //settings Button Position
    
    settingsTenFPS.setPosition(rootx+100 ,rootY+75 );//Default
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
    

    
    
    
    
    
    
    //Settings Text Declare
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
    
    //Settings Text Color
    settingsBackground.setPosition(rootx,rootY);//Move settings background in place
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
    
    
    
    

    
    
/*/----Draw ----/*/
    // Play the music
    //music.play();

/*/------------------------Start the game loop-----------------------
 --------------------------------------------------------------------
 --------------------------------------------------------------------
 ------------------------------------------------------------------/*/
   
    
    while (window.isOpen())
    {
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
        window.draw(line);
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
            //Menu selection
            if( menuLayer == 0){
            
                if(event.type == sf::Event::MouseMoved){
                    if(event.mouseMove.x > 0 && event.mouseMove.x < 94){
                        if(event.mouseMove.y > 0 && event.mouseMove.y < 119){//Settings
                            selection.setPosition(0, 26);
                            selectionText.setString("Settings");
                            selectionText.setPosition(50 , 89);
                            selectionTextBox.setPosition(50,89);
                        }
                        if(event.mouseMove.y > 119 && event.mouseMove.y < 189){//New
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
                else if(event.mouseMove.x > 94){//Mouse not over on toolbar
                    selection.setPosition(-100, -100);//Move Offscreen
                    selectionText.setString("Void");
                    selectionText.setPosition( -100 , -100);//Move Offscreen
                    selectionTextBox.setPosition(-100,-100);//Move Offscreen
                }
            }            
            if( menuLayer == 1 ){
                if(event.type == sf::Event::MouseMoved){
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2i position = sf::Mouse::getPosition(window);
                        if (position.x > 0 && position.x < 95){//Within toolbar
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
            if(menuLayer == 0){
                //Settings
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i position = sf::Mouse::getPosition(window);
                if (position.x > 0 && position.x < 95){//Within toolbar
                    if (position.y > 0 && position.y < 119){
                       
                        menuLayer = 1;
                    }
                }
                //exit
                if (position.x > 0 && position.x < 95){//Within toolbar
                    if (position.y > 590 && position.y < 700){
                        window.close();
                        
                    }
                }
            }
            }
            
            /*/----Layer 1 "Settings"----/*/
            if(menuLayer == 1){ // Hit Boxes
                // Exit Button
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > 143  && position.x < 173){
                        if (position.y > 93 && position.y < 123){//settings Exit Button
                            menuLayer = 0;

                        }
                    }
                    
                }
                
                // 10 FPS
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > (rootx + 100)  && position.x < (rootx+175)){
                        if (position.y > (rootY+ 75) && position.y < (rootY+100)){
                            settingsTenFPS.setFillColor(sf::Color(0,255,0));
                            settingsOneFPS.setFillColor(sf::Color(255,0,0));
                            gridward.FPS = 10;
                        }
                    }
                }
                // One FPS
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > (rootx + 325)  && position.x < (rootx+400)){
                        if (position.y > (rootY+75) && position.y < (rootY+100)){
                            settingsOneFPS.setFillColor(sf::Color(0,255,0));
                            settingsTenFPS.setFillColor(sf::Color(255,0,0));
                            gridward.FPS = 1;
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
                            settingsMinsUp.setFillColor(sf::Color(0,255,0));
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
                            settingsMinsDown.setFillColor(sf::Color(255,0,0));
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
                            settingsSecondsUp.setFillColor(sf::Color(0,255,0));
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
                            settingsSecondsDown.setFillColor(sf::Color(255,0,0));
                        }
                    }
                }
                // Sensor TRUE
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > (rootx + 75)  && position.x < (rootx + 175)){
                        if (position.y > (rootY + 300) && position.y < (rootY + 325)){
                            settingsRangeTrue.setFillColor(sf::Color(0,255,0));
                            settingsRangeHuman.setFillColor(sf::Color(255,0,0));
                        }
                    }
                }
                // Sensor HUMAN
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > (rootx + 325)  && position.x < (rootx + 425)){
                        if (position.y > (rootY + 300) && position.y < (rootY + 325)){
                            settingsRangeHuman.setFillColor(sf::Color(0,255,0));
                            settingsRangeTrue.setFillColor(sf::Color(255,0,0));

                        }
                    }
                }
                // RESET
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > (rootx + 50)  && position.x < (rootx+200)){
                        if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                            settingsReset.setFillColor(sf::Color(0,255,0));
                            gridward.reset();
                            settingsRangeTrue.setFillColor(sf::Color(0,255,0));
                            settingsTenFPS.setFillColor(sf::Color(0,255,0));
                            recordMins = 0;
                            settingsMinsText.setString(std::to_string(recordMins));
                            recordSeconds = 0;
                            settingsSecondsText.setString(std::to_string(recordSeconds));
                            
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
                            settingsApply.setFillColor(sf::Color(0,255,0));
                            gridward.update();
                            menuLayer = 0;
                        }
                    }
                }
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > (rootx + 300)  && position.x < (rootx + 450)){
                        if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                            settingsApply.setFillColor(sf::Color(255,144,255));
                            gridward.update();
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
        window.draw(r_text);
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
        
          
        /*/----Draw Toolbar----/*/
            
        window.draw(toolbarFrame);
        window.draw(toolbarHeader);
            
        window.draw(settings);
            
            
        window.draw(record);
        window.draw(stop);
        window.draw(play);
        window.draw(trash);
        window.draw(save);
        window.draw(quit);
        
        window.draw(selection);
        window.draw(selectionTextBox);
        window.draw(selectionText);
        
        //Draw output Grid
       
        if(menuLayer == 0){
        for( i=0 ; i < 8 ; i++ ){
            for( j=0 ; j<8 ; j++ ){
                window.draw(grid[i][j]);            }
        }
        }
       
        
        
        //Draw the Terminal window
        std::string newText;
        
        for(int i = 0; i < 5; i++){
            terminalTextArray[i] = terminalTextArray[i+1];
        }
        terminalTextArray[5] = newText;
       /*/
        terminalText1.setString(terminalTextArray[0]);
        terminalText2.setString(terminalTextArray[1]);
        terminalText3.setString(terminalTextArray[2]);
        terminalText4.setString(terminalTextArray[3]);
        terminalText5.setString(terminalTextArray[4]);
        terminalText6.setString(terminalTextArray[5]);
        /*/
        
        
        window.draw(terminalHeader);
        window.draw(terminal);
        window.draw(terminalText1);
        window.draw(terminalText2);
        window.draw(terminalText3);
        window.draw(terminalText4);
        window.draw(terminalText5);
        window.draw(terminalText6);
       
        
        
        
        //window.draw(line);
        //window.draw(line2);
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}


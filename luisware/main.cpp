
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
    void test(int row, int col);//Draw Test pattern
    int r,g,b;
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


int menuLayer = 0; //Each "screen" gets its own layer. ie main screen is 0, settings menu is 1, ect.
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
    
    sf::Text r_text("Recording", font, 30);
    r_text.setFillColor(sf::Color::Red);
    r_text.setPosition( 550 , 10);
    
    /*/----Settings Objects----/*/
    sf::RectangleShape settingsBackground(sf::Vector2f(500, 400 ));
    settingsBackground.setFillColor(sf::Color(255, 255, 255,150));
    settingsBackground.setPosition(-500, -500);
    
    Sprite settingsExit(t_close);
    settingsExit.setPosition(143,93);
    settingsExit.scale(0.1, 0.1);
    
    //Settings Buttons
    CircleShape settingsTenFPS;
    CircleShape settingsOneFPS;
    RectangleShape settingsMinsUp;
    RectangleShape settingsMinsDown;
    RectangleShape settingsSecondsUp;
    RectangleShape settingsSecondsDown;
    CircleShape settingsRangeTrue;
    CircleShape settingsRangeHuman;
    RectangleShape settingsReset;
    RectangleShape settingsApply;
    
    RectangleShape settingsMinsBox;
    RectangleShape settingsSecondsBox;
    
    
    Text settingsFPSText("Frames Per Second",font, 10);
    Text settingsFPSTextValTen("10 FPS", font, 10);
    Text settingsFPSTextValOne("10 FPS",font,10);
    Text settngsMinsText;
    Text settingsSecondsText;
    Text settingsRangeText("Sensor Dynamic Range",font,10);
    Text settingsRangeTextTrue("True",font,10);
    Text settingsRangeTextHuman("Human Mode",font, 10);
    Text settingsResetText("Reset Sensor",font, 10);
    Text settingsApplyText("Apply Settings", font, 10);
     
    
    
    

    
    
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
            
            /*/----Layer 1 "Settings"----/*/
            if(menuLayer == 1){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (position.x > 143  && position.x < 173){
                        if (position.y > 93 && position.y < 123){//settings Exit Button
                        menuLayer = 0;
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
        
        
        /*/---Draw Settings Window----/*/
            if(menuLayer == 1){
                
                // Settings Background
                window.draw(settingsBackground);//Draw settings menu when clicked
                // Exit Button
                window.draw(settingsExit);//Exit button settings menu
               
                // Frame Settings
                window.draw(settingsTenFPS);
                window.draw(settingsOneFPS);
                
                // Collection Settings
                window.draw(settingsMinsUp);
                window.draw(settingsMinsDown);
                window.draw(settingsSecondsUp);
                window.draw(settingsSecondsDown);
                
                // Sensor Range Settings
                window.draw(settingsRangeTrue);
                window.draw(settingsRangeHuman);
                // Reset Sensor
                window.draw(settingsReset);
                
                // Apply Settings
                window.draw(settingsApply);


                
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


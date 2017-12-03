//
//  graphicClasses.cpp
//  GridEYE
//
//  Created by Grant Hilgert on 12/1/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "graphicClasses.h"



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
    
    if (!toolbarFont.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
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
    
    selection.setSize(sf::Vector2f( 89, 70 ));
    selection.setFillColor(sf::Color(0, 0, 0, 100));
    selection.setPosition(-100, -100);
    
    
    selectionTextBox.setSize(sf::Vector2f( 94, 20 ));
    selectionTextBox.setFillColor(sf::Color(255, 255, 255, 100));
    selectionTextBox.setPosition(-100, -100);
    
    selectionText.setString("void");
    selectionText.setCharacterSize(8);
    selectionText.setFont(toolbarFont);
    selectionText.setFillColor(sf::Color::Black);
    selectionText.setPosition( -100 , -100);
    
    
    
}
//Draws toolbar
void toolbar::draw(sf::RenderWindow &window){
    //Draws Objects on display buffer
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
}
//Toolbar Mouse Events
void toolbar::event(sf::Event &toolbarEvent){
    //When mouse moves over menu item, semi transparent box is drawn over them
    if(toolbarEvent.type == sf::Event::MouseMoved){//If event is Mousedmoved type
        if(toolbarEvent.mouseMove.x > 0 && toolbarEvent.mouseMove.x < 94){//if Mouse is within toolbar
            //Settings
            if(toolbarEvent.mouseMove.y > 0 && toolbarEvent.mouseMove.y < 119){
                selection.setPosition(0, 26);
                selectionText.setString("Settings");
                selectionText.setPosition(50 , 89);
                selectionTextBox.setPosition(50,89);
            }
            //New Capture
            if(toolbarEvent.mouseMove.y > 119 && toolbarEvent.mouseMove.y < 189){
                selection.setPosition(0, 119);
                selectionText.setString("Capture");
                selectionText.setPosition( 50 , 159);
                selectionTextBox.setPosition(50,159);
                
            }
            //Play Capture
            if(toolbarEvent.mouseMove.y > 219 && toolbarEvent.mouseMove.y < 308){
                selection.setPosition(0, 219);
                selectionText.setString("Play Capture");
                selectionText.setPosition( 50 , 278);
                selectionTextBox.setPosition(50,278);
            }
            //Stop Capture
            if(toolbarEvent.mouseMove.y > 308 && toolbarEvent.mouseMove.y < 402){
                selection.setPosition(0, 308);
                selectionText.setString("Stop Capture");
                selectionText.setPosition( 30 , 372);
                selectionTextBox.setPosition(30,372);
            }
            //Save Capture
            if(toolbarEvent.mouseMove.y > 402 && toolbarEvent.mouseMove.y < 496){
                selection.setPosition(0, 402);
                selectionText.setString("Save Capture");
                selectionText.setPosition( 30 , 439);
                selectionTextBox.setPosition(30,439);
            }
            //Delete Capture
            if(toolbarEvent.mouseMove.y > 496 && toolbarEvent.mouseMove.y < 590){
                selection.setPosition(0, 496);
                selectionText.setString("Delete Capture");
                selectionText.setPosition( 30 , 560);
                selectionTextBox.setPosition(30,560);
            }
            //Ouit Program
            if(toolbarEvent.mouseMove.y > 590 && toolbarEvent.mouseMove.y < 700){
                selection.setPosition(0, 590);
                selectionText.setString("Close Application");
                selectionText.setPosition( 30 , 670);
                selectionTextBox.setPosition(30,670);
            }
        }
        //Moves Selection objects offscreen when mouse exits hit box
        else if(toolbarEvent.mouseMove.x > 94){
            selectionText.setString("Void");
            selectionText.setPosition( -100 , -100);
            selectionTextBox.setPosition(-100,-100);
            selection.setPosition(-100, -100);
        }
    }
}

void toolbar::onClick(sf::RenderWindow &window, terminal &stackward){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){//If left button is pressed
        sf::Vector2i position = sf::Mouse::getPosition(window);//Get position of mouse
            if (position.x > 0 && position.x < 95){//Within toolbar
                //Settings
                if (position.y > 0 && position.y < 119){
                    menuLayer = 1; //Change layer to settings layer
                }
                //Start Capture
                if (position.y > 119 && position.y < 189){
                    stackward.print("Starting Capture");
                }
                
                //Play capture
                if (position.y > 189 && position.y < 308){
                    stackward.print("Entering Playback Mode");
                    menuLayer = 2;//Change layer to playback
                }
                //Stop Caputre
                  if (position.y >308 && position.y < 402){
                      stackward.print("Stopping Capture");
                  }
                //Save capture
                if (position.y > 402 && position.y < 496){
                    stackward.print("Saving Capture");
                }
                //Delete capture
                if (position.y > 496 && position.y < 590){
                    stackward.print("Deleting Capture");
                }
                //exit - quit program
                if (position.y > 590 && position.y < 700){
                    window.close();//Close Window
                }
            }
        

}
}

int toolbar::exit(void){
    return menuLayer;
}
void toolbar::sync(int newMenuLayer){
    menuLayer = newMenuLayer;
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

void settingsMenu::onClick(sf::RenderWindow &window){//Button presses
    // Colors - Select: 30,144,255 Unselect: 135,206,250
    menuLayer = 1; //Set internal menuLayer reference
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){//When Left Mouse is clicked
        sf::Vector2i position = sf::Mouse::getPosition(window);//Get Mouse Coordinates
        
        //Settings Exit Button
        if (position.x > 143  && position.x < 173){//Add root to this
            if (position.y > 93 && position.y < 123){//Add root to this
                menuLayer = 0;
            }}
        
        // 10 FPS
        if (position.x > (rootx + 100)  && position.x < (rootx+175)){
            if (position.y > (rootY+ 75) && position.y < (rootY+100)){
                settingsTenFPS.setFillColor(sf::Color(30,144,255));
                settingsTenFPS.setOutlineThickness(2);
                settingsOneFPS.setFillColor(sf::Color(135,206,250));
                settingsOneFPS.setOutlineThickness(0);
                //gridward.setFPS(10);
            }}
        
        // One FPS
        if (position.x > (rootx + 325)  && position.x < (rootx+400)){
            if (position.y > (rootY+75) && position.y < (rootY+100)){
                settingsOneFPS.setFillColor(sf::Color(30,144,255));
                settingsOneFPS.setOutlineThickness(2);
                settingsTenFPS.setFillColor(sf::Color(135,206,250));
                settingsTenFPS.setOutlineThickness(0);
                //gridward.setFPS(1);
            }}
        
        // Minutes UP
        if (position.x > (rootx + 150)  && position.x < (rootx+200)){
            if (position.y > (rootY+175) && position.y < (rootY+200)){
                settingsMinsUp.setFillColor(sf::Color(255,144,255));
                if(recordMins <= 50){
                    recordMins++;
                    settingsMinsText.setString(std::to_string(recordMins));
                }
            }}
        
        // Minutes DOWN
        if (position.x > (rootx + 150)  && position.x < (rootx +200)){
            if (position.y > (rootY + 200) && position.y < (rootY+225)){
                settingsMinsDown.setFillColor(sf::Color(255,144,255));
                if(recordMins > 0){
                    recordMins--;
                    settingsMinsText.setString(std::to_string(recordMins));
                }
            }}
        // Seconds UP
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
            }}
        
        // Seconds DOWN
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
            }}
        
        // Sensor TRUE
        if (position.x > (rootx + 75)  && position.x < (rootx + 175)){
            if (position.y > (rootY + 300) && position.y < (rootY + 325)){
                settingsRangeTrue.setFillColor(sf::Color(30,144,255));
                settingsRangeTrue.setOutlineThickness(2);
                settingsRangeHuman.setFillColor(sf::Color(135,206,250));
                settingsRangeHuman.setOutlineThickness(0);
            }}
        
        // Sensor HUMAN
        if (position.x > (rootx + 325)  && position.x < (rootx + 425)){
            if (position.y > (rootY + 300) && position.y < (rootY + 325)){
                settingsRangeHuman.setFillColor(sf::Color(30,144,255));
                settingsRangeHuman.setOutlineThickness(2);
                settingsRangeTrue.setFillColor(sf::Color(135,206,250));
                settingsRangeTrue.setOutlineThickness(0);
                
            }}
        
        // RESET
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
                
            }}
        
        // APPLY
        if (position.x > (rootx + 300)  && position.x < (rootx + 450)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsApply.setFillColor(sf::Color(30,144,255));
                //gridward.update();
                //stackward.print("Settings Applied");
                menuLayer = 0;
            }}
    }//end button down
    
    
    //
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){  // Release
        sf::Vector2i position = sf::Mouse::getPosition(window);
        
        //MINS UP
        if (position.x > (rootx + 150)  && position.x < (rootx+200)){
            if (position.y > (rootY+175) && position.y < (rootY+200)){
                settingsMinsUp.setFillColor(sf::Color(30,144,255));
            }}
        
        //Mins Down
        if (position.x > (rootx + 150)  && position.x < (rootx +200)){
            if (position.y > (rootY + 200) && position.y < (rootY+225)){
                settingsMinsDown.setFillColor(sf::Color(135,206,250));
            }}
        
        //seconds up
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY + 175) && position.y < (rootY+200)){
                settingsSecondsUp.setFillColor(sf::Color(30,144,255));
            }}
        
        //seconds down
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY+200) && position.y < (rootY+225)){
                settingsSecondsDown.setFillColor(sf::Color(135,206,250));
            }}
        //reset
        if (position.x > (rootx + 50)  && position.x < (rootx+200)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsReset.setFillColor(sf::Color(255,144,255));
            }}
        //apply
        if (position.x > (rootx + 300)  && position.x < (rootx + 450)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsApply.setFillColor(sf::Color(255,255,255));
                //gridward.update();
            }}
    }
}
void settingsMenu::draw(sf::RenderWindow &window){
    window.draw(settingsBackground);
    window.draw(settingsExit);
    window.draw(settingsTenFPS);
    window.draw(settingsOneFPS);
    window.draw(settingsFPSText);
    window.draw(settingsFPSTextValTen);
    window.draw(settingsFPSTextValOne);
    window.draw(settingsMinsUp);
    window.draw(settingsMinsDown);
    window.draw(settingsSecondsUp);
    window.draw(settingsSecondsDown);
    window.draw(settingsMinsBox);
    window.draw(settingsSecondsBox);
    window.draw(settingsCollectionText);
    window.draw(settingsMinsText);
    window.draw(settingsSecondsText);
    window.draw(settingsRangeTrue);
    window.draw(settingsRangeHuman);
    window.draw(settingsRangeText);
    window.draw(settingsRangeTextTrue);
    window.draw(settingsRangeTextHuman);
    window.draw(settingsReset);
    window.draw(settingsResetText);
    window.draw(settingsApply);
    window.draw(settingsApplyText);
}

int settingsMenu::exit(void){
    return menuLayer;
}


/*/ -------- topBar Layer --------/*/

topBar::topBar(void){
   
    if (!topBarFont.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    //Rectangle Shape Objects
    background.setSize(sf::Vector2f( 606, 75 ));
    header.setSize(sf::Vector2f(606, 5 ));
    
    background.setFillColor(sf::Color(0, 0, 0,50));
    header.setFillColor(sf::Color(255, 94, 20,150));
                    
    background.setPosition(94, 0);
    header.setPosition(94, 75);
    
    
    //Text Objects
    modeText.setString("Booting");
    titleText.setString("Panasonic Grid-EYE");
    subText.setString("Created by Grant Hilgert and Richard Oman");
    
    modeText.setCharacterSize(30);
    titleText.setCharacterSize(36);
    subText.setCharacterSize(15);
    
    modeText.setFont(topBarFont);
    titleText.setFont(topBarFont);
    subText.setFont(topBarFont);
    
    modeText.setFillColor(sf::Color::White);
    titleText.setFillColor(sf::Color::White);
    subText.setFillColor(sf::Color::Magenta);
    
    modeText.setPosition( 550 , 10);
    titleText.setPosition( 109 , 10);
    subText.setPosition(109,55);
    
}
void topBar::setMode(int newMode){
    mode = newMode;
    update();
}
    void topBar::update(void){
        switch(mode){
            case 0:
                modeText.setFillColor(sf::Color::Green);
                modeText.setString("Stand-By");
                break;
            case 1:
                modeText.setFillColor(sf::Color::Red);
                modeText.setString("Recording");
                break;
            case 2:
                modeText.setFillColor(sf::Color::Yellow);
                modeText.setString("Play Back");
                break;
        }
    };

void topBar::draw(sf::RenderWindow &window){
    window.draw(background);
    window.draw(header);
    window.draw(modeText);
    window.draw(titleText);
    window.draw(subText);
    
}


/*/
backgroundGraphics::backgroundGraphics(void){
    if(!t_background.loadFromFile("texture2.jpg")){
        return EXIT_FAILURE;
    }
    sf::Font backgroundFont;
    if (!backgroundFont.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    backgroundHeader.setSize(sf::Vector2f( 400, 10 ));
    backgroundHeader2.setSize(sf::Vector2f( 400, 10 ));
    backgroundHeader3.setSize(sf::Vector2f(606, 5 ));
    topbarBackground.setSize(sf::Vector2f( 606, 75 ));
    
    text.setString("Thermal Camera");
    text.setCharacterSize(50);
    
    
    recordText.setString("Standy-by");
    recordText.setCharacterSize(25);
    
    background.setTexture(t_background);
    background.setPosition(0,0);
    
    backgroundHeader.setFillColor(sf::Color(0, 255, 0,150));
    backgroundHeader.setPosition(94, 70);
    
    backgroundHeader2.setFillColor(sf::Color(0, 255, 0,150));
    backgroundHeader2.setPosition(488, 75);
    backgroundHeader2.rotate(-60);
    
    backgroundHeader3.setFillColor(sf::Color(255, 94, 20,150));
    backgroundHeader3.setPosition(94, 75);
    
    topbarBackground.setFillColor(sf::Color(0, 0, 0,50));
    topbarBackground.setPosition(94, 0);
    
    text.setFillColor(sf::Color::White);
    text.setPosition( 109 , 10);
    
    recordText.setFillColor(sf::Color::Green);
    recordText.setPosition( 550 , 10);
    
    recordingTimeText.setString("UNDEFINED");
    recordingTimeText.setFont(backgroundFont);
    recordingTimeText.setCharacterSize(20);
    recordingTimeText.setFillColor(sf::Color::White);
    recordingTimeText.setPosition( 560 , 45);
}


    window.draw(background);
    window.draw(topbarBackground);
    window.draw(backgroundHeader3);
    window.draw(text);
    window.draw(recordText);
    window.draw(recordingTimeText);
}

/*/

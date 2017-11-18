      //
     // SFML - Simple and Fast Multimedia Library
     // Copyright (C) 2007-2017 Laurent Gomila (laurent@sfml-dev.org)
     //
     // This software is provided 'as-is', without any express or implied warranty.
  //In no event will the authors be held liable for any damages arising from the use of this software.
    //
     // Permission is granted to anyone to use this software for any purpose,
    // including commercial applications, and to alter it and redistribute it freely,
    // subject to the following restrictions:
    //
    // 1. The origin of this software must not be misrepresented;
    //    you must not claim that you wrote the original software.
    //    If you use this software in a product, an acknowledgment
    //    in the product documentation would be appreciated but is not required.
    //
    // 2. Altered source versions must be plainly marked as such,
    //    and must not be misrepresented as being the original software.
    //
    // 3. This notice may not be removed or altered from any source distribution.
    //
    
    #ifndef SFML_EVENT_HPP
    #define SFML_EVENT_HPP
    
    // Headers
    #include <SFML/Config.hpp>
    #include <SFML/Window/Joystick.hpp>
    #include <SFML/Window/Keyboard.hpp>
    #include <SFML/Window/Mouse.hpp>
    #include <SFML/Window/Sensor.hpp>
    
    
 namespace sf
    {
    class Event
    {
    public:
    
        struct SizeEvent
        {
            unsigned int width;  
            unsigned int height; 
        };
    
        struct KeyEvent
        {
            Keyboard::Key code;    
            bool          alt;     
            bool          control; 
            bool          shift;   
            bool          system;  
        };
    
        struct TextEvent
        {
            Uint32 unicode; 
        };
    
        struct MouseMoveEvent
        {
            int x; 
            int y; 
        };
    
        struct MouseButtonEvent
        {
            Mouse::Button button; 
            int           x;      
            int           y;      
       };
   
       struct MouseWheelEvent
       {
           int delta; 
           int x;     
           int y;     
       };
   
       struct MouseWheelScrollEvent
       {
           Mouse::Wheel wheel; 
           float        delta; 
           int          x;     
           int          y;     
       };
   
       struct JoystickConnectEvent
       {
           unsigned int joystickId; 
       };
   
       struct JoystickMoveEvent
       {
          unsigned int   joystickId; 
           Joystick::Axis axis;       
           float          position;   
       };
   
       struct JoystickButtonEvent
       {
           unsigned int joystickId; 
           unsigned int button;     
       };
   
       struct TouchEvent
       {
           unsigned int finger; 
           int x;               
           int y;               
       };
   
       struct SensorEvent
       {
           Sensor::Type type; 
           float x;           
           float y;           
           float z;           
       };
   
       enum EventType
       {
          Closed,                 
           Resized,                
           LostFocus,              
           GainedFocus,            
           TextEntered,            
           KeyPressed,             
           KeyReleased,            
           MouseWheelMoved,        
           MouseWheelScrolled,     
           MouseButtonPressed,     
           MouseButtonReleased,    
       MouseMoved,             
           MouseEntered,           
           MouseLeft,              
           JoystickButtonPressed,  
  
         JoystickButtonReleased, 
           JoystickMoved,          
           JoystickConnected,      
           JoystickDisconnected,   
           TouchBegan,             
           TouchMoved,             
           TouchEnded,             
           SensorChanged,          
   
           Count                   
       };
   
       // Member data
       EventType type; 
   
       union
       {
           SizeEvent             size;              
           KeyEvent              key;               
           TextEvent             text;              
           MouseMoveEvent        mouseMove;         
           MouseButtonEvent      mouseButton;       
           MouseWheelEvent       mouseWheel;        
           MouseWheelScrollEvent mouseWheelScroll;  
           JoystickMoveEvent     joystickMove;      
          JoystickButtonEvent   joystickButton;    
          JoystickConnectEvent  joystickConnect;   
           TouchEvent            touch;             
           SensorEvent           sensor;            
      };
   };
   
   } // namespace sf
   
   
 #endif // SFML_EVENT_HPP
 
   
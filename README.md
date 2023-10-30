# «SSPS3» or «S-alutem S-mart P-anel based on ESP32 S3»
### About project
The original plan was to design and build my own controller with a 4 inch display to retrofit the house under the smart home category and additionally build a system to charge and power the house from a solar panel. A very ambitious plan, which I started developing back in the summer of 2022 in parallel with my service in the police department of my city. At the time of my termination and employment at Salutem LLC, my development was in the design and assembly phase of a PLC prototype. It is the skills I acquired in the six months prior to my employment that have allowed me to now complete the project, bring value to the company, and tell you about the project. The controller I have developed so far is named «SSPS3» and the acronym is explained in the project title.
«SSPS3» is a fully self-developed, assembled, with self-written software, PLC + HMI project for which the production process has been fine-tuned for company.

### Navigation
1. About me
2. How the project originated
    -  Employment at Salutem LLC, desktop software development
    -  Study of all technological processes of the organization
    -  A bit of initiative
3. Product requirements
    - More about of demand and wishes of the firm
    - Summarizing the TA
4. Study of the subject area
    - Choice between «PLC - HMI» and «PLC + HMI»
    - Controller components
    - Plastic molding process
5. Development process. The present sequence
    - Purchasing devkit kits. Building the prototype. First tests
    - Circuit drawing and PCB layout. PCB orders
    - Assembly of homemade prototypes
    - Modeling of 3D case, cover, holders for the designed PCB
    - Developing its own vertical injection molding machine
    - Bad idea? Purchase and conversion of a vertical press for plastic injection molding
    - Molding plastic parts. First assembly without keyboard
    - Purchasing a CNC router. Conversion to a plotter
    - Development of membrane keyboard production technology
    - First build with keyboard. First test
    - Installation of the release candidate v1 on the equipment. First «field» tests
    - Time cost analysis of PCB assembly. Analysis of PNP machine offers
    - Homemade SMD component PNP machine. Assembly. First test
6. SSPS3 Software
    - Why C++, VS Code, Platformio/Arduino and ESP32
    - «DDD» in action
    - Software solutions. Models and services
        - Storing variable values. Bridge between ram and eeprom
        - Working with I/O
        - Date & time
        - Independent button logic
        - Business logic model - lambda task container
        - Variable storage serivce
        - Physical input and output service
        - Keyboard service based on the button model
        - RTC
        - Interaction with eeprom
        - UI, LVGL
        - UI navigation service
        - Task manager based on interrupts
        - Business logic implementation - main.cpp and part of TaskService.cpp
7. Release
8. Technologies, frameworks, services used
9. Unrealized software solutions available and implemented on hardware
10. To summarize

## 1. About me
I am a desktop fullstack .NET, WPF/Avalonia UI, DB (Microsoft SQL server, My SQL, SQLite) developer. Experience in development of small CRM systems, warehouse accounting programs. In freelancing - development of projects for graduate students in colleges and universities. Outside of commerce I have experience in .net/avalonia based development for Android devices, lending websites, hence basic understanding of javascript. In college, I solved tasks for 2.5 years using C++ while studying.

## 2. How the project originated
#### 2.1. Employment at Salutem LLC, desktop software development
Before I started cooperation with Salutem LLC with the development of software for the needs of employees of production departments (warehouse accounting, preparation of requests for cutting metal and spare parts by specialists) and office (crm system to control the efficiency of managers), I already had experience with this company. In 2020, before the beginning of service in the police unit as an alternative to the mandatory service in the army, I was a system administrator and developer of the site based on WordPress in this company. Already from that moment I was quite familiar with the company's structure from the inside. 
And a word or two about who Salutem are. Salutem LLC - Belarus-based manufacturer of equipment for livestock breeding and dairy producers.

#### 2.2. Study of all technological processes of the organization
Upon returning to the company after a tour of duty and writing several working prototypes of production software at a rapid pace, I began studying process changes and researching needs. 
I found that the company was not satisfied with the PLC selection for the equipment they were producing and they were in search of new solutions among the equipment control systems between «PLC - HMI» and «PLC + HMI».

#### 2.3. A bit of initiative
In June 2023, I gathered all my work and proposed to the company's management to allocate my development time instead of software on the PLC. After studying my proposals and action plan, it was decided to spend all the previously allocated time resources on software development in PLC. Thus began the study of the subject area of PLC development, writing software for it and setting up the production cycle accordingly. 

## 3. Product requirements
#### 3.1. More about of demand and wishes of the firm
The main request from the organization was: load control through 8 relays, reading digital signal on 8 inputs, reading 4x analog signals, at least 4x segment display for 16+ characters , keyboard for 10+ buttons.
I am an enthusiast and could not afford to leave such a potential project unattended and subsequently, at the TA stage, I added my own requirements for the controller, which was gladly accepted by the management.

#### 3.2. Summarizing the TA
As a result, I was faced with the task of realizing a product with the following requirements:
- maximum case size 140 x 140 x 80 mm
- ultraviolet, dust and water resistance (outdoor conditions)
- 24V supplying
- load control via 8 relays
- reading of digital signals for 8 channels (made with galvanic isolation, optocoupler. 3 isolated channels and 5 with common ground)
- 4 analog inputs up to 28v
- digital ips display with 320x480 resolution and 4 inch size
- 16 buttons
- WiFi for OTA
- RF channel for remote control (peripherals under development)
- UHF channel for RFID reading
- GPS/GPRS support with sim card
- RS232 port (optional) for integration with the cloud services of the company OWEN

## 4. Study of the subject area
#### 4.1. Choice between «PLC - HMI» and «PLC + HMI»
The market of controllers is diverse and when we talk about PLC, we mean a small computer, which is isolated from the user and solves the tasks set by the program in relation to the data coming from outside. When we talk about HMI, we mean small panels that only deal with inputs and outputs from the user information. From experience with controllers I can give as an example for "PLC + HMI" the 2 in 1 solution in picture 1 from Unitronics Jazz, and for "PLC - HMI" via modbus the solution in a combination of FX3U and OP320 in picture 2.
I decided to take a more complicated path and develop a 2-in-1 controller, i.e. "PLC + HMI" and try to fit into the smallest possible dimensions.

#### 4.2. Controller components
For the realization of the conceived it was decided to stop on ESP32, because this module has support for wifi and bluetooth, high frequency of the processor, a good framework ESP-IDF and a perfectly remodeled version of ESP-IDF on Arduino Core. For RF channel support it was decided to leave the iron level support between NRF and JDY modules. The SIMCOM module is responsible for GPS/GPRS. For keyboard, relay control and digital signal reading it was decided to use PCF because of their availability in my country. DS3231 real time clock. For data storage is responsible eeprom in soic 8. The display is connected via 8 bit line, on the ILI driver.

#### 4.3. Plastic molding process
PLC enclosure. Not a simple question. To solve this problem I purchased a 3D printer and made a succession of seals from different plastics in order to identify flaws in the rigidity of the design. Another question was whether the printer itself can be used to print enclosures on an industrial scale? Are the layers sintered enough during printing to withstand the loads applied to the equipment manufactured by Salutem. I did not save the results of the test, as they were deplorable. Only a glimpse, in 1 of the videos, did I find an underprinted sample. I came to the conclusion that I will have to buy or build my own plastic injection molding machine. I decided to postpone the plastic issue for the future and started the development.

## 5. Development process. The present sequence
The comments here would not be superfluous in places, but the media content more than covers the topics of the headlines

#### 5.1. Purchasing devkit kits. Building the prototype. First tests
#### 5.2. Circuit drawing and PCB layout. PCB orders
#### 5.3. Assembly of homemade prototypes
#### 5.4. Modeling of 3D case, cover, holders for the designed PCB
#### 5.5. Developing its own vertical injection molding machine
#### 5.6. Bad idea? Expensive? Purchase and conversion of a vertical press for plastic injection molding
#### 5.7. Molding plastic parts. First assembly without keyboard
#### 5.8. Purchasing a CNC router. Conversion to a plotter
#### 5.9. Development of membrane keyboard production technology
#### 5.10. First build with keyboard. First test
#### 5.11. Installation of the release candidate v1 on the equipment. First «field» tests
#### 5.12. Time cost analysis of PCB assembly. Analysis of PNP machine offers
#### 5.13. Homemade SMD component PNP machine. Assembly. First test

## 6. SSPS3 Software
#### 6.1. Why C++, VS Code, Platformio/Arduino and ESP32
When it comes to microcontroller development, I strive for higher performance and flexible work with system resources, which C++ can provide, but definitely not Python. 
VS Code - because I had previous experience of working with it during the development of landing pages and initially I liked the editor as a derivative of Visual Studio. Arduino Core and Platformio - very fast launch of projects and good toolchain with support of working with libraries, firmware and debugging.

#### 6.2. «DDD» in action
I had a deadline in front of me and I realized that planned a huge project for developing it from 0 to release, and 4 months is not enough. That's why I decided to develop in a modular and «multi-layer» way, i.e. according to the «DDD» principle. This allowed me to leave the «lower levels» of code independent, for porting, adding features and debugging in the future.
Going to the software folder you will find the division of logic according to «DDD» from Domain to Application layer.

## 7. Release
In September 2023, the software for one of the series of manufactured equipment was fully completed. The PLC was flashed and successfully tested. October was allocated for writing documentation for the subsequent delivery of manufactured equipment with the new controller. As feedback is received, the reports in this readme will be updated.

## 8. Technologies, frameworks, services used
| Stage | Applied |
| ------ | ------ |
| IDE & toolchain | VS Code, Platformio |
| Backend | C++, Arduino Core, DDD pattern |
| Frontend | LVGL, LovyanGFX |
| PCBs design | Easy EDA, Inkscape |
| 3D models | Solidworks |
| External design | Adobe Photoshop & Illustrator |
| CNC assembly | Marlin for Ramps, OpenPNP, Pronterface |
| PCB production | JLCPCB, PCB way |

## 9. Unrealized features in current software version
- RF module control via SPI is supported at the hardware level, but not implemented by software
- Work with SIMCOM (GPS, GPRS) is supported by hardware, but not implemented by software
- Reading of RFID by connecting external antenna with the module is realized, works over UART, but not implemented in software
- RS232 bridge not implemented at the hardware level (not enough space on the PCB for MAX chip). In development, PCB redesign
- ESP32 supports wifi, but OTA firmware update is not implemented

All of the above features are in development

## 10. To summarize
It was a rather difficult project, thanks to which I learned to work with various CNC machines, learned to assemble the CNC machines themselves, understood the technological process of production of all PLC components (board, keyboard, housing), mastered the skills of firmware development for microcontrollers, and also thanks to homemade CNC installations debugged the full cycle of PLC assembly/production in semi-automatic mode, where 1 operator is enough for the whole cycle.

Thanks for your attention!

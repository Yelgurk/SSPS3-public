# «SSPS3» or «S-alutem S-mart P-anel based on ESP32 S3»
### About project
The original plan was to design and build my own controller with a 4 inch display to retrofit the house under the smart home category and additionally build a system to charge and power the house from a solar panel. A very ambitious plan, which I started developing back in the summer of 2022 in parallel with my service in the police department of my city. At the time of my termination and employment at [Salutem LLC](https://salutem.by/), my development was in the design and assembly phase of a PLC prototype. It is the skills I acquired in the six months prior to my employment that have allowed me to now complete the project, bring value to the company, and tell you about the project. The controller I have developed so far is named «SSPS3» and the acronym is explained in the project title.
«SSPS3» is a fully self-developed, assembled, with self-written software, PLC + HMI project for which the production process has been fine-tuned for company.

### Navigation
1. [ About me ](#p1)
2. How the project originated
    -  [ Employment at Salutem LLC, desktop software development ](#p21)
    -  [ Study of all technological processes of the organization ](#p22)
    -  [ A bit of initiative ](#p23)
3. Product requirements
    - [ More about of demand and wishes of the firm ](#p31)
    - [ Summarizing the TA ](#p32)
4. Study of the subject area
    - [ Choice between «PLC - HMI» and «PLC + HMI» ](#p41)
    - [ Controller components ](#p42)
    - [ Plastic molding process ](#p43)
5. Development process. The present sequence
    - [ Purchasing devkit kits. Building the prototype. First tests ](#p51)
    - [ Circuit drawing and PCB layout. PCB orders ](#p52)
    - [ Assembly of homemade prototypes ](#p53)
    - [ Modeling of 3D case, cover, holders for the designed PCB ](#p54)
    - [ Developing its own vertical injection molding machine ](#p55)
    - [ Bad idea? Purchase and conversion of a vertical press for plastic injection molding ](#p56)
    - [ Molding plastic parts. First assembly without keyboard ](#p57)
    - [ Purchasing a CNC router. Conversion to a plotter ](#p58)
    - [ Development of membrane keyboard production technology ](#p59)
    - [ First build with keyboard. First test ](#p510)
    - [ Milestones to release candidate v1 on the equipment. First «field» tests ](#p511)
    - [ Time cost analysis of PCB assembly ](#p512)
    - [ Homemade SMD component PNP machine. Assembly. First test ](#p513)
6. SSPS3 Software
    - [ Why C++, VS Code, Platformio/Arduino and ESP32 ](#p61)
    - [ «DDD» in action ](#p62)
    - Software solutions. Models and services (part of the code for demo)
        - Storing variable values. Bridge between ram and eeprom ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Domain/include/objectUnitModel.hpp) / [cpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Domain/src/objectUnitModel.cpp))
        - Working with I/O ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Domain/include/controlUnitModel.hpp))
        - Date & time ([dt_base.hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Domain/include/dateTimeBase.hpp) / [dt_model.cpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Domain/include/dateTimeModel.hpp))
        - Independent button logic ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Domain/include/keyModel.hpp) / [cpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Domain/src/keyModel.cpp))
        - Business logic model - lambda task container ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Domain/include/taskModel.hpp))
        - Variable storage serivce ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Core/include/DBService.hpp))
        - Physical input and output service ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Core/include/IOService.hpp) / [cpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Core/src/IOService.cpp))
        - Keyboard service based on the button model ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Core/include/KBService.hpp) / [cpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Core/src/KBService.cpp))
        - Interaction with eeprom ([hpp](https://github.com/Yelgurk/SSPS3-public/tree/main/Software/SSPS3_DDD_Infrastructure/include) / [cpp](https://github.com/Yelgurk/SSPS3-public/tree/main/Software/SSPS3_DDD_Infrastructure/src))
        - UI, LVGL ([ui_service.hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/include/UIService.hpp) / one_of_ui_element_lvgl([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/include/el_task_c.hpp)/[cpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/src/el_task_c.cpp)) / [ui_res_dependency.hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/include/lv_resources.hpp))
        - UI navigation service ([model.hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/include/NaviModel.hpp) / [navi_service.hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/include/NaviService.hpp))
        - Task manager based on interrupts ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/include/TaskService.hpp) / [cpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/src/TaskService.cpp))
        - Controller init ([hpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/include/main.hpp) / [cpp](https://github.com/Yelgurk/SSPS3-public/blob/main/Software/SSPS3_DDD_Application/src/main.cpp))
7. [ Release ](#p7)
8. [ Technologies, frameworks, services used ](#p8)
9. [ Unrealized software solutions available and implemented on hardware ](#p9)
10. [ To summarize ](#p10)

<a name="p1"></a>
## 1. About me
I am a desktop fullstack .NET, WPF/Avalonia UI, DB (Microsoft SQL server, My SQL, SQLite) developer. Experience in development of small CRM systems, warehouse accounting programs. In freelancing - development of projects for graduate students in colleges and universities. Outside of commerce I have experience in .net/avalonia based development for Android devices, lending websites, hence basic understanding of javascript. In college, I solved tasks for 2.5 years using C++ while studying.

## 2. How the project originated
<a name="p21"></a>
#### 2.1. Employment at [Salutem LLC](https://salutem.by/), desktop software development
Before I started cooperation with [Salutem LLC](https://salutem.by/) with the development of software for the needs of employees of production departments (warehouse accounting, preparation of requests for cutting metal and spare parts by specialists) and office (crm system to control the efficiency of managers), I already had experience with this company. In 2020, before the beginning of service in the police unit as an alternative to the mandatory service in the army, I was a system administrator and developer of the site based on WordPress in this company. Already from that moment I was quite familiar with the company's structure from the inside. 
And a word or two about who Salutem are. [Salutem LLC](https://salutem.by/) - Belarus-based manufacturer of equipment for livestock breeding and dairy producers.
In what follows we will talk about the development of a controller for this company's equipment, one of which is shown below
<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/salutem_llc_dairy_taxi_old.jpg" width="80%">
</p>

<a name="p22"></a>
#### 2.2. Study of all technological processes of the organization
Upon returning to the company after a tour of duty and writing several working prototypes of production software at a rapid pace, I began studying process changes and researching needs. 
I found that the company was not satisfied with the PLC selection for the equipment they were producing and they were in search of new solutions among the equipment control systems between «PLC - HMI» and «PLC + HMI».

<a name="p23"></a>
#### 2.3. A bit of initiative
In June 2023, I gathered all my work and proposed to the company's management to allocate my development time instead of software on the PLC. After studying my proposals and action plan, it was decided to spend all the previously allocated time resources on software development in PLC. Thus began the study of the subject area of PLC development, writing software for it and setting up the production cycle accordingly. 

## 3. Product requirements
<a name="p31"></a>
#### 3.1. More about of demand and wishes of the firm
The main request from the organization was: load control through 8 relays, reading digital signal on 8 inputs, reading 4x analog signals, at least 4x segment display for 16+ characters , keyboard for 10+ buttons.
I am an enthusiast and could not afford to leave such a potential project unattended and subsequently, at the TA stage, I added my own requirements for the controller, which was gladly accepted by the management.

<a name="p32"></a>
#### 3.2. Summarizing the TA
As a result, I was faced with the task of realizing a product with the following requirements:
- maximum case size 140 x 140 x 80 mm
- ultraviolet, dust and water resistance (outdoor conditions)
- 24V supplying
- load control via 8 relays
- reading of digital signals for 8 channels
- 4 analog inputs up to 28v
- 16 symbols x 4 lines display 
- 16 buttons
- WiFi for OTA
- RF channel for remote control (peripherals under development)
- UHF channel for RFID reading
- GPS/GPRS support with sim card
- RS232 port (optional) for integration with the cloud services of the company OWEN

## 4. Study of the subject area
<a name="p41"></a>
#### 4.1. Choice between «PLC - HMI» and «PLC + HMI»
The market of controllers is diverse and when we talk about PLC, we mean a small computer, which is isolated from the user and solves the tasks set by the program in relation to the data coming from outside. When we talk about HMI, we mean small panels that only deal with inputs and outputs from the user information. From experience with controllers I can give as an example for "PLC + HMI" the 2 in 1 solution in first picture like Unitronics Jazz, and for "PLC - HMI" via modbus the solution in a combination of FX3U and OP320 ([PLC - master and HMI - slave, old and unused project](https://github.com/Yelgurk/fx3u-m-op320-s-rs232)) in second picture.
I decided to take a more complicated path and develop a 2-in-1 controller, i.e. "PLC + HMI" and try to fit into the smallest possible dimensions.

<table>
  <tr>
    <th width="40%"><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/Unitronics_jazz.jpg"></th>
    <th width="40%"><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/fx3u_and_op320.jpg"></th>
  </tr>
</table>

<a name="p42"></a>
#### 4.2. Controller components
For the realization of the conceived it was decided to stop on ESP32, because this module has support for wifi and bluetooth, high frequency of the processor, a good framework ESP-IDF and a perfectly remodeled version of ESP-IDF on Arduino Core. For RF channel support it was decided to leave the iron level support between NRF and JDY modules. The SIMCOM module is responsible for GPS/GPRS. For keyboard, relay control and digital signal reading it was decided to use PCF because of their availability in my country. DS3231 real time clock. For data storage is responsible eeprom in soic 8. The display is connected via 8 bit line, on the ILI driver.

<a name="p43"></a>
#### 4.3. Plastic molding process
PLC enclosure. Not a simple question. To solve this problem I purchased a 3D printer and made a succession of seals from different plastics in order to identify flaws in the rigidity of the design. Another question was whether the printer itself can be used to print enclosures on an industrial scale? Are the layers sintered enough during printing to withstand the loads applied to the equipment manufactured by Salutem. I did not save the results of the test, as they were deplorable. Only a glimpse, in 1 of the videos, did I find an underprinted sample. I came to the conclusion that I will have to buy or build my own plastic injection molding machine. I decided to postpone the plastic issue for the future and started the development.

## 5. Development process. The present sequence
The comments here would not be superfluous in places, but the media content more than covers the topics of the headlines
<a name="p51"></a>
#### 5.1. Purchasing devkit kits. Building the prototype. First tests

<p align="center">
  <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/devkit_based_proto.jpg" height="450">
</p>

<a name="p52"></a>
#### 5.2. Circuit drawing and PCB layout. PCB orders
<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/rc_pcb_circuit.png" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/rc_pcb_preview_4layer.jpg" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/rc_pcb_preview_front.jpg" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/rc_pcb_preview_back.jpg" width="40%">
</p>

<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/pcb_milestones_1.jpg" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/pcb_milestones_2.jpg" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/pcb_milestones_3.jpg" width="40%">
</p>

<a name="p53"></a>
#### 5.3. Assembly of homemade prototypes
Old designs
<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/one_of_proto_1.jpg" height="350">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/one_of_proto_2.jpg" height="350">
</p>

Release candidate version
<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/rc_pcb_assembly_1.jpg" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20assembly/rc_pcb_assembly_2.jpg" width="40%">
</p>

<a name="p54"></a>
#### 5.4. Modeling of 3D case, cover, holders for the designed PCB
<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20case/plc_salutem_case_main.png" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20case/plc_salutem_case_main_rotated.png" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20case/plc_salutem_case_holder.png" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20case/plc_salutem_case_cover.png" width="40%">
</p>

<a name="p55"></a>
#### 5.5. Developing its own vertical injection molding machine
<table align="center">
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=kosuv8pDtM8"><img src="https://img.youtube.com/vi/kosuv8pDtM8/0.jpg" alt="YouTube video" width="80%"></a>
        </p>
    </th>
  </tr>
</table>

<a name="p56"></a>
#### 5.6. Bad idea? Expensive? Purchase and conversion of a vertical press for plastic injection molding
<table>
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=d58FZt9dFoM"><img src="https://img.youtube.com/vi/d58FZt9dFoM/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=hRRuVWcUvr0"><img src="https://img.youtube.com/vi/hRRuVWcUvr0/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=vWRh88ctS2Y"><img src="https://img.youtube.com/vi/vWRh88ctS2Y/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=EJf8Ut2OAh0"><img src="https://img.youtube.com/vi/EJf8Ut2OAh0/0.jpg" alt="YouTube video" width="40%"></a>
        </p>
    </th>
  </tr>
</table>

<a name="p57"></a>
#### 5.7. Molding plastic parts. First assembly without keyboard
<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20case/VIMM_success.jpg" width="80%">
</p>


<a name="p58"></a>
#### 5.8. Purchasing a CNC router. Conversion to a plotter
<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/DIY%20plotter/blade_holder_case.png" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/DIY%20plotter/blade_holder_bracket.png" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/DIY%20plotter/blade_pusher.png" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/DIY%20plotter/blade_assembly.PNG" width="40%">
</p>

<table>
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=GK3WdmIWEUw"><img src="https://img.youtube.com/vi/GK3WdmIWEUw/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=rLXt5yHCtIw"><img src="https://img.youtube.com/vi/rLXt5yHCtIw/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=Aa3JUrb-wec"><img src="https://img.youtube.com/vi/Aa3JUrb-wec/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=s9LD8PRHcKs"><img src="https://img.youtube.com/vi/s9LD8PRHcKs/0.jpg" alt="YouTube video" width="40%"></a>
        </p>
    </th>
  </tr>
</table>

<a name="p59"></a>
#### 5.9. Development of membrane keyboard production technology
<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/PLC%20membrane%20keyboard/keyboard_pcb.png" width="%80">
</p>

<table>
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=QHYeXaWpzjc"><img src="https://img.youtube.com/vi/QHYeXaWpzjc/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=NsPw-UJum3g"><img src="https://img.youtube.com/vi/NsPw-UJum3g/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=gBm4K6k2e2Q"><img src="https://img.youtube.com/vi/gBm4K6k2e2Q/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=8YzL3hZF7nk"><img src="https://img.youtube.com/vi/8YzL3hZF7nk/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=x0SnF8Yu7dI"><img src="https://img.youtube.com/vi/x0SnF8Yu7dI/0.jpg" alt="YouTube video" width="40%"></a>
        </p>
    </th>
  </tr>
</table>

<a name="p510"></a>
#### 5.10. First build with keyboard. First test
<table align="center">
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=ze1laU3m5XU"><img src="https://img.youtube.com/vi/ze1laU3m5XU/0.jpg" alt="YouTube video" width="80%"></a>
        </p>
    </th>
  </tr>
</table>

<a name="p511"></a>
#### 5.11. Milestones from first prototypes to release candidate on the equipment. First «field» tests
<table>
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=SWYs3RbE2wU"><img src="https://img.youtube.com/vi/SWYs3RbE2wU/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=Redw7KNXDMc"><img src="https://img.youtube.com/vi/Redw7KNXDMc/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=7FnvGc54QIc"><img src="https://img.youtube.com/vi/7FnvGc54QIc/0.jpg" alt="YouTube video" width="40%"></a>
        </p>
    </th>
  </tr>
</table>

<p align="center">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Engineering%20sample%20and%20final/ssps_es_4.jpg" width="40%">
    <img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Engineering%20sample%20and%20final/ssps_es_5.jpg" width="40%">
</p>

<table>
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=B1pWBA5PGBo"><img src="https://img.youtube.com/vi/B1pWBA5PGBo/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=FIn7ylNEf58"><img src="https://img.youtube.com/vi/FIn7ylNEf58/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=Lc7RaMw1E1M"><img src="https://img.youtube.com/vi/Lc7RaMw1E1M/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=3DTh6nJJigI"><img src="https://img.youtube.com/vi/3DTh6nJJigI/0.jpg" alt="YouTube video" width="40%"></a>
          <a href="https://www.youtube.com/watch?v=vj34nDyH62Y"><img src="https://img.youtube.com/vi/vj34nDyH62Y/0.jpg" alt="YouTube video" width="40%"></a>
        </p>
    </th>
  </tr>
</table>

<a name="p512"></a>
#### 5.12. Time cost analysis of PCB assembly
The PCB consists of 180 SMD components, some form factor 0805 and very dense arrangement on PCB. Together with the application of solder paste, the whole assembly process takes up to one and a half hours of time to produce a PLC board. For this reason it was decided to assemble a homemade pick and place machine. According to calculations, the preliminary productivity of the PNP is expected to be around 800 components per hour. Such probable productivity of the machine will allow to assemble up to 4 boards within an hour.

<a name="p513"></a>
#### 5.13. Homemade SMD component PNP machine. Assembly. First test
<table align="center">
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=S3Pohj1ywoo"><img src="https://img.youtube.com/vi/S3Pohj1ywoo/0.jpg" alt="YouTube video" width="80%"></a>
        </p>
    </th>
  </tr>
</table>

<p align="center">
    <img src="https://github.com/Yelgurk/SSPS3-public/blob/main/Content/DIY%20PNP/diy_pnp_electronics.jpg" width="40%">
</p>

<p align="center">
    <img src="https://github.com/Yelgurk/SSPS3-public/blob/main/Content/DIY%20PNP/diy_pnp_parts_printed.jpg" width="40%">
    <img src="https://github.com/Yelgurk/SSPS3-public/blob/main/Content/DIY%20PNP/diy_pnp_assembly_1.jpg" width="40%">
    <img src="https://github.com/Yelgurk/SSPS3-public/blob/main/Content/DIY%20PNP/diy_pnp_assembly_2.jpg" width="40%">
    <img src="https://github.com/Yelgurk/SSPS3-public/blob/main/Content/DIY%20PNP/diy_pnp_assembly_3.jpg" width="40%">
</p>

<table align="center">
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=JaPltSFoI6c"><img src="https://img.youtube.com/vi/JaPltSFoI6c/0.jpg" alt="YouTube video" width="80%"></a>
        </p>
    </th>
  </tr>
</table>

## 6. SSPS3 Software
<a name="p61"></a>
#### 6.1. Why C++, VS Code, Platformio/Arduino and ESP32
When it comes to microcontroller development, I strive for higher performance and flexible work with system resources, which C++ can provide, but definitely not Python. 
VS Code - because I had previous experience of working with it during the development of landing pages and initially I liked the editor as a derivative of Visual Studio. Arduino Core and Platformio - very fast launch of projects and good toolchain with support of working with libraries, firmware and debugging.

<a name="p62"></a>
#### 6.2. «DDD» in action
I had a deadline in front of me and I realized that planned a huge project for developing it from 0 to release, and 4 months is not enough. That's why I decided to develop in a modular and «multi-layer» way, i.e. according to the «DDD» principle. This allowed me to leave the «lower levels» of code independent, for porting, adding features and debugging in the future.
Going to the software folder you will find the division of logic according to «DDD» from Domain to Application layer.

<a name="p7"></a>
## 7. Release
In September 2023, the software for one of the series of manufactured equipment was fully completed. The PLC was flashed and successfully tested. October was allocated for writing documentation for the subsequent delivery of manufactured equipment with the new controller. As feedback is received, the reports in this readme will be updated.

<table align="center">
  <tr>
    <th><img src="https://raw.githubusercontent.com/Yelgurk/SSPS3-public/main/Content/Extra/youtube_com_icon.png" height="30"></th>
  </tr>
  <tr>
    <th>
        <p align="center">
          <a href="https://www.youtube.com/watch?v=sU9fEazrGZo"><img src="https://img.youtube.com/vi/sU9fEazrGZo/0.jpg" alt="YouTube video" width="80%"></a>
        </p>
    </th>
  </tr>
</table>

Final PLC+HMI parameters:
- case size 130 x 110 x 38 mm
- ultraviolet, dust and water resistance (will be clear in the near future in practice.)
- 12-36V supplying
- load control via 8 relays
- reading of digital signals for 8 channels (made with galvanic isolation, optocoupler. 3 isolated channels and 5 with common ground)
- 4 analog inputs up to 28V
- digital ips display with 320x480 resolution and 4 inch size
- 16 buttons
- WiFi & Bluetooth built-in ESP32
- NRF and JDY module support
- connector for UHF antenna with build-in module
- GPS/GPRS SIMCOM support with sim card slot
- an additional i2c line has been taken out for the development of the extra shield

<a name="p8"></a>
## 8. Technologies, frameworks, services used
| Stage | Applied |
| ------ | ------ |
| IDE & toolchain | VS Code, Platformio |
| Backend | C++, Arduino Core, DDD pattern |
| Frontend | LVGL, LovyanGFX |
| PCBs design | Easy EDA, Inkscape |
| 3D models | Solidworks, Cura |
| External design | Adobe Photoshop & Illustrator |
| CNC assembly | Marlin for Ramps, OpenPNP, Pronterface |
| PCB production | JLCPCB, PCB way |

<a name="p9"></a>
## 9. Unrealized features in current software version
- RF module control via SPI is supported at the hardware level, but not implemented by software
- Work with SIMCOM (GPS, GPRS) is supported by hardware, but not implemented by software
- Reading of RFID by connecting external antenna with the module is realized, works over UART, but not implemented in software
- RS232 bridge not implemented at the hardware level (not enough space on the PCB for MAX chip). In development, PCB redesign
- ESP32 supports wifi, but OTA firmware update is not implemented

All of the above features are in development

<a name="p10"></a>
## 10. To summarize
It was a rather difficult project, thanks to which I learned to work with various CNC machines, learned to assemble the CNC machines themselves, understood the technological process of production of all PLC components (board, keyboard, housing), mastered the skills of firmware development for microcontrollers, and also thanks to homemade CNC installations debugged the full cycle of PLC assembly/production in semi-automatic mode, where 1 operator is enough for the whole cycle.

Thanks for your attention!

[dill]: <https://github.com/joemccann/dillinger>
[git-repo-url]: <https://github.com/joemccann/dillinger.git>
[john gruber]: <http://daringfireball.net>
[df1]: <http://daringfireball.net/projects/markdown/>

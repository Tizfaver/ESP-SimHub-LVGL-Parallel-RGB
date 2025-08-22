# SimHub Firmware for CrowPanel ESP Terminal  
**Device:** [ESP32 3.5" 480×320 Parallel RGB Touch Display](https://www.elecrow.com/esp-terminal-with-esp32-3-5-inch-parallel-480x320-tft-capacitive-touch-display-rgb-by-chip-ili9488.html)  

This project is based on the excellent work of [@eCrowneEng](https://github.com/eCrowneEng/ESP-SimHub).  

I’ve trimmed it down to the essentials required to connect this board to **SimHub** (in my case version 9.9.5) and i merged the essential files and configuration from the example project from the Documentation of this board. You will find three SHCustomProtocol.h files: one of these is completly empty (**SHCustomProtocol_empty.h**). The other has already some configuration to just start the Display driver (**SHCustomProtocol.h**). Meanwhile the last file has both Driver and Touch drivers (not tested, just copied and modified from the example project) (**SHCustomProtocol_display_and_touch.h**). 
If you don't need the Touch, you could also delete the FT6236.cpp and FT6236.h files.

For other examples on how to use this board, you can download the PlatformIO examples from the Wiki of the board: [Wiki](https://www.elecrow.com/wiki/esp-terminal-with-35inch-rgb-capacitive-touch-display.html)

Just to be clear, the SKU (from the official online store) of the board is: DLC35010R.

## Background  
It took me several hours (and plenty of frustration) to get this board working with SimHub.  
The issue turned out to be a misconfigured board definition. After a lot of trial and error, I found a working configuration online. You’ll find this configuration included in the **`boards`** folder of the project.  

## Main Code  
As with the original project, the primary logic will be found in the SHCustomProtocol.h file.  

## How To Use This
You will need to download this repo, open VS Code (you obviously need PlatformIO extension installed) and open the project with PlatformIO, from the PIO HOME.
When opened, it will automatically install the libreries. Once the libreries are done installing YOU MUST move the **lv_conf.h** file from the root of the project to the folder: **.pio\libdeps\esp32**.
So now you will have the project looking like that:
<img width="274" height="475" alt="image" src="https://github.com/user-attachments/assets/8cc73b08-09d3-4838-a9e6-cd7b9f845819" />

Try and compile and it will compile:
<img width="1259" height="211" alt="image" src="https://github.com/user-attachments/assets/9e307785-0ee0-42f5-9976-f3000f025ded" />

**Happy rallying!**

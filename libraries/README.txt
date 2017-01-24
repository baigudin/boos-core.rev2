Built libraries
---------------

 Common kernel libraries:

 - boos.core.ti.am18x.coff.ccstudio.debug.lib
    Texas Instruments AM18x ARM Microprocessors family library
    Build Options of ARM Optimizing C/C++ Compiler v4.6.6
    cl470.exe -g -me -mv5e --abi=ti_arm9_abi --code_state=32 --coff

 - boos.core.ti.am18x.coff.ccstudio.release.lib
    Texas Instruments AM18x ARM Microprocessors family library
    Build Options of ARM Optimizing C/C++ Compiler v4.6.6
    cl470.exe -o3 -me -mv5e --abi=ti_arm9_abi --code_state=32 --coff

 - boos.core.ti.tms320c64x.coff.ccstudio.debug.lib
    Texas Instruments TMS320C64x Digital Signal Processors family library
    Build Options of TMS320C6000 C/C++ Optimizing Compiler v7.2.0:
    cl6x.exe -g -mv6400 --mem_model:data=far --abi=coffabi
    
 - boos.core.ti.tms320c64x.coff.ccstudio.release.lib
    Texas Instruments TMS320C64x Digital Signal Processors family library
    Build Options of TMS320C6000 C/C++ Optimizing Compiler v7.2.0:
    cl6x.exe -o3 -mv6400 --mem_model:data=far --abi=coffabi
    
 Target kernel libraries:
    
 - boos.target.ti.am18x.coff.ccstudio.debug.lib
    Texas Instruments AM18x ARM Microprocessors family library
    Build Options of ARM Optimizing C/C++ Compiler v4.6.6
    cl470.exe -g -me -mv5e --abi=ti_arm9_abi --code_state=32 --coff

 - boos.target.ti.am18x.coff.ccstudio.release.lib
    Texas Instruments AM18x ARM Microprocessors family library
    Build Options of ARM Optimizing C/C++ Compiler v4.6.6
    cl470.exe -o3 -me -mv5e --abi=ti_arm9_abi --code_state=32 --coff    
    
 - boos.target.ti.tms320c64x.coff.ccstudio.debug.lib
    Texas Instruments TMS320C64x Digital Signal Processors family library
    Build Options of TMS320C6000 C/C++ Optimizing Compiler v7.2.0:
    cl6x.exe -g -mv6400 --mem_model:data=far --abi=coffabi    
    
 - boos.target.ti.tms320c64x.coff.ccstudio.release.lib
    Texas Instruments TMS320C64x Digital Signal Processors family library
    Build Options of TMS320C6000 C/C++ Optimizing Compiler v7.2.0:
    cl6x.exe -o3 -mv6400 --mem_model:data=far --abi=coffabi 
    


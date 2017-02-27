/**
 * TI TMS320F2833x/F2823x DSC GPIO Registers.
 *
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_TARGET_REGISRES_GPIO_HPP_
#define BOOS_TARGET_REGISRES_GPIO_HPP_

#include "boos.Types.hpp"

namespace target
{
  namespace registers
  {
    struct Gpio
    {
    
    public:
    
      /**
       * Memory mapped addresses.
       */    
      static const uint32 ADDRESS = 0x00006F80;
    
      /** 
       * Constructor.
       */  
      Gpio() :
        gpactrl      (),
        gpaqsel1     (),
        gpaqsel2     (),
        gpamux1      (),
        gpamux2      (),
        gpadir       (),
        gpapud       (),
        gpbctrl      (),
        gpbqsel1     (),
        gpbqsel2     (),
        gpbmux1      (),
        gpbmux2      (),
        gpbdir       (),
        gpbpud       (),
        gpcmux1      (),
        gpcmux2      (),
        gpcdir       (),
        gpcpud       (),
        gpadat       (),
        gpaset       (),
        gpaclear     (),
        gpatoggle    (),
        gpbdat       (),
        gpbset       (),
        gpbclear     (),
        gpbtoggle    (),
        gpcdat       (),
        gpcset       (),
        gpcclear     (),
        gpctoggle    (),
        gpioxint1sel (),
        gpioxint2sel (),
        gpioxnmisel  (),
        gpioxint3sel (),
        gpioxint4sel (),
        gpioxint5sel (),
        gpioxint6sel (),
        gpioint7sel  (),
        gpiolpmsel   (){
      }
      
      
      /** 
       * Destructor.
       */    
     ~Gpio(){}    
     
      /**
       * Operator new.
       *
       * @param size unused.
       * @param ptr  address of memory.
       * @return address of memory.
       */     
      void* operator new(size_t, uint32 ptr)
      {
        return reinterpret_cast<void*>(ptr);
      }
    
      // EALLOW PROTECTED
      
      /**
       * GPIO A Control Register (GPIO0 to 31).
       */
      union Gpactrl
      {
        Gpactrl(){}
        Gpactrl(uint32 v){val = v;}          
       ~Gpactrl(){}    
       
        uint32 val;
        struct Val
        {
          uint32 qualprd0 : 8;
          uint32 qualprd1 : 8;
          uint32 qualprd2 : 8;
          uint32 qualprd3 : 8;
        } bit;
      } gpactrl;
      
      /**
       * GPIO A Qualifier Select 1 Register (GPIO0 to 15).
       */
      union Gpaqsel1
      {
        Gpaqsel1(){}
        Gpaqsel1(uint32 v){val = v;}          
       ~Gpaqsel1(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 2;
          uint32 gpio1  : 2;
          uint32 gpio2  : 2;
          uint32 gpio3  : 2;
          uint32 gpio4  : 2;
          uint32 gpio5  : 2;
          uint32 gpio6  : 2;
          uint32 gpio7  : 2;
          uint32 gpio8  : 2;
          uint32 gpio9  : 2;
          uint32 gpio10 : 2; 
          uint32 gpio11 : 2; 
          uint32 gpio12 : 2; 
          uint32 gpio13 : 2; 
          uint32 gpio14 : 2; 
          uint32 gpio15 : 2; 
        } bit;
      } gpaqsel1;
      
      /**
       * GPIO A Qualifier Select 2 Register (GPIO16 to 31).
       */
      union Gpaqsel2
      {
        Gpaqsel2(){}
        Gpaqsel2(uint32 v){val = v;}          
       ~Gpaqsel2(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio16 : 2;
          uint32 gpio17 : 2;
          uint32 gpio18 : 2;
          uint32 gpio19 : 2;
          uint32 gpio20 : 2;
          uint32 gpio21 : 2;
          uint32 gpio22 : 2;
          uint32 gpio23 : 2;
          uint32 gpio24 : 2;
          uint32 gpio25 : 2;
          uint32 gpio26 : 2; 
          uint32 gpio27 : 2; 
          uint32 gpio28 : 2; 
          uint32 gpio29 : 2; 
          uint32 gpio30 : 2; 
          uint32 gpio31 : 2; 
        } bit;
      } gpaqsel2;
      
      /**
       * GPIO A MUX 1 Register (GPIO0 to 15).
       */
      union Gpamux1
      {
        Gpamux1(){}
        Gpamux1(uint32 v){val = v;}          
       ~Gpamux1(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 2;
          uint32 gpio1  : 2;
          uint32 gpio2  : 2;
          uint32 gpio3  : 2;
          uint32 gpio4  : 2;
          uint32 gpio5  : 2;
          uint32 gpio6  : 2;
          uint32 gpio7  : 2;
          uint32 gpio8  : 2;
          uint32 gpio9  : 2;
          uint32 gpio10 : 2; 
          uint32 gpio11 : 2; 
          uint32 gpio12 : 2; 
          uint32 gpio13 : 2; 
          uint32 gpio14 : 2; 
          uint32 gpio15 : 2;
        } bit;
      } gpamux1;
      
      /**
       * GPIO A MUX 2 Register (GPIO16 to 31).
       */
      union Gpamux2
      {
        Gpamux2(){}
        Gpamux2(uint32 v){val = v;}          
       ~Gpamux2(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio16 : 2;
          uint32 gpio17 : 2;
          uint32 gpio18 : 2;
          uint32 gpio19 : 2;
          uint32 gpio20 : 2;
          uint32 gpio21 : 2;
          uint32 gpio22 : 2;
          uint32 gpio23 : 2;
          uint32 gpio24 : 2;
          uint32 gpio25 : 2;
          uint32 gpio26 : 2;
          uint32 gpio27 : 2;
          uint32 gpio28 : 2;
          uint32 gpio29 : 2;
          uint32 gpio30 : 2;
          uint32 gpio31 : 2;
        } bit;
      } gpamux2;
      
      /**
       * GPIO A Direction Register (GPIO0 to 31).
       */
      union Gpadir
      {
        Gpadir(){}
        Gpadir(uint32 v){val = v;}          
       ~Gpadir(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 1;
          uint32 gpio1  : 1;
          uint32 gpio2  : 1;
          uint32 gpio3  : 1;
          uint32 gpio4  : 1;
          uint32 gpio5  : 1;
          uint32 gpio6  : 1;
          uint32 gpio7  : 1;
          uint32 gpio8  : 1;
          uint32 gpio9  : 1;
          uint32 gpio10 : 1; 
          uint32 gpio11 : 1; 
          uint32 gpio12 : 1; 
          uint32 gpio13 : 1; 
          uint32 gpio14 : 1; 
          uint32 gpio15 : 1;
          uint32 gpio16 : 1;
          uint32 gpio17 : 1;
          uint32 gpio18 : 1;
          uint32 gpio19 : 1;
          uint32 gpio20 : 1;
          uint32 gpio21 : 1;
          uint32 gpio22 : 1;
          uint32 gpio23 : 1;
          uint32 gpio24 : 1;
          uint32 gpio25 : 1;
          uint32 gpio26 : 1;
          uint32 gpio27 : 1;
          uint32 gpio28 : 1;
          uint32 gpio29 : 1;
          uint32 gpio30 : 1;
          uint32 gpio31 : 1;      
        } bit;
      } gpadir;
      
      /**
       * GPIO A Pullup Disable Register (GPIO0 to 31)  .
       */
      union Gpapud
      {
        Gpapud(){}
        Gpapud(uint32 v){val = v;}          
       ~Gpapud(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 1;
          uint32 gpio1  : 1;
          uint32 gpio2  : 1;
          uint32 gpio3  : 1;
          uint32 gpio4  : 1;
          uint32 gpio5  : 1;
          uint32 gpio6  : 1;
          uint32 gpio7  : 1;
          uint32 gpio8  : 1;
          uint32 gpio9  : 1;
          uint32 gpio10 : 1;
          uint32 gpio11 : 1;
          uint32 gpio12 : 1;
          uint32 gpio13 : 1;
          uint32 gpio14 : 1;
          uint32 gpio15 : 1;
          uint32 gpio16 : 1;
          uint32 gpio17 : 1;
          uint32 gpio18 : 1;
          uint32 gpio19 : 1;
          uint32 gpio20 : 1;
          uint32 gpio21 : 1;
          uint32 gpio22 : 1;
          uint32 gpio23 : 1;
          uint32 gpio24 : 1;
          uint32 gpio25 : 1;
          uint32 gpio26 : 1;
          uint32 gpio27 : 1;
          uint32 gpio28 : 1;
          uint32 gpio29 : 1;
          uint32 gpio30 : 1;
          uint32 gpio31 : 1;
        } bit;
      } gpapud;
      
    private:        
    
      uint16 space0_[2];
      
    public:
    
      /**
       * GPIO B Control Register (GPIO32 to 63).
       */
      union Gpbctrl
      {
        Gpbctrl(){}
        Gpbctrl(uint32 v){val = v;}          
       ~Gpbctrl(){}    
       
        uint32 val;
        struct Val
        {
          uint32 qualprd0 : 8;
          uint32 qualprd1 : 8;
          uint32 qualprd2 : 8;
          uint32 qualprd3 : 8;
        } bit;
      } gpbctrl;
    
      /**
       * GPIO B Qualifier Select 1 Register (GPIO32 to 47).
       */
      union Gpbqsel1
      {
        Gpbqsel1(){}
        Gpbqsel1(uint32 v){val = v;}          
       ~Gpbqsel1(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio32 : 2;
          uint32 gpio33 : 2;
          uint32 gpio34 : 2;
          uint32 gpio35 : 2;
          uint32 gpio36 : 2;
          uint32 gpio37 : 2;
          uint32 gpio38 : 2;
          uint32 gpio39 : 2;
          uint32 gpio40 : 2;
          uint32 gpio41 : 2;
          uint32 gpio42 : 2; 
          uint32 gpio43 : 2; 
          uint32 gpio44 : 2; 
          uint32 gpio45 : 2; 
          uint32 gpio46 : 2; 
          uint32 gpio47 : 2; 
        } bit;
      } gpbqsel1;
      
      /**
       * GPIOB Qualifier Select 2 Register (GPIO48 to 63).
       */
      union Gpbqsel2
      {
        Gpbqsel2(){}
        Gpbqsel2(uint32 v){val = v;}          
       ~Gpbqsel2(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio48 : 2;
          uint32 gpio49 : 2;
          uint32 gpio50 : 2;
          uint32 gpio51 : 2;
          uint32 gpio52 : 2;
          uint32 gpio53 : 2;
          uint32 gpio54 : 2;
          uint32 gpio55 : 2;
          uint32 gpio56 : 2;
          uint32 gpio57 : 2;
          uint32 gpio58 : 2; 
          uint32 gpio59 : 2; 
          uint32 gpio60 : 2; 
          uint32 gpio61 : 2; 
          uint32 gpio62 : 2; 
          uint32 gpio63 : 2;
        } bit;
      } gpbqsel2;
      
      /**
       * GPIO B MUX 1 Register (GPIO32 to 47).
       */
      union Gpbmux1
      {
        Gpbmux1(){}
        Gpbmux1(uint32 v){val = v;}          
       ~Gpbmux1(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio32 : 2;
          uint32 gpio33 : 2;
          uint32 gpio34 : 2;
          uint32 gpio35 : 2;
          uint32 gpio36 : 2;
          uint32 gpio37 : 2;
          uint32 gpio38 : 2;
          uint32 gpio39 : 2;
          uint32 gpio40 : 2;
          uint32 gpio41 : 2;
          uint32 gpio42 : 2; 
          uint32 gpio43 : 2; 
          uint32 gpio44 : 2; 
          uint32 gpio45 : 2; 
          uint32 gpio46 : 2; 
          uint32 gpio47 : 2; 
        } bit;
      } gpbmux1;
      
      /**
       * GPIO B MUX 2 Register (GPIO48 to 63).
       */
      union Gpbmux2
      {
        Gpbmux2(){}
        Gpbmux2(uint32 v){val = v;}          
       ~Gpbmux2(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio48 : 2;
          uint32 gpio49 : 2;
          uint32 gpio50 : 2;
          uint32 gpio51 : 2;
          uint32 gpio52 : 2;
          uint32 gpio53 : 2;
          uint32 gpio54 : 2;
          uint32 gpio55 : 2;
          uint32 gpio56 : 2;
          uint32 gpio57 : 2;
          uint32 gpio58 : 2; 
          uint32 gpio59 : 2; 
          uint32 gpio60 : 2; 
          uint32 gpio61 : 2; 
          uint32 gpio62 : 2; 
          uint32 gpio63 : 2;
        } bit;
      } gpbmux2;
      
      /**
       * GPIO B Direction Register (GPIO32 to 63).
       */
      union Gpbdir
      {
        Gpbdir(){}
        Gpbdir(uint32 v){val = v;}          
       ~Gpbdir(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio32 : 1;
          uint32 gpio33 : 1;
          uint32 gpio34 : 1;
          uint32 gpio35 : 1;
          uint32 gpio36 : 1;
          uint32 gpio37 : 1;
          uint32 gpio38 : 1;
          uint32 gpio39 : 1;
          uint32 gpio40 : 1;
          uint32 gpio41 : 1;
          uint32 gpio42 : 1; 
          uint32 gpio43 : 1; 
          uint32 gpio44 : 1; 
          uint32 gpio45 : 1; 
          uint32 gpio46 : 1; 
          uint32 gpio47 : 1; 
          uint32 gpio48 : 1;
          uint32 gpio49 : 1;
          uint32 gpio50 : 1;
          uint32 gpio51 : 1;
          uint32 gpio52 : 1;
          uint32 gpio53 : 1;
          uint32 gpio54 : 1;
          uint32 gpio55 : 1;
          uint32 gpio56 : 1;
          uint32 gpio57 : 1;
          uint32 gpio58 : 1; 
          uint32 gpio59 : 1; 
          uint32 gpio60 : 1; 
          uint32 gpio61 : 1; 
          uint32 gpio62 : 1; 
          uint32 gpio63 : 1;      
        } bit;
      } gpbdir;
      
      /**
       * GPIO B Pullup Disable Register (GPIO32 to 63).
       */
      union Gpbpud
      {
        Gpbpud(){}
        Gpbpud(uint32 v){val = v;}          
       ~Gpbpud(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio32 : 1;
          uint32 gpio33 : 1;
          uint32 gpio34 : 1;
          uint32 gpio35 : 1;
          uint32 gpio36 : 1;
          uint32 gpio37 : 1;
          uint32 gpio38 : 1;
          uint32 gpio39 : 1;
          uint32 gpio40 : 1;
          uint32 gpio41 : 1;
          uint32 gpio42 : 1; 
          uint32 gpio43 : 1; 
          uint32 gpio44 : 1; 
          uint32 gpio45 : 1; 
          uint32 gpio46 : 1; 
          uint32 gpio47 : 1; 
          uint32 gpio48 : 1;
          uint32 gpio49 : 1;
          uint32 gpio50 : 1;
          uint32 gpio51 : 1;
          uint32 gpio52 : 1;
          uint32 gpio53 : 1;
          uint32 gpio54 : 1;
          uint32 gpio55 : 1;
          uint32 gpio56 : 1;
          uint32 gpio57 : 1;
          uint32 gpio58 : 1; 
          uint32 gpio59 : 1; 
          uint32 gpio60 : 1; 
          uint32 gpio61 : 1; 
          uint32 gpio62 : 1; 
          uint32 gpio63 : 1;      
        } bit;
      } gpbpud;
    
    private:        
    
      uint16 space1_[8];
      
    public:
    
      /**
       * GPIO C MUX1 Register (GPIO64 to 79).
       */
      union Gpcmux1
      {
        Gpcmux1(){}
        Gpcmux1(uint32 v){val = v;}          
       ~Gpcmux1(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio64 : 2;
          uint32 gpio65 : 2;
          uint32 gpio66 : 2;
          uint32 gpio67 : 2;
          uint32 gpio68 : 2;
          uint32 gpio69 : 2;
          uint32 gpio70 : 2;
          uint32 gpio71 : 2;
          uint32 gpio72 : 2;
          uint32 gpio73 : 2;
          uint32 gpio74 : 2; 
          uint32 gpio75 : 2; 
          uint32 gpio76 : 2; 
          uint32 gpio77 : 2; 
          uint32 gpio78 : 2; 
          uint32 gpio79 : 2; 
        } bit;
      } gpcmux1;
      
      /**
       * GPIO C MUX2 Register (GPIO80 to 87).
       */
      union Gpcmux2
      {
        Gpcmux2(){}
        Gpcmux2(uint32 v){val = v;}          
       ~Gpcmux2(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio80 : 2;
          uint32 gpio81 : 2;
          uint32 gpio82 : 2;
          uint32 gpio83 : 2;
          uint32 gpio84 : 2;
          uint32 gpio85 : 2;
          uint32 gpio86 : 2;
          uint32 gpio87 : 2;
          uint32        : 16;
        } bit;
      } gpcmux2;
      
      /**
       * GPIO C Direction Register (GPIO64 to 87).
       */
      union Gpcdir
      {
        Gpcdir(){}
        Gpcdir(uint32 v){val = v;}          
       ~Gpcdir(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio64 : 1;
          uint32 gpio65 : 1;
          uint32 gpio66 : 1;
          uint32 gpio67 : 1;
          uint32 gpio68 : 1;
          uint32 gpio69 : 1;
          uint32 gpio70 : 1;
          uint32 gpio71 : 1;
          uint32 gpio72 : 1;
          uint32 gpio73 : 1;
          uint32 gpio74 : 1; 
          uint32 gpio75 : 1; 
          uint32 gpio76 : 1; 
          uint32 gpio77 : 1; 
          uint32 gpio78 : 1; 
          uint32 gpio79 : 1;       
          uint32 gpio80 : 1;
          uint32 gpio81 : 1;
          uint32 gpio82 : 1;
          uint32 gpio83 : 1;
          uint32 gpio84 : 1;
          uint32 gpio85 : 1;
          uint32 gpio86 : 1;
          uint32 gpio87 : 1;
          uint32        : 16;
        } bit;
      } gpcdir;
      
      /**
       * GPIO C Pullup Disable Register (GPIO64 to 87).
       */
      union Gpcpud
      {
        Gpcpud(){}
        Gpcpud(uint32 v){val = v;}          
       ~Gpcpud(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio64 : 1;
          uint32 gpio65 : 1;
          uint32 gpio66 : 1;
          uint32 gpio67 : 1;
          uint32 gpio68 : 1;
          uint32 gpio69 : 1;
          uint32 gpio70 : 1;
          uint32 gpio71 : 1;
          uint32 gpio72 : 1;
          uint32 gpio73 : 1;
          uint32 gpio74 : 1; 
          uint32 gpio75 : 1; 
          uint32 gpio76 : 1; 
          uint32 gpio77 : 1; 
          uint32 gpio78 : 1; 
          uint32 gpio79 : 1; 
          uint32 gpio80 : 1;
          uint32 gpio81 : 1;
          uint32 gpio82 : 1;
          uint32 gpio83 : 1;
          uint32 gpio84 : 1;
          uint32 gpio85 : 1;
          uint32 gpio86 : 1;
          uint32 gpio87 : 1;
          uint32        : 16;
        } bit;
      } gpcpud;
    
    private:        
    
      uint16 space2_[18];
      
    public:
    
      // NOT EALLOW PROTECTED
      
      /**
       * GPIO A Data Register (GPIO0 to 31).
       */
      union Gpadat
      {
        Gpadat(){}
        Gpadat(uint32 v){val = v;}          
       ~Gpadat(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 1;
          uint32 gpio1  : 1;
          uint32 gpio2  : 1;
          uint32 gpio3  : 1;
          uint32 gpio4  : 1;
          uint32 gpio5  : 1;
          uint32 gpio6  : 1;
          uint32 gpio7  : 1;
          uint32 gpio8  : 1;
          uint32 gpio9  : 1;
          uint32 gpio10 : 1;
          uint32 gpio11 : 1;
          uint32 gpio12 : 1;
          uint32 gpio13 : 1;
          uint32 gpio14 : 1;
          uint32 gpio15 : 1;
          uint32 gpio16 : 1;
          uint32 gpio17 : 1;
          uint32 gpio18 : 1;
          uint32 gpio19 : 1;
          uint32 gpio20 : 1;
          uint32 gpio21 : 1;
          uint32 gpio22 : 1;
          uint32 gpio23 : 1;
          uint32 gpio24 : 1;
          uint32 gpio25 : 1;
          uint32 gpio26 : 1;
          uint32 gpio27 : 1;
          uint32 gpio28 : 1;
          uint32 gpio29 : 1;
          uint32 gpio30 : 1;
          uint32 gpio31 : 1;
        } bit;
      } gpadat;
      
      /**
       * GPIO A Data Set Register (GPIO0 to 31).
       */
      union Gpaset
      {
        Gpaset(){}
        Gpaset(uint32 v){val = v;}          
       ~Gpaset(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 1;
          uint32 gpio1  : 1;
          uint32 gpio2  : 1;
          uint32 gpio3  : 1;
          uint32 gpio4  : 1;
          uint32 gpio5  : 1;
          uint32 gpio6  : 1;
          uint32 gpio7  : 1;
          uint32 gpio8  : 1;
          uint32 gpio9  : 1;
          uint32 gpio10 : 1;
          uint32 gpio11 : 1;
          uint32 gpio12 : 1;
          uint32 gpio13 : 1;
          uint32 gpio14 : 1;
          uint32 gpio15 : 1;
          uint32 gpio16 : 1;
          uint32 gpio17 : 1;
          uint32 gpio18 : 1;
          uint32 gpio19 : 1;
          uint32 gpio20 : 1;
          uint32 gpio21 : 1;
          uint32 gpio22 : 1;
          uint32 gpio23 : 1;
          uint32 gpio24 : 1;
          uint32 gpio25 : 1;
          uint32 gpio26 : 1;
          uint32 gpio27 : 1;
          uint32 gpio28 : 1;
          uint32 gpio29 : 1;
          uint32 gpio30 : 1;
          uint32 gpio31 : 1;
        } bit;
      } gpaset;
      
      /**
       * GPIO A Data Clear Register (GPIO0 to 31).
       */
      union Gpaclear
      {
        Gpaclear(){}
        Gpaclear(uint32 v){val = v;}          
       ~Gpaclear(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 1;
          uint32 gpio1  : 1;
          uint32 gpio2  : 1;
          uint32 gpio3  : 1;
          uint32 gpio4  : 1;
          uint32 gpio5  : 1;
          uint32 gpio6  : 1;
          uint32 gpio7  : 1;
          uint32 gpio8  : 1;
          uint32 gpio9  : 1;
          uint32 gpio10 : 1;
          uint32 gpio11 : 1;
          uint32 gpio12 : 1;
          uint32 gpio13 : 1;
          uint32 gpio14 : 1;
          uint32 gpio15 : 1;
          uint32 gpio16 : 1;
          uint32 gpio17 : 1;
          uint32 gpio18 : 1;
          uint32 gpio19 : 1;
          uint32 gpio20 : 1;
          uint32 gpio21 : 1;
          uint32 gpio22 : 1;
          uint32 gpio23 : 1;
          uint32 gpio24 : 1;
          uint32 gpio25 : 1;
          uint32 gpio26 : 1;
          uint32 gpio27 : 1;
          uint32 gpio28 : 1;
          uint32 gpio29 : 1;
          uint32 gpio30 : 1;
          uint32 gpio31 : 1;
        } bit;
      } gpaclear;
      
      /**
       * GPIO A Data Toggle Register (GPIO0 to 31).
       */
      union Gpatoggle
      {
        Gpatoggle(){}
        Gpatoggle(uint32 v){val = v;}          
       ~Gpatoggle(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 1;
          uint32 gpio1  : 1;
          uint32 gpio2  : 1;
          uint32 gpio3  : 1;
          uint32 gpio4  : 1;
          uint32 gpio5  : 1;
          uint32 gpio6  : 1;
          uint32 gpio7  : 1;
          uint32 gpio8  : 1;
          uint32 gpio9  : 1;
          uint32 gpio10 : 1;
          uint32 gpio11 : 1;
          uint32 gpio12 : 1;
          uint32 gpio13 : 1;
          uint32 gpio14 : 1;
          uint32 gpio15 : 1;
          uint32 gpio16 : 1;
          uint32 gpio17 : 1;
          uint32 gpio18 : 1;
          uint32 gpio19 : 1;
          uint32 gpio20 : 1;
          uint32 gpio21 : 1;
          uint32 gpio22 : 1;
          uint32 gpio23 : 1;
          uint32 gpio24 : 1;
          uint32 gpio25 : 1;
          uint32 gpio26 : 1;
          uint32 gpio27 : 1;
          uint32 gpio28 : 1;
          uint32 gpio29 : 1;
          uint32 gpio30 : 1;
          uint32 gpio31 : 1;
        } bit;
      } gpatoggle;
      
      /**
       * GPIO B Data Register (GPIO32 to 63).
       */
      union Gpbdat
      {
        Gpbdat(){}
        Gpbdat(uint32 v){val = v;}          
       ~Gpbdat(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio32 : 1;
          uint32 gpio33 : 1;
          uint32 gpio34 : 1;
          uint32 gpio35 : 1;
          uint32 gpio36 : 1;
          uint32 gpio37 : 1;
          uint32 gpio38 : 1;
          uint32 gpio39 : 1;
          uint32 gpio40 : 1;
          uint32 gpio41 : 1;
          uint32 gpio42 : 1; 
          uint32 gpio43 : 1; 
          uint32 gpio44 : 1; 
          uint32 gpio45 : 1; 
          uint32 gpio46 : 1; 
          uint32 gpio47 : 1; 
          uint32 gpio48 : 1;
          uint32 gpio49 : 1;
          uint32 gpio50 : 1;
          uint32 gpio51 : 1;
          uint32 gpio52 : 1;
          uint32 gpio53 : 1;
          uint32 gpio54 : 1;
          uint32 gpio55 : 1;
          uint32 gpio56 : 1;
          uint32 gpio57 : 1;
          uint32 gpio58 : 1; 
          uint32 gpio59 : 1; 
          uint32 gpio60 : 1; 
          uint32 gpio61 : 1; 
          uint32 gpio62 : 1; 
          uint32 gpio63 : 1;   
        } bit;
      } gpbdat;
      
      /**
       * GPIO B Data Set Register (GPIO32 to 63).
       */
      union Gpbset
      {
        Gpbset(){}
        Gpbset(uint32 v){val = v;}          
       ~Gpbset(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio32 : 1;
          uint32 gpio33 : 1;
          uint32 gpio34 : 1;
          uint32 gpio35 : 1;
          uint32 gpio36 : 1;
          uint32 gpio37 : 1;
          uint32 gpio38 : 1;
          uint32 gpio39 : 1;
          uint32 gpio40 : 1;
          uint32 gpio41 : 1;
          uint32 gpio42 : 1; 
          uint32 gpio43 : 1; 
          uint32 gpio44 : 1; 
          uint32 gpio45 : 1; 
          uint32 gpio46 : 1; 
          uint32 gpio47 : 1; 
          uint32 gpio48 : 1;
          uint32 gpio49 : 1;
          uint32 gpio50 : 1;
          uint32 gpio51 : 1;
          uint32 gpio52 : 1;
          uint32 gpio53 : 1;
          uint32 gpio54 : 1;
          uint32 gpio55 : 1;
          uint32 gpio56 : 1;
          uint32 gpio57 : 1;
          uint32 gpio58 : 1; 
          uint32 gpio59 : 1; 
          uint32 gpio60 : 1; 
          uint32 gpio61 : 1; 
          uint32 gpio62 : 1; 
          uint32 gpio63 : 1; 
        } bit;
      } gpbset;
      
      /**
       * GPIO B Data Clear Register (GPIO32 to 63).
       */
      union Gpbclear
      {
        Gpbclear(){}
        Gpbclear(uint32 v){val = v;}          
       ~Gpbclear(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio32 : 1;
          uint32 gpio33 : 1;
          uint32 gpio34 : 1;
          uint32 gpio35 : 1;
          uint32 gpio36 : 1;
          uint32 gpio37 : 1;
          uint32 gpio38 : 1;
          uint32 gpio39 : 1;
          uint32 gpio40 : 1;
          uint32 gpio41 : 1;
          uint32 gpio42 : 1; 
          uint32 gpio43 : 1; 
          uint32 gpio44 : 1; 
          uint32 gpio45 : 1; 
          uint32 gpio46 : 1; 
          uint32 gpio47 : 1; 
          uint32 gpio48 : 1;
          uint32 gpio49 : 1;
          uint32 gpio50 : 1;
          uint32 gpio51 : 1;
          uint32 gpio52 : 1;
          uint32 gpio53 : 1;
          uint32 gpio54 : 1;
          uint32 gpio55 : 1;
          uint32 gpio56 : 1;
          uint32 gpio57 : 1;
          uint32 gpio58 : 1; 
          uint32 gpio59 : 1; 
          uint32 gpio60 : 1; 
          uint32 gpio61 : 1; 
          uint32 gpio62 : 1; 
          uint32 gpio63 : 1; 
        } bit;
      } gpbclear;
      
      /**
       * GPIOB Data Toggle Register (GPIO32 to 63).
       */
      union Gpbtoggle
      {
        Gpbtoggle(){}
        Gpbtoggle(uint32 v){val = v;}          
       ~Gpbtoggle(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio32 : 1;
          uint32 gpio33 : 1;
          uint32 gpio34 : 1;
          uint32 gpio35 : 1;
          uint32 gpio36 : 1;
          uint32 gpio37 : 1;
          uint32 gpio38 : 1;
          uint32 gpio39 : 1;
          uint32 gpio40 : 1;
          uint32 gpio41 : 1;
          uint32 gpio42 : 1; 
          uint32 gpio43 : 1; 
          uint32 gpio44 : 1; 
          uint32 gpio45 : 1; 
          uint32 gpio46 : 1; 
          uint32 gpio47 : 1; 
          uint32 gpio48 : 1;
          uint32 gpio49 : 1;
          uint32 gpio50 : 1;
          uint32 gpio51 : 1;
          uint32 gpio52 : 1;
          uint32 gpio53 : 1;
          uint32 gpio54 : 1;
          uint32 gpio55 : 1;
          uint32 gpio56 : 1;
          uint32 gpio57 : 1;
          uint32 gpio58 : 1; 
          uint32 gpio59 : 1; 
          uint32 gpio60 : 1; 
          uint32 gpio61 : 1; 
          uint32 gpio62 : 1; 
          uint32 gpio63 : 1; 
        } bit;
      } gpbtoggle;
      
      /**
       * GPIO C Data Register (GPIO64 to 87).
       */
      union Gpcdat
      {
        Gpcdat(){}
        Gpcdat(uint32 v){val = v;}          
       ~Gpcdat(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio64 : 1;
          uint32 gpio65 : 1;
          uint32 gpio66 : 1;
          uint32 gpio67 : 1;
          uint32 gpio68 : 1;
          uint32 gpio69 : 1;
          uint32 gpio70 : 1;
          uint32 gpio71 : 1;
          uint32 gpio72 : 1;
          uint32 gpio73 : 1;
          uint32 gpio74 : 1; 
          uint32 gpio75 : 1; 
          uint32 gpio76 : 1; 
          uint32 gpio77 : 1; 
          uint32 gpio78 : 1; 
          uint32 gpio79 : 1; 
          uint32 gpio80 : 1;
          uint32 gpio81 : 1;
          uint32 gpio82 : 1;
          uint32 gpio83 : 1;
          uint32 gpio84 : 1;
          uint32 gpio85 : 1;
          uint32 gpio86 : 1;
          uint32 gpio87 : 1;
          uint32        : 16;
        } bit;
      } gpcdat;
      
      /**
       * GPIO C Data Set Register (GPIO64 to 87).
       */
      union Gpcset
      {
        Gpcset(){}
        Gpcset(uint32 v){val = v;}          
       ~Gpcset(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio64 : 1;
          uint32 gpio65 : 1;
          uint32 gpio66 : 1;
          uint32 gpio67 : 1;
          uint32 gpio68 : 1;
          uint32 gpio69 : 1;
          uint32 gpio70 : 1;
          uint32 gpio71 : 1;
          uint32 gpio72 : 1;
          uint32 gpio73 : 1;
          uint32 gpio74 : 1; 
          uint32 gpio75 : 1; 
          uint32 gpio76 : 1; 
          uint32 gpio77 : 1; 
          uint32 gpio78 : 1; 
          uint32 gpio79 : 1; 
          uint32 gpio80 : 1;
          uint32 gpio81 : 1;
          uint32 gpio82 : 1;
          uint32 gpio83 : 1;
          uint32 gpio84 : 1;
          uint32 gpio85 : 1;
          uint32 gpio86 : 1;
          uint32 gpio87 : 1;
          uint32        : 16;
        } bit;
      } gpcset;
      
      /**
       * GPIO C Data Clear Register (GPIO64 to 87).
       */
      union Gpcclear
      {
        Gpcclear(){}
        Gpcclear(uint32 v){val = v;}          
       ~Gpcclear(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio64 : 1;
          uint32 gpio65 : 1;
          uint32 gpio66 : 1;
          uint32 gpio67 : 1;
          uint32 gpio68 : 1;
          uint32 gpio69 : 1;
          uint32 gpio70 : 1;
          uint32 gpio71 : 1;
          uint32 gpio72 : 1;
          uint32 gpio73 : 1;
          uint32 gpio74 : 1; 
          uint32 gpio75 : 1; 
          uint32 gpio76 : 1; 
          uint32 gpio77 : 1; 
          uint32 gpio78 : 1; 
          uint32 gpio79 : 1; 
          uint32 gpio80 : 1;
          uint32 gpio81 : 1;
          uint32 gpio82 : 1;
          uint32 gpio83 : 1;
          uint32 gpio84 : 1;
          uint32 gpio85 : 1;
          uint32 gpio86 : 1;
          uint32 gpio87 : 1;
          uint32        : 16;
        } bit;
      } gpcclear;
      
      /**
       * GPIO C Data Toggle Register (GPIO64 to 87).
       */
      union Gpctoggle
      {
        Gpctoggle(){}
        Gpctoggle(uint32 v){val = v;}          
       ~Gpctoggle(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio64 : 1;
          uint32 gpio65 : 1;
          uint32 gpio66 : 1;
          uint32 gpio67 : 1;
          uint32 gpio68 : 1;
          uint32 gpio69 : 1;
          uint32 gpio70 : 1;
          uint32 gpio71 : 1;
          uint32 gpio72 : 1;
          uint32 gpio73 : 1;
          uint32 gpio74 : 1; 
          uint32 gpio75 : 1; 
          uint32 gpio76 : 1; 
          uint32 gpio77 : 1; 
          uint32 gpio78 : 1; 
          uint32 gpio79 : 1; 
          uint32 gpio80 : 1;
          uint32 gpio81 : 1;
          uint32 gpio82 : 1;
          uint32 gpio83 : 1;
          uint32 gpio84 : 1;
          uint32 gpio85 : 1;
          uint32 gpio86 : 1;
          uint32 gpio87 : 1;
          uint32        : 16;
        } bit;
      } gpctoggle;
    
    private:        
    
      uint16 space3_[8];
      
    public:
    
      // EALLOW PROTECTED
      
      /**
       * XINT1 GPIO Input Select Register (GPIO0 to 31).
       */
      union Gpioxint1sel
      {
        Gpioxint1sel(){}
        Gpioxint1sel(uint16 v){val = v;}          
       ~Gpioxint1sel(){}    
       
        uint16 val;
        struct Val
        {
          uint16 gpioxint1sel : 5;
          uint16              : 11;
        } bit;
      } gpioxint1sel;
      
      /**
       * XINT2 GPIO Input Select Register (GPIO0 to 31).
       */
      union Gpioxint2sel
      {
        Gpioxint2sel(){}
        Gpioxint2sel(uint16 v){val = v;}          
       ~Gpioxint2sel(){}    
       
        uint16 val;
        struct Val
        {
          uint16 gpioxint2sel : 5;
          uint16              : 11;
        } bit;
      } gpioxint2sel;
      
      /**
       * XNMI GPIO Input Select Register (GPIO0 to 31).
       */
      union Gpioxnmisel
      {
        Gpioxnmisel(){}
        Gpioxnmisel(uint16 v){val = v;}          
       ~Gpioxnmisel(){}    
       
        uint16 val;
        struct Val
        {
          uint16 gpiosel : 5;
          uint16         : 11;
        } bit;
      } gpioxnmisel;
      
      /**
       * XINT3 GPIO Input Select Register (GPIO32 to 63).
       */
      union Gpioxint3sel
      {
        Gpioxint3sel(){}
        Gpioxint3sel(uint16 v){val = v;}          
       ~Gpioxint3sel(){}    
       
        uint16 val;
        struct Val
        {
          uint16 gpioxint3sel : 5;
          uint16              : 11;
        } bit;
      } gpioxint3sel;
      
      /**
       * XINT4 GPIO Input Select Register (GPIO32 to 63).
       */
      union Gpioxint4sel
      {
        Gpioxint4sel(){}
        Gpioxint4sel(uint16 v){val = v;}          
       ~Gpioxint4sel(){}    
       
        uint16 val;
        struct Val
        {
          uint16 gpioxint4sel : 5;
          uint16              : 11;
        } bit;
      } gpioxint4sel;
      
      /**
       * XINT5 GPIO Input Select Register (GPIO32 to 63).
       */
      union Gpioxint5sel
      {
        Gpioxint5sel(){}
        Gpioxint5sel(uint16 v){val = v;}          
       ~Gpioxint5sel(){}    
       
        uint16 val;
        struct Val
        {
          uint16 gpioxint5sel : 5;
          uint16              : 11;
        } bit;
      } gpioxint5sel;
      
    
      /**
       * XINT6 GPIO Input Select Register (GPIO32 to 63).
       */
      union Gpioxint6sel
      {
        Gpioxint6sel(){}
        Gpioxint6sel(uint16 v){val = v;}          
       ~Gpioxint6sel(){}    
       
        uint16 val;
        struct Val
        {
          uint16 gpioxint6sel : 5;
          uint16              : 11;
        } bit;
      } gpioxint6sel;
      
      /**
       * XINT7 GPIO Input Select Register (GPIO32 to 63).
       */
      union Gpioint7sel
      {
        Gpioint7sel(){}
        Gpioint7sel(uint16 v){val = v;}          
       ~Gpioint7sel(){}    
       
        uint16 val;
        struct Val
        {
          uint16 gpioxint7sel : 5;
          uint16              : 11;
        } bit;
      } gpioint7sel;
      
      /**
       * LPM GPIO Select Register (GPIO0 to 31).
       */
      union Gpiolpmsel
      {
        Gpiolpmsel(){}
        Gpiolpmsel(uint32 v){val = v;}          
       ~Gpiolpmsel(){}    
       
        uint32 val;
        struct Val
        {
          uint32 gpio0  : 1;
          uint32 gpio1  : 1;
          uint32 gpio2  : 1;
          uint32 gpio3  : 1;
          uint32 gpio4  : 1;
          uint32 gpio5  : 1;
          uint32 gpio6  : 1;
          uint32 gpio7  : 1;
          uint32 gpio8  : 1;
          uint32 gpio9  : 1;
          uint32 gpio10 : 1;
          uint32 gpio11 : 1;
          uint32 gpio12 : 1;
          uint32 gpio13 : 1;
          uint32 gpio14 : 1;
          uint32 gpio15 : 1;
          uint32 gpio16 : 1;
          uint32 gpio17 : 1;
          uint32 gpio18 : 1;
          uint32 gpio19 : 1;
          uint32 gpio20 : 1;
          uint32 gpio21 : 1;
          uint32 gpio22 : 1;
          uint32 gpio23 : 1;
          uint32 gpio24 : 1;
          uint32 gpio25 : 1;
          uint32 gpio26 : 1;
          uint32 gpio27 : 1;
          uint32 gpio28 : 1;
          uint32 gpio29 : 1;
          uint32 gpio30 : 1;
          uint32 gpio31 : 1;
        } bit;
      } gpiolpmsel;
     
    private:        
    
      uint16 space4_[22];
      
    public:
    
    };
  }
}  
#endif // BOOS_TARGET_REGISRES_GPIO_HPP_

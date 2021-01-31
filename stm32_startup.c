#include<stdint.h>

#define SRAM_START  0x20000000U
#define SRAM_SIZE (128 * 1024) //128kb
#define SRAM_END  (SRAM_START) + (SRAM_SIZE)

#define STACK_START SRAM_END

void reset_handler(void); 
void default_handler(void);
//prototype of main
int main(void);
//my memory sections 
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _ebss;
extern uint32_t _sbss;
//__attribute defines a different section for the vector table helping in placing the vector table in a different section all together this way it can be place in at the start of the .text section
//@link :: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes

uint32_t vector[] __attribute__ ((section (".isr_vector"))) = {
    STACK_START,
    (uint32_t)(&reset_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    0,
    0,
    0,
    0,
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    0,
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),
    (uint32_t)(&default_handler),

};

void default_handler(void){
    while (1);
}
void reset_handler(void){
    // copy .data section to sram
    uint32_t size = &(_edata) - &(_sdata);
    uint32_t i;
    uint32_t *pDst = (uint32_t*)&_sdata;
    uint32_t *pSrc = (uint32_t*)&_etext;

    for(i =0 ; i<size; i++)
    {
        *pDst++ = *pSrc++;
    }
    
    //init the .bss section to zero in sram
    size = &_ebss - &_sbss;
    pDst = (uint32_t*)&_sbss;
     for(i =0 ; i<size; i++)
    {
        *pDst++ = 0;
    }
    // call init functions of std library (eg printf and scanf fucntions to be intialized here) not going to use here 

    //call main()
    main();

}
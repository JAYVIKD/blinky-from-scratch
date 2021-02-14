// base addres of the registers
#define rcc_base 0x40023800
#define gpiob_base 0x40020400

// address of the required 

#define rcc_ahb1enr (rcc_base + 0x30)
#define gpiob_moder	(gpiob_base + 0x00)
#define gpiob_ospeedr (gpiob_base + 0x08)	
#define gpiob_odr (gpiob_base + 0x14)

#define reg(X) (*(volatile unsigned int *) X)

int main(){
	unsigned int i=0;
	
	reg(rcc_ahb1enr) |=(1<<1);
	reg(gpiob_moder) |= (1<<14)|(1<<28)|(1<<0);
	reg(gpiob_ospeedr) = 0x0000;
	while(1){
		reg(gpiob_odr) ^= (1<<14);
		reg(gpiob_odr) ^= (1<<0);
		for( i=0 ; i<10000;i++){}
		for( i=0 ; i<10000;i++){}
		for( i=0 ; i<10000;i++){}
		for( i=0 ; i<10000;i++){}
		for( i=0 ; i<10000;i++){}

		
	}
	
}

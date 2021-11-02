#include <stdint.h> //declara��o de biblioteca
#include "TExaS.h" //declara��o de biblioteca
// DEFINE PARA PORTF
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC)) //atribui um "nome" a um local na mem�ria
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400)) //atribui um "nome" a um local na mem�ria 
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420)) //atribui um "nome" a um local na mem�ria
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510)) //atribui um "nome" a um local na mem�ria
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C)) //atribui um "nome" a um local na mem�ria
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))//atribui um "nome" a um local na mem�ria
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))//atribui um "nome" a um local na mem�ria
#define	SYSCTL_SYSDIV_16				(*((volatile unsigned long *)0x078E.3AD1))//atribui um "nome" a um local na mem�ria
	//DEFINE PARA PORTD
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))//atribui um "nome" a um local na mem�ria
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))//atribui um "nome" a um local na mem�ria

unsigned long SW2; //cria��o de vari�vel SW2    

void PortF_Init(void); //Declara��o da fun��o que faz as configura��es iniciais do PORTF
void Delay(uint8_t t); //Fun��o de delay
void PortD_Init(void); //Declara��o da fun��o que faz as configura��es iniciais do PORTF
int main(void) // in�cio programa principal
{    
int i=0,j=0, k=0; //cria��o de vari�veis para executar loop
TExaS_Init(SW_PIN_PF40,LED_PIN_PF321); //inicia as chaves e leds
PortF_Init();  //Chama a fun��o PortF_init
PortD_Init(); //Chama a fun��o PortD_init
while(1) //executa infinitamente
{
    SW2 = GPIO_PORTF_DATA_R&0x01;     // atribui este endere�o � vari�vel SW2
	
		GPIO_PORTF_DATA_R=0x00;  	//LEDS APAGADOS	
		GPIO_PORTD_DATA_R=0x00; //PORTD come�a apagado
		Delay(4); //DELAY PARA SER POSS�VEL VER A SITUA��O (os ciclos de m�quina s�o muito r�pidos, a olho nu, n�o conseguir�amos observar)
	//a fun��o delay "gasta" ciclos de m�quina do programa para que seja poss�vel observar as mudan�as
		GPIO_PORTF_DATA_R=0x04;  //LED AZUL
		Delay(4); //Delay 
	  GPIO_PORTF_DATA_R=0x00; //Apaga de novo
		Delay(4); //Delay 
    if(SW2==0x00) //Se a chave for pressionada (como � pull-up, pression�-la
			{      

				for(i=0; i<2; i++) //executa a a��o duas vezes 
				{
					GPIO_PORTF_DATA_R= 0x02; //LED vermelho 
					GPIO_PORTF_DATA_R = 0x00; 	//LEDS APAGADOS	
				} 
				while(j<5) //executa a a��o 5 vezes
				{
					GPIO_PORTD_DATA_R=0x04; //Liga o 4 bit da porta D, ou seja, PD3
					
					GPIO_PORTF_DATA_R = 0x08; //LED verde
					Delay(4); //Delay 
					GPIO_PORTF_DATA_R = 0x00;  //LEDS APAGADOS	
					Delay(4); //Delay 
					GPIO_PORTF_DATA_R = 0x04;  //LED azul
					Delay(4); //Delay 
					GPIO_PORTF_DATA_R = 0x00; //LEDS APAGADOS	 
					Delay(4); //Delay 
					GPIO_PORTF_DATA_R = 0x02; //LED vermelho  
					Delay(4); //Delay 
					GPIO_PORTF_DATA_R = 0x00;  //LEDS APAGADOS	
					Delay(4);//Delay 
					j=j+1;
			}
					
		}
			else
			{ 

				while(k<5) //repete por 5 vezes
				{
					GPIO_PORTF_DATA_R = 0x00; //leds apagados 
					Delay(4); //delay
					GPIO_PORTF_DATA_R = 0x08; //acende LED verde 
					Delay(4); //delay
					k=k+1; //soma mais um

				}

		  }
			
  }
}

void PortF_Init(void)
{
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // Clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // Desbloqueia portF  
  GPIO_PORTF_CR_R = 0x1F;           // Permite mudan�as      
  GPIO_PORTF_AMSEL_R = 0x00;        //Desativa fun��o anal�gica
  GPIO_PORTF_PCTL_R = 0x0000FFFF;   //Limpa bit PCTL 
  GPIO_PORTF_DIR_R = 0x0E;          //SW2 como input, leds como output  
  GPIO_PORTF_AFSEL_R =0x00;        //Sem fun��o alternativa
  GPIO_PORTF_PUR_R = 0x01;          // Ativa pino como pull-up na SW2       
  GPIO_PORTF_DEN_R |= 0x1F;          // Ativa portas digitais         
}
void PortD_Init(void)
{
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     //Clock do uC
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   //Desbloqueia PortD  
  GPIO_PORTD_CR_R = 0x1F;           //Permite mudan�as do portD   
  GPIO_PORTD_AMSEL_R = 0x00;        //Desativa fun��o anal�gica do uC
  GPIO_PORTD_PCTL_R = 0x0000FFFF;   //Limpa o bit PCTL  
  GPIO_PORTD_DIR_R = 0x0E;          // Ativa sa�da PD3
  GPIO_PORTD_AFSEL_R =0x00;        // Sem fun��o alternativa    
  GPIO_PORTD_DEN_R |= 0x1F;          // Ativa portas digitais        
}

//Inserir tempo para multipica��o
//Sa�da tempo*0.1 s
void Delay(uint8_t t)
{
unsigned long volatile time;
time = t*(727240*200/91); //Tempo de 0.1 (esse valor resulta em 1.6 M, como o programa executar� as linhas de 
	//c�digo 1.6.10^6 vezes, causar� um atraso na visualiza��o da sa�da de 0.1 s considerando o clock de 16MHz para
	//esse ucontrolador
	while(time)
	{
		time--; //decrementa 1.6.10^6 vezes para provocar atraso
	}
	
}



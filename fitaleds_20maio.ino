#include <MsTimer2.h>

const int fita = 3;             // fita de leds
const int movi = 4;           	// sensor de movimento
const int lumi = A0;           	// sensor de luminosidade
const int mode = 13;			// mode de leds  activo = usa luminosidade, desactivo = max
const int botao	= 1;			// botao para alterar o estado do leds
const int timer_luz_off = 5000; // tempo para desligar a luz 5s
const int threshold_lumi = 20;  // limiar da luminosidade

int sensemovi;
int ledLevel = 0;
int statefita = 0;
int state_mode = 0;
int stateinterrupt = 0;



void setup() {
	pinMode(fita, OUTPUT);  
	pinMode(mode, OUTPUT);  
	pinMode(movi, INPUT);    
	pinMode(lumi, INPUT); 
	pinMode(botao, INPUT);
  
	MsTimer2::set(timer_luz_off,luz_off ); // 5s period
}



void loop(){

	sensemovi = digitalRead(movi);		// le o sensor de movimento
	statebotao = digitalRead(botao);	// le estado do botao de estado
	lumino = digitalRead(lumi);			// le sensor luminosidade
  
	if (statebotao == HIGH){				// muda o estado  ver se é valido ser com soma e dividir por 2 
		if (state_mode == LOW){
			state_mode = HIGH;
			digitalWrite(mode, HIGH);
		}else{
			state_mode = LOW;
			digitalWrite(mode, LOW);
		}	
	}
  
    if (statefita == 0){              //se luz apagada
		if (sensemovi == HIGH){
			if (lumino >= threshold_lumi){ 	//ver melhor a condicao       
				luz_on();                	//liga a luz
			}
		}
	}

  
  
	if(statefita == 1){              	//se luz ligada
		if (sensemovi == HIGH){
			MsTimer2::stop();      	// novo movimento
			stateinterrupt = 0;
		}

		if (sensemovi == LOW){
			if(stateinterrupt == 0){  	// os liga a interrupccao se tiver ligada
				MsTimer2::start();    	// parou o movimento
				stateinterrupt = 1;
			}
		}
	}
}


// desliga a luz e o que envolve
void luz_off(){			
	adjust(0);
	statefita = 0;
    stateinterrupt = 0;
}


// liga a luz e o que tudo envolve
void luz_on(){			
	adjust(brilho());
	MsTimer2::start();
	statefita = 1;
	stateinterrupt = 1;
}


// ve o brilho que se poem nos leds
int brilho (){			

	if(mode == HIGH){
		lumino = digitalRead(lumi);	
		intensidade = 51 * lumino;	//51 = 255/5
	}else
		intensidade = 255;
	}

	return (intensidade);
}


// faz o ajuste automatico da intensidade da luz
void adjust(int targetValue)  {  	

	if (ledLevel < targetValue) {
		for (int x = ledLevel; x <= targetValue; x++) {
			analogWrite(fita, x);
			delay(8);
		}
	}

	if (ledLevel > targetValue) {
		for (int x = ledLevel; x >= targetValue; x--) {
			analogWrite(fita, x);
			delay(8);
		}
	}
}

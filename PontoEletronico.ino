#include <Keypad.h>
#include <EEPROM.h>
#include <TimerOne.h> 

byte pinoslinhas[] = {9, 8, 7, 6};
byte pinoscolunas[] = {5, 4, 3, 2};

char teclas[4][4] = { 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'#', '0', '*', 'D'}
};

Keypad teclado = Keypad(makeKeymap(teclas), pinoslinhas, pinoscolunas, 4, 4);

char senha[4] = {'1', '2', '3', '4'}; 
char senhadig[4]; 
uint8_t digito = 0;

volatile long int TempDeTrabalho = 0; 
int horasTrabalhadas = 0; 


void Contador() {
  TempDeTrabalho++;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Digite a senha e aperte * (Entrada) ou # (Saida)");
}

void loop() {
  char tecla_pressionada = teclado.getKey(); 
  
  if (tecla_pressionada) {
    Serial.print(tecla_pressionada);
    
    
    if (tecla_pressionada != '*' && tecla_pressionada != '#') {
      if (digito < 4) { 
        senhadig[digito] = tecla_pressionada; 
        digito++; 
      }
    } 
    
    else if (digito == 4) {
      Serial.println(); 
      
      bool acesso = true; 
      for (int i = 0; i < 4; i++) {
        if (senhadig[i] != senha[i]) {
          acesso = false; 
        }
      }

      if (acesso == true) {
        
       
        if (tecla_pressionada == '*') {
          Serial.println("Acesso Liberado: Ponto de ENTRADA");
          Timer1.initialize(1000000); 
          Timer1.attachInterrupt(Contador);
        } 
        
        
        else if (tecla_pressionada == '#') {
          Serial.println("Acesso Liberado: Ponto de SAIDA");
          Timer1.detachInterrupt(); // Para a contagem do tempo
          
          horasTrabalhadas = TempDeTrabalho / 3600; 
          
          
          EEPROM.write(0, horasTrabalhadas);
          
          Serial.print("Horas trabalhadas hoje salvas: ");
          Serial.println(horasTrabalhadas);
          
          
          TempDeTrabalho = 0; 
        }
      } 
      else {
        Serial.println("Senha Incorreta! Acesso negado.");
      }
      
      
      digito = 0; 
      Serial.println("-----------------");
      Serial.println("Digite a senha e aperte * (Entrada) ou # (Saida)");
    }
  }
}

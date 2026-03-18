#include <Keypad.h>



byte pinoslinhas[] = {10, 9, 8, 7};
byte pinoscolunas[] = {6, 5, 4, 3};

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

 


void setup() {
  Serial.begin(9600);
  Serial.println("Digite a senha");
}

void loop() {
  char tecla_pressionada = teclado.getKey(); 
  
  if (tecla_pressionada) {
    Serial.print(tecla_pressionada);
  
    if (tecla_pressionada){
      if (digito<4){
        senhadig[digito]=tecla_pressionada;
          digito++;
      }
    }
    

    
     if (digito == 4) {
      Serial.println(); 
      
      bool acesso = true; 
      for (int i = 0; i < 4; i++) {
        if (senhadig[i] != senha[i]) {
          acesso = false; 
        }
      }

      if (acesso == true) {
       Serial.println("Bem Vindo Moreno!");
       digitalWrite (2, HIGH);//Energiza um dos lados da bobina do relé, fechando o circuito
       delay(7000);
       digitalWrite(2, LOW) ;//Aguarda 7s e abre a chave de novo, trancando a porta
          
          
      } 
      else {
        Serial.println("Senha Incorreta!");
          delay(2000);;
      }
      
      
      digito = 0; 
      Serial.println("-----------------");
      Serial.println("Digite a senha ");
    }
  }
}


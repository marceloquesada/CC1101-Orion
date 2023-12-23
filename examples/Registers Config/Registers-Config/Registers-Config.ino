//#include <ELECHOUSE_CC1101_SRC_DRV.h>

void setup() {
  // Configura a porta serial e inicia ela
  Serial.begin(9600,SERIAL_8N1);
  while (!Serial){
    ;//Esperar a comunicacao serial iniciar
  }
}

void loop() {
  // Espera a nova mensagem
  if (Serial.available() > 0) {
    //Recebe a string
    String recebido = Serial.readStringUntil('\n');
    //Recebe o indice do caractere para split
    int charSplit = recebido.indexOf(',');
    //Divide a string em duas variaveis
    String endereco = recebido.substring(0,charSplit);
    String valor = recebido.substring(charSplit,recebido.length());
    //Remove os valores 0x das strings
    endereco.remove(0,2); //0x
    valor.remove(0,3);//,0x
    //Converte os valores em int
    //int intEndereco = strtoll(endereco, NULL, 16);

    Serial.println(endereco + "+" + valor +"OK");
  }
}

#include <ELECHOUSE_CC1101_SRC_DRV.h>

char convertChartoByte(char c){
  //Funcao para converter caractere para hexadecimal
  //Feita por preguiça e por não encontrar forma melhor
 char resposta;
 switch(c){
  case '0':
    resposta = 0x00;
    break;
  case '1':
    resposta = 0x01;
    break;
  case '2':
    resposta = 0x02;
    break;
  case '3':
    resposta = 0x03;
    break;
  case '4':
    resposta = 0x04;
    break;
  case '5':
    resposta = 0x05;
    break;
  case '6':
    resposta = 0x06;
    break;
  case '7':
    resposta = 0x07;
    break;
  case '8':
    resposta = 0x08;
    break;
  case '9':
    resposta = 0x09;
    break;
  case 'A':
    resposta = 0x0A;
    break;
  case 'B':
    resposta = 0x0B;
    break;
  case 'C':
    resposta = 0x0C;
    break;
  case 'D':
    resposta = 0x0D;
    break;
  case 'E':
    resposta = 0x0E;
    break;
  case 'F':
    resposta = 0x0F;
    break;
 };
 return resposta;
}

void setup() {
  // Configura a porta serial e inicia ela
  Serial.begin(9600,SERIAL_8N1);
  while (!Serial){
    ;//Esperar a comunicacao serial iniciar
  }
  if (ELECHOUSE_cc1101.getCC1101()){      // Check the CC1101 Spi connection.
    Serial.println("Connection OK");
    }else{
    Serial.println("Connection Error");
    }
  ELECHOUSE_cc1101.Init();
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
    endereco.remove(0,2); //"0x"
    valor.remove(0,3);//"",0x"
    //Converte os valores em byte
    /* 
    Ideia principal:
    Cada byte é recebido pela serial, porém, o resultado está em hexadecimal
    Temos que separar os valores em valores nas variaveis do Arduino
    */
    //Para endereco
    //Variavel para guardar os valores hexadecimais
    char byteAddr = 0x00;
    //Para cada valor na variavel do endereco
    for(int i = 0; i < endereco.length();i++){
      char c = endereco.charAt(i);
      c = convertChartoByte(c);
      //Slide para a esquerda
      byteAddr = (byteAddr << 4);
      //Pelo tamanho da byteAddr, esse processo descartará os
      //dois primeiros valores recebidos, que para o CC1101 será 0
      //Coloca o valor dos 4 bits na variavel       
      byteAddr = byteAddr | c;
    };
    //Para o valor a ser escrito
    //Variavel para guardar os valores hexadecimais
    char byteValue = 0x00;
    for(int i = 0; i < valor.length();i++){
      char c = valor.charAt(i);
      c = convertChartoByte(c);
      //Slide para a esquerda
      byteValue = byteValue << 4;
      //Coloca o valor dos 4 bits na variavel
      byteValue = byteValue | c;
    };
    ELECHOUSE_cc1101.SpiWriteReg(byteAddr,byteValue);
    Serial.write(byteAddr);
    Serial.print("<-");
    Serial.write(byteValue);
    Serial.println(" OK");
  }
}

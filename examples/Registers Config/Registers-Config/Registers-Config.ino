//#include <ELECHOUSE_CC1101_SRC_DRV.h>

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
    Cada byte é recebido pela serial, porém, o resultado está em hexa
    Temos que separar 2 caracteres e colocá-los em um único byte
    Após isso, temos que salvar no
    */
    Serial.println(endereco+"+"+valor);
    //Para endereco
    //Variaveis booleanos para controlar a entrada dos enderecos
    bool slide = 0;
    int push = 0;
    //Variavel para guardar os valores hexadecimais
    char byteAddr[endereco.length()/2];
    //Variavel temporaria para guardar valor entre iteracao
    char temp;
    //Para cada valor na variavel do endereco
    for(int i = 0; i < endereco.length();i++){
      char c = endereco.charAt(i);
      c = convertChartoByte(c);
      if(slide == 1){
        //Push
        //Somar os dois valores
        temp = temp | c;
        //Retornar a variavel de slide
        slide = 0;
        //Coloca o valor no endereco
        byteAddr[i/(int)2] = temp;
      }
      else{
        //Slide
        //Coloca o valor da
        temp = c << 4;
        slide = 1;
      };
    };
    //Para o valor a ser escrito
    //Usando as mesmas variaveis antigas
    //Para colocar valor
    char byteValue[valor.length()/2];
    for(int i = 0; i < valor.length();i++){
      char c = valor.charAt(i);
      c = convertChartoByte(c);
      if(slide == 1){
        //Push
        //Somar os dois valores
        temp = temp | c;
        //Retornar a variavel de slide
        slide = 0;
        //Coloca o valor no endereco
        byteValue[i/(int)2] = temp;
      }
      else{
        //Slide
        //Coloca o valor da
        temp = c << 4;
        slide = 1;
      };
    };
    for(int i = 0; i < sizeof(byteAddr);i++){
      Serial.write(byteAddr[i]);
    };
    Serial.print("+");
    for(int i = 0; i < sizeof(byteValue);i++){
      Serial.write(byteValue[i]);
    };
    Serial.println("OK");
  }
}

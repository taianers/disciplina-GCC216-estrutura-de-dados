#include <SPI.h>
#include <MFRC522.h>
#include "Arduino.h"
#include "Noh.h"
#include "TabelaHash.h"

constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;     // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

MFRC522::MIFARE_Key key;

typedef int Dado;
TabelaHash th(10);
  
void setup(){
  Serial.begin(9600);   //Inicia a serial
  SPI.begin();      //Inicia  SPI bus
  mfrc522.PCD_Init();   //Inicia MFRC522
  Serial.println(F("Inicializado"));
  inserirDadosTeste();
}
 
void loop(){
  //Prepara chave - padrao de fabrica = FFFFFFFFFFFFh
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  ManipulaDadosRFID();

  delay (1000);
  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}
//*********************************************************
String lerStringSerial(){
  String conteudo = "";
  char caractere;
  while(Serial.available() == 0);
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  } 
  return conteudo;
}

void ManipulaDadosRFID(){
  //Aguarda cartao
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Dado matricula = modoLeituraMatricula();
  int credito = modoLeituraCredito();
//  funcao que calcula posicao pelo numero da matricula.
  int hash = th.Posicao(th.DivideChave(matricula));
  String received_string;
  
  if(th.Recuperar(matricula, hash) == -1){
    th.Inserir(matricula, credito, hash);
  }else{
    Serial.println("Matrícula já cadastrada. Deseja removê-la ?");
    Serial.println("1 - Sim \n0 - Não");
    if(lerStringSerial().toInt()){
      th.Remover(matricula);
    }
  }
  th.Percorrer();

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
//*************************************************************
int modoLeituraMatricula(){
  MFRC522::StatusCode status;
  byte buffer1[18];
  byte block = 4;
  byte len = 18;
  char matricula[5];

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      if(i > 0 and i < 6){
         matricula[i - 1] = char(buffer1[i]);
      }
    }
  }
  return atoi(matricula);
}

int modoLeituraCredito(){
  MFRC522::StatusCode status;
  byte buffer2[18];
  byte block = 1;
  byte len = 18;
  char creditos[2];
  
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  
  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  
  for (uint8_t i = 0; i < 16; i++) {
    if(i < 2){
      creditos[i] = char(buffer2[i]);
    }
  }

  int creditoConvert = atoi(creditos);
  while(creditoConvert > 20){
    creditoConvert = creditoConvert / 10;
  }
  return creditoConvert;
}

//Cria 50 dados e insere na hash 
void inserirDadosTeste(){
  Dado matricula1;
  Dado matricula2;
  for(int j = 15; j <= 19; j++){
    for(int i = 0; i < 5; i++){
      matricula1 = (j * 1000) + 100 + i;
      int hash = th.Posicao(th.DivideChave(matricula1));
      th.Inserir(matricula1, i, hash);
      matricula2 = (j * 1000) + 200 + i;
      hash = th.Posicao(th.DivideChave(matricula2));
      th.Inserir(matricula2, i + 2, hash);
    }
  }
  th.Percorrer();
}

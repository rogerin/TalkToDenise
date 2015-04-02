/*
 * Projeto: Arduino com AJAX
 * Autor: Rogerio Alencar Filho
 * Data: 01/04/2014
 * Versão: v0.1
 * Descrição: O Arduino recebe uma requisição HTTP e retorna um JSON que é tratado no HTML com Javascript para exibir na tela.
 * Github: https://github.com/rogerin/----
 * Twitter: https://twitter.com/rogerin
 * Facebook: https://twitter.com/rogerioalencar
 */


#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};


IPAddress ipServer(192, 168, 1, 177);
IPAddress ipClient(192, 168, 1, 111);
//IPAddress denise(200, 217, 58, 75);                                     //IP DA DENISE
IPAddress gateway(192, 168, 1, 1);
char denise[] = "http://minhascameras2014.dyndns.org";


EthernetServer server(92);

int LUZ1 = 22;
int LUZ2 = 23;
int LUZ3 = 24;
int LUZ4 = 25;
int LUZ5 = 26;

char textoDenise[] = "";


void setup()
{
  
  Serial.begin(115200);
  Serial.println("Iniciando programa..a");
  
  Ethernet.begin(mac, ipServer, ipClient, gateway);
  Serial.println("Server ativo no IP: ");
  Serial.print(Ethernet.localIP());
  server.begin();
  
  for(int i = 22; i<=26; i ++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
    Serial.println(i);
  }
 
  
  
}
void loop()
{
  EthernetClient client = server.available();
  if(client)
  {
    boolean continua = true;
    String linha = "";

    while(client.connected())
    {
      if(client.available()){
        char c = client.read();
        linha.concat(c);
  
        if(c == '\n' && continua)
        {
          client.println("HTTP/1.1 200 OK");
          // IMPORTANTE, ISSO FAZ O ARDUINO RECEBER REQUISIÇÃO AJAX DE OUTRO SERVIDOR E NÃO APENAS LOCAL.
          client.println("Content-Type: text/javascript");
          client.println("Access-Control-Allow-Origin: *");
          client.println();          
         
          int iniciofrente = linha.indexOf("?");
                
          if(iniciofrente>-1){     //verifica se o comando veio
            iniciofrente     = iniciofrente+6; //pega o caractere seguinte
            int fimfrente    = iniciofrente+3; //esse comando espero 3 caracteres
            String acao    = linha.substring(iniciofrente,fimfrente);//recupero o valor do comando
            
 
            if      ( acao == "001"){ 
              digitalWrite(LUZ1, LOW);
                  if (client.connect(denise, 1000)) {  //PORTA DA DENISE
                    Serial.println("conexao estabelecida");
                    client.print("GET http://minhascameras2014.dyndns.org:1000/denise.php?msg=Luz 1 desligada. HTTP/1.1\r\n");
                    client.print("Host: minhascameras2014.dyndns.org:1000\r\n");
                    client.print("User-Agent: arduino-ethernet\r\n");
                    client.print("Connection: close\r\n\r\n");
                  }
            }
            
            else if ( acao == "002"){ 
              digitalWrite(LUZ1, HIGH);
               if (client.connect(denise, 1000)) {  //PORTA DA DENISE
                    Serial.println("conexao estabelecida");
                    client.print("GET http://minhascameras2014.dyndns.org:1000/denise.php?msg=Luz 1 ligada. HTTP/1.1\r\n");
                    client.print("Host: minhascameras2014.dyndns.org:1000\r\n");
                    client.print("User-Agent: arduino-ethernet\r\n");
                    client.print("Connection: close\r\n\r\n");
                  }
            } 
            
            else if ( acao == "003"){ 
              digitalWrite(LUZ2, LOW);
               if (client.connect(denise, 1000)) {  //PORTA DA DENISE
                    Serial.println("conexao estabelecida");
                    client.print("GET http://minhascameras2014.dyndns.org:1000/denise.php?msg=Luz 2 desligada. HTTP/1.1\r\n");
                    client.print("Host: minhascameras2014.dyndns.org:1000\r\n");
                    client.print("User-Agent: arduino-ethernet\r\n");
                    client.print("Connection: close\r\n\r\n");
                  }
            }
            else if ( acao == "004"){ 
              digitalWrite(LUZ2, HIGH); 
               if (client.connect(denise, 1000)) {  //PORTA DA DENISE
                    Serial.println("conexao estabelecida");
                    client.print("GET http://minhascameras2014.dyndns.org:1000/denise.php?msg=Luz 2 ligada. HTTP/1.1\r\n");
                    client.print("Host: minhascameras2014.dyndns.org:1000\r\n");
                    client.print("User-Agent: arduino-ethernet\r\n");
                    client.print("Connection: close\r\n\r\n");
                  }
            }
            
            else if ( acao == "005"){ digitalWrite(LUZ3, LOW); }
            else if ( acao == "006"){ digitalWrite(LUZ3, HIGH); }
            
            else if ( acao == "007"){ digitalWrite(LUZ4, LOW); }
            else if ( acao == "008"){ digitalWrite(LUZ4, HIGH); }
            
            else if ( acao == "009"){ digitalWrite(LUZ5, LOW); }
            else if ( acao == "010"){ digitalWrite(LUZ5, HIGH); }    
            else {}
            
         
            
            
            client.print("dados({ LUZ1 : ");
            client.print(digitalRead(LUZ1));
            client.print(", LUZ2 :  ");
            client.print(digitalRead(LUZ2));
            client.print(",");
            client.print(" LUZ3 : ");
            client.print(digitalRead(LUZ3));
            client.print(",");
            client.print(" LUZ4 : ");
            client.print(digitalRead(LUZ4));
            client.print(",");
            client.print(" LUZ5 : ");
            client.print(digitalRead(LUZ5));
            client.print("})");
            
         }          
          break;
        }
        if(c == '\n') { continua = true; }
        else if (c != '\r') { continua = false; }
      }
    }
     delay(1);
     client.stop();
  }
}





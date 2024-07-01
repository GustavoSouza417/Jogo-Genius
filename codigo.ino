//SEÇÃO DE DEFINES
  //BOTÕES
    #define botInit 7
    
    #define botVerd 6
    #define botVerm 5
    #define botAmar 4
    #define botAzul 3
  
  //LEDS
    #define ledVerd 13
    #define ledVerm 12
    #define ledAmar 11
    #define ledAzul 10
  
  //PIEZO
    #define piezo 8



//SEÇÃO DE DECLARAÇÃO E ATRIBUIÇÃO DE VARIÁVEIS
  bool estaJogando, acertou;
  int  numeroAleatorio, ledEscolhido;



//SEÇÃO DE PROTOTIPAÇÃO
  void desligarTodosOsLeds();
  void piscarLedAleatorio(int);
  void jogando();



//FUNÇÕES PRINCIPAIS
  void setup()
  {
    randomSeed(analogRead(0));
    Serial.begin(9600);

    pinMode(botInit, INPUT);
    pinMode(botVerd, INPUT_PULLUP);
    pinMode(botVerm, INPUT_PULLUP);
    pinMode(botAmar, INPUT_PULLUP);
    pinMode(botAzul, INPUT_PULLUP);

    pinMode(ledVerd, OUTPUT);
    pinMode(ledVerm, OUTPUT);
    pinMode(ledAmar, OUTPUT);
    pinMode(ledAzul, OUTPUT);

    pinMode(piezo, OUTPUT);
  }

  void loop()
  {
    if(digitalRead(botInit) == HIGH or estaJogando == true)
    {
      estaJogando = true;

      numeroAleatorio = random(1, 5);
      piscarLedAleatorio(numeroAleatorio);
      desligarTodosOsLeds();

      while(true)
      {
        jogando();

        if(acertou == true and ledEscolhido != 0)
        {
          tone(piezo, 132, 650);
          delay(1000);
          break;
        }
        else if(acertou == false)
        {
          tone(piezo, 30, 3000);
          estaJogando = false;
          break;
        }
      }
    }
    else
    {
      estaJogando = false;
      acertou = true;

      desligarTodosOsLeds();
    }
  }



//SEÇÃO DE FUNÇÕES
  void desligarTodosOsLeds()
  {
    digitalWrite(ledVerd, LOW);
    digitalWrite(ledVerm, LOW);
    digitalWrite(ledAmar, LOW);
    digitalWrite(ledAzul, LOW);
  }

  void piscarLedAleatorio(int numeroAleatorio)
  {
    tone(piezo, 132, 500);
    
    desligarTodosOsLeds();
    
    if(numeroAleatorio == 1)
      digitalWrite(ledVerd, HIGH);
    
    else if(numeroAleatorio == 2)
      digitalWrite(ledVerm, HIGH);
    
    else if(numeroAleatorio == 3)
      digitalWrite(ledAmar, HIGH);
    
    else if(numeroAleatorio == 4)
      digitalWrite(ledAzul, HIGH);
    
    else
      Serial.println("PiscarLedAleatorio: problema");
    
    delay(1000);
  }
  
  void jogando()
  {
    if(digitalRead(botVerd) == LOW)
    {
        ledEscolhido = 1;
        
        if(numeroAleatorio == ledEscolhido)
          digitalWrite(ledVerd, HIGH);
        else
          acertou = false;
    }
    else if(digitalRead(botVerm) == LOW)
    {
        ledEscolhido = 2;
        
        if(numeroAleatorio == ledEscolhido)
          digitalWrite(ledVerm, HIGH);
        else
          acertou = false;
    }
    else if(digitalRead(botAmar) == LOW)
    {
        digitalWrite(ledAmar, HIGH);
        ledEscolhido = 3;
        
        if(numeroAleatorio == ledEscolhido)
          digitalWrite(ledAmar, HIGH);
        else
          acertou = false;
    }
    else if(digitalRead(botAzul) == LOW)
    {
        digitalWrite(ledAzul, HIGH);
        ledEscolhido = 4;
        
        if(numeroAleatorio == ledEscolhido)
          digitalWrite(ledAzul, HIGH);
        else
          acertou = false;
    }
    else
    {
      desligarTodosOsLeds();
      ledEscolhido = 0;
    }
  }
# ABJALU
Projeto de comunicação de dados.

# Composição:

O sistema é composto de um master e dois slaves.
O master é a interface com o pc.
O slave 1 é um controle de luz.
O slave 2 controla um ventilador.

Eles se comunicam via protocolo RS485.

## Master

O master consulta valores, realiza ações de controle e pode selecionar
setpoints para ação de controle local.

Contém um linkit 7688 duo.

## Slave1

O Slave 1 é um controle de iluminação com sensor de luminosidade.
Permite controle local e responde requests de leitura e sets/unsets.

Contém um nodemcu, um fotoresistor e um relé.

## Slave2

O Slave 2 é um controle de iluminação com sensor de luminosidade.
Permite controle local e responde requests de leitura e sets/unsets.

Contém um nodemcu, um lm35 e um relé.

## Testes do programa:

A partir de um terminal ssl via conexão wifi direta à 
placa linkit smart duo (no modo AP), 
você pode executar o programa minicom para comunicação serial:

`ssh root@192.168.100.1`

`minicom`

e digite os comandos ou o protocolo diretamente.
Você deve digitar normalmente o comando e apertar enter ao finalizar.
Para protocol, você não precisa apertar enter.

## Protocolo:

O protocolo obedece à seguinte regra:

### O primeiro caractere deve ser o endereço da slave que se quer pedir por informação.
São possíveis, assim, 256 endereços menos o usado para controle (a). Portanto são possíveis:

#### 255 ENDEREÇOS.

#### '0' é o endereço da slave_zero.
#### '1' é o endereço da slave_one.

### O segundo caratere deve ser o caractere de controle a (ADDRESS).

#### '0a' para falar com placa slave_zero.
#### '1a' para falar com placa slave_one.

### O terceiro caratere deve ser 'r' para operação de leitura ou o valor para setup ('0' ou '1').

#### '0ar' para ler o sensor da placa slave_zero.
#### '1ar' para ler o sensor da placa slave_one.

### Um quarto caratere é necessário para o caso de escrita ('s').

#### '0a0s' para desligar o relê da placa slave_zero.
#### '1a1s' para ligar o relê da placa slave_one.



## Cli:

`ping`
retorna o ping da placa linkit master.

`ping_slave`
retorna o ping de todos os slaves escutando (use somente com um slave para debugar).

`autoping`
ativa/desativa o modo autoping que ping de um em um segundo pela slave (use somente com um slave para debugar).

# PARTE 2

## Modificações no Protocolo:

O protocolo obedece agora à seguinte regra:

### SEMPRE A PALAVRA É COMPOSTA DE EXATOS 5 CARACTERES

### O primeiro caractere deve ser 'a' seguido do byte de endereço.

#### '0' é o endereço da slave_zero.
#### '1' é o endereço da slave_one.

#### 'a0' para falar com placa slave_zero.
#### '01' para falar com placa slave_one.

### O terceiro caratere deve ser 'r' para operação de leitura ou o caractere 's' para sets.
### O quarto caractere é usado para identificar o valor ('0' ou '1') à ser setado. Ele é ignorado no caso de leitura ('r' 

### Um quinto caratere de checksum.

#### 'a0r0l' para ler o sensor da placa slave_zero. Onde 'l' na verdade deve ser substituído pelo byte de checksum ('a'+'0'+'r'+'0')
#### 'a1s1l' para ligar o relê da placa slave_one. Onde 'l' na verdade deve ser substituído pelo byte de checksum ('a'+'0'+'r'+'0')

### As respostas das placas também são em 5 CARACTERES

### O primeiro caractere da resposta é sempre 's' seguido do byte de endereço da placa que está respondendo.

#### '0' é o endereço da slave_zero.
#### '1' é o endereço da slave_one.

#### 's0' é uma resposta da placa slave_zero.
#### 's1' é uma resposta da placa slave_one.

### O terceiro caratere será 'r'.
### O quarto caractere é o byte com a leitura do sensor; 
### O quinto caratere é o checksum.

#### 's0r?l' indica a leitura ? do sensor da placa slave_zero. Onde 'l' na verdade deve ser substituído pelo byte de checksum ('s'+'0'+'r'+'?')

Os arquivos da parte dois estão em uma pasta separada. Destaque para o código do checksum:

```
char protocol_errorCharacterFor(String msg) {
  byte cks = 0;
  
  for(int i=0; i < 4; i++) {
    cks += byte(msg[i]);
  }
  
  return char(cks);
  //return 'l';
}
```

Testes para comunicação sem fio:

A partir de um terminal ssl via conexão wifi direta à placa linkit smart duo (no modo AP), você pode executar o programa telnet para comunicação wifi usando o endereço ip de qualquer node:

``` telnet 192.168.100.220``` (A máscara é a da rede da nodemcu 255.255.255.0 e o final 220 varia)

Você pode encontrar o endereço das nodes usando a interface do arduino que mapeia o ip ao nome da placa pela biblioteca OTA de upload via wifi.

e digite o protocolo diretamente. Você deve digitar normalmente a palavra do protocolo e apertar enter ao finalizar. Recomenda-se comentar a parte do cálculo de detecção do erro e retornar qualquer outro fixo ao invés do calculado (letra 'l' por exemplo). Isso para que você não tenha que calcular o checksum de cabeça. 

### Próximos passos:

Implementar o código nodejs para operar as placas e entregar uma interface amigável via express que pode ser acessada pelo navegador e abstrai os códigos para controles simples de chaves e displays com a leitura do sensor.

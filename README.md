# abjalu
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

Contém um linkit 7698 duo, um fotoresistor e um relé.

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





  

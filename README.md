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

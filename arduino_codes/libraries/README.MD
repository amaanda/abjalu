# ATENÇÃO

NODE_MCU REQUER BIBLIOTECA ESPECIAL PARA SOFTWARE_SERIAL.

Quando programar com arduino a node_mcu você precisa salvar esta biblioteca na pasta libraries com o nome:


espsoftwareserial-master_NODEMCU -> espsoftwareserial-master

E precisa se lembrar de desfazer quando for tornar a programar com linkit. (e reiniciar a IDE)

Eu uso os seguintes alias no terminal unix:

alias prognode='cp -r ~/arduino_libraries/espsoftwareserial-master ~/arduino_sketchbook/libraries/'
alias proglink='rm -r ~/arduino_sketchbook/libraries/espsoftwareserial-master'

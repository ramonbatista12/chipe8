# chipe8
## Estatus : Em desenvolvimento  

O CHIP-8 é uma máquina virtual antiga que permitia a programadores trabalharem com códigos voltados à produção de jogos de 8 bits. Com esse estudo eu pude ver um pouco mais sobre como a máquina funciona, pois o emulador trabalha decodificando os opcodes para saber o que cada instrução de máquina vai fazer. E é possível ver e entender muito sobre o funcionamento de um processador real; mesmo o emulador não tendo a ULA e outras partes do pipeline bem definidas, é possível ver muito bem que para um software funcionar é necessário o ciclo de pegar a instrução, codificá-la e então realizar as operações necessári

## linguagem
- C++

## gui
- SDL

#### Por que das minhas escolhas
  
C++ foi escolhida pela facilidade de se encontrar tutoriais para a criação de emuladores e também pela facilidade com a integração da SDL3, que é o framework mostrado pelo artigo que segui para fazer a minha versão. Essas escolhas me permitem uma manutenção maior a longo prazo, pois o projeto também poderia ser feito em Rust, mas traria grandes dificuldades para integrar bibliotecas C++ no projeto.

## Para testar
  
Para testar o emulador, é necessário baixar o projeto e compilá-lo, e também ter a SDL3 em seu sistema. Depois, é só mudar o diretório no método main para o diretório de uma ROM válida em sua máquina.

## Observação
  
Esta versão apresenta um bug no qual parte da UI renderizada fica fora da tela. 

 ## Link do artigo  

 https://austinmorlan.com/posts/chip8_emulator/  


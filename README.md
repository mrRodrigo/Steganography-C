# Img-C

## O programa pode ser dividido em duas partes:

* Codificador (classe steganography): lê uma imagem, encripta uma mensagem nele, grava um novo arquivo com o resultado.</br>
* Decodificador (classe undoGraphy): lê a imagem com as informações ocultas, decifra e exibe a mensagem na tela.

### Encriptação 
Para a encriptação é utilizado a Cifra de César,uma das mais simples e conhecidas técnicas de criptografia. É um tipo de cifra de substituição na qual cada letra do texto é substituída por outra, que se apresenta no alfabeto acima dela um número fixo de vezes. Por exemplo, com uma troca de duas posições, A seria substituído por C, B se tornaria D, e assim por diante. O nome do método é em homenagem a Júlio César, que o usou para se comunicar com os seus generais.


### Esteganografia 
Há diversas técnicas para realizar o processo de esteganografia em imagens, com graus diferentes de complexidade. Uma técnica simples é a alteração dos bits menos significativos de cada pixel. Essa técnica consiste em substituir um ou mais bits menos significativos de cada componente de cor de um pixel por uma parte da mensagem. Como temos 8 bits para R, G e B, isso em geral altera muito pouco a cor de cada pixel. 

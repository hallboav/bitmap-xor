# bmp-xor

Cifrando e decifrando imagens bitmaps usando a técnica one-time pad.

### Descrição

Os *bits dos pixels* de uma imagem bitmap de 1 bit de profundidade de cor foram cifrados utilizando *bitwise xor*.

O resultado está localizado em ``resources/encrypted.bmp`` e a chave também está localizada nesse diretório.

A chave foi gerada aleatoriamente, e somente usando-a é **possível** decifrar os sets de bits dos pixels (para ver a imagem original).

O software apresentado é capaz de ler uma linha inteira da imagem bitmap e aplicar a parte correspondente da chave para então gravar o resultado em um outro arquivo — a imagem decifrada.

As informações dos cabeçalhos sempre serão mantidas.

O software foi escrito apenas para fins de entretenimento e não há nenhuma verificação de entrada do usuário.

### Modo de usar

No terminal:
```shell
gcc bmp-xor.c -o bmp-xor
./bmp-xor resources/encrypted.bmp resources/otp.hex decrypted.bmp

```


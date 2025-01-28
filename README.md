# Controle de Matriz de LEDs 5x5 com Raspberry Pi Pico W

Este repositório contém o projeto de controle de uma matriz de LEDs RGB 5x5 utilizando um teclado matricial 4x4 e um Raspberry Pi Pico W. O objetivo é gerar animações personalizadas e controlar os LEDs em diferentes modos de operação, conforme comandos do teclado.

## Funcionalidades

- **Animações Personalizadas:** As teclas `0-9` acionam diferentes animações.
- **Modos de Controle:**
  - `A`: Desliga todos os LEDs.
  - `B`: Liga todos os LEDs na cor azul com 100% de intensidade.
  - `C`: Liga todos os LEDs na cor vermelha com 80% de intensidade.
  - `D`: Liga todos os LEDs na cor verde com 50% de intensidade.
  - `#`: Liga todos os LEDs na cor branca com 20% de intensidade.
  - `*`: Reinicia o sistema para modo de gravação.
  
- **Sinalização Opcional:** Integração de som com um buzzer para algumas animações.

## Estrutura do Projeto

### Principais Componentes
- **Teclado Matricial 4x4**: Captura os comandos do usuário.
- **Matriz de LEDs RGB WS2812**: Exibe as animações.
- **Microcontrolador Raspberry Pi Pico W**: Processa os comandos e controla os LEDs.
- **Buzzer (Opcional):** Gera sons para sinalização.

### Configuração do Teclado
- **Teclas 0-9:** Disparam animações diferentes.
- **Teclas Especiais:** A, B, C, D, # e * controlam estados específicos da matriz de LEDs.

### Demonstração de Execução
Confira o funcionamento do sistema assistindo ao vídeo demonstrativo: *(adicionar link dos vídeos aqui)*.

## Como Usar

### Requisitos
- Ambiente de desenvolvimento **VS Code**.
- **Simulador Wokwi** para simulação do hardware.
- Kit de desenvolvimento **Pico SDK**.

### Passos para Execução
1. Clone este repositório:
   ```bash
   git clone <URL-do-repositório>
   ```
2. Instale as dependências necessárias para o Pico SDK.
3. Importe o projeto no **VS Code** e configure o simulador Wokwi.
4. Compile o código e inicie a simulação.

### Observação
A prática pode ser realizada apenas com o simulador Wokwi, sem necessidade de hardware real.

## Estrutura do Código

O programa principal está estruturado em:

### Funções Principais
- **`lerTeclado`**: Captura comandos do teclado matricial.
- **`apagarLeds`**: Desliga todos os LEDs.
- **`ligarLedsCor`**: Liga todos os LEDs com uma cor e intensidade especificadas.
- **`executarAnimacao`**: Executa as animações configuradas para cada tecla.
- **Funções auxiliares para controle de LEDs individuais**.

### Inicialização
- Configuração inicial do teclado matricial, matriz de LEDs e outros periféricos.

### Execução
- Loop principal que monitora as entradas do teclado e executa os comandos.

## Estrutura de Branches

Cada desenvolvedor deve trabalhar em uma branch específica, garantindo commits regulares com mensagens descritivas. O líder do projeto será responsável por revisar e aprovar pull requests.

## Contribuição

Contribuições são bem-vindas! Siga os passos abaixo para colaborar:
1. Faça um fork do repositório.
2. Crie uma branch para sua feature/correção:
   ```bash
   git checkout -b minha-feature
   ```
3. Faça o commit de suas alterações:
   ```bash
   git commit -m "Descrição da alteração"
   ```
4. Envie as alterações para sua branch remota:
   ```bash
   git push origin minha-feature
   ```
5. Abra um pull request no GitHub.

## Links Relacionados
- Vídeo de simulação no Wokwi: *(adicionar link aqui)*
- Vídeo de demonstração com hardware: *(adicionar link aqui)*

## Licença

Este projeto está sob a licença MIT. Consulte o arquivo `LICENSE` para mais detalhes.

---

**Equipe de Desenvolvimento:**
- Desenvolvedores:
    - Alícia
    - André Lima
    - Cláudio
    - David
    - Edcarllos (líder)
    - James
    - Tiago


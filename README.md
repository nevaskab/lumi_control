<h1 align = "center">Inserção de caracteres UART enviados para display da placa BitDogLab</h1>

<p align = "center">O projeto apresentado utiliza a placa BitDogLab e seus componentes juntamente com a linguagem C para utilizar o display, que mostra informação sobre o estado dos LEDs verde e azul 
  além de mostrar o último caractere inserido através do teclado do computador.</p>

---
<h3>🎯 Objetivos</h3>
<p>O programa desenvolvido em Linguagem C para placa Pi Pico W tem como principais objetivos:</p>

- ☑️ Inserir caracteres de A-Z, a-z e 0-9
- ☑️ Mostrar os caracteres no display e no serial monitor
- ☑️ Fazer com que o Botão A altere o estado do LED verde (on/off)
- ☑️ Fazer com que o Botão B altere o estado do LED azul (on/off)
- ☑️ Mostrar o estado dos LEDs no display e no serial monitor
- ☑️ Desenvolver funções de Debouncing e Interrupção para cada botão
  
---
<h3>🛠️ Ferramentas</h3>

  - Placa BitDogLab
  - Cabo tipo micro-usb para usb-a
  - Ferramentas CMake e Pico SDK instaladas
---

<h3>🚀 Utilizando o programa</h3>

Siga as etapas a seguir:
  - Pressione o botão "Bootsel" da placa
  - Conecte a placa no computador e solte o botão "Bootsel"
  - Clone o repositório usando o comando abaixo
    
    ```gitconfig
    git clone https://github.com/nevaskab/lumi_control.git
    ```
  - Compile e Rode o código <br>

    ![Captura de tela 2025-01-19 150112](https://github.com/user-attachments/assets/62fbcc03-5653-4826-be75-316d8e6581bb)

  - Pronto! Sua placa, devidamente conectada, será capaz de rodar o código :D <br>

  - Pressione o botão A para alternar o estado do LED Verde entre Ligado e Desligado 🟢
    
    <img width = 300px src = "https://github.com/user-attachments/assets/42cfd814-8ac6-4d98-9f52-bae853e324f4"/>
    <img src = "https://github.com/user-attachments/assets/d1011611-7aea-4e04-ad87-46a29c023ec3"/>

  - Pressione o botão B para alterar o estado do LED Azul entre Ligado e Desligado 🔵
    
    <img width = 300px src = "https://github.com/user-attachments/assets/409ec0be-b63d-4e61-adf3-5bb778f491da"/>

      - ATENÇÃO: cada botão só altera o estado de um único LED, ao apertar o botão A e em seguida apertar o botão B, o LED Verde não apagará pois o botão A não foi pressionado novamente, ambos os leds estarão ligados.
      
        <img width = 200px src = "https://github.com/user-attachments/assets/334fa39d-81de-4e9e-903c-5c09210299db"/>

    - Digite caracteres de A-Z maísculos e minúsculos
    - Digite caracteres de 0-9 (que serão representados na matriz 5x5)

---

<h2>Para mais detalhe sobre o funcionamento...</h2>
Visite: https://drive.google.com/file/d/1_daAQxvdPMc-o0mxomK6RjXxTsUcyUqh/view?usp=drive_link

### Autor
---
<a><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/133506658?s=400&u=add96d4ebb6071b0473386091845a1509b3de27b&v=4" width="100px;" alt=""/>
<br />
<sub><b>Andressa Martins</b></sub></a>

Feito por Andressa Martins. Entre em contato <3.

<a href="mailto:andressa.devsystem@gmail.com"><img alt="Static Badge" src="https://img.shields.io/badge/andressa.devsystem%40gmail.com-black?style=flat&logo=gmail&logoColor=%23EA4335&logoSize=auto&color=EDF2F4"></a>

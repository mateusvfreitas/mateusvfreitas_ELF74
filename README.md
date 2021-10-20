# mateusvfreitas_ELF74

Lab1 => A mensagem "Hello World" aparece no Terminal I/O.
Lab2 => A principal razão por trás do uso da palavra-chave volatile é evitar que o compilador aplique quaisquer otimizações em objetos que podem mudar de maneiras que não podem ser determinadas pelo compilador. No caso do blinky original, essa keyword em uma variável dentro da main evita otimizações no ui32Loop, que é usado para fazer os delays do LED.